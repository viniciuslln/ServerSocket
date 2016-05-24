/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Utils.cpp
 * Author: vinih
 * 
 * Created on 24 de Maio de 2016, 10:13
 */

#include "Utils.h"

    const char* Utils::getDate()
    {
        time_t _tm = time(NULL);
        struct tm * curtime = localtime(&_tm);
        return asctime(curtime);
    }
