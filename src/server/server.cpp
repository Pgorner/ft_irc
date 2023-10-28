/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:59:30 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/28 11:56:24 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/irc.hpp"


Server::Server(const int &port, const std::string &pwd)
    : _port(port),
      _pwd(pwd),
	  _socket(-1),
	  running(false),
      _start_time(std::time(NULL)),
      _last_ping(std::time(NULL))
{
    sig_handlerserv();
}

Server::~Server()
{
    running = false;
    if (_socket >= 0) {
        close(_socket);
        _socket = -1;
	}
}

Server& Server::operator=(const Server& obj) {
  (void)obj;
  return *this;
}

// --------------------------------------------------------------

void Server::addNewClient(bool& hCC)
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_socket = accept(_socket, (struct sockaddr*)&client_addr, &client_addr_len);
	if (client_socket < 0)
        std::cout << RED << "Client socket error\n";
	else
	{
		write_nice(GREEN, "\n	NEW CLIENT SUCESSFULLY ADDED", true);
        // New client connected successfully, add it to the list of monitored file descriptors.	
        pollfd new_client_poll_fd;
        new_client_poll_fd.fd = client_socket;
        new_client_poll_fd.events = POLLIN; // Monitoring for read events.
		logsend(new_client_poll_fd.fd, SERVERNAME " Enter the password, user and nickname\r\n" SERVERNAME " PASS <password>\r\n" SERVERNAME " USER <username>\r\n" SERVERNAME " NICK <nickname>\r\n", -1);
        _poll_fds.push_back(new_client_poll_fd);
		_clients.push_back(ClientData(client_socket, false, false, false, "", "" ,"", "", "", true));
		hCC = true;
    }
}

int Server::handleClient(int i)
{
	int bytes_received = 10000;
	size_t cc = 0;
					
    for (; cc < _clients.size(); cc++)
	{
        if (_clients[cc].fd == _poll_fds[i].fd)
            break;
    }
	
	std::vector<char> buffer(1024);
	bytes_received = recv(_poll_fds[i].fd, buffer.data(), buffer.size(), 0);

    if (bytes_received <= 0)
	{
		write_nice(RED, "Client Error occured: ", false);
		write_nice(RED, _clients[cc].nick, false);
		quit(i, cc, "An error occured");
    }
	else 
	{
		std::string received_data(buffer.begin(), buffer.begin() + bytes_received);

		_clients[cc].msg += received_data;
		if (_clients[cc].msg[_clients[cc].msg.length() - 1] != '\n') 
			return true;
		std::vector<std::string> tokens;
		std::stringstream iss(_clients[cc].msg);
		std::string token;
		std::string line;
		
		write_nice(WHITE, _clients[cc].msg, true);
		LOG << "CLIENT SENT: " + _clients[cc].msg;
		_clients[cc].msg = "";
    	while (std::getline(iss, line))
		{
    		std::istringstream lineStream(line);
    		while (lineStream >> token)
    		    tokens.push_back(token);
			for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
				if (!it->empty() && (*it)[0] == ':')
					it->erase(0, 1);
			if (tokens.size() != 0)
				commands(i, cc, tokens);
			tokens.clear();
		}
		debugprint(tokens, cc);
	}
	sendmsgstoclients();
	return 0;
}

void Server::commands(int i, int cc, std::vector<std::string> tokens)
{
	//Cap handshake
	if (tokens[0] == "PONG")
		pong(cc);
	if (_clients[cc].cap == false && tokens[0] == "CAP")
	{
		cap(_poll_fds[i].fd, tokens, _clients[cc].cap, cc);
		return;
	}
	//Password authentication
	if (_clients[cc].passwordAccepted == false && tokens[0] == "PASS")
		checkPwd(tokens, i, cc);
	else if (_clients[cc].passwordAccepted == false && tokens[0] != "PASS")
	{
		_clients[cc].send_to_user += irc::cEM(irc::ERR_NOTREGISTERED());
		return;
	}
	//Nick and User authentication
	if (tokens[0] == "NICK")
		nick(tokens, cc);
	else if (tokens[0] == "USER")
		user(tokens, cc, i);
	else if (_clients[cc].auth == false)
		return;
	if (_clients[cc].user.size() != 0 && _clients[cc].nick.size() != 0 && _clients[cc].auth == false)
	{
		_clients[cc].send_to_user += irc::cEM(irc::RPL_WELCOME(_clients[cc].nick, _clients[cc].user, SERVERNAME));
		_clients[cc].auth = true;
	}
	// individual commands
	if (tokens[0] == "MODE")
		mode(cc, tokens);
	else if (tokens[0] == "OPER")
		changeoper(tokens, cc);
	else if (tokens[0] == "JOIN")
		joinchannel(tokens, cc);
	else if (tokens[0] == "PRIVMSG")
		sendmsg(tokens, cc);
	else if (tokens[0] == "PART")
		leavechannel(tokens, cc);
	else if (tokens[0] == "KICK")
		kick(tokens, cc);
	else if (tokens[0] == "PING")
		ping(tokens, cc);
	else if (tokens[0] == "QUIT")	
		quit(i, cc, "You have quit the server");
	else if (tokens[0] == "NAMES")
		names(tokens, cc);
}

void Server::sendmsgstoclients()
{
	for(size_t k = 0; k < _clients.size(); k++)
	{
		if (_clients[k].send_to_user.size() != 0)
		{
			logsend(_clients[k].fd, _clients[k].send_to_user, k);
			_clients[k].send_to_user = "";
		}
	}
	write(1, "\n", 1);
	write_nice(WHITE, LINE, true);
}

void Server::printconnect(int& connection, int& numcount, bool& hCC)
{
		if (connection == 0 && numcount == 0 && hCC == false)
			write_nice(YELLOW, "	waiting to connect ", false);
		if (numcount++ < 3 && connection < 3 && hCC == false)
			write_nice(YELLOW, ".", false);
		else if (hCC == false)
		{
			numcount = 0;
			connection++;
			if (connection == 4)
			{
				write(1, "\n", 1);
				clear(0);
				connection = 0;
			}
		}
}
void Server::debugprint(std::vector<std::string> tokens, std::vector<ClientData>::size_type cc)
{
	if (!DEBUG)
	{
		if (_clients.empty()) {
			std::cout << "No clients available to display." << std::endl;
			return;
		}

		if (cc >= _clients.size()) {
			std::cout << "Invalid client index." << std::endl;
			return;
		}

		for(std::vector<std::string>::const_iterator it = tokens.begin(); it != tokens.end(); ++it)
			write_nice(BLUE, it->c_str(), true );

		write_nice(RED, "--------ALL POLL FDS--------\n", false);
		if (_poll_fds.empty())
			std::cout << "No FDS\n" << std::endl;
		else
			for (size_t o = 0; o < _poll_fds.size(); o++)
			{
				std::cout << o << ":" << _poll_fds[o].fd;
				for (size_t l = 0; l < _clients.size(); l++)
				{
					if (_clients[l].fd == _poll_fds[o].fd)
						std::cout << "  :" << _clients[l].nick;
					if (_clients[l].ping == false)
						std::cout << " PING FALSE" << std::endl;
					else	
						std::cout << " PING TRUE" << std::endl;
				}
			}
		write_nice(RED, "--------ALL CLIENTS--------\n", false);
		if (_clients.empty())
			std::cout << "No Clients\n" << std::endl;
		else
			for (size_t i = 0; i < _clients.size(); i++)
			{
				std::cout << RED << i << ". NICK:";
				if (_clients[cc].nick.empty())
					std::cout << RED << "/";
				else
					std::cout << RED << _clients[i].nick;
				std::cout << RED << " USER:" ;
				std::cout << RED << i << ". PING:";
				if (_clients[cc].nick.empty())
					std::cout << RED << "/";
				else
					std::cout << RED << _clients[i].nick;
				std::cout << RED << " USER:" ;
				if (_clients[cc].user.empty())
					std::cout << RED << "/";
				else
					std::cout << RED << _clients[i].user;
				std::cout << RED << " REALNAME:";
				if (_clients[cc].realname.empty())
					std::cout << RED << "/";
				else
					std::cout << RED << _clients[i].realname;

				for (size_t j = 0; j < _clients[i]._channels.size(); j++)
				{
					std::cout << RED << "\nChannel: " << j << " " <<  _clients[i]._channels[j];	
				}
				std::cout << "\n";
			}

		write_nice(RED, "--------THIS CLIENT--------", false);
		
		std::cout << RED << "\nNICK: ";
		if (_clients[cc].nick.empty())
			std::cout << RED << "No nick yet";
		else
			std::cout << RED << _clients[cc].nick;
		std::cout << RED << "\nUSER: " ;
		if (_clients[cc].user.empty())
			std::cout << RED << "No username yet";
		else
			std::cout << RED << _clients[cc].user;
		std::cout << RED << "\nREALNAME: ";
		if (_clients[cc].realname.empty())
			std::cout << RED << "No realname yet";
		else
			 std::cout << RED << _clients[cc].realname;
		std::cout << RED << 
		"\nPWDACCEPT(0=n/y=1): " << _clients[cc].passwordAccepted <<
		"\nAUTH(0=n/y=1): " << _clients[cc].auth <<
		"\nMODE: " << _clients[cc].mode <<
		"\nUSER IN CHANNELS: \n";

		if (_clients[cc]._channels.empty())
			std::cout << "No channels available for this client." << std::endl;
		else
			for (size_t i = 0; i < _clients[cc]._channels.size(); i++)
			{
				write_nice(RED, "	", false);
				write_nice(RED, _clients[cc]._channels[i].c_str(), true);
			}

		write_nice(RED, "ALL CHANNELS:", true);

		if (_channels.empty())
			std::cout << RED << "No channels available." << std::endl;
		else
			for (size_t i = 0; i < _channels.size(); i++)
			{
				write_nice(RED, "name:	", false);
				write_nice(RED, _channels[i].name.c_str(), true);
				write_nice(RED, "mode:	", false);
				write_nice(RED, _channels[i].mode.c_str(), true);
				write_nice(RED, "members:	", false);

				if (_channels[i].members.empty()) {
					std::cout << "No members in this channel." << std::endl;
				} else {
					for (size_t j = 0; j < _channels[i].members.size(); j++){
						write_nice(RED, _clients[_channels[i].members[j]].nick, false);
						write_nice(RED, "/", false);
					}
					write_nice(RED, "", true);
				}
			}

		std::cout << RESET << std::endl;
	}
}


void Server::run() 
{
	int ping = 0;
    int numcount = 0;
	bool handleClientConnect = false;
    int connection = 0;
	
    while (true)
	{
        int num_events = poll(_poll_fds.data(), static_cast<nfds_t>(_poll_fds.size()), POLLTIME);
		
		printconnect(connection, numcount, handleClientConnect);

        if (num_events == -1)
		{
            if (errno == EINTR)
                write_nice(RED, "poll interrupted", true);
			else
			{
				err("poll has failed");
                exit(1);
            }
        }
        for (size_t i = 0; i < _poll_fds.size(); i++)
		{
            if (_poll_fds[i].revents & POLLIN)
			{
				if (_poll_fds[i].fd == _socket)
					addNewClient(handleClientConnect);
				else
					handleClient(i);
            }
			if (_poll_fds.size() == 1)
            	handleClientConnect = false;
        }
		ping++;
		if (ping % 100 == 0)
		{
			std::cout << CYAN << "\nPING TRIGGERED\n" << RESET;
			for (size_t k = 0; k < _clients.size(); k++) {
				logsend(_clients[k].fd, "PING\r\n", k);
				if (_clients[k].ping == false) {
					for (size_t j = 0; j < _poll_fds.size(); j++)
					{
						if (_poll_fds[j].fd == _clients[k].fd)
						{
							std::cout << CYAN << _clients[k].nick << "disconnected\n" << RESET;
							quit(j, k, "You have been disconnected due to inactivity");
							break;
						}
					}
				}
				else
					_clients[k].ping = false;
			}
		}
    }
}

