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
#include <ctime>

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
            game->addTeam(msg[1]);
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
    {
        cout << "Can't create socket." << endl;
        return (NULL);
    }
    
    cout << "\033[32mConnected to " << host << ":" << port << "\033[0m" << endl;
    
    FD_ZERO(&read);
    FD_SET(sock, &read);

    str = "GRAPHIC\n";
    write_server(sock, str);

    while ((sel = select(sock + 1, &read, NULL, NULL, &timeout)) > 0)
    {
        read_server(sock, str);
        split(str, ' ', elems);
        if (elems[0] == "msz")
            game = new Game(stoi(elems[1].c_str()), stoi(elems[2].c_str()), sock, 0);
        else
            manager(elems, game);
        elems.clear();
    }

    if (sel == -1 || str == "none")
    {
        cout << "\033[31mServer error, can't receive informations.\033[0m" << endl;
        return (NULL);
    }
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

void        demo_mode(Game *game)
{
    vector<string> elems;
    
    game->setTime(100);

    game->addTeam("sconso");
    game->addTeam("gpetrov");
    game->addTeam("ebaudet");
    game->addTeam("wbeets");
    
    split("pnw #1 2 3 2 1 gpetrov", ' ', elems);
    manager(elems, game);
    split("pnw #2 14 5 1 5 gpetrov", ' ', elems);
    manager(elems, game);
    split("pnw #3 3 5 1 5 sconso", ' ', elems);
    manager(elems, game);
    split("pnw #4 2 4 2 5 sconso", ' ', elems);
    manager(elems, game);
    split("pnw #5 8 12 18 5 sconso", ' ', elems);
    manager(elems, game);
    split("pnw #6 10 13 2 1 ebaudet", ' ', elems);
    manager(elems, game);
    split("pnw #7 12 9 2 1 ebaudet", ' ', elems);
    manager(elems, game);
    split("pnw #8 2 15 2 1 ebaudet", ' ', elems);
    manager(elems, game);
    split("pnw #42 18 5 2 5 wbeets", ' ', elems);
    manager(elems, game);

    split("pin #1 245 4 5 1 3 5 1\n", ' ', elems);
    manager(elems, game);
    split("pin #2 620 1 3 6 8 5 1\n", ' ', elems);
    manager(elems, game);
    split("pin #3 20 9 7 3 5 3 2\n", ' ', elems);
    manager(elems, game);
    split("pin #4 2 8 5 11 2 56 2\n", ' ', elems);
    manager(elems, game);
    split("pin #5 142 4 5 2 7 9 3\n", ' ', elems);
    manager(elems, game);
    split("pin #6 69 4 4 7 3 5 6\n", ' ', elems);
    manager(elems, game);
    split("pin #7 19 1 2 3 4 5 6\n", ' ', elems);
    manager(elems, game);
    split("pin #8 79 6 5 4 3 2 1\n", ' ', elems);
    manager(elems, game);
    split("pin #42 463 4 2 1 6 3 1\n", ' ', elems);
    manager(elems, game);
    
    for (int y = 0; y < game->getHeight(); ++y)
    {
        for (int x = 0; x < game->getWidth(); ++x)
        {
            if (rand() % 2)
            {
                string str = "bct " + to_string(x) + " " + to_string(y) + " 1 1 1 1 1 1 1\n";
                split(str, ' ', elems);
                manager(elems, game);
            }
        }
    }
}

int			main(int ac, char **av)
{
	Game            *game = NULL;
    vector<string>  elems;
    int            demo(0);
    
    if (ac == 2)
    {
        string str = av[1];
        if (str == "-demo")
        {
            demo = 1;
            game = new Game(20, 20, 0, demo);
        }
    }
    else if (ac < 2)
    {
        cout << "Usage : " << av[0] << " <port> [hostname]" << endl;
        return (1);
    }
    
    if (demo == 0 && !(game = initGame(ac, av)))
    {
        cout << "Server error." << endl;
        return (-1);
    }
    
    srand(time(0));
    if (demo)
        demo_mode(game);

    Render::newWindow(ac, av, 1280, 700, "Zappy::GFX", game);
    Render::enableAA();
    Render::mainLoop();
    
	delete game;
	return (0);
}
