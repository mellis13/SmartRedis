/*
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Hewlett Packard Enterprise
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SMARTREDIS_NONKEYEDCOMMAND_H
#define SMARTREDIS_NONKEYEDCOMMAND_H

#include "command.h"

///@file

namespace SmartRedis {

class RedisServer;

/*!
*   \brief The NonKeyedCommand intermediary class constructs Client
*          commands without keys. These commands use db node addresses.
*   \details The KeyedCommand class has multiple methods for dealing
*            with non-keyed commands.
*/
class NonKeyedCommand : public Command
{
    public:
        /*!
        *   \brief Set address and port for command
        *          to be executed on
        *   \param address Address of database
        *   \param port Port of database
        */
        void set_exec_address_port(std::string address,
                                   uint16_t port);

        /*!
        *   \brief Get address that command will be
        *          to be executed on
        *   \return std::string of address
        *           if an address hasn't been set,
        *                 returns an empty string
        */
        std::string get_address();

        /*!
        *   \brief Get port that command will be
        *          to be executed on
        *   \return uint16_t of port
        *           if port hasn't been set, returns 0
        */
        uint16_t get_port();

        virtual CommandReply runme(RedisServer * r) = 0;

    private:
        /*!
        *   \brief Address of database node
        */
        std::string _address;

        /*!
        *   \brief Port of database node
        */
        uint64_t _port;
};

} //namespace SmartRedis

#endif //NONKEYEDCOMMAND