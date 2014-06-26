// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Player.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2014/06/20 16:23:37 by Myrkskog          #+#    #+#             //
//   Updated: 2014/06/20 16:23:39 by Myrkskog         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <Player.h>

using namespace std;

Player::Player(int nb, int x, int y, int orientation, int level, Team *team) :
m_nb(nb), m_x(x), m_y(y), m_orientation(orientation), m_level(level), m_team(team)
{
    m_inventory = new Resources();
    cout << "Player n*" << nb << " successfully added on team " << team->getName() << endl;
}

Player::~Player()
{
    delete m_inventory;
}

int Player::getNb() const
{
    return (m_nb);
}

int Player::getX() const
{
    return (m_x);
}

int Player::getY() const
{
    return (m_y);
}

string Player::getTeam() const
{
    return m_team->getName();
}


void Player::getPlayer() const
{
    cout << "Player " << m_nb << ": " << endl;
    cout << "X = " << m_x << " - Y = " << m_y << endl;
    cout << "Orientation : " << m_orientation << endl;
    cout << "Level : " << m_level << endl;
    cout << "Team : " << m_team->getName() << endl;
}

void Player::move(int x, int y, int orientation)
{
    m_x = x;
    m_y = y;
    m_orientation = orientation;
}

int Player::getLevel(void) const
{
    return (m_level);
}

void Player::setLevel(int level)
{
    m_level = level;
}

void Player::getInventory() const
{
    cout << "Inventory of player " << m_nb << ": " << endl;
    m_inventory->getResources();
}

void Player::getInventory(int tab[]) const
{
    m_inventory->getResources(tab);
}

void Player::setInventory(vector<string> &str)
{
    m_inventory->setInventory(str);
}

void Player::talk(string msg) const
{
    cout << "Player " << m_nb << " says : \"" << msg << "\"" << endl;
}