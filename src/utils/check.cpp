/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:53:30 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/27 20:54:35 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"


bool isValidPort(const char* port) {
    char* end;
    long iport = std::strtol(port, &end, 10);
    if (*end != '\0' || end == port || iport < 1 || iport > 65535)
        return log("port invalid"), false;
    return log("port validated"), true;
}



int welcome(int argc, char **argv){
	clear(100);
	std::string str;
	write_irc();
	if (argv[1] && argv[2] && (argc == 3) && isValidPort(argv[1]) == true)
	{
		str = "	   Selected port: ";
		str += argv[1];
		str += "\n";
		write_nice(WHITE, str, false);
		str = "	   Password     : ";
		str += argv[2];
		str += "\n";
		write_nice(WHITE, str, false);
		std::cout << LINE;
		if(DEBUG){std::this_thread::sleep_for(std::chrono::seconds(3));}
		return log("welcome successfully done"), 1;
	}
	else if (argc == 3 && isValidPort(argv[1]) == false)
		return write_nice(RED, "		Invalid Port", true), log("invalid port entry\n"), 0;
	else
		return write_nice(RED, "	  Please adhere to syntax:\n	 ./ircserv <port> <password>", true), log("invalid syntax\n"), 0;
	std::cout << LINE;
	return log("error in welcome function\n"), 0;
}