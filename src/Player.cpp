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
#include <Render.h>

using namespace std;

Player::Player(int nb, int x, int y, int orientation, int level, Team *team) :
m_nb(nb), m_x(x), m_y(y), m_orientation(orientation), m_level(level), m_team(team), m_msgTimeout(0)
{
    m_inventory = new Resources();
    m_animation = NULL;
    m_animationFunct = NULL;
    cout << "Player n*" << nb << " successfully added on team " << team->getName() << endl;
}

Player::~Player()
{
    delete m_inventory;
    if (m_animation != NULL)
        delete m_animation;
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

Animation *Player::getAnimation(void) const
{
    return (m_animation);
}

void Player::removeAnimation(void)
{
    if (m_animation != NULL)
    {
        delete m_animation;
        m_animation = NULL;
        m_animationFunct = NULL;
    }
}

int Player::doAnimation(void) const
{
    int ret(0);
    
    if (m_animationFunct != NULL)
        ret = (m_animation->*m_animationFunct)();
    return (ret);
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
    removeAnimation();
    m_animation = new Animation(3, 0.1, 10, 1, 1, 75);
    m_animationFunct = &Animation::levelUpAnimation;
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

void Player::expulse(void)
{
    removeAnimation();
    m_animation = new Animation(3, 0.3, 1, 0.1, 0.3, 150);
    m_animationFunct = &Animation::CircleAnimation;
}

void Player::talk(string &msg)
{
    m_msg = msg;
    m_msgTimeout = 1000;
    cout << "Player " << m_nb << " says : \"" << msg << "\"" << endl;
}

void Player::incantation(int timeUnit)
{
    removeAnimation();
    m_animation = new Animation(1, 0.3, 1, 0.1, 0.3, 75);
    m_animation->setTimeout(126, timeUnit);
    m_animationFunct = &Animation::CircleAnimation;
}
