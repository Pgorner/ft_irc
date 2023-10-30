/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:50:02 by pgorner           #+#    #+#             */
/*   Updated: 2023/10/30 15:40:36 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

int Server::addchanmode(char letter, int cc, int channel)
{
	if(_channels[channel].mode.find(letter) == std::string::npos)
		_channels[channel].mode += letter;
	else
	{
		_clients[cc].send_to_user += SERVERNAME" Cannot add MODE \"";
		_clients[cc].send_to_user += letter;
		_clients[cc].send_to_user += "\" as it is already active\r\n";
		return -1;
	}
	return 1;
}

int Server::rmchanletter(char letter, int cc, int channel){
	std::string result;
	bool noletter = true;
    for (std::size_t i = 0; i < _channels[channel].mode.length(); ++i)
	{
        if ( _channels[channel].mode[i] != letter)
            result +=  _channels[channel].mode[i];
        else if ( _channels[channel].mode[i] == letter)
			noletter = false;
    }
	if (noletter == true)
	{
        _clients[cc].send_to_user += SERVERNAME" Cannot remove MODE \"";
		_clients[cc].send_to_user += letter;
		_clients[cc].send_to_user += "\" as it was never active\r\n";
		return -1;
	}
    _channels[channel].mode = result;
	return 1;
}

// void Server::admin_oper(int cc, std::vector<std::string> tokens)
// {
// 	if (!string_contains(_clients[cc].mode, 'O'))
// 	{
// 		_clients[cc].send_to_user += irc::cEM(irc::ERR_NOPRIVILEGES());
// 		return;
// 	}
// 	for (size_t user = 0; user < _clients.size(); user++)
// 	{
// 		if (_clients[user].nick == tokens[1])
// 		{
// 			if (tokens[2][0] == '-')
// 			{
// 				for (int i = 1; tokens[2][i]; i++)
// 					rmletter(tokens[2][i], user);	
// 				_clients[user].send_to_user += irc::cEM(irc::RPL_UMODEIS(_clients[user].mode));
// 				return;
// 			}
// 			else if (tokens[2][0] == '+')
// 			{
// 				for (int i = 1; tokens[2][i]; i++)
// 				{
// 					if ((tokens[2][i] == 'o' 
// 						|| tokens[2][i] == 'a'
// 						|| tokens[2][i] == 'i'
// 						|| tokens[2][i] == 'w'
// 						|| tokens[2][i] == 'r'
// 						|| tokens[2][i] == 's'))
// 						addmode(tokens[2][i], user);
// 				}
// 			_clients[user].send_to_user += irc::cEM(irc::RPL_UMODEIS(_clients[user].mode));
// 			}
// 		_clients[cc].send_to_user += "You have changed " + _clients[user].nick + "\'s Mode\r\n";
// 		}
// 	}
// }

// void Server::userMode(int cc, std::vector<std::string> tokens)
// {
// 	if (tokens[2][0] == '-')
// 	{
// 		for (int i = 1; tokens[2][i]; i++)
// 			rmletter(tokens[2][i], cc);	
// 		_clients[cc].send_to_user += irc::cEM(irc::RPL_UMODEIS(_clients[cc].mode));
// 		return;
// 	}
// 	else if (tokens[2][0] == '+')
// 	{
// 		for (int i = 1; tokens[2][i]; i++)
// 		{
// 			if ((tokens[2][i] != 'o' 
// 				&& tokens[2][i] != 'O'
// 				&& tokens[2][i] != 'a') 
// 				&& (tokens[2][i] == 'a'
// 				|| tokens[2][i] == 'i'
// 				|| tokens[2][i] == 'w'
// 				|| tokens[2][i] == 'r'
// 				|| tokens[2][i] == 's'))
// 				addmode(tokens[2][i], cc);
// 			if (tokens[2][i] == 'O' || tokens[2][i] == 'o')
// 				_clients[cc].send_to_user += SERVERNAME" Use OPER cmd to gain priviledges\r\n";
// 		}
// 	_clients[cc].send_to_user += irc::cEM(irc::RPL_UMODEIS(_clients[cc].mode));
// 	}
// }


int Server::channelMode(int cc, std::vector<std::string> tokens)
{
	int chan = find_chan(tokens[1]);
	bool addrm = false;
	std::string resp = "";
	if (tokens.size() == 2){return(_clients[cc].send_to_user += irc::cEM(irc::RPL_CHANNELMODEIS(_channels[chan].name, _channels[chan].mode, _channels[chan].modeparams)), 0);}
	if (!string_contains(tokens[2], '-') && !string_contains(tokens[2], '+')){ return (_clients[cc].send_to_user += SERVERNAME" Adding or removing MODES requires +/-\r\n", 0);}
	if (_clients[cc].admin == false && !client_oper(cc, find_chan(tokens[1]))){_clients[cc].send_to_user += irc::cEM(irc::ERR_NOPRIVILEGES()); return 0;}
	if (isalpha(tokens[2][1]))
	{
		std::string modes = "it";
		if(tokens[2][1] == 'k')
		{
			if (tokens[2][0] == '+' && !check_params(tokens, 4)){ return (_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("MODE")), 0);}
			else if (tokens[2][0] == '+')
			{
				if (addchanmode('k', cc, chan) > 0)
					return (_channels[chan].pwd = tokens[3], _clients[cc].send_to_user += SERVERNAME" Password has been added to channel\r\n", 0);
				else
					return (_channels[chan].pwd = tokens[3], _clients[cc].send_to_user += SERVERNAME" Password has been changed\r\n", 0);
			}
			else if (tokens[2][0] == '-')
			{
				rmchanletter('k', cc, chan);
				_channels[chan].pwd = "";
				return (_clients[cc].send_to_user += SERVERNAME" Password has been removed from channel\r\n", 0);
			}
		}
		else if(tokens[2][1] == 'o')
		{
			int u = find_user(tokens[3]);
			if ((tokens[2][0] == '+' || tokens[2][0] == '-') && !check_params(tokens, 3))
				return (_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("MODE")), 0);
			if (tokens[2][0] == '+')
			{
				for (size_t g = 0; g < _channels[chan].opers.size(); g++)
				{
				if (_channels[chan].opers[g] == u)
					return(_clients[cc].send_to_user += SERVERNAME" User already has oper mode for this channel\r\n", 0);
				}
				_channels[chan].opers.push_back(u);
				return (_clients[cc].send_to_user += SERVERNAME" Oper privs have been granted to " + tokens[3] + " for " + tokens[1] + "\r\n", 0);
			}
			if (tokens[2][0] == '-')
			{
				for (size_t g = 0; g < _channels[chan].opers.size(); g++)
				{
					if (_channels[chan].opers[g] == u)
						return(_channels[chan].opers.erase(_channels[chan].opers.begin() + g), _clients[cc].send_to_user += SERVERNAME" Oper privs removed for " + tokens[3] + " in " + tokens[1] + "\r\n", 0);
				}
				return (_clients[cc].send_to_user += SERVERNAME" Oper privs for " + tokens[3] + " in " + tokens[1] + " could not be found\r\n", 0);
			}
		}
		else if(tokens[2][1] == 'l')
		{
			if (tokens[2][0] == '-')
			{
				rmchanletter('l', cc, chan);
				_channels[chan].ulimit = -1;
				return (_clients[cc].send_to_user += SERVERNAME" Userlimit has been removed from channel\r\n", 0);
			}
			if ((tokens[2][0] == '+' && !check_params(tokens, 4)) || isAllDigits(tokens[3]) == false)
				return (_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("MODE")), 0);
			else if (tokens[2][0] == '+')
			{
				if (addchanmode('l', cc, chan) > 0)
					return (_channels[chan].ulimit = std::atoi(tokens[3].c_str()), _clients[cc].send_to_user += SERVERNAME" Userlimit has been added to channel\r\n", 0);
				else
					return (_channels[chan].ulimit = std::atoi(tokens[3].c_str()), _clients[cc].send_to_user += SERVERNAME" Userlimit has been changed\r\n", 0);
			}
		}
		else if (string_contains(modes, tokens[2][1]))
		{
			addrm = true;
			if (tokens[2][0] == '+')
			{
				if(addchanmode(tokens[2][1], cc, chan) > 0)
				{
					_clients[cc].send_to_user += SERVERNAME" Added mode ";
					_clients[cc].send_to_user += tokens[2][1];
					_clients[cc].send_to_user += " to channel\r\n";
				}
			}
			else if (tokens[2][0] == '-')
			{
				if (rmchanletter(tokens[2][1], cc, chan) > 0)
				{
					_clients[cc].send_to_user += SERVERNAME" Removed mode ";
					_clients[cc].send_to_user += tokens[2][1];
					_clients[cc].send_to_user += " from channel\r\n";
				}
			}
		}
	}
	if (addrm)
		return ( resp.c_str(), 0);
	return(_clients[cc].send_to_user += SERVERNAME" Requested MODE/S are not available\r\n", 0);
}

bool Server::userexists(std::string username)
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].nick == username)
			return (true);
	}
	return (false);
}

bool Server::channelexists(std::string channame)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].name == channame)
			return (true);
	}
	return (false);
}

int Server::mode(int cc, std::vector<std::string> tokens)
{
	if (!check_params(tokens, 3)){_clients[cc].send_to_user += irc::cEM(irc::ERR_NEEDMOREPARAMS("OPER"));}
	if (channelexists(tokens[1]))
		return(channelMode(cc, tokens), 0);
	return(_clients[cc].send_to_user += SERVERNAME" Channel could not be found \r\n", 0);
}