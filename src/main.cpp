/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:15:38 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/02 19:25:38 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

Server* Server::server_ptr = nullptr;

int main(int argc, char **argv)
{
	log_creation();
	if(welcome(argc, argv))
	{
		Server server(std::stoi(argv[1]), argv[2]);
		Server::server_ptr = &server;
		server.run();
	}
	return (0);
}