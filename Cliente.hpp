/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cliente.hpp
 * Author: vinih
 *
 * Created on 21 de Maio de 2016, 23:59
 */

#ifndef CLIENTE_HPP
#define CLIENTE_HPP
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctime>

/**
 * Classe que armazena dados do cliente
 */
class Cliente {
private:
    int client;
    struct sockaddr_in clientAddr;
    struct sockaddr_in serverAddr;
    socklen_t clientSize;
    char* ip;
    bool status;
    time_t logIn;
    time_t logOut;
    
public:
    Cliente();
    Cliente(int, sockaddr_in, socklen_t, sockaddr_in);
    Cliente(const Cliente& orig);
    virtual ~Cliente();
    
    int getClient() {return client;}
    void setClient(int c){ client = c ;}
    
    sockaddr_in* getClientAddr() {return &clientAddr;}
    void setClientAddres(struct sockaddr_in c){ clientAddr = c ;}

    socklen_t* getClientSize() {return &clientSize;}
    void setClientAdressSize(socklen_t c){ clientSize = c; }

    char* getClientIp() { return inet_ntoa(clientAddr.sin_addr);}
    char* getServerIp() { return inet_ntoa(serverAddr.sin_addr);}
    
    bool getClientStatus(){return status;}
    void setClientStatus(bool s){ status = s; }
    
    time_t getClientLogin(){return logIn;}
    void setClientLogin(time_t s){ logIn = s; }
  
    time_t getClientSLogout(){return logOut;}
    void setClientLogout(time_t s){ logOut = s; }
    
};

#endif /* CLIENTE_HPP */

