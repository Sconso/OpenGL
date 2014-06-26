/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Resources.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 16:23:49 by Myrkskog          #+#    #+#             */
/*   Updated: 2014/06/20 16:24:08 by Myrkskog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCES_H
# define RESOURCES_H

#include <vector>
#include <string>

class Resources
{
    public:
    Resources();
    Resources(std::vector<std::string> &str);
    void setResources(std::vector<std::string> &str);
    void setInventory(std::vector<std::string> &str);
    void getResources() const;
    void getResources(int tab[]) const;
    int getFood(void) const;
    void setFood(int food);
    
    private:
    int m_resources[8];
};

#endif
