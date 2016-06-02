/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ServerManager.hpp"


/* 
 * File:   main.cpp
 * Author: vinih
 *
 * Created on 21 de Maio de 2016, 21:39
 */

#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    /**
     * instanciando objeto para ServerManager
     */
    ServerManager *serv;

    /*
     *Recuperando porta de conexão dos args 
     */
    if (argc <= 1)
        serv = new ServerManager();
    else
        serv = new ServerManager(argv[2]);
    
    /**
     * Inicia servidor
     */
    serv->conectar();
    
    return 0;
}

