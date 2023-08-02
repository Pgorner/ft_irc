/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:14:39 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/02 18:37:43 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

int Server::err(std::string msg)
{
	std::cout << RED << msg << RESET << std::endl;
	log(msg);
	proper_exit();
	exit(42);
}