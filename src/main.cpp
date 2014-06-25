// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2014/06/20 13:10:10 by Myrkskog          #+#    #+#             //
//   Updated: 2014/06/20 14:19:39 by Myrkskog         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <gfx.h>
#include <iostream>
#include <Game.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <Render.h>

using namespace std;

int			main(int ac, char **av)
{
	Game            *game = NULL;
    vector<string>  elems;
    
	game = new Game(19, 20);
    game->setTime(100);
    game->addTeam("Blabla");
    game->addTeam("LesConnards");
    game->addTeam("Banane");
    game->listTeams();

    split("lol #1 2 3 2 1 LesConnards", ' ', elems);
    game->addPlayer(elems);
    elems.clear();
    split("lol #2 3 5 1 5 Blabla", ' ', elems);
    game->addPlayer(elems);
    elems.clear();
    split("lol #3 2 5 2 5 Blabla", ' ', elems);
    game->addPlayer(elems);
    elems.clear();
    split("lol #42 14 5 1 5 Blabla", ' ', elems);
    game->addPlayer(elems);
    elems.clear();
    split("lol #4 10 13 2 1 Banane", ' ', elems);
    game->addPlayer(elems);
    elems.clear();
    split("lol #5 12 9 2 1 Banane", ' ', elems);
    game->addPlayer(elems);
    elems.clear();
    split("lol #6 2 15 2 1 Banane", ' ', elems);
    game->addPlayer(elems);
    elems.clear();
    
    game->listPlayers("Blabla");
    game->listPlayers("Blabokhfa");
    game->listPlayers("LesConnards");

    game->listPlayers(14, 5);
    game->listPlayers(1, 4);

    split("lol #42 1 4 2\n", ' ', elems);
    game->movePlayer(elems);
    elems.clear();

    game->listPlayers(14, 5);
    game->listPlayers(1, 4);
    
    split("lol #2 2 4 5 1 3 5 1\n", ' ', elems);
    game->setInventory(elems);
    elems.clear();
    game->getInventory(2);
    game->getInventory(3);
    
    split("bct 0 0 2 4 5 1 3 5 1\n", ' ', elems);
    if (elems[0] == "bct")
        game->setSquare(atoi(elems[1].c_str()), atoi(elems[2].c_str()), elems);
    elems.clear();
    split("bct 4 19 32 5 45 2 32 53 21\n", ' ', elems);
    if (elems[0] == "bct")
        game->setSquare(atoi(elems[1].c_str()), atoi(elems[2].c_str()), elems);

    game->getSquare(0, 0);
    game->getSquare(2, 0);
    game->getSquare(4, 19);
    
    elems.clear();

    split("lol #42 Salut les pucelles !", ' ', elems);
    game->broadcast(elems);
    elems.clear();
        
    Render::newWindow(ac, av, 1280, 700, "Zappy::GFX", game);
    Render::enableAA();
    Render::mainLoop();
    
	delete game;
	return (0);
}
