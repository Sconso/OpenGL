/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 16:17:37 by Myrkskog          #+#    #+#             */
/*   Updated: 2014/06/20 16:17:57 by Myrkskog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H

#include <string>
#include <Resources.h>
#include <Player.h>
#include <map>

class Square
{
    public:
    Square();
    void getResources() const;
    void getResources(int tab[]) const;
    void setResources(std::vector<std::string> &str);
    void addPlayer(Player *player);
    void removePlayer(Player *player);
    void listPlayers(void) const;
    std::map<int, Player *> getPlayers(void) const;
    
    private:
    
    Resources           m_resources;
    std::map<int, Player *> m_players;
};

#endif
