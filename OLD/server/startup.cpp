/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:18:55 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/24 10:53:14 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server.hpp"

int Server::sig_handler(void){
	signal(SIGINT, Server::change_running);
	signal(SIGQUIT, Server::change_running);
	return log("sig_handler started"), 0;
}


int Server::start_poll(void){
    _poll_fd = pollfd();
    _poll_fd.fd = _socket;
    _poll_fd.events = POLLIN;
    _poll_fds.push_back(_poll_fd);
	return log("poll started successfully"), 0;
}

int Server::start_sock(void)
{
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
	return(0);
}