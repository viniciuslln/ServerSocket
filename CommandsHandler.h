/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CommandsHandler.h
 * Author: vinih
 *
 * Created on 24 de Maio de 2016, 09:19
 */

#ifndef COMMANDSHANDLER_H
#define COMMANDSHANDLER_H

#include "Commands.hpp"
#include "Cliente.hpp"
#include <map>
#include <string>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
class CommandsHandler {
public:
    static Commands bufferToCommand(char ch[]);
    static std::string getCommandMessage(Commands cmm, Cliente* cli);
   
private:
    static const char* getDate();
    static std::string getMessage(char* );    
    static const char* getDate(time_t);
    
};

#endif /* COMMANDSHANDLER_H */

