/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:59:30 by pgorner           #+#    #+#             */
/*   Updated: 2023/07/22 16:25:03 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/server.hpp"

Server::Server(int port, const std::string& pwd) :  _port(port),
													_pwd(pwd),
													_socket(-1)
{
	start_sock();
	sig_handler();
}

Server::~Server() {}

Server& Server::operator=(const Server& obj) {
  (void)obj;
  return *this;
}

// --------------------------------------------------------------

//creates support for both IPv4 and IPv6
int Server::which_ipv(void){
	char input;
	int option = 1;
	initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true); // Enable non-blocking input
    // Print the initial message
    if (option == 1){
		printw("%s", IRC);
		printw("%s", OPTION1);}
    else{
		printw("%s", IRC);
		printw("%s", OPTION0);}

    while (1) {
        input = getch(); // Get character without blocking

        if (input != ERR) { // Check if a character was read
			if (input == '\n')
				break;
            if (input == ' ') {
                if (option == 1)
                    option = 0;
                else
                    option = 1;
            }
            // Move the cursor to the beginning of the first line
            move(0, 0);

    		if (option == 1){
				printw("%s", IRC);
				printw("%s", OPTION1);}
    		else{
				printw("%s", IRC);
				printw("%s", OPTION0);}
        }
        // Add some delay to prevent high CPU usage (optional)
        napms(100);
		refresh();
    }
    // Cleanup
    endwin();
	if (option == 1)
		return 4;
	return 6;
}

int Server::sig_handler(void){
	signal(SIGINT, change_running);
	signal(SIGQUIT, change_running);
	return 0;
}


int Server::start_sock(void){
	
	// first an IPv6 connection is tried
	if (which_ipv() == 6)
	{
		write_nice(BLUE, "	creating an IPv6 socket...\n");
		_socket = socket(AF_INET6, SOCK_STREAM, 0);
		if (_socket < 0)
			return err("socket failed at IPv6"), -1;
		
		struct sockaddr_in6 addr = {};
		addr.sin6_family = AF_INET6;
		addr.sin6_port = htons(_port);
		addr.sin6_addr = in6addr_any;
		if (bind(_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0)
			return err("binding failed at IPv6"), -1;
		else
			write_nice(GREEN, "	IPv6 socket created\n");
	}
	else{
		write_nice(BLUE, "	creating an IPv4 socket...\n");
		_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (_socket < 0)
			return err("socket failed at IPv4"), -1;

		struct sockaddr_in addr4 = {};
		addr4.sin_family = AF_INET;
		addr4.sin_port = htons(_port);
		addr4.sin_addr.s_addr = htonl(INADDR_ANY);

		if (bind(_socket, (struct sockaddr*)&addr4, sizeof(addr4)) < 0)
			return err("binding failed at IPv4"), -1;
		else
			write_nice(GREEN, "	IPv4 socket created\n");
	}
	return 0;
}

//epoll used to coordinate events (has superceeded poll)
