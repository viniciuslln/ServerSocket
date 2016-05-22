/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Server_Manager.hpp"


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

    Server_Manager *serv = new Server_Manager();
    serv->conectar();
    
    return 0;
}

