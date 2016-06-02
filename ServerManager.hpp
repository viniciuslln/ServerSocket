/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Server_Manager.hpp
 * Author: vinih
 *
 * Created on 21 de Maio de 2016, 21:40
 */

#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <list>
#include <chrono>
#include <ctime>
#include <thread>
#include "Cliente.hpp"
#include "ClientHandler.hpp"

#define buf_size 1024

class ServerManager {
public:
    ServerManager();
    ServerManager(int argc, char *argv[]);
    ServerManager(char * port);
    virtual ~ServerManager();
    static std::list<Cliente*> clients;

    void conectar();

private:

    int num;
    int server;
    int port_number;
    char buffer[buf_size];
    std::list<ClientHandler*>* clientsHandlerList;
   // std::list<std::thread>* threads_list;

    struct sockaddr_in server_addr;
    socklen_t server_size;



};

#endif /* SERVER_MANAGER_HPP */

