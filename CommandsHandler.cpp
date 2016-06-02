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

/**
 * Classe que pocessa os comandos recebidos
 * 
 */
#include "CommandsHandler.h"
#include "Cliente.hpp"

/**
 * Retorno o enum COmmand correspondente ao comando recebido
 * @param ch, string do comando
 * @return enum command
 */
Commands CommandsHandler::bufferToCommand(char ch[])
{
    std::map<std::string, Commands> mapCommand = {
        {"/help", Commands::HELP},
        {"/exit", Commands::EXIT},
        {"/loggin_hour", Commands::LOOGING_HOUR},
        //{"/server_ip", Commands::SERVER_IP},
        {"/my_ip", Commands::MY_IP},
        {"/server_hour", Commands::SERVER_HOUR},
        {"/server_memory", Commands::SERVER_MEMORY},
        {"/server_hd", Commands::SERVER_HD},
        {"/server_time", Commands::SERVER_TIME},
        {"/server_pro", Commands::SERVER_PRO},
        {"/server_open_ports", Commands::SERVER_OPEN_PORTS}
    };
    return mapCommand[(std::string)ch];

}
 /**
  * Processa o comando e retorna a mensagem correspondente
  * @param cmm string comando
  * @param cli cliente correspondente (alguns comandos usam informaçoes deste)
  * @return mensagem
  */
std::string CommandsHandler::getCommandMessage(Commands cmm, Cliente* cli)
{
    std::string resposta;
    switch ( cmm )
    {
        case Commands::HELP:
            break;
        case Commands::SERVER_HOUR:
            resposta = std::string(CommandsHandler::getDate());
            break;
        case Commands::LOOGING_HOUR:
            resposta = std::string(CommandsHandler::getDate(cli->getClientLogin()));
            break;
        case Commands::MY_IP:
            resposta = cli->getClientIp();
            break;
        case Commands::SERVER_IP:
            resposta = cli->getServerIp();
            break;
        case Commands::SERVER_PORT:
            resposta = ntohs(cli->getClientAddr()->sin_port);
            break;
        case Commands::SERVER_MEMORY:
            resposta = CommandsHandler::getMessage("free -m > temp");
            break;
        case Commands::SERVER_HD:
            resposta = CommandsHandler::getMessage("df -h > temp");
            break;
        case Commands::SERVER_TIME:
            resposta = CommandsHandler::getMessage("uptime > temp");
            break;
        case Commands::SERVER_PRO:
            resposta = CommandsHandler::getMessage("ps -a > temp");
            break;
        case Commands::SERVER_OPEN_PORTS:
            resposta = CommandsHandler::getMessage("netstat -ant > temp");
            break;
        default:
            resposta = std::string(CommandsHandler::getDate());
            break;
    }
    return resposta;
}

/**
 * Recupera commando do sistema retorna a mensagem correspondente
 * @param com string comando
 * @return mensagem
 */
std::string CommandsHandler::getMessage(char* com)
{
    char resposta[1024];
    system(com);
    int pontarq = open("temp", O_RDONLY, 0666);
    if ( pontarq < 0 )
    {
        puts("Erro no arquivo temporario!");
    }
    system("rm -r temp");

    int tbuf = read(pontarq, resposta, sizeof (resposta));
    close(pontarq);
    return std::string(resposta);
}

/**
 * Recupera data atual
 * @return 
 */
const char* CommandsHandler::getDate()
{
    time_t _tm = time(NULL);
    struct tm * curtime = localtime(&_tm);
    return asctime(curtime);
}

/**
 * Retorna data em string de time_t informado
 * @param _tm
 * @return 
 */
const char* CommandsHandler::getDate(time_t _tm)
{
    struct tm * curtime = localtime(&_tm);
    return asctime(curtime);
}