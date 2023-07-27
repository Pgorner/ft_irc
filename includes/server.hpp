/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:59:30 by pgorner           #+#    #+#             */
/*   Updated: 2023/07/27 20:47:35 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "irc.hpp"

#define FALSE 0
#define TRUE 1
#define INDETERMINATE 2

#define POLLTIME 500 
#define SERVERNAME "IRCSERV: "

    struct ClientData {
        int fd;               // File descriptor for the client
        int passwordAccepted; // Flag indicating if the password is accepted for this client
        ClientData(int client_socket, int pwdAccepted) : fd(client_socket), passwordAccepted(pwdAccepted) {}
    };


class Server {
 public:
    Server(const int &port, const std::string &pwd);
    ~Server();
    Server& operator=(const Server& obj);

    int which_ipv(void);
    int start_sock(void);
	int start_poll(void);
    int sig_handler(void);
    void proper_exit(void);
	int err(std::string msg);
    void run(); 
    void change_running(int signal);
    void checkPwd(const std::vector<std::string>& tokens, int i);
    void logsend(int fd, const char* msg);
 private:
    int _port;
    std::string _pwd;
    int _socket;
    time_t _start_time;
    time_t _last_ping;
	struct pollfd _poll_fd;  // poll file descriptor
	std::vector<struct pollfd> _poll_fds;  // to store poll descriptors
    std::vector<ClientData> _clients;

};


#endif  // SERVER_HPP_
