/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cliente.cpp
 * Author: vinih
 * 
 * Created on 21 de Maio de 2016, 23:59
 */

#include "Cliente.hpp"

Cliente::Cliente() {
}
Cliente::Cliente(int cli, sockaddr_in soc_add, socklen_t soc_len, sockaddr_in server_addr) {
    this->client = cli;
    this->clientAddr = soc_add;
    this->serverAddr = server_addr;
    this->clientSize = soc_len;
    
    this->logIn = time(0);
    this->status = true;
}

Cliente::Cliente(const Cliente& orig) {
}

Cliente::~Cliente() {
}

