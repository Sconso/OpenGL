/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 16:23:12 by Myrkskog          #+#    #+#             */
/*   Updated: 2014/06/20 16:23:28 by Myrkskog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

#include <Team.h>
#include <Resources.h>

class Player
{
    public:
    Player(int nb, int x, int y, int orientation, int level, Team *team);
    ~Player();
    int getNb(void) const;
    void getPlayer(void) const;
    int getX(void) const;
    int getY(void) const;
    int getTimeout(void) const;
    void setTimeout(int timeout);
    std::string getMsg(void) const;
    std::string getTeam() const;
    void move(int x, int y, int orientation);
    int getLevel(void) const;
    void setLevel(int level);
    void getInventory() const;
    void getInventory(int tab[]) const;
    void starve(void);
    void setInventory(std::vector<std::string> &str);
    void talk(std::string &msg);
      
    private:
    int m_nb;
    int m_x;
    int m_y;
    int m_orientation;
    int m_level;
    Team *m_team;
    Resources *m_inventory;
    
    std::string m_msg;
    int m_msgTimeout;
};

#endif
