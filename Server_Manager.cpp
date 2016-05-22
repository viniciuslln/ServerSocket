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


using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}


Server_Manager::Server_Manager() 
{
    port_number = 6969;
}

Server_Manager::Server_Manager(const Server_Manager& orig) {
}

Server_Manager::~Server_Manager() {
}


void Server_Manager::conectar()
{
    //while(1){
        
        Cliente *client = new Cliente();
        
        int server = socket(AF_INET, SOCK_STREAM, 0);
        
        if (server < 0)
        {
            cout << "Erro ao estabelecer conexão" << endl;
            exit(1);
        }
        
        memset(&server_addr, 0, sizeof(struct sockaddr_in));

        cout << "Server socket criado" << endl;
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htons(INADDR_ANY);
        server_addr.sin_port = htons(port_number);
        
        //binding
        if(bind(server, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        {
            cout << "Erro bind socket" << endl;
            exit(1);
        }
        
        server_size = sizeof(server_addr);
        
        cout << "Procurando Cliente" << endl;
        
        listen(client->get_Client(), 0);

        client->set_Client( accept( server, (struct sockaddr*) client->get_Client_Addr(), client->get_Client_Size() ) );
        
        if (client->get_Client() < 0)
        {
            cout << "Erro ao aceitar" << endl;
            exit(1);
        }
        
        strcpy(buffer, "server conncted");
        
        
        //------------------------------------------
        /*
           int sfd, cfd;
           struct sockaddr_un my_addr, peer_addr;
           socklen_t peer_addr_size;

           sfd = socket(AF_UNIX, SOCK_STREAM, 0);
           if (sfd == -1)
               handle_error(”socket”);

           memset(&my_addr, 0, sizeof(struct sockaddr_un));
           
            //  Clear structure 
           my_addr.sun_family = AF_UNIX;
           strncpy(my_addr.sun_path, MY_SOCK_PATH,
                   sizeof(my_addr.sun_path) - 1);

           if (bind(sfd, (struct sockaddr *) &my_addr,
                   sizeof(struct sockaddr_un)) == -1)
               handle_error(”bind”);

           if (listen(sfd, LISTEN_BACKLOG) == -1)
               handle_error(”listen”);

           /// Now we can accept incoming connections one
           //   at a time using accept(2) 

           peer_addr_size = sizeof(struct sockaddr_un);
           cfd = accept(sfd, (struct sockaddr *) &peer_addr,
                        &peer_addr_size);
           if (cfd == -1)
               handle_error(”accept”);
         
        */
        
           /* Code to deal with incoming connection(s)... */

           /* When no longer required, the socket pathname,
           MY_SOCK_PATH
              should be deleted using unlink(2) or remove(3) */
        
        
       //----------------------------------------- 
        
        //clients.push_back( client );
    //}
}

