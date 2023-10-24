/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:59:30 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/24 19:29:47 by pgorner          ###   ########.fr       */
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
	{
        std::cout << RED << "Client socket error\n";
   	}
	else
	{
		write_nice(GREEN, "\n	NEW CLIENT SUCESSFULLY ADDED", true);
        // New client connected successfully, add it to the list of monitored file descriptors.	
        pollfd new_client_poll_fd;
        new_client_poll_fd.fd = client_socket;
        new_client_poll_fd.events = POLLIN; // Monitoring for read events.
		logsend(new_client_poll_fd.fd, SERVERNAME" Enter the password, user and nickname\r\n"SERVERNAME" PASS <password>\r\n"SERVERNAME" USER <username>\r\n"SERVERNAME" NICK <nickname>\r\n", -1);
        _poll_fds.push_back(new_client_poll_fd);
		_clients.push_back(ClientData(client_socket, false, false, false, "", "" ,"", "", ""));
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
	
	char* buffer = nullptr; // Initialize buffer pointer to nullptr
    buffer = new char[1024]; // Allocate memory for buffer
    bytes_received = recv(_poll_fds[i].fd, buffer, 1024, 0); // Receive data into buffer
    if (bytes_received <= 0)
	{
		write_nice(RED, "Client Error occured: ", false);
		write_nice(RED, _clients[cc].nick, false);
        close(_poll_fds[i].fd);
        _poll_fds.erase(_poll_fds.begin() + i);
		_clients.erase(_clients.begin() + cc);
    }
	else 
	{
        std::string received_data(buffer, bytes_received);
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
	delete[] buffer;
	return 0;
}

void Server::commands(int i, int cc, std::vector<std::string> tokens)
{
	//Cap handshake
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
		_clients[cc].send_to_user += irc::ERR_NOTREGISTERED();
		return;
	}
	//Nick and User authentication
	if (tokens[0] == "NICK")
		nick(tokens, cc, i);
	else if (tokens[0] == "USER")
		user(tokens, cc, i);
	else if (_clients[cc].auth == false)
		return;
	if (_clients[cc].user.size() != 0 && _clients[cc].nick.size() != 0 && _clients[cc].auth == false)
	{
		_clients[cc].send_to_user += irc::RPL_WELCOME(_clients[cc].nick, _clients[cc].user, SERVERNAME);
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
		quit(tokens, i, cc);
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

void Server::printconnect(int& connection, int& numcount, bool& hCC, std::string& str)
{
		if (connection == 0 && numcount == 0 && hCC == false)
			write_nice(YELLOW, "	waiting to connect ", false);
		if (numcount++ < 3 && connection < 3 && hCC == false)
			write_nice(YELLOW, ".", false);
		else if (hCC == false)
		{
			numcount = 0;
			connection++;
    		str = std::to_string(connection);
			if (connection == 4)
			{
				write(1, "\n", 1);
				clear(0);
				connection = 0;
			}
			else
				write_nice(YELLOW, str, false);
		}
}
void Server::debugprint(std::vector<std::string> tokens, int cc)
{
	if (!DEBUG)
	{
		for(std::vector<std::string>::const_iterator it = tokens.begin(); it != tokens.end(); ++it)
			write_nice(BLUE, it->c_str(), true );
		std::cout << RED << "--------STATUS--------" <<
			"\nNICK: " << _clients[cc].nick <<
			"\nUSER: " << _clients[cc].user <<
			"\nREALNAME: " << _clients[cc].realname <<
			"\nPWDACCEPT(0=n/y=1): " << _clients[cc].passwordAccepted <<
			"\nAUTH(0=n/y=1): " << _clients[cc].auth <<
			"\nMODE: " << _clients[cc].mode <<
			"\nUSER IN CHANNELS: \n";
			for (size_t i = 0; i < _clients[cc]._channels.size(); i++)
			{
				write_nice(RED, "	", false);
				write_nice(RED, _clients[cc]._channels[i].c_str(), true);
			}
			write_nice(RED, "ALL CHANNELS:", true);
			for (size_t i = 0; i < _channels.size(); i++)
			{
				write_nice(RED, "name:	", false);
				write_nice(RED, _channels[i].name.c_str(), true);
				write_nice(RED, "mode:	", false);
				write_nice(RED, _channels[i].mode.c_str(), true);
				write_nice(RED, "members:	", false);
				for (size_t j = 0; j < _channels[i].members.size(); j++){
					write_nice(RED, _clients[_channels[i].members[j]].nick, false);
					write_nice(RED, "/", false);
				}
				write_nice(RED, "", true);
			}
			std::cout << RESET << std::endl;
	}
}

void Server::run() 
{
    int numcount = 0;
	std::string str;
	bool handleClientConnect = false;
    int connection = 0;
	
    while (true) {
        int num_events = poll(_poll_fds.data(), static_cast<nfds_t>(_poll_fds.size()), POLLTIME);
		
		printconnect(connection, numcount, handleClientConnect, str);

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
    }
}

