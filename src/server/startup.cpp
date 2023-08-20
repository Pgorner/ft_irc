/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner < pgorner@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:18:55 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/06 16:18:55 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.hpp"

//creates support for both IPv4 and IPv6
int Server::which_ipv(void) {
    char input;
    int option = 1;

	if (!DEBUG)
		return 4;
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
	signal(SIGINT, Server::change_running);
	signal(SIGQUIT, Server::change_running);
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