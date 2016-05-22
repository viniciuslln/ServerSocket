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

#define buf_size 256
#define handle_error(msg) \
           do { perror(msg); /*exit(EXIT_FAILURE);*/ } while (0)

void ClientHandler::send( std::list <Cliente*>* clients )
{
    char buffer[buf_size];
    while(1)
    {
        std::cout<<"Send to : " << clients->size() << "Clients" << std::endl;

        for( auto current : *clients)
        {
            strcpy(buffer, "=> Server connected...\n");

                if (write(current->get_Client(),buffer,buf_size) < 0) 
                {
                    handle_error("write");
                    break;
                }           

                if ( recv(current->get_Client(), buffer, buf_size, 0) < 0) 
                {
                    handle_error("recv");
                    break;
                }

                printf("%s\n",buffer);
        }
            std::this_thread::sleep_for (std::chrono::seconds(5));
    }
    

}

ClientHandler::ClientHandler()
{
}

ClientHandler::ClientHandler(std::list <Cliente*>* cli)
{
    clients_list = cli;
    try
    {
        std::thread (&ClientHandler::send, this, clients_list ).detach();
    }
    catch(const std::exception &ex)
    {
        std::cerr << "Thread exited with exception: " << ex.what() << "\n";
    } 
}

ClientHandler::ClientHandler(const ClientHandler& orig)
{
}

ClientHandler::~ClientHandler()
{
}

