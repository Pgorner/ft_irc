/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:53:30 by pgorner           #+#    #+#             */
/*   Updated: 2023/07/22 15:33:50 by pgorner          ###   ########.fr       */
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
		return 1;
	}
	if (argc == 3 && isValidPort(argv[1]) == false)
		write_nice(RED, "		Invalid Port\n");
	else
		write_nice(RED, "	  Please adhere to syntax:\n	 ./ircserv <port> <password>\n");
	std::cout << LINE;
	return 0;
}