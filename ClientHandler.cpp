/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClientHandler.cpp
 * Author: vinih
 * 
 * Created on 22 de Maio de 2016, 13:54
 */

#include "ClientHandler.hpp"
#include "CommandsHandler.h"



#define buf_size 1024
#define handle_error(msg) \
           do { perror(msg); /*exit(EXIT_FAILURE);*/ } while (0)

ClientHandler::ClientHandler()
{
}

ClientHandler::ClientHandler(Cliente* cli)
{
    this->client = cli;
    std::thread(&ClientHandler::threadSendRecieve, this).detach();
}

ClientHandler::ClientHandler(std::list <Cliente*>* cli)
{
    clients_list = cli;
    try
    {
        std::thread(&ClientHandler::sendLoop, this, clients_list).detach();
    }    catch ( const std::exception &ex )
    {
        std::cerr << "Thread exited with exception: " << ex.what() << "\n";
    }
}

ClientHandler::ClientHandler(const ClientHandler& orig)
{
}

ClientHandler::~ClientHandler()
{
    delete( this->client);
}

void ClientHandler::threadSendRecieve()
{
    bool finalize = false;
    char bufferCommand[COMMANDS_BUFFER_SIZE];
    char bufferMessage[MESSAGE_BUFFER_SIZE];

    do
    {
        //TODO trocar para receber enum Commands ao inves do comando
        int r = recv(client->getClient(), bufferCommand, COMMANDS_BUFFER_SIZE, 0);
        if ( r < 0 )
            handle_error("recv");
        else if ( r == 0 )
        {
            std::cerr << "Client: "<< client->getClient() << " ip: "<< client->getClientIp() <<" O bytes recieved, probably desconected" << std::endl;
            finalize = true;
        }
        else
        {
            std::cout<< "Recieve from Client: "<< client->getClient() << " ip: "<< client->getClientIp() << bufferCommand << std::endl;
            Commands command = CommandsHandler::bufferToCommand(bufferCommand);
            bzero(bufferCommand, COMMANDS_BUFFER_SIZE);

            if ( command == Commands::EXIT )
            {
                 finalize = true;   
            } else
            {
                strcpy(bufferMessage, CommandsHandler::getCommandMessage(command, this->client).c_str());
                
                if ( send(client->getClient(), bufferMessage, MESSAGE_BUFFER_SIZE, 0) < 0 )
                    handle_error("send");
                
                std::cout<< "Sended request to Client: "<< client->getClient() << " ip: "<< client->getClientIp() << std::endl;
                bzero(bufferMessage, MESSAGE_BUFFER_SIZE);

            }
        }
    } while ( !finalize );

    closeConnection();
    
}

void ClientHandler::closeConnection()
{
    close(client->getClient());
    client->setClientStatus(false);
    client->setClientLogout(time(0));
}


void ClientHandler::sendLoop(std::list <Cliente*>* clients)
{
    char buffer_out[buf_size];
    char buffer_in[buf_size];

    while ( 1 )
    {
        std::cout << "Send to : " << clients->size() << " Clients" << std::endl;

        for ( auto current : *clients )
        {
            std::cout << "Sending to : " << current->getClient() << " ip: " << inet_ntoa(current->getClientAddr()->sin_addr) << std::endl;

            strcpy(buffer_out, "=> Server connected...\n");
           /// strcat(buffer_out, Utils::getDate());

            if ( write(current->getClient(), buffer_out, buf_size) < 0 )
            {
                handle_error("write");
                break;
            }

            if ( recv(current->getClient(), buffer_in, buf_size, 0) < 0 )
            {
                handle_error("recv");
                break;
            }

            printf("%s\n", buffer_in);
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

