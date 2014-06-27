// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Game.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2014/06/20 15:58:02 by Myrkskog          #+#    #+#             //
//   Updated: 2014/06/20 15:58:05 by Myrkskog         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <gfx.h>
#include <Game.h>
#include <Square.h>
#include <Team.h>
#include <vector>
#include <string>
#include <iostream>
#include <Render.h>

using namespace std;

Game::Game(int width, int height, int socket, int demo) : m_width(width), m_height(height), m_socket(socket), m_demo(demo), m_time(0)
{
    m_map = new Square* [height];
    if (m_map)
    {
        for (int i = 0; i < height; ++i)
        {
            m_map[i] = new Square[width];
            cout << ".";
        }
        cout << endl << "Map succefully created ! (";
        cout << width << " x " << height << ")" << endl;
    }
}

Game::~Game()
{
    for (int i = 0; i < m_height; ++i)
        delete [] m_map[i];
    delete [] m_map;

    map<string, Team*>::iterator it = m_teams.begin();
    if (it != m_teams.end())
    {
        delete it->second;
        m_teams.erase(it);
    }
}

int Game::getDemo(void) const
{
    return (m_demo);
}

void Game::setDemo(int val)
{
    m_demo = val;
}

int Game::getSocket(void) const
{
    return (m_socket);
}

void Game::getSquare(const int x, const int y) const
{
    cout << "Ressources présentes sur la case (" << x << ", " << y << ") : " << endl;
    m_map[y][x].getResources();
}

void Game::getSquare(const int x, const int y, int tab[]) const
{
    m_map[y][x].getResources(tab);
}

void Game::setSquare(const int x, const int y, vector<string> &str)
{
    if (x >= m_width || y >= m_height || x < 0 || y < 0)
        ft_exit("Bad coordinates.");
    m_map[y][x].setResources(str);
    cout << "Resources succefully added on " << x << ", " << y << " !" << endl;
}

void Game::getInventory(int nb)
{
    m_players[nb]->getInventory();
}

void Game::getInventory(int nb, int tab[])
{
    m_players[nb]->getInventory(tab);
}

void Game::setInventory(vector<string> &str)
{
    string tmp = &str[1][1];
    int nb = stoi(tmp.c_str());
    
    m_players[nb]->setInventory(str);
}

int Game::getWidth() const
{
	return (m_width);
}

int Game::getHeight() const
{
	return (m_height);
}

int Game::getTime() const
{
    return (m_time);
}

void Game::setTime(int time)
{
    m_time = time;
    cout << "Time set to 1s / " << m_time << endl;
}

void Game::addTeam(string name)
{
    Team *team = NULL;
    
    team = new Team(name);
    m_teams[name] = team;
}

void Game::listTeams() const
{
    map<string, Team *>::const_iterator it;
    int i = 0;

    cout << "TEAMS :" << endl;
    for (it = m_teams.begin(); it != m_teams.end(); ++it, ++i)
        cout << "Team n*" << i << ": " << (*it).second->getName() << endl;
}

string Game::getTeam(int nb)
{
    return (m_players[nb]->getTeam());
}


void Game::addPlayer(vector<string> &str)
{
    string tmp = &str[1][1];
    int nb = stoi(tmp.c_str());
    int x = stoi(str[2].c_str());
    int y = stoi(str[3].c_str());
    int orientation = stoi(str[4].c_str());
    int level = stoi(str[5].c_str());
    Team *team = m_teams[str[6]];
    m_players[nb] = new Player(nb, x, y, orientation, level, team);
    m_teams[str[6]]->addPlayer(m_players[nb]);
    m_map[y][x].addPlayer(m_players[nb]);
}

void Game::removePlayer(vector<string> &str)
{
    map<int, Player *>::iterator it;
    string tmp = &str[1][1];
    int nb = stoi(tmp.c_str());
    
    it = m_players.find(nb);
    if (it != m_players.end())
    {
        string team = it->second->getTeam();
        int x = it->second->getX();
        int y = it->second->getY();
        
        cout << "Player " << nb << " is dead ..." << endl;
        
        m_teams[team]->removePlayer(nb);
        m_map[y][x].removePlayer(nb);
        delete it->second;
        m_players.erase(it);
    }
}

void Game::listPlayers() const
{
    map<int, Player*>::const_iterator it;
    
    for (it = m_players.begin(); it != m_players.end(); ++it)
        (*it).second->getPlayer();
}

void Game::listPlayers(int x, int y) const
{
    cout << "Players on square (" << x << ", " << y << ") :" << endl;
    m_map[y][x].listPlayers();
}

void Game::listPlayers(string name)
{
    map<string, Team *>::iterator it;
    
    it = m_teams.find(name);
    if (it == m_teams.end())
        cout << "La team " << name << " n'existe pas." << endl;
    else
        m_teams[name]->listPlayers();
}

map<int, Player *> Game::getPlayers(void) const
{
    return (m_players);
}

Player *Game::getPlayer(int nb) const
{
    map<int, Player *>::const_iterator it;
    
    it = m_players.find(nb);
    if (it != m_players.end())
        return (it->second);
    else
        return (NULL);
}

map<int, Player *> Game::getPlayers(int x, int y) const
{
    return (m_map[y][x].getPlayers());
}

map<string, Team *> Game::getTeams(void) const
{
    return (m_teams);
}


void Game::movePlayer(vector<string> &str)
{
    string tmp = &str[1][1];
    int nb = stoi(tmp.c_str());
    int x = stoi(str[2].c_str());
    int y = stoi(str[3].c_str());
    int orientation = stoi(str[4].c_str());
    
    m_map[m_players[nb]->getY()][m_players[nb]->getX()].removePlayer(m_players[nb]);
    m_map[y][x].addPlayer(m_players[nb]);
    m_players[nb]->move(x, y, orientation);

    cout << "Player " << nb << " moved to (" << x << ", " << y << ")." << endl;
}

void Game::starvePlayers(void)
{
    map<int, Player *>::iterator it;
    
    for (it = m_players.begin(); it != m_players.end(); ++it)
        it->second->starve();
}

void Game::setLevel(vector<string> &str)
{
    string tmp = &str[1][1];
    int nb = stoi(tmp.c_str());
    int level = stoi(str[2].c_str());
    
    m_players[nb]->setLevel(level);
}

int Game::getLevel(int nb)
{
    return (m_players[nb]->getLevel());
}

void Game::expulse(vector<string> &str)
{
    string tmp = &str[1][1];
    int nb = stoi(tmp.c_str());
    
    m_players[nb]->expulse();
}

void Game::incantation(vector<string> &str)
{
    string tmp = &str[4][1];
    int nb = stoi(tmp.c_str());
    
    m_players[nb]->incantation(m_time);
}

void Game::broadcast(vector<string> &str)
{
    string tmp = &str[1][1];
    string msg;
    int nb = stoi(tmp.c_str());
    
    for (unsigned long i = 2; i < str.size(); ++i)
    {
        if (i > 2)
            msg += " ";
        msg += str[i];
    }
    
    m_players[nb]->talk(msg);
}

void Game::win(string &team)
{
    Render::Win(team);
}