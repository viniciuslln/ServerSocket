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

class Cliente {
private:
    int client;
    struct sockaddr_in client_addr;
    socklen_t client_size;
    
public:
    Cliente();
    Cliente(const Cliente& orig);
    virtual ~Cliente();
    
    int get_Client() {return client;}
    void set_Client(int c){ client = c }
    
    struct sockaddr_in get_Client_Addr() {return client_addr;}
    void set_Client(struct sockaddr_in c){ client_addr = c }

    int get_Client_Size() {return client_size;}
    void set_Client(socklen_t c){ client_size = c }

};

#endif /* CLIENTE_HPP */

