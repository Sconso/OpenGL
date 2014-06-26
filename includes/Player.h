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
    int getNb() const;
    void getPlayer() const;
    int getX() const;
    int getY() const;
    std::string getTeam() const;
    void move(int x, int y, int orientation);
    int getLevel(void) const;
    void setLevel(int level);
    void getInventory() const;
    void getInventory(int tab[]) const;
    void setInventory(std::vector<std::string> &str);
    void talk(std::string msg) const;
      
    private:
    int m_nb;
    int m_x;
    int m_y;
    int m_orientation;
    int m_level;
    Team *m_team;
    Resources *m_inventory;
};

#endif
