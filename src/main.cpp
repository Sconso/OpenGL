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
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/select.h>

using namespace std;

int			create_socket(string addr, int port)
{
	int					sock;
	struct sockaddr_in	sin;
    struct hostent      *hostinfo;
	struct protoent		*proto;

    
	if (!(proto = getprotobyname("tcp")))
    {
        cout << "\033[31mProto error.\033[0m" << endl;
		return (-1);
    }
    if ((sock = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
    {
        cout << "\033[31mSock error.\033[0m" << endl;
        return (-1);
    }
    if ((hostinfo = gethostbyname(addr.c_str())) == NULL)
    {
        cout << "\033[31mThe host " << addr << " doesn't exist.\033[0m" << endl;
        return (-1);
    }
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr.c_str());
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
        cout << "\033[31mConnect error.\033[0m" << endl;
        return (-1);
    }
	return (sock);
}

void        manager(vector<string> &msg, Game *game)
{
    if (game)
    {
        if (msg[0] == "bct")
            game->setSquare(stoi(msg[1].c_str()), stoi(msg[2].c_str()), msg);
        else if (msg[0] == "tna")
            game->listPlayers(msg[1]);
        else if (msg[0] == "pnw")
            game->addPlayer(msg);
        else if (msg[0] == "ppo")
            game->movePlayer(msg);
        else if (msg[0] == "plv")
            game->setLevel(msg);
        else if (msg[0] == "pin")
            game->setInventory(msg);
        else if (msg[0] == "pex")
            game->expulse(msg);
        else if (msg[0] == "pbc")
            game->broadcast(msg);
        else if (msg[0] == "pic")
            game->incantation(msg);
        else if (msg[0] == "pdi")
            game->removePlayer(msg);
        else if (msg[0] == "sgt")
            game->setTime(stoi(msg[1].c_str()));
        else if (msg[0] == "seg")
            game->win(msg[1]);
    }
    msg.clear();
}

Game        *initGame(int ac, char **av)
{
    int             sock;
    int             port;
    int             sel;
    string          host;
    string          str = "none";
    struct timeval  timeout;
    fd_set          read;
    Game            *game;
    vector<string>  elems;

    port = stoi(av[1]);
    host = (ac < 3 ? "127.0.0.1" : av[2]);
    host = (host == "localhost" ? "127.0.0.1" : host);
    timeout.tv_sec = 0;
    timeout.tv_usec = 10000;
   
    if ((sock = create_socket(host, port)) == -1)
        return (NULL);
    
    cout << "\033[32mConnected to " << host << ":" << port << "\033[0m" << endl;
    
    FD_ZERO(&read);
    FD_SET(sock, &read);
    
    while ((sel = select(sock + 1, &read, NULL, NULL, &timeout)) > 0)
    {
        read_server(sock, str);
        split(str, ' ', elems);
        if (elems[0] == "msz")
        {
            game = new Game(stoi(elems[1].c_str()), stoi(elems[2].c_str()), sock);
            str = "msz";
            write_server(sock, str);
        }
        else
            manager(elems, game);
    }

    if (sel == -1 || str == "none")
    {
        cout << "\033[31mServer error, can't receive informations.\033[0m" << endl;
        return (NULL);
    }
    
    str = "GRAPHIC\n";
    write_server(sock, str);
    
    game = new Game(20, 20, sock);
    return (game);
}

void        askServer(Game *game)
{
    int             sock;
    int             sel;
    fd_set          read;
    vector<string>  elems;
    string          str;
    struct timeval  timeout;
    
    sock = game->getSocket();
    FD_ZERO(&read);
    FD_SET(sock, &read);
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    
    if ((sel = select(sock + 1, &read, NULL, NULL, &timeout)) > 0)
    {
        read_server(sock, str);
        split(str, ' ', elems);
        manager(elems, game);
    }
    if (sel == -1)
    {
        cout << "\033[31mServer seems to be closed, exiting.\033[0m" << endl;
        exit(0);
    }
}

int			main(int ac, char **av)
{
	Game            *game = NULL;
    vector<string>  elems;
    
    if (ac < 2)
    {
        cout << "Usage : " << av[0] << " <port> [hostname]" << endl;
        return (1);
    }
    
    if (!(game = initGame(ac, av)))
        return (-1);

    game->setTime(100);
    game->addTeam("sconso");
    game->addTeam("gpetrov");
    game->addTeam("ebaudet");
    game->listTeams();

    split("lol #1 2 3 2 1 gpetrov", ' ', elems);
    game->addPlayer(elems);
    elems.clear();
    split("lol #2 3 5 1 5 sconso", ' ', elems);
    game->addPlayer(elems);
    elems.clear();
    split("lol #3 2 5 2 5 sconso", ' ', elems);
    game->addPlayer(elems);
    elems.clear();
    split("lol #42 14 5 1 5 gpetrov", ' ', elems);
    game->addPlayer(elems);
    elems.clear();
    split("lol #4 10 13 2 1 ebaudet", ' ', elems);
    game->addPlayer(elems);
    elems.clear();
    split("lol #5 12 9 2 1 ebaudet", ' ', elems);
    game->addPlayer(elems);
    elems.clear();
    split("lol #6 2 15 2 1 ebaudet", ' ', elems);
    game->addPlayer(elems);
    elems.clear();
    
  
    game->listPlayers("sconso");
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
        game->setSquare(stoi(elems[1].c_str()), stoi(elems[2].c_str()), elems);
    elems.clear();
    split("bct 4 19 32 5 45 2 32 53 21\n", ' ', elems);
    if (elems[0] == "bct")
        game->setSquare(stoi(elems[1].c_str()), stoi(elems[2].c_str()), elems);

    game->getSquare(0, 0);
    game->getSquare(2, 0);
    game->getSquare(4, 19);
    
    elems.clear();

    split("lol #42 Salut les pucelles !", ' ', elems);
    game->broadcast(elems);
    elems.clear();
    
//    split("pic 5 6 1 #6 #5", ' ', elems);
//    manager(elems, game);
    
    Render::newWindow(ac, av, 1280, 700, "Zappy::GFX", game);
    Render::enableAA();
    Render::mainLoop();
    
	delete game;
	return (0);
}
