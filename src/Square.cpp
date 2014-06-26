// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Square.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2014/06/20 16:18:02 by Myrkskog          #+#    #+#             //
//   Updated: 2014/06/20 16:18:05 by Myrkskog         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <Square.h>
#include <iostream>

using namespace std;

Square::Square()
{
}

void Square::getResources() const
{
    m_resources.getResources();
}

void Square::getResources(int tab[]) const
{
    m_resources.getResources(tab);
}

void Square::setResources(std::vector<std::string> &str)
{
    m_resources.setResources(str);
}

void Square::addPlayer(Player *player)
{
    m_players[player->getNb()] = player;
}

void Square::removePlayer(int nb)
{
    map<int, Player *>::iterator it;
    
    it = m_players.find(nb);
    m_players.erase(nb);
}

void Square::removePlayer(Player *player)
{
    map<int, Player *>::iterator it;
    
    it = m_players.find(player->getNb());
    if (it != m_players.end())
        m_players.erase(it);
}

void Square::listPlayers(void) const
{
    map<int, Player *>::const_iterator it;
    
    for (it = m_players.begin(); it != m_players.end(); ++it)
        (*it).second->getPlayer();
}

map<int, Player *> Square::getPlayers(void) const
{
    return (m_players);
}