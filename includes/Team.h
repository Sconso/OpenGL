/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Team.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 16:24:22 by Myrkskog          #+#    #+#             */
/*   Updated: 2014/06/20 16:24:36 by Myrkskog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEAM_H
# define TEAM_H

#include <map>
#include <string>

class Player;
class Team
{
    public:
    Team(std::string name);
    std::string getName() const;
    void addPlayer(Player *player);
    void removePlayer(int nb);
    void listPlayers() const;
    int getPoints() const;
      
    private:
    
    std::string m_name;
    std::map<int, Player*> m_players;
};

#endif
