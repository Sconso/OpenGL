// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Team.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2014/06/20 16:24:41 by Myrkskog          #+#    #+#             //
//   Updated: 2014/06/20 16:24:48 by Myrkskog         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <Team.h>
#include <Player.h>
#include <iostream>

using namespace std;

Team::Team(string name) : m_name(name)
{
    cout << "Team " << name << " successfully added !" << endl;
}

string Team::getName() const
{
    return (m_name);
}

void Team::addPlayer(Player *player)
{
    m_players[player->getNb()] = player;
}

void Team::removePlayer(int nb)
{
    map<int, Player *>::iterator it;
    
    it = m_players.find(nb);
    m_players.erase(nb);
}

void Team::listPlayers() const
{
    map<int, Player *>::const_iterator it;
    
    cout << "Players in team " << m_name << ": " << endl;
    for (it = m_players.begin(); it != m_players.end(); ++it)
        (*it).second->getPlayer();
}

int Team::getPoints() const
{
    map<int, Player *>::const_iterator it;
    int points = 0;
    
    for (it = m_players.begin(); it != m_players.end(); ++it)
        points += (*it).second->getLevel();
    return (points);
}