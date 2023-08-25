/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:59:30 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/25 19:36:34 by pgorner          ###   ########.fr       */
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


int Server::sig_handlerserv(void){
	signal(SIGINT, Server::change_running);
	signal(SIGQUIT, Server::change_running);
	return log("sig_handler started"), 0;
}



void Server::checkPwd(const std::vector<std::string>& tokens, int i, int cc)
{
    if ((tokens.empty() || tokens[0].compare(0, 5, "PASS") != 0))
        logsend(_poll_fds[i].fd, SERVERNAME" : WRONG PASSWORD\r\n");
    else if (tokens[1] == _pwd) 
	{
        _clients[cc].passwordAccepted = TRUE;
		_clients[cc].send_to_user += SERVERNAME" Your PASSWORD is correct\r\n";
	}
	else
        logsend(_poll_fds[i].fd, irc::ERR_PASSWDMISMATCH());
}

void Server::cap(int fd, const std::vector<std::string>& tokens, bool& cap) {
	if (contains(tokens, "CAP") == true && contains(tokens, "LS") == true)
		logsend(fd, "CAP * LS :\n");
	else if (contains(tokens, "CAP") == true && contains(tokens, "REQ") == true){
		std::string req = "CAP * ACK :";
		if (contains(tokens, "multi-prefix"))
			req += "multi-prefix";
		if (contains(tokens, "multiple-channel-joins"))
			req += "multiple-channel-joins";
		logsend(fd, req.c_str());
	}
	else if (contains(tokens, "CAP") == true && contains(tokens, "END") == true)
		cap = true;
}

void Server::run() {
    int connection = 0;
	bool hCC = false; //ahs connected clients
    int i = 0;
	std::string str;

    while (true) {
        int num_events = poll(_poll_fds.data(), static_cast<nfds_t>(_poll_fds.size()), POLLTIME);
		if (connection == 0 && i == 0 && hCC == false)
			write_nice(YELLOW, "	waiting to connect ", false);
		if (i++ < 3 && connection < 3 && hCC == false)
			write_nice(YELLOW, ".", false);
		else if (hCC == false){
		i = 0;
		connection++;
    	str = std::to_string(connection);
		if (connection == 4 && hCC == false){
			write(1, "\n", 1);
			clear(0);
			connection = 0;
		}
		else if (hCC == false)
			write_nice(YELLOW, str, false);
		}
        if (num_events == -1) {
            if (errno == EINTR) {
                write_nice(RED, "poll interrupted", true);
                continue;
            } else {
				err("poll has failed");
                exit(1);
            }
        }
		// else if (num_events )
		// {
		// 	write(1, "\n", 1);
		// 	write_nice(WHITE, LINE, true);
		// }
        for (size_t i = 0; i < _poll_fds.size(); i++) {

            if (_poll_fds[i].revents & POLLIN)
			{
				if (_poll_fds[i].fd == _socket)
				{
    					// Handle incoming connection on the server socket.
    					struct sockaddr_in client_addr;
    					socklen_t client_addr_len = sizeof(client_addr);
    					int client_socket = accept(_socket, (struct sockaddr*)&client_addr, &client_addr_len);
	
						if (client_socket < 0)
						{
    					    // Handle the error, and optionally continue or exit.
   						}
						else
						{
							write_nice(GREEN, "	NEW CLIENT SUCESSFULLY ADDED", true);
    					    // New client connected successfully, add it to the list of monitored file descriptors.	
    					    pollfd new_client_poll_fd;
    					    new_client_poll_fd.fd = client_socket;
    					    new_client_poll_fd.events = POLLIN; // Monitoring for read events.
							logsend(new_client_poll_fd.fd, SERVERNAME" Enter the password, user and nickname\r\n"SERVERNAME" PASS <password>\r\n"SERVERNAME" USER <username>\r\n"SERVERNAME" NICK <nickname>\r\n");
    					    _poll_fds.push_back(new_client_poll_fd);
							_clients.push_back(ClientData(client_socket, false, false, false, "", "" ,"", ""));
							hCC = true;
    					    // Optionally, you can store client information or perform other tasks here.
    					}
            	}
				else
				{
    				// Handle events on other file descriptors (clients).
					size_t cc = 0;
					
            		for (; cc < _clients.size(); cc++)
					{
            		    if (_clients[cc].fd == _poll_fds[i].fd)
            		        break;
            		}
    				char buffer[1024];
    				int bytes_received = recv(_poll_fds[i].fd, buffer, sizeof(buffer), 0);
					
    				if (bytes_received <= 0)
					{
    				    // Client disconnected or an error occurred, remove it from the monitored file descriptors.
    				    close(_poll_fds[i].fd);
    				    _poll_fds.erase(_poll_fds.begin() + i);
						write_nice(RED, "Client Error occured: ", false);
						write_nice(RED, _clients[cc].nick, false);
						_clients.erase(_clients.begin() + cc);
    				}
					else 
					{
    				    // Process the received data from the client.
    				    std::string received_data(buffer, bytes_received);
						std::vector<std::string> tokens;
						std::stringstream iss(received_data);
						std::string token;
						std::string line;
						
						write_nice(WHITE, received_data, true);
						LOG << "CLIENT SENT: " + received_data;
    					while (std::getline(iss, line))
						{
							std::string token;
        					std::istringstream lineStream(line);

        					while (lineStream >> token)
        					    tokens.push_back(token);
							for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
							{
								if (!it->empty() && (*it)[0] == ':')
									it->erase(0, 1);
							}
							if (tokens.size() != 0)
							{
								if (_clients[cc].cap == false)
									cap(_poll_fds[i].fd, tokens, _clients[cc].cap);
								if(_clients[cc].passwordAccepted == true)
									commands(i, cc, tokens);
								else if (_clients[cc].passwordAccepted == false && tokens[0] == "PASS")
									checkPwd(tokens, i, cc);
							}
							tokens.clear();
						}
						if (!DEBUG)
						{
							for(std::vector<std::string>::const_iterator it = tokens.begin(); it != tokens.end(); ++it)
								write_nice(BLUE, it->c_str(), true );
							std::cout << RED << "STATUS: " <<
								"\nNICK: " << _clients[cc].nick <<
								"\nUSER: " << _clients[cc].user <<
								"\nREALNAME: " << _clients[cc].realname <<
								"\nPWDACCEPT(0=n/y=1): " << _clients[cc].passwordAccepted <<
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
					for(size_t k = 0; k < _clients.size(); k++)
					{
						if (_clients[k].send_to_user.size() != 0)
						{
							logsend(_poll_fds[i].fd, _clients[cc].send_to_user);
							_clients[k].send_to_user = "";
						}
					}
					write(1, "\n", 1);
					write_nice(WHITE, LINE, true);
				}
            }
		if (_poll_fds.size() == 1)
            hCC = false;
        }
    }
}

void Server::commands(int i, int cc, std::vector<std::string> tokens)
{
	if (tokens[0] == "NICK")
		nick(tokens, cc, i);
	else if (tokens[0] == "USER")
		user(tokens, cc, i);
	else if (_clients[cc].auth == false)
		_clients[cc].send_to_user += irc::ERR_NOTREGISTERED();
	if (_clients[cc].user.size() != 0 && _clients[cc].nick.size() != 0 && _clients[cc].auth == false)
	{
		_clients[cc].send_to_user += irc::RPL_WELCOME(_clients[cc].nick, _clients[cc].user, SERVERNAME);
		_clients[cc].auth = true;
	}
	if (_clients[cc].auth == true)
	{
		if (tokens[0] == "OPER")
		{
			changeoper(tokens, cc);
		}
		else if (tokens[0] == "MODE")
		{
			if (tokens[1].empty() == true)
			{
				_clients[cc].send_to_user += irc::RPL_UMODEIS(_clients[cc].mode.c_str());
			}
			else if (tokens[1].empty() && tokens[2].empty())
				_clients[cc].send_to_user += irc::ERR_NEEDMOREPARAMS("MODE");
			else
				_clients[cc].send_to_user += mode(cc, tokens);
		}
		else if (tokens[0] == "JOIN")
			joinchannel(tokens, cc);
		else if (tokens[0] == "PRIVMSG")
		{
			if (tokens[1].empty())
				_clients[cc].send_to_user += irc::ERR_NEEDMOREPARAMS("PRIVMSG");
			else
				sendmsg(tokens, cc);
		}
		else if (tokens[0] == "PING")
			ping(tokens, cc);
		else if (tokens[0] == "QUIT")
			quit(tokens, i, cc);
		else if (tokens[0] == "NAMES")
			names(tokens, cc);
	}
	// else if (tokens[0] == "SERVICE") {}
	// else if (tokens[0] == "SQUIT") {}
	// else if (tokens[0] == "PART") {}
	// else if (tokens[0] == "TOPIC") {}
	// else if (tokens[0] == "LIST") {}
	// else if (tokens[0] == "INVITE") {}
	// else if (tokens[0] == "KICK") {}
	// else if (tokens[0] == "NOTICE") {}
	// else if (tokens[0] == "MOTD") {}
	// else if (tokens[0] == "LUSERS") {}
	// else if (tokens[0] == "VERSION") {}
	// else if (tokens[0] == "STATS") {}
	// else if (tokens[0] == "LINKS") {}
	// else if (tokens[0] == "TIME") {}
	// else if (tokens[0] == "CONNECT") {}
	// else if (tokens[0] == "TRACE") {}
	// else if (tokens[0] == "ADMIN") {}
	// else if (tokens[0] == "INFO") {}
	// else if (tokens[0] == "SERVLIST") {}
	// else if (tokens[0] == "SQUERY") {}
	// else if (tokens[0] == "WHO") {}
	// else if (tokens[0] == "WHOIS") {}
	// else if (tokens[0] == "WHOWAS") {}
	// else if (tokens[0] == "KILL") {}
	// else if (tokens[0] == "PONG") {}
	// else if (tokens[0] == "ERROR") {}
	// else if (tokens[0] == "AWAY") {}
	// else if (tokens[0] == "REHASH") {}
	// else if (tokens[0] == "DIE") {}
	// else if (tokens[0] == "RESTART") {}
	// else if (tokens[0] == "SUMMON") {}
	// else if (tokens[0] == "USERS") {}
	// else if (tokens[0] == "WALLOPS") {}
	// else if (tokens[0] == "USERHOST") {}
	// else if (tokens[0] == "ISON") {}
	// else if (tokens[0] == "ISON") {}
}