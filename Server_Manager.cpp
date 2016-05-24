/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Server_Manager.cpp
 * Author: vinih
 * 
 * Created on 21 de Maio de 2016, 21:40
 */

#include "Server_Manager.hpp"
#include "ClientHandler.hpp"


#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

Server_Manager::Server_Manager()
{
    clients = new std::list<Cliente*>();
    clientsHandlerList = new std::list<ClientHandler*>();

    port_number = 6969;

    server_size = sizeof (server_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_number);

}

Server_Manager::Server_Manager(char* port)
{
    clients = new std::list<Cliente*>();
    clientsHandlerList = new std::list<ClientHandler*>();

    port_number = atoi(port);

    server_size = sizeof (server_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_number);

}

Server_Manager::Server_Manager(const Server_Manager& orig)
{
}

Server_Manager::~Server_Manager()
{
}

void Server_Manager::conectar()
{

    int server = socket(AF_INET, SOCK_STREAM, 0); //IPPROTO_TCP);

    if ( server < 0 )
    {
        cout << "Erro ao estabelecer conexão" << endl;
        exit(1);
    }

    cout << "Server socket criado" << endl;

    //binding
    if ( bind(server, ( struct sockaddr* ) &server_addr, server_size) < 0 )
    {
        handle_error("bind");
        cout << "Erro bind socket" << endl;
        exit(1);
    }


    cout << "Procurando Cliente, port number: " << port_number << endl;


    if ( listen(server, 0) == -1 )
        handle_error("listen");


    //ClientHandler* ch = new ClientHandler(clients);


    while ( 1 )
    {
        int cli;
        struct sockaddr_in cli_addr;
        socklen_t cli_size = sizeof (struct sockaddr_in);

        cout << "Aceitando Cliente " << port_number << endl;

        cli = accept(server, ( struct sockaddr * ) &cli_addr, &cli_size);

        if ( cli < 0 )
        {
            handle_error("accept");
            cout << "Erro ao aceitar" << endl;
            exit(1);
        }

        Cliente *client = new Cliente(cli, cli_addr, cli_size);
        
        clientsHandlerList->push_back(new ClientHandler(client) );
        clients->push_back(client);


    }


}

