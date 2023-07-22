/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:59:30 by pgorner           #+#    #+#             */
/*   Updated: 2023/07/22 16:02:39 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "irc.hpp"

class Server {
 public:
    Server(int port, const std::string& pwd);
    ~Server();
    Server& operator=(const Server& obj);

    int which_ipv(void);
    int start_sock(void);
    int sig_handler(void);

 private:
    int _port;
    int _socket;
    std::string _pwd;
};

int start_sock(void);

#endif  // SERVER_HPP_
