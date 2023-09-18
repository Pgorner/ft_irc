/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typography.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:38:45 by pgorner           #+#    #+#             */
/*   Updated: 2023/09/16 17:11:16 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// ----- Typography ------
#if(DEBUG)
	#define WRITESPEED 3000
#else
	#define WRITESPEED 0
#endif
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define PURPLE "\033[35m"

// ----- Texts -----------
#define IRC "\
--------------------------------------------\n\
	╦╦═╗╔═╗  ╔═╗╔═╗╦═╗╦  ╦╔═╗╦═╗\n\
	║╠╦╝║    ╚═╗║╣ ╠╦╝╚╗╔╝║╣ ╠╦╝\n\
	╩╩╚═╚═╝  ╚═╝╚═╝╩╚═ ╚╝ ╚═╝╩╚═\n\
--------------------------------------------\n"
#define LINE "\
--------------------------------------------\n"
#define OPTION1 "\
would you like to connect with IPv4 or IPv6?\n\
	press SPACE to cycle ENTER to select\n\
--------------------------------------------\n\
	    IPv4  ■  IPv6  ☐"
#define OPTION0 "\
would you like to connect with IPv4 or IPv6?\n\
	press SPACE to cycle ENTER to select\n\
--------------------------------------------\n\
	    IPv4  ☐  IPv6  ■"
#define GOODBYE "Farewell, dear friend!\n\
\n\
As you embark on a new journey and bid adieu\n\
to our little corner of the digital realm, we\n\
want to express our heartfelt gratitude for\n\
the moments we've shared together. Your\n\
presence has enriched our IRC community, and\n\
your contributions will forever be cherished.\n\
\n\
Though the pixels and text may fade, the\n\
memories we created will endure. Your wit,\n\
kindness, and camaraderie have left an\n\
indelible mark on each of us. As you venture\n\
onward, remember that you carry a piece of\n\
this community with you, just as we carry a\n\
piece of you in our hearts.\n\
\n\
May your path be filled with joy, success,\n\
and abundant blessings. Whenever you wish to\n\
return, our virtual doors will always be\n\
open, eagerly awaiting your presence once more.\n\
\n\
So, with both a heavy heart and boundless hope,\n\
we say our fond farewells. Until we meet again,\n\
remember that you are treasured and\n\
celebrated here.\n\
\n\
Safe travels and goodbye for now!\n"

#define LOGFILE "\n\
    _/          _/_/      _/_/_/  _/_/_/_/  _/_/_/  _/        _/_/_/_/   \n\
   _/        _/    _/  _/        _/          _/    _/        _/          \n\
  _/        _/    _/  _/  _/_/  _/_/_/      _/    _/        _/_/_/       \n\
 _/        _/    _/  _/    _/  _/          _/    _/        _/            \n\
_/_/_/_/    _/_/      _/_/_/  _/        _/_/_/  _/_/_/_/  _/_/_/_/       "