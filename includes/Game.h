/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 15:58:28 by Myrkskog          #+#    #+#             */
/*   Updated: 2014/06/20 15:58:45 by Myrkskog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

#include <Square.h>
#include <Player.h>
#include <Team.h>
#include <string>
#include <vector>
#include <map>

class Game
{
    public:
    
    Game(int width, int height, int socket, int demo);
    ~Game();
    
    int getDemo(void) const;
    void setDemo(int val);
    int getSocket(void) const;
    
    void getSquare(const int x, const int y) const;
    void getSquare(const int x, const int y, int tab[]) const;
    void setSquare(const int x, const int y, std::vector<std::string> &str);
    
    void getInventory(int nb);
    void getInventory(int nb, int tab[]);
    void setInventory(std::vector<std::string> &str);

    
    int getTime() const;
    void setTime(int time);
   	int getWidth() const;
	int getHeight() const;
    void addTeam(std::string name);
    void listTeams() const;
    std::string getTeam(int nb);
    void addPlayer(std::vector<std::string> &str);
    void removePlayer(std::vector<std::string> &str);
    void listPlayers() const;
    void listPlayers(int x, int y) const;
    void listPlayers(std::string name);
    std::map<int, Player *> getPlayers(void) const;
    Player *getPlayer(int nb) const;
    std::map<int, Player *> getPlayers(int x, int y) const;
    std::map<std::string, Team *> getTeams(void) const;
    void movePlayer(std::vector<std::string> &str);
    void starvePlayers(void);
    void setLevel(std::vector<std::string> &str);
    int getLevel(int nb);
    void expulse(std::vector<std::string> &str);
    void broadcast(std::vector<std::string> &str);
    void incantation(std::vector<std::string> &str);
    void win(std::string &team);
    
    private:
    
    int m_width;
    int m_height;
    int m_socket;
    int m_demo;
    Square **m_map;
    int m_time;
    std::map<std::string, Team *> m_teams;
    std::map<int, Player *> m_players;
};

#endif
