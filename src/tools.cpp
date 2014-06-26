// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   tools.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2014/06/20 17:21:20 by Myrkskog          #+#    #+#             //
//   Updated: 2014/06/20 17:21:21 by Myrkskog         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <gfx.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <sys/socket.h>
#include <string.h>

using namespace std;

vector<string> &split(const string &s, char delim, vector<string> &elems)
{
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
        elems.push_back(item);
    return elems;
}

void	write_server(int sock, string &buf)
{
	if (send(sock, buf.c_str(), buf.size(), 0) < 0)
	{
		cout << "\033[31msend() error\033[0m" << endl;
		exit(0);
	}
}

int		read_server(int sock, string &buf)
{
	int		r;
    char    *str = new char[BUF_SIZE + 1];

    strcpy(str, buf.c_str());
    if ((r = recv(sock, str, BUF_SIZE - 1, 0)) < 0)
	{
		cout << "\033[31mread_server() error\033[0m" << endl;
		exit(0);
	}
	str[r] = 0;
    
    buf = str;
    delete [] str;
	return (r);
}