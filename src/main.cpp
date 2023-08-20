/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:15:38 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/04 17:37:28 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

Server* Server::server_ptr = nullptr;
void first_exit(int signal)
{
	(void)signal;
	endwin();
	write_nice(RED, "\n	Server shutting down...", true);
	if (DEBUG){std::this_thread::sleep_for(std::chrono::seconds(3));}
	clear(100);
	exit (0);
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
		Server server(std::stoi(argv[1]), argv[2]);
		Server::server_ptr = &server;
		server.start_sock();
		server.start_poll();
		write_nice(BLUE, "	SERVER CREATION SUCCESSFUL", true);
		write_nice(WHITE, LINE, false);
		server.run();
	}
	return (0);
}