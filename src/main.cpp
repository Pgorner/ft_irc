/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:15:38 by pgorner           #+#    #+#             */
/*   Updated: 2023/07/24 13:47:24 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"


int main(int argc, char **argv)
{
	// atexit(); // add exit handling
	if(welcome(argc, argv))
	{
		Server server(std::stoi(argv[1]), argv[2]);
		while(running == true){}
	}
	LOG << "Insert text";
	return (0);
}