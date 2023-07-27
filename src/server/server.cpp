/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:59:30 by pgorner           #+#    #+#             */
/*   Updated: 2023/07/27 16:17:55 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/server.hpp"
#include <fcntl.h> 

Server::Server(const int &port, const std::string &pwd)
    : _port(port),
      _pwd(pwd),
      _socket(-1),
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

void Server::proper_exit(void)
{
    running = false;

    // Close all client sockets and remove them from the pollfd list.
    for (size_t i = 0; i < _poll_fds.size(); i++) {
        close(_poll_fds[i].fd);
    }
    _poll_fds.clear();

    // Close the server socket and reset its value to -1.
    if (_socket >= 0) {
        close(_socket);
        _socket = -1;
    }

    write_nice(RED, "	Server shutting down...", true);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    clear(100);
}

//creates support for both IPv4 and IPv6
int Server::which_ipv(void) {
    char input;
    int option = 1;

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true); // Enable non-blocking input

    printw("%s", IRC);
    printw("%s", option == 1 ? OPTION1 : OPTION0);

    while (true) {
        input = getch();
        if (input != ERR) {
            if (input == '\n')
                break;
            if (input == ' ') {
                option = 1 - option;
            }
            move(0, 0);
            printw("%s", IRC);
            printw("%s", option == 1 ? OPTION1 : OPTION0);
        }
        napms(100);
        refresh();
    }
    endwin();
    if (option == 1)
        return log("IPv4 chosen"), 4;
	else
        return log("IPv6 chosen"), 6;
}

int Server::sig_handler(void){
	// signal(SIGINT, change_running);
	// signal(SIGQUIT, change_running);
	return log("sig_handler started"), 0;
}


int Server::start_poll(void){
    _poll_fd = pollfd();  // Initialize the poll file descriptor

    // Assuming that the socket creation and binding are already done in the start_sock() function.
    // Add the socket to the list of file descriptors to monitor.
    _poll_fd.fd = _socket;
    _poll_fd.events = POLLIN;  // Monitoring for read events.
    _poll_fds.push_back(_poll_fd);
	return log("poll started successfully"), 0;
}

int Server::start_sock(void){
	if (which_ipv() == 6)
	{
		write_nice(BLUE, "	creating an IPv6 socket...", true);
		_socket = socket(AF_INET6, SOCK_STREAM, 0);
		if (_socket < 0)
			return err("	socket failed at IPv6"), -1;
		if (fcntl(_socket, F_SETFL, O_NONBLOCK) < 0)
			return err("	Unable to set the file descriptor to non-blocking mode"), -1;
		struct sockaddr_in6 addr = {};
		addr.sin6_family = AF_INET6;
		addr.sin6_port = htons(_port);
		addr.sin6_addr = in6addr_any;
		if (bind(_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0)
			return err("	binding failed at IPv6"), -1;
		else
			write_nice(GREEN, "	IPv6 socket created", true);
		if (listen(_socket, addr.sin6_port) < 0)
			err("	listening failed at IPv6");
	}
	else{
		write_nice(BLUE, "	creating an IPv4 socket...", true);
		_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (_socket < 0)
			return err("	socket failed at IPv4"), -1;

		struct sockaddr_in addr4 = {};
		addr4.sin_family = AF_INET;
		addr4.sin_port = htons(_port);
		addr4.sin_addr.s_addr = htonl(INADDR_ANY);
		int reuse = 1;
    	if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
			return err("	Failed to set SO_REUSEADDR option."), -1;
		if (bind(_socket, (struct sockaddr*)&addr4, sizeof(addr4)) < 0)
			return err("	binding failed at IPv4"), -1;
		else
			write_nice(GREEN, "	IPv4 socket created", true);
		if (listen(_socket, addr4.sin_port) < 0)
			err("	listening failed at IPv4");
	}
	return 0;
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
						hCC = true;
    				    // Optionally, you can store client information or perform other tasks here.
    			}
                } else {
    				// Handle events on other file descriptors (clients).
    				char buffer[1024];
    				int bytes_received = recv(_poll_fds[i].fd, buffer, sizeof(buffer), 0);
					std::cout << buffer << std::endl;
    				if (bytes_received <= 0) {
    				    // Client disconnected or an error occurred, remove it from the monitored file descriptors.
    				    close(_poll_fds[i].fd);
    				    _poll_fds.erase(_poll_fds.begin() + i);
    				} else 
					{
    				    // Process the received data from the client.
    				    std::string received_data(buffer, bytes_received);
						std::vector<std::string> tokens;
						std::stringstream iss(received_data);
						std::string token;

						while (std::getline(iss, token, ' ')) 
						{
							tokens.push_back(token);
						}

						// Now the 'tokens' vector contains the individual tokens from the input string
						bool passwordAccepted = false;
						std::cout << tokens[2] << std::endl;
						// while (!passwordAccepted)
						// {
						// 	if (tokens[0].compare(0, 5, "PASS") == 0)
						// 	{
						// 		if (tokens[1] == _pwd)
						// 		{
									
						// 			std::cout << "Password accepted" << std::endl;
						// 			passwordAccepted = true;
						// 		}
						// 		else
						// 			std::cout << "Invalid password" << std::endl;
						// 	}
							
						// }
						write_nice(BLUE, received_data, true);
    				    // Process the received_data here. For an IRC server, this will involve parsing and handling IRC messages.
    				}
				}
            }
		if (_poll_fds.size() == 1)
            hCC = false;
        }
    }
}
	