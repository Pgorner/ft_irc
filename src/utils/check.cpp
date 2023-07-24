/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:53:30 by pgorner           #+#    #+#             */
/*   Updated: 2023/07/24 13:39:27 by pgorner          ###   ########.fr       */
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
		write_nice(WHITE, str);
		str = "	   Password     : ";
		str += argv[2];
		str += "\n";
		write_nice(WHITE, str);
		std::cout << LINE;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		return log("welcome successfully done"), 1;
	}
	if (argc == 3 && isValidPort(argv[1]) == false){
		write_nice(RED, "		Invalid Port\n");
		return log("invalid port entry\n"), 0;
	}
	else{
		write_nice(RED, "	  Please adhere to syntax:\n	 ./ircserv <port> <password>\n");
		return log("invalid syntax\n"), 0;
	}
	std::cout << LINE;
	return log("error in welcome function\n"), 0;
}