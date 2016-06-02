/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClientHandler.cpp
 * Author: vinih
 * 
 * Created on 22 de Maio de 2016, 13:54
 */

#include "ClientHandler.hpp"
#include "CommandsHandler.h"


ClientHandler::ClientHandler()
{
}

/**
 * Construtor 
 * @param cli cliente atual da execuçãp
 */
ClientHandler::ClientHandler(Cliente* cli)
{
    this->client = cli;
    try
    {
    /**
    * Inicia a thread
     * detach permite a execução independente
    */
    std::thread(&ClientHandler::threadSendRecieve, this).detach(); 
    } catch ( const std::exception &ex )
    {
        std::cerr << "Thread exited with exception: " << ex.what() << "\n";
    }
}

/**
 * TESTE, NAO É USADO
 * @param cli
 */
ClientHandler::ClientHandler(std::list <Cliente*>* cli)
{
    clients_list = cli;
    try
    {
        std::thread(&ClientHandler::sendLoop, this, clients_list).detach();
    } catch ( const std::exception &ex )
    {
        std::cerr << "Thread exited with exception: " << ex.what() << "\n";
    }
}

ClientHandler::ClientHandler(const ClientHandler& orig)
{
}

ClientHandler::~ClientHandler()
{
    delete( this->client);
}

const char* getDate(time_t _tm)
{
    struct tm * curtime = localtime(&_tm);
    return asctime(curtime);
}

/**
 * Commando principal realizado pela thread
 * Responsavel por enviar e receber dados ao cliente
 */
void ClientHandler::threadSendRecieve()
{
    /*
     *Variavel para realizar interrupção do programa 
     *caso haja erro ou termino da conexao
     */
    bool finalize = false;
    /*
     * declarando buffers
     * 
     * bufferCommand ( Buffer que envia os comandos. Pequeno com 256bytes )
     * 
     * bufferMessage ( Buffer que envia recebe as mensagens. Maior com 1024bytes )
     * 
     */
    char bufferCommand[COMMANDS_BUFFER_SIZE];
    char bufferMessage[MESSAGE_BUFFER_SIZE];

    /*
    *Enviando mensagem de confirmação
    *Assim que conectado servidor manda mensagem da data/hora de conexão
    */    
    strcpy(bufferMessage, "Client connected at:  ");
    strcat(bufferMessage, getDate(client->getClientLogin()));

    if ( send(client->getClient(), bufferMessage, MESSAGE_BUFFER_SIZE, 0) < 0 )
        perror("send");

    std::cout << "Sended to Client: " << bufferMessage << std::endl;
    /*
    * Escreve zeros no buffer(previne erros)
    */
    bzero(bufferMessage, MESSAGE_BUFFER_SIZE);

    do
    {
        /*
        * Recebe comando do servidor e printa na tela
        */
        int r = recv(client->getClient(), bufferCommand, COMMANDS_BUFFER_SIZE, 0);
        /*
         * Verifica retorno do recv
         * se < 0 erro! encerra o programa
         * se = 0 Cliente desconectado!
         * senão continua execução
        */
        if ( r < 0 )
            perror("recv");
        else if ( r == 0 )
        {
            std::cerr << "Client: " << client->getClient() << " ip: " << client->getClientIp() << " O bytes recieved, DESCONECTED" << std::endl;
            finalize = true;
        } else
        {
            std::cout << "Recieve from Client: " << client->getClient() << " ip: " << client->getClientIp() << bufferCommand << std::endl;
            /*
             * Recupera enum do comando recebido
             */ 
            Commands command = CommandsHandler::bufferToCommand(bufferCommand);
            
            /*
            * Escreve zeros no buffer(previne erros)
            */
            bzero(bufferCommand, COMMANDS_BUFFER_SIZE);

            /*
             * Se for comando de encerramento o cliente é fechado
             * senao continua 
             */
            if ( command == Commands::EXIT )
            {
                std::cerr << "Client: " << client->getClient() << " ip: " << client->getClientIp() << " DESCONECTED" << std::endl;
                finalize = true;
            } else
            {
                /*
                 * Recupera e copia a menssagem para o buffer
                 */
                strcpy(bufferMessage, CommandsHandler::getCommandMessage(command, this->client).c_str());

                /*
                * Mensagem é enviado para cliente
                */
                if ( send(client->getClient(), bufferMessage, MESSAGE_BUFFER_SIZE, 0) < 0 )
                    perror("send");

                std::cout << "Sended request to Client: " << client->getClient() << " ip: " << client->getClientIp() << std::endl;
                /*
                * Escreve zeros no buffer(previne erros)
                */
                bzero(bufferMessage, MESSAGE_BUFFER_SIZE);

            }
        }
    } while ( !finalize );

    /**
     *Realiza desconexão 
     */
    closeConnection();

}

/**
 * Realiza desconexão
 */
void ClientHandler::closeConnection()
{
    close(client->getClient());
    client->setClientStatus(false);
    client->setClientLogout(time(0));
}

/**
 * TESTE, NÃO É USADO
 * @param clients
 */
void ClientHandler::sendLoop(std::list <Cliente*>* clients)
{
    //    char buffer_out[buf_size];
    //    char buffer_in[buf_size];
    //
    //    while ( 1 )
    //    {
    //        std::cout << "Send to : " << clients->size() << " Clients" << std::endl;
    //
    //        for ( auto current : *clients )
    //        {
    //            std::cout << "Sending to : " << current->getClient() << " ip: " << inet_ntoa(current->getClientAddr()->sin_addr) << std::endl;
    //
    //            strcpy(buffer_out, "=> Server connected...\n");
    //           /// strcat(buffer_out, Utils::getDate());
    //
    //            if ( write(current->getClient(), buffer_out, buf_size) < 0 )
    //            {
    //                perror("write");
    //                break;
    //            }
    //
    //            if ( recv(current->getClient(), buffer_in, buf_size, 0) < 0 )
    //            {
    //                perror("recv");
    //                break;
    //            }
    //
    //            printf("%s\n", buffer_in);
    //        }
    //        std::this_thread::sleep_for(std::chrono::seconds(5));
    //    }
}

