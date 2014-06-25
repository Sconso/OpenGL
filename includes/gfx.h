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

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

/*
** ft_errors
*/
void    ft_exit(std::string str);

/*
** tools.cpp
*/
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);


#endif
