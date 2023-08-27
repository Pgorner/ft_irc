/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:52:14 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/27 21:01:56 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

int Server::sig_handlerserv(void){
	signal(SIGINT, Server::change_running);
	signal(SIGQUIT, Server::change_running);
	return log("sig_handler started"), 0;
}

void Server::checkPwd(const std::vector<std::string>& tokens, int i, int cc)
{
    if ((tokens.empty() || tokens[0].compare(0, 5, "PASS") != 0))
        logsend(_poll_fds[i].fd, SERVERNAME" : WRONG PASSWORD\r\n", cc);
    else if (tokens[1] == _pwd) 
	{
        _clients[cc].passwordAccepted = TRUE;
		_clients[cc].send_to_user += SERVERNAME" Your PASSWORD is correct\r\n";
	}
	else
        logsend(_poll_fds[i].fd, irc::ERR_PASSWDMISMATCH(), cc);
}

void Server::cap(int fd, const std::vector<std::string>& tokens, bool& cap, int cc) {
	if (contains(tokens, "CAP") == true && contains(tokens, "LS") == true)
		logsend(fd, "CAP * LS :\n", cc);
	else if (contains(tokens, "CAP") == true && contains(tokens, "REQ") == true){
		std::string req = "CAP * ACK :";
		if (contains(tokens, "multi-prefix"))
			req += "multi-prefix";
		if (contains(tokens, "multiple-channel-joins"))
			req += "multiple-channel-joins";
		logsend(fd, req.c_str(), cc);
	}
	else if (contains(tokens, "CAP") == true && contains(tokens, "END") == true)
		cap = true;
}
