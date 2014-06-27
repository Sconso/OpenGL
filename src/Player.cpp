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
#include <GLUT/glut.h>

using namespace std;

Player::Player(int nb, int x, int y, int orientation, int level, Team *team) :
m_nb(nb), m_x(x), m_y(y), m_orientation(orientation), m_level(level), m_team(team), m_msgTimeout(0)
{
    m_inventory = new Resources();
    cout << "Player n*" << nb << " successfully added on team " << team->getName() << endl;
}

Player::~Player()
{
    delete m_inventory;
}

int Player::getNb(void) const
{
    return (m_nb);
}

int Player::getX(void) const
{
    return (m_x);
}

int Player::getY(void) const
{
    return (m_y);
}

int Player::getTimeout(void) const
{
    return (m_msgTimeout);
}

void Player::setTimeout(int timeout)
{
    m_msgTimeout = timeout;
}

string Player::getMsg(void) const
{
    return (m_msg);
}

string Player::getTeam(void) const
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

void Player::starve(void)
{
    m_inventory->setFood(m_inventory->getFood() - 1);
}

void Player::talk(string &msg)
{
    m_msg = msg;
    m_msgTimeout = 100;
    cout << "Player " << m_nb << " says : \"" << msg << "\"" << endl;
}