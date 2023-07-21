/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:59:30 by pgorner           #+#    #+#             */
/*   Updated: 2023/07/21 19:30:40 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/server.hpp"

Server::Server(int port, const std::string& pwd) :
	_port(port),
	_pwd(pwd),
	_socket(-1)
{}

Server::~Server() {}

Server& Server::operator=(const Server& obj) {
  (void)obj;
  return *this;
}

// --------------------------------------------------------------

//creates support for both IPv4 and IPv6
int Server::which_ipv(void){
	char input;
	int option = 0;
	unsigned long k = 0;
	std::string str = "would you like to connect with IPv4 or IPv6?\npress SPACE to cycle ENTER to select\n";
    while (k < str.size()) 
    {
        std::cout << str[k++] << std::flush;
        std::this_thread::sleep_for(std::chrono::microseconds(WRITESPEED));;
    }
	std::cout << "--------------------------------------------\n";
	SetTerminalEcho(false);
	SetTerminalNonBlocking(true);
	std::cout << "	   IPv4  ☐  IPv6  ■";
	while (1)
    {
        if (std::cin.eof()){
            std::cin.clear();
            continue;
        }
		std::cin.get(input);
		if (input == ' '){
			if (option == 1)
				option = 0;
			else
				option = 1;
		}
		if (option == 1 && input != '\0'){
			std::cout << "\x0D";
			std::cout << "	   IPv4  ■  IPv6  ☐";
		}
		else if (input != '\0'){
			std::cout << "\x0D";
			std::cout << "	   IPv4  ☐  IPv6  ■";
		}
		std::this_thread::sleep_for(std::chrono::microseconds(WRITESPEED));
	}
	SetTerminalNonBlocking(false);
	SetTerminalEcho(true);
	return 1;
}


int Server::start_sock(void){
	
	// first an IPv6 connection is tried
	if (which_ipv() == 6){
	std::cout << BLUE << "creating an IPv6 socket..." << RESET << std::endl;
	_socket = socket(AF_INET6, SOCK_STREAM, 0);
	if (_socket < 0)
		return err("socket failed at IPv6"), -1;
	
	struct sockaddr_in6 addr = {};
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(_port);
	addr.sin6_addr = in6addr_any;

	//if the Ipv6 connection fails, IPv4 is tried
	if (bind(_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0)
		return err("binding failed at IPv6"), -1;
	else
		std::cout << GREEN << "IPv6 socket created" << RESET << std::endl;
	}
	else{
		std::cout << BLUE << "creating an IPv4 socket..." << RESET << std::endl;

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
			std::cout << GREEN << "IPv4 socket created" << RESET << std::endl;
	}
	return 0;
}

//epoll used to coordinate events (has superceeded poll)
