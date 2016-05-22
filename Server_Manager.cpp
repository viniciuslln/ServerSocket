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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

Server_Manager::Server_Manager() {}

Server_Manager::Server_Manager(int argc, char *argv[]) {
    
    while(1){
        
        Cliente *client = new Cliente();
        
        int client = socket(AF_INET, SOCK_STREAM, 0);
        
        if (client < 0)
        {
            cout << "Erro ao estabelecer conexão" << endl;
            exit(1);
        }
        
        cout << "Server socket criado" << endl;
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htons(INADDR_ANY);
        server_addr.sin_port = htons(port_number);
        
        //binding
        if(bind(client, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        {
            cout << "Erro bind socket" << endl;
            exit(1);
        }
        
        size = sizeof(server_addr);
        
        cout << "Procurando Cliente" << endl;
        
        listen(client, 0);

        server = accept(client, (struct sockaddr*) &server_addr, &size );
        
        if (server < 0)
        {
            cout << "Erro ao aceitar" << endl;
            exit(1);
        }
        
        strcpy(buffer, "server conncted");
        
        
        
        
        
        
        
        
        
        clients.push_back( client );
        
    }
     
     
     
}

Server_Manager::Server_Manager(const Server_Manager& orig) {
}

Server_Manager::~Server_Manager() {
}

