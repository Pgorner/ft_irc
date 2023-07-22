/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:07:10 by pgorner           #+#    #+#             */
/*   Updated: 2023/07/22 16:12:58 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void SetTerminalEcho(bool enable) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (enable)
        tty.c_lflag |= ECHO;
	else
        tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void SetTerminalNonBlocking(bool nonBlocking) {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);

    if (nonBlocking) {
        ttystate.c_lflag &= ~(ICANON | ECHO);
        ttystate.c_cc[VMIN] = 0;
        ttystate.c_cc[VTIME] = 0;
    } else {
        ttystate.c_lflag |= ICANON | ECHO;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

void    clear(int i)
{
    for (int k = 0; k <= i; k++)
        std::cout << "\033[A\033[2K";
}

void    goodbye(void)
{
    clear(100);
    write_nice(YELLOW, GOODBYE);
}
void    write_nice(const char color[6], std::string str)
{
    setlocale(LC_ALL, "");
    unsigned long k = 0;
    while (k < str.size()) 
    {
        std::cout << color << str[k++] << RESET << std::flush;
        std::this_thread::sleep_for(std::chrono::microseconds(WRITESPEED));;
    }
}
void    write_irc(void){
    unsigned long k = 0;
	std::string str = IRC;
    while (k < str.size()) 
    {
        std::cout << str[k++] << std::flush;
        std::this_thread::sleep_for(std::chrono::microseconds(WRITESPEED));
    }
}

void change_running(int signal)
{
    if (signal == SIGINT || signal == SIGQUIT){
        running = false;
        goodbye();
        exit(1);
    }
}