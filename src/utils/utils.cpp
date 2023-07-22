/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:07:10 by pgorner           #+#    #+#             */
/*   Updated: 2023/07/22 16:27:11 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

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

void proper_exit(void)
{
//add proper exit handling
}

void change_running(int signal)
{
    if (signal == SIGINT || signal == SIGQUIT){
        running = false;
        proper_exit();
        goodbye();
        exit(1);
    }
}
