// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ft_errors.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2014/06/20 17:34:23 by Myrkskog          #+#    #+#             //
//   Updated: 2014/06/20 17:34:24 by Myrkskog         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <gfx.h>
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

void    ft_exit(string str)
{
    cout << str << endl << "Exiting now..." << endl;
    exit(1);
}