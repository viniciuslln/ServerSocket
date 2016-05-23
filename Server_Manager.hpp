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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <list>
#include "Cliente.hpp"

#define buf_size 1024

class Server_Manager {
public:
    Server_Manager();
    Server_Manager(int argc, char *argv[]);
    Server_Manager(const Server_Manager& orig);
    virtual ~Server_Manager();

    void conectar();

private:

    int num;
    int server;
    int port_number;
    char buffer[buf_size];
    std::list<Cliente*>* clients;

    struct sockaddr_in server_addr;
    socklen_t server_size;



};

#endif /* SERVER_MANAGER_HPP */

