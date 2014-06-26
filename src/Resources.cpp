// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Resources.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2014/06/20 16:24:16 by Myrkskog          #+#    #+#             //
//   Updated: 2014/06/20 16:24:16 by Myrkskog         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <Resources.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

Resources::Resources()
{
    for (int i = 0; i < 8; ++i)
        m_resources[i] = 0;
}

Resources::Resources(vector<string> &str)
{
    for (int i = 0; i < 7; ++i)
        m_resources[i] = atoi(str[i + 3].c_str());
    m_resources[7] = 0;
}

void Resources::setResources(vector<string> &str)
{
    for (int i = 0; i < 7; ++i)
        m_resources[i] = atoi(str[i + 3].c_str());
}

void Resources::setInventory(vector<string> &str)
{
    for (int i = 0; i < 7; ++i)
        m_resources[i] = atoi(str[i + 2].c_str());
}

void Resources::getResources() const
{
    cout << "Food : " << m_resources[0] << endl;
    cout << "Linemate : " << m_resources[1] << endl;
    cout << "Deraumere : " << m_resources[2] << endl;
    cout << "Sibur : " << m_resources[3] << endl;
    cout << "Mendiane : " << m_resources[4] << endl;
    cout << "Phiras : " << m_resources[5] << endl;
    cout << "Thystame : " << m_resources[6] << endl;
//    cout << "Oeuf : " << m_resources[7] << endl;
}

void Resources::getResources(int tab[]) const
{
    tab[0] = m_resources[0];
    tab[1] = m_resources[1];
    tab[2] = m_resources[2];
    tab[3] = m_resources[3];
    tab[4] = m_resources[4];
    tab[5] = m_resources[5];
    tab[6] = m_resources[6];
}

int Resources::getFood(void) const
{
    return (m_resources[0]);
}

void Resources::setFood(int food)
{
    if (food >= 0)
        m_resources[0] = food;
}
