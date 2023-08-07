/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:14:39 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/02 18:37:43 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

int Server::err(std::string msg)
{
	std::cout << RED << msg << RESET << std::endl;
	log(msg);
	proper_exit();
	exit(42);
}

void Server::proper_exit(void)
{
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
    write_nice(RED, "\n	Server shutting down...", true);
	if (DEBUG){
    	std::this_thread::sleep_for(std::chrono::seconds(3));
		goodbye();
    	std::this_thread::sleep_for(std::chrono::seconds(3));
	}
	clear(100);
}