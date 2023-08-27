/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:31:26 by pgorner           #+#    #+#             */
/*   Updated: 2023/08/27 21:32:14 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

bool validateUser(const std::string& filePath, const std::string& username, const std::string& password)
{
    std::ifstream file(filePath.c_str());
    std::string line;

    while (std::getline(file, line)) {
        std::string tokens[3];

        std::istringstream iss(line);
        for (int i = 1; i <= 2 && std::getline(iss, tokens[i], ' '); ++i);
        if (tokens[1] == username && tokens[2] == password)
            return true;
    }

    return false;
}

bool fileExists(const std::string& fileName) 
{
    FILE* file = fopen(fileName.c_str(), "r");
    if (file)
	{
        fclose(file);
        return true;
    }
    return false;
}
