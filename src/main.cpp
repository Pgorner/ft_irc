/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:15:38 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/25 14:33:35 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"
#include <cstdlib> // for atoi
#include <signal.h> // for signal handling

Server* Server::server_ptr = NULL;

void first_exit(int signal)
{
	(void)signal;
	write_nice(RED, "\n    Server shutting down...", true);
	if (DEBUG) sleep(3); // Sleep for 3 seconds, assuming sleep function is available
	clear(100);
	exit(0);
}

int sig_handler(void){
	signal(SIGINT, first_exit);
	signal(SIGQUIT, first_exit);
	return log("first exit started"), 0;
}

int main(int argc, char **argv)
{
	log_creation();
	sig_handler();
	if(welcome(argc, argv))
	{
		Server server(atoi(argv[1]), argv[2]); // Using atoi instead of std::stoi
		Server::server_ptr = &server;
		server.start_sock();
		server.start_poll();
		write_nice(BLUE, "    SERVER CREATION SUCCESSFUL", true);
		write_nice(WHITE, LINE, false);
		server.run();
	}
	return 0;
}
