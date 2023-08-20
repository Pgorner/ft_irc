/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:59:30 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/20 16:26:14 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "irc.hpp"

#define FALSE 0
#define TRUE 1
#define INDETERMINATE 2

#define POLLTIME 500 

    struct ClientData {
        int fd;               // File descriptor for the client
        int passwordAccepted; // Flag indicating if the password is accepted for this client
        bool cap; // Flag indicating if CAP has been handled
        bool auth; // Flag indicating successfull authenticated (NICK & USER)
        std::string mode;       
        std::string nick;
        std::string user;       
        std::string realname;       
        ClientData(int client_socket, int pwdAccepted, bool cap, bool auth, std::string mode) : fd(client_socket), passwordAccepted(pwdAccepted), cap(cap), auth(auth), mode(mode) {}
    };


class Server {
 public:
    Server(const int &port, const std::string &pwd);
    ~Server();
    Server& operator=(const Server& obj);

    int which_ipv(void);
    int start_sock(void);
	int start_poll(void);
    int sig_handlerserv(void);
    void proper_exit(void);
    void goodbye(void);
	int err(std::string msg);
    void run(); 
    static void change_running(int signal);
    void checkPwd(const std::vector<std::string>& tokens, int i, int cc);
    void logsend(int fd, const char* msg, bool servname);
    bool contains(const std::vector<std::string>& tokens, std::string search);
    void cap(int fd, const std::vector<std::string>& tokens, bool cap);
    void commands(int i, int cc, std::vector<std::string> tokens);
    std::string rmletter(char letter, std::string mode);
    std::string addmode(char letter, std::string mode);
    
    //cmd functions
    void nick(std::vector<std::string> tokens, int cc, int i);
    void user(std::vector<std::string> tokens, int cc, int i);
    int oper(std::vector<std::string> tokens);
    const char* mode(int cc, std::vector<std::string> tokens);
    void quit(std::vector<std::string> tokens, int i);

    static Server* server_ptr;

 private:
    int _port;
    std::string _pwd;
    int _socket;
    bool running;
    time_t _start_time;
    time_t _last_ping;
	struct pollfd _poll_fd;  // poll file descriptor
	std::vector<struct pollfd> _poll_fds;  // to store poll descriptors
    std::vector<ClientData> _clients;

};

#endif  // SERVER_HPP_
