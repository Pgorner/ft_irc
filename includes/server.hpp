/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:49:30 by ccompote          #+#    #+#             */
/*   Updated: 2023/08/26 18:22:07 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "irc.hpp"

#define FALSE 0
#define TRUE 1
#define INDETERMINATE 2

#define POLLTIME 500 
	
	struct ClientData;
	
	struct Channel
	{
		std::string name;
		std::string mode;
		std::string modeparams;
		std::vector<int> members;
		// std::vector<int> opers;
        Channel(std::string channelname, std::string channelmode, std::string channelmodeparams) : name(channelname), mode(channelmode), modeparams(channelmodeparams) {}
	};
    
    struct ClientData
    {
        int fd;               // File descriptor for the client
        bool passwordAccepted; // Flag indicating if the password is accepted for this client
        bool cap; // Flag indicating if CAP has been handled
        bool auth; // Flag indicating successfull authenticated (NICK & USER)
        std::string mode;
		std::vector<std::string> _channels;    
        std::string nick;
        std::string user;       
        std::string realname;   
        std::string send_to_user;
        ClientData(int client_socket, bool pwdAccepted, bool cap, bool auth, std::string mode, std::string nick, std::string user, std::string realname) : fd(client_socket), passwordAccepted(pwdAccepted), cap(cap), auth(auth), mode(mode), nick(nick), user(user), realname(realname){}
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
    int sig_handler(void);
    void proper_exit(void);
    void goodbye(void);
	int err(std::string msg);
    void run(); 
    static void change_running(int signal);
    void checkPwd(const std::vector<std::string>& tokens, int i, int cc);
    void logsend(int fd, const std::string& msg);
    bool contains(const std::vector<std::string>& tokens, std::string search);
    void cap(int fd, const std::vector<std::string>& tokens, bool& cap);
    void commands(int i, int cc, std::vector<std::string> tokens);
    void rmletter(char letter, int cc);
    void addmode(char letter, int cc);
    void addchanmode(char letter, std::string& chanmodes);
    
    //cmd functions
    void nick(std::vector<std::string> tokens, int cc, int i);
    void ping(std::vector<std::string> tokens, int cc);
    void user(std::vector<std::string> tokens, int cc, int i);
    int oper(std::vector<std::string> tokens);
    void changeoper(std::vector<std::string> tokens, int cc);
    const char* mode(int cc, std::vector<std::string> tokens);
    void quit(std::vector<std::string> tokens, int i, int cc);
	int joinchannel(std::vector<std::string> tokens , int cc);
	void sendmsg(std::vector<std::string> tokens, int cc);
    void names(std::vector<std::string> tokens , int cc);
	void leavechannel(std::vector<std::string> tokens, int cc);
	void kick(std::vector<std::string> tokens , int cc);
	void removefromchannel(std::string channelname, int cc);
	void sendmsg(std::vector<std::string> tokens, std::string nick);
	int find_user_fd(std::string username);


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
	std::vector<Channel> _channels;

};

#endif  // SERVER_HPP_
