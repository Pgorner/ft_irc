/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:49:30 by ccompote          #+#    #+#             */
/*   Updated: 2023/11/03 17:42:26 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "irc.hpp"

	struct ClientData;

	struct Channel
	{
		std::string name;
		std::string topic;
		std::string mode;
		std::string pwd;
		std::string modeparams;
		int ulimit;
		std::vector<std::string> members;
		std::vector<int> invited;
		std::vector<int> opers;
        Channel(std::string channelname, std::string channeltopic, std::string channelmode, std::string channelpassword, std::string channelmodeparams) : name(channelname), topic(channeltopic), mode(channelmode), pwd(channelpassword), modeparams(channelmodeparams) {}
	};
    
    struct ClientData
    {
        int fd;               // File descriptor for the client
        bool passwordAccepted; // Flag indicating if the password is accepted for this client
        bool cap; // Flag indicating if CAP has been handled
        bool auth; // Flag indicating successfull authenticated (NICK & USER)
        bool admin;
		std::vector<std::string> _channels;
        std::string nick;
        std::string user;       
        std::string realname;   
        std::string send_to_user;
        std::string num_offense;
        std::string data_buffer;
        std::string msg;
        bool ping;
        ClientData(int client_socket, bool pwdAccepted, bool cap, bool auth, bool admin, std::string nick, std::string user, std::string realname, std::string send_to_user, bool ping) \
                    : fd(client_socket), passwordAccepted(pwdAccepted), cap(cap), auth(auth), admin(admin), nick(nick), user(user), realname(realname),send_to_user(send_to_user), ping(ping){}
    };
	

class Server {
 public:
    Server(const int &port, const std::string &pwd);
    ~Server();
    Server& operator=(const Server& obj);
    void sendmsgstoclients();
    void broadcastinchannel(std::string channelname, std::string msg);

    void debugprint(std::vector<std::string> tokens, std::vector<ClientData>::size_type cc);
    int start_sock(void);
	int start_poll(void);
    void addNewClient(bool& hCC);
    void printconnect(int& connection, int& i, bool& hCC);
    int handleClient(int i);
    int sig_handlerserv(void);
    int sig_handler(void);
    void proper_exit(void);
    void goodbye(void);
	int err(std::string msg);
    void run(); 
    static void change_running(int signal);
    void checkPwd(std::vector<std::string>& tokens, int i, int cc);
    void logsend(int fd, const std::string& msg, int cc);
    bool token_contains(const std::vector<std::string>& tokens, std::string search);
    bool string_contains(const std::string& token, char search);
    void cap(int fd, const std::vector<std::string>& tokens, bool& cap, int cc);
    void commands(int i, int cc, std::vector<std::string> tokens);
    int rmchanletter(char letter, int cc, int channel);
    int addchanmode(char letter, int cc, int channel);
    bool isAllDigits(const std::string& str);

    //cmd functions
    bool check_params(std::vector<std::string>& tokens, size_t count);
    bool check_tokensize(std::string& token, size_t size);
    bool check_inchannel(int cc, std::string channelname);
    void nick(std::vector<std::string> tokens, int cc);
    void ping(std::vector<std::string> tokens, int cc);
    void pong(int cc);
    void user(std::vector<std::string> tokens, int cc);
    int oper(int cc ,std::vector<std::string> tokens);
    void changeoper(std::vector<std::string> tokens, int cc);
    void admin_oper(int cc, std::vector<std::string> tokens);
    bool client_oper(int cc, int channel);
    int mode(int cc, std::vector<std::string> tokens);
    void quit(size_t i, int cc, std::string msg);
	int joinchannel(std::vector<std::string> tokens , int cc);
	void sendmsg(std::vector<std::string> tokens, int cc);
    void names(std::vector<std::string> tokens , int cc);
    bool userexists(std::string username);
    bool channelexists(std::string channame);
	void leavechannel(std::vector<std::string> tokens, int cc);
	void kick(std::vector<std::string> tokens , int cc);
	void removefromchannel(std::string channelname, int cc, std::string msg);
    void userMode(int cc, std::vector<std::string> tokens);
    int channelMode(int cc, std::vector<std::string> tokens);
	void sendmsg(std::vector<std::string> tokens, std::string nick);
	int find_user(std::string username);
	void broadcastpriv(std::string channelname, std::string msg, int cc);
    bool find_user_inchan(int channel, int user);
	int find_nick(std::string nickname);
    int find_chan(std::string channelname);
    int find_ulimit(int i);
    void invite(std::vector<std::string> tokens, int cc);
    void topic(std::vector<std::string> tokens, int cc);
    void removeMemberFromChannel(const std::string& channelName, int clientID);

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

    bool censorship(const std::vector<std::string>& tokens);
    void warn_ban(int cc, int channel);
std::vector<std::string> load_words(const std::string& filename);
bool fileExists(const std::string& fileName);
bool validateUser(const std::string& filePath, const std::string& username, const std::string& password);

#endif  // SERVER_HPP_
