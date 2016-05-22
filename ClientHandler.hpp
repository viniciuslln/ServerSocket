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
#include <thread>
#include <sys/socket.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <list>



class ClientHandler {
private:
    std::list <Cliente*>*  clients_list;
public:
    ClientHandler();
    ClientHandler( std::list <Cliente*>* cli );
    ClientHandler(const ClientHandler& orig);
    virtual ~ClientHandler();
    void send( std::list <Cliente*>* clients );

};

#endif /* CLIENTHANDLER_HPP */

