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

#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> &split(const string &s, char delim, vector<string> &elems)
{
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
        elems.push_back(item);
    return elems;
}