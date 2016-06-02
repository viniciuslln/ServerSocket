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

#include "ServerManager.hpp"
#include "ClientHandler.hpp"

using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

/**
 * Construtor com porta padrão
 */
ServerManager::ServerManager()
{
    //clients = new std::list<Cliente*>();
    clientsHandlerList = new std::list<ClientHandler*>();//armazena os ClientHandler da execução

    port_number = 6969;

    
    /*
     *Declarando variaveis de endereço
     */
    server_size = sizeof (server_addr);
    server_addr.sin_family = AF_INET; //IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; //Ip da maquina
    server_addr.sin_port = htons(port_number); 

}
/**
 * COnstrutor com porta informada
 * @param port numero da porta
 */
ServerManager::ServerManager(char* port)
{
    clientsHandlerList = new std::list<ClientHandler*>();//armazena os ClientHandler da execução

    port_number = atoi(port);

    /*
     *Declarando variaveis de endereço
     */
    server_size = sizeof (server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_number);

}

ServerManager::~ServerManager()
{
}

/**
 * Realiza dota operação do servidor
 */
void ServerManager::conectar()
{

    /**
     * Declarando descritor de arquivo do servidor, cria socket e verificando erro
     */
    int server = socket(AF_INET, SOCK_STREAM, 0); //IPPROTO_TCP);
    if ( server < 0 )
    {
        cout << "Erro ao estabelecer conexão" << endl;
        exit(1);
    }

    cout << "Server socket criado" << endl;

    /**
     * Realisa o bind e verifica erros
     */
    if ( bind(server, ( struct sockaddr* ) &server_addr, server_size) < 0 )
    {
        perror("bind");
        cout << "Erro bind socket" << endl;
        exit(1);
    }


    cout << "Listen Clients, port number: " << port_number << endl;


    /**
     * Realisa o bind e verifica erros
     */
    if ( listen(server, 0) == -1 )
        perror("listen");


    //ClientHandler* ch = new ClientHandler(clients);

    /**
     * aceita clientes continuamente
     */
    while ( 1 )
    {
        /*
        *Declarando descritor de arquivo do cliente
        * e suas variaveis de endereço
        */
        int cli;
        struct sockaddr_in cli_addr;
        socklen_t cli_size = sizeof (struct sockaddr_in);

        /**
         * Aguarda e aceita cliente
         * verifica erros
         */
        cli = accept(server, ( struct sockaddr * ) &cli_addr, &cli_size);
        if ( cli < 0 )
        {
            perror("accept");
            cout << "Erro ao aceitar" << endl;
            exit(1);
        }

        /**
         * Cria novo objeto Cliente
         */
        Cliente *client = new Cliente(cli, cli_addr, cli_size, server_addr );
        
        cout << "Connected Client: " << client->getClient() << " IP: " << client->getClientIp() << endl;
        
        /**
         * começa operação
         */
        clientsHandlerList->push_back(new ClientHandler(client) );

    }


}

