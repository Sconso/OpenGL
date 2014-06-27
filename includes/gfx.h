/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 17:20:49 by Myrkskog          #+#    #+#             */
/*   Updated: 2014/06/20 17:21:06 by Myrkskog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H

#include <Game.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

# define BUF_SIZE (1024)

enum e_animationState
{
    BEGIN,
    PLAY,
    STOP,
    ONE_SHOT
};

/*
 ** main.c
 */
void askServer(Game *game);

/*
** ft_errors
*/
void    ft_exit(std::string str);

/*
** tools.cpp
*/
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
void write_server(int sock, std::string &buf);
int read_server(int sock, std::string &buf);



#endif
