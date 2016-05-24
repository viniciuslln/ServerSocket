/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CommandsHandler.cpp
 * Author: vinih
 * 
 * Created on 24 de Maio de 2016, 09:19
 */

#include "CommandsHandler.h"
#include "Utils.h"

Commands CommandsHandler::bufferToCommand(char ch[])
{
    std::map<std::string, Commands> mapCommand = {
        {"/help", Commands::HELP},
        {"/system_hour", Commands::SYSTEM_HOUR},
        {"/exit", Commands::EXIT}
    };
    return mapCommand[(std::string)ch];

}

std::string CommandsHandler::getCommandMessage(Commands cmm)
{

    std::string  resposta; 
    switch ( cmm )
    {
        case Commands::HELP:
                        resposta = std::string(Utils::getDate());
            break;
        case Commands::SYSTEM_HOUR:
            resposta = std::string(Utils::getDate());
            break;
        default:
                        resposta = std::string(Utils::getDate());
            break;
    }
    return resposta;
}



