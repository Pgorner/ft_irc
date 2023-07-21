/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:53:30 by pgorner           #+#    #+#             */
/*   Updated: 2023/07/21 19:06:50 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"


bool isValidPort(const char* port) {
    char* end;
    long iport = std::strtol(port, &end, 10);
    if (*end != '\0' || end == port || iport < 1 || iport > 65535)
        return false;
    return true;
}

int welcome(int argc, char **argv){
    unsigned long k = 0;
	std::cout << "--------------------------------------------\n";
	std::string str = "	╦╦═╗╔═╗  ╔═╗╔═╗╦═╗╦  ╦╔═╗╦═╗\n	║╠╦╝║    ╚═╗║╣ ╠╦╝╚╗╔╝║╣ ╠╦╝\n	╩╩╚═╚═╝  ╚═╝╚═╝╩╚═ ╚╝ ╚═╝╩╚═\n";
    while (k < str.size()) 
    {
        std::cout << str[k++] << std::flush;
        std::this_thread::sleep_for(std::chrono::microseconds(WRITESPEED));;
    }
	std::cout << "--------------------------------------------\n";
	if (argv[1] && argv[2] && (argc == 3) && isValidPort(argv[1]) == true)
	{
		str = "	   Selected port: ";
		str += argv[1];
		str += "\n";
		k = 0;
    	while (k < str.size()) 
    	{
    	    std::cout << str[k++] << std::flush;
    	    std::this_thread::sleep_for(std::chrono::microseconds(WRITESPEED));;
    	}
		str = "	   Password     : ";
		str += argv[2];
		str += "\n";
		k = 0;
    	while (k < str.size()) 
    	{
    	    std::cout << str[k++] << std::flush;
    	    std::this_thread::sleep_for(std::chrono::microseconds(WRITESPEED));;
    	}
	std::cout << "--------------------------------------------\n";
	return 1;
	}
	if (argc == 3 && isValidPort(argv[1]) == false)
		str = "		Invalid Port\n";
	else
		str = "	  Please adhere to syntax:\n	 ./ircserv <port> <password>\n";
	k = 0;
    while (k < str.size()) 
    {
        std::cout << str[k++] << std::flush;
        std::this_thread::sleep_for(std::chrono::microseconds(WRITESPEED));;
    }
	std::cout << "--------------------------------------------\n";
	return 0;
}