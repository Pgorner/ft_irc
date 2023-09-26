/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:59:30 by pgorner           #+#    #+#             */
/*   Updated: 2023/09/26 15:30:45 by pgorner          ###   ########.fr       */
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

void Server::handleNewClient() {
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int clientSocket = accept(_socket, (struct sockaddr*) &clientAddr, &clientAddrLen);

    if (clientSocket < 0) {
        // Handle the error, and optionally continue or exit.
    } else {
        write_nice(GREEN, "\nNEW CLIENT SUCCESSFULLY ADDED", true);
        pollfd newClientPollFd;
        newClientPollFd.fd = clientSocket;
        newClientPollFd.events = POLLIN; // Monitoring for read events.
        logsend(newClientPollFd.fd, SERVERNAME" Enter the password, user and nickname\r\n" SERVERNAME" PASS <password>\r\n" SERVERNAME" USER <username>\r\n" SERVERNAME" NICK <nickname>\r\n", -1);
        _poll_fds.push_back(newClientPollFd);
        _clients.push_back(ClientData(clientSocket, false, false, false, "", "", "", ""));
    }
}

void Server::handleClientData(size_t clientIndex) {
    size_t cc = 0;

    for (; cc < _clients.size(); cc++) {
        if (_clients[cc].fd == _poll_fds[clientIndex].fd)
            break;
    }

    char buffer[1024];
    int bytesReceived = recv(_poll_fds[clientIndex].fd, buffer, sizeof(buffer), 0);

    if (bytesReceived <= 0) {
        close(_poll_fds[clientIndex].fd);
        _poll_fds.erase(_poll_fds.begin() + clientIndex);
        write_nice(RED, "Client Error occurred: ", false);
        write_nice(RED, _clients[cc].nick, false);
        _clients.erase(_clients.begin() + cc);
    } else {
        std::string receivedData(buffer, bytesReceived);
        _clients[cc].data_buffer += receivedData; // Add received data to the buffer
        processClientCommands(cc);
    }

    // Process any data to send back to the client
    for (size_t h = 0; h < _poll_fds.size(); h++) {
        for (size_t k = 0; k < _clients.size(); k++) {
            if (_poll_fds[h].fd == _clients[k].fd && !_clients[k].send_to_user.empty()) {
                logsend(_poll_fds[h].fd, _clients[k].send_to_user, cc);
                _clients[k].send_to_user = "";
            }
        }
    }
    write(1, "\n", 1);
    write_nice(WHITE, LINE, true);
}

void Server::processClientCommands(size_t clientIndex) {
    while (_clients[clientIndex].data_buffer.find("\n") != std::string::npos) {
        size_t pos = _clients[clientIndex].data_buffer.find("\n");
        std::string command = _clients[clientIndex].data_buffer.substr(0, pos);
        _clients[clientIndex].data_buffer.erase(0, pos + 1); // Remove processed data

        // Process the command
        std::vector<std::string> tokens;
        std::istringstream iss(command);
        std::string token;
        std::string line;

        write_nice(WHITE, command, true);

        while (std::getline(iss, line)) {
            std::string token;
            std::istringstream lineStream(line);

            while (lineStream >> token)
                tokens.push_back(token);

            for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
                if (!it->empty() && (*it)[0] == ':')
                    it->erase(0, 1);
            }

            if (tokens.size() != 0) {
                if (_clients[clientIndex].cap == false)
                    cap(_poll_fds[clientIndex].fd, tokens, _clients[clientIndex].cap, clientIndex);
                if (_clients[clientIndex].passwordAccepted == true)
                    commands(clientIndex, clientIndex, tokens);
                else if (_clients[clientIndex].passwordAccepted == false && tokens[0] == "PASS")
                    checkPwd(tokens, clientIndex, clientIndex);
            }

            tokens.clear();
        }
    }
}



void Server::run() {
    int connectionCount = 0;
    bool hasConnectedClients = false;
    int dotsCount = 0;
    std::string str;

    while (true) {
        int numEvents = poll(_poll_fds.data(), static_cast<nfds_t>(_poll_fds.size()), POLLTIME);

        // Display waiting message when no clients are connected
        if (!hasConnectedClients) {
            if (connectionCount == 0 && dotsCount == 0) {
                write_nice(YELLOW, "waiting to connect ", false);
				dotsCount++;
            } else if (dotsCount < 3 && connectionCount < 3) {
                write_nice(YELLOW, ".", false);
                dotsCount++;
            } else {
                dotsCount = 0;
                connectionCount++;
                str = std::to_string(connectionCount);

                if (connectionCount == 4) {
                    write(1, "\n", 1);
                    clear(0);
                    connectionCount = 0;
                } else {
                    write_nice(YELLOW, str, false);
                }
            }
        }

        if (numEvents == -1) {
            if (errno == EINTR) {
                write_nice(RED, "poll interrupted", true);
                continue;
            } else {
                err("poll has failed");
                exit(1);
            }
        }

        for (size_t i = 0; i < _poll_fds.size(); i++) {
            if (_poll_fds[i].revents & POLLIN) {
                if (_poll_fds[i].fd == _socket) {
                    handleNewClient();
                    hasConnectedClients = true;
                } else {
                    handleClientData(i);
                }
            }
        }

        if (_poll_fds.size() == 1) {
            hasConnectedClients = false;
        }
    }
}


void Server::commands(int i, int cc, std::vector<std::string> tokens)
{
	if (tokens[0] == "NICK")
	{
		nick(tokens, cc, i);
	}
	else if (tokens[0] == "USER")
	{
		user(tokens, cc, i);
	}
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
		{
			joinchannel(tokens, cc);
		}
		else if (tokens[0] == "PRIVMSG")
		{
			if (tokens[1].empty())
				_clients[cc].send_to_user += irc::ERR_NEEDMOREPARAMS("PRIVMSG");
			else
				sendmsg(tokens, cc);
		}
		else if (tokens[0] == "PART")
		{
			leavechannel(tokens, cc);
		}
		else if (tokens[0] == "KICK")
		{
			kick(tokens, cc);
		}
		else if (tokens[0] == "PING")
		{
			ping(tokens, cc);
		}
		else if (tokens[0] == "QUIT")
		{
			quit(tokens, i, cc);
		}
		else if (tokens[0] == "NAMES")
		{
			names(tokens, cc);
		}
		else if (tokens[0] == "INVITE")
		{
			invite(tokens, cc);
		}
		else if (tokens[0] == "TOPIC")
		{
			topic(tokens, cc);
		}
		else if (tokens[0] == "NOTICE")
		{
			notice(tokens, cc);
		}
	}
}
	// else if (tokens[0] == "SQUIT") {}
	// else if (tokens[0] == "LIST") {}
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
