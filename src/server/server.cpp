/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:59:30 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/08 18:56:34 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/server.hpp"

Server::Server(const int &port, const std::string &pwd)
    : _port(port),
      _pwd(pwd),
	  _socket(-1),
	  running(false),
      _start_time(std::time(NULL)),
      _last_ping(std::time(NULL))
{
    sig_handler();
    start_sock();
	start_poll();
	write_nice(BLUE, "	SERVER CREATION SUCCESSFUL", true);
	write_nice(WHITE, LINE, false);
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



void Server::checkPwd(const std::vector<std::string>& tokens, int i, int cc) {
    if ((tokens.empty() || tokens[0].compare(0, 5, "PASS") != 0)) {
        const char* errorMessage = "Invalid password command.\r\n"; // Customize the error message
        logsend(_poll_fds[i].fd, errorMessage, true);
        return;
    }

    else if (tokens.size() < 2) {
        const char* errorMessage = "Password not provided.\r\n"; // Customize the error message
        logsend(_poll_fds[i].fd, errorMessage, true);
        return;
    }

    else if (tokens[1] == _pwd) 
	{
        std::cout << "Password accepted" << std::endl;
        _clients[i - 1].passwordAccepted = TRUE;
        const char* welcomeMessage = "Welcome to the IRC server!\r\n"; // Customize the welcome message
        logsend(_poll_fds[i].fd, welcomeMessage, true);
		if(_clients[cc].auth == false)
        	logsend(_poll_fds[i].fd, "Please authenticate with NICK and USER", true);
    } 
	else 
	{
        const char* errorMessage = "Invalid password.\r\n"; // Customize the error message
        logsend(_poll_fds[i].fd, errorMessage, true);
    }
}

void Server::cap(int fd, const std::vector<std::string>& tokens, bool cap) {
	if (contains(tokens, "CAP") == true && contains(tokens, "LS") == true)
		logsend(fd, "CAP * LS :\n", false);
	else if (contains(tokens, "CAP") == true && contains(tokens, "REQ") == true){
		std::string req = "CAP * ACK :";
		if (contains(tokens, "multi-prefix"))
			req += "multi-prefix";
		if (contains(tokens, "multiple-channel-joins"))
			req += "multiple-channel-joins";
		logsend(fd, req.c_str(), false);
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
		else if (num_events){
			write(1, "\n", 1);
			write_nice(WHITE, LINE, true);
		}
        for (size_t i = 0; i < _poll_fds.size(); i++) {

            if (_poll_fds[i].revents & POLLIN) {
			if (_poll_fds[i].fd == _socket) {
    				// Handle incoming connection on the server socket.
    				struct sockaddr_in client_addr;
    				socklen_t client_addr_len = sizeof(client_addr);
    				int client_socket = accept(_socket, (struct sockaddr*)&client_addr, &client_addr_len);
    				if (client_socket < 0) {
    				    // Handle the error, and optionally continue or exit.
    				} else {
						write_nice(GREEN, "	NEW CLIENT SUCESSFULLY ADDED", true);
    				    // New client connected successfully, add it to the list of monitored file descriptors.	
    				    pollfd new_client_poll_fd;
    				    new_client_poll_fd.fd = client_socket;
    				    new_client_poll_fd.events = POLLIN; // Monitoring for read events.
    				    _poll_fds.push_back(new_client_poll_fd);
						_clients.push_back(ClientData(client_socket, INDETERMINATE, false, false, ""));
						hCC = true;
    				    // Optionally, you can store client information or perform other tasks here.
    			}
                } else {
    				// Handle events on other file descriptors (clients).
					size_t cc = 0;
            		for (; cc < _clients.size(); cc++) {
            		    if (_clients[cc].fd == _poll_fds[i].fd) {
            		        break;
            		    }
            		}
    				char buffer[1024];
    				int bytes_received = recv(_poll_fds[i].fd, buffer, sizeof(buffer), 0);
					// std::cout << buffer << std::endl; 
    				if (bytes_received <= 0) {
    				    // Client disconnected or an error occurred, remove it from the monitored file descriptors.
    				    close(_poll_fds[i].fd);
    				    _poll_fds.erase(_poll_fds.begin() + i);
						write_nice(RED, "Client: ", false);
						write_nice(RED, _clients[cc].realname, false);
						write_nice(RED, " disconnected", true);
						_clients.erase(_clients.begin() + cc);
    				} else 
					{
    				    // Process the received data from the client.
    				    std::string received_data(buffer, bytes_received);
						std::vector<std::string> tokens;
						std::stringstream iss(received_data);
						std::string token;
						std::string line;

    					while (std::getline(iss, line)) {
        					
							std::string token;
        					std::istringstream lineStream(line);

        					while (lineStream >> token)
        					    tokens.push_back(token);
							for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
								if (!it->empty() && (*it)[0] == ':') {
									it->erase(0, 1);
								}
							}
							
							if (_clients[cc].cap == false){cap(_poll_fds[i].fd, tokens, _clients[cc].cap);}
							if(_clients[cc].passwordAccepted == TRUE){commands(i, cc, tokens);}
							else if (_clients[cc].passwordAccepted == FALSE && tokens[0] == "PASS"){checkPwd(tokens, i, cc);}
							else if(_clients[cc].passwordAccepted == INDETERMINATE){
								_clients[cc].passwordAccepted = FALSE;
        						logsend(_poll_fds[i].fd, "Enter the password:\nSyntax: PASS <password>\n", true);
							}
							// if (_clients[cc].passwordAccepted && _clients[cc].auth)
							// {
							// 	// std::string str = "001" + " " + "Welcome to the Internet Relay Network\r\n" + _clients[cc].nick + "!" + "\r\n";
							// 	// logsend(_poll_fds[i].fd, str, true);
							// 	std::string resp;
							// 	const std::string SERNAME = "YourServerName";
							// 	resp = ":"+ SERNAME + " 001 "+_clients[cc].nick +" :Welcome to the irc network "+ _clients[cc].nick +"!\r\n";
							// 	send(_poll_fds[i].fd, resp.c_str(), resp.size(), 0);	
				
							// }
							if (!DEBUG){
								for(std::vector<std::string>::const_iterator it = tokens.begin(); it != tokens.end(); ++it)
									write_nice(BLUE, it->c_str(), true );
							}
    						tokens.clear();
						}
					}
				}
            }
		if (_poll_fds.size() == 1)
            hCC = false;
        }
    }
}

void Server::commands(int i, int cc, std::vector<std::string> tokens)
{
	if (_clients[cc].user.size() != 0 && _clients[cc].nick.size() != 0)
		_clients[cc].auth = true;			
	if (tokens[0] == "NICK")
	{
		nick(tokens, cc, i);
		if (_clients[cc].user.size() != 0 && _clients[cc].nick.size() != 0)
		{
			std::string resp;
			const std::string SERNAME = "YourServerName";
			resp = ":"+ SERNAME + " 001 "+ "Welcome to the Internet Relay Network\r\n"+ _clients[cc].nick +"!\r\n";
			send(_poll_fds[i].fd, resp.c_str(), resp.size(), 0);
		}
	} 
	else if (tokens[0] == "USER")
	{
		user(tokens, cc, i);
		if (_clients[cc].user.size() != 0 && _clients[cc].nick.size() != 0)
		{
			std::string resp;
			const std::string SERNAME = "YourServerName";
			resp = ":"+ SERNAME + " 001 "+ "Welcome to the Internet Relay Network\r\n"+ _clients[cc].nick +"!\r\n";
			send(_poll_fds[i].fd, resp.c_str(), resp.size(), 0);	
		}
	}
	else if (_clients[cc].auth == true)
	{
	if (tokens[0] == "OPER") {
		if (tokens[1].empty() || tokens[2].empty())
			logsend(_poll_fds[i].fd, ERR_NEEDMOREPARAMS_MSG, true);
		else if(oper(tokens) == 1){
			_clients[cc].mode += "o";
			logsend(_poll_fds[i].fd, RPL_YOUREOPER_MSG, true);
		}
		else if(oper(tokens) == 0) 
			logsend(_poll_fds[i].fd, ERR_NOOPERHOST_MSG, true);
		else if(oper(tokens) == 2)
			logsend(_poll_fds[i].fd, ERR_PASSWDMISMATCH_MSG, true);
	}
	else if (tokens[0] == "MODE") {
		if (tokens[1].empty() == true)
			logsend(_poll_fds[i].fd, _clients[cc].mode.c_str(), true);
		else if (tokens[1].empty() || tokens[2].empty())
			logsend(_poll_fds[i].fd, ERR_NEEDMOREPARAMS_MSG, true);
		else
			logsend(_poll_fds[i].fd, mode(cc, tokens), true);
	}
	else if (tokens[0] == "QUIT") {quit(tokens, i);}
	
	}
	else
		logsend(_poll_fds[i].fd, "Please authenticate with NICK and USER", true);
	// else if (tokens[0] == "SERVICE") {}
	// else if (tokens[0] == "SQUIT") {}
	// else if (tokens[0] == "JOIN") {}
	// else if (tokens[0] == "PART") {}
	// else if (tokens[0] == "TOPIC") {}
	// else if (tokens[0] == "NAMES") {}
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
	// else if (tokens[0] == "PING") {}
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