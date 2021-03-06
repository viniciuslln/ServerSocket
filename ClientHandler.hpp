/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClientHandler.hpp
 * Author: vinih
 *
 * Created on 22 de Maio de 2016, 13:54
 */

#ifndef CLIENTHANDLER_HPP
#define CLIENTHANDLER_HPP

#include "Cliente.hpp"
#include "Commands.hpp"
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <list>
#include <ctime>


class ClientHandler {
private:
    Cliente* client;
    std::list <Cliente*>*  clients_list;
    void threadSendRecieve();
    void closeConnection();
public:
    ClientHandler();
    ClientHandler(Cliente*);
    ClientHandler( std::list <Cliente*>* cli );
    ClientHandler(const ClientHandler& orig);
    virtual ~ClientHandler();
    void sendLoop( std::list <Cliente*>* clients );

};

#endif /* CLIENTHANDLER_HPP */

