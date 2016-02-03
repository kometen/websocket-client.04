/*
 * WebsocketEndpoint.h
 *
 *  Created on: 03/02/2016
 *      Author: claus
 */

#ifndef WEBSOCKETENDPOINT_HPP_
#define WEBSOCKETENDPOINT_HPP_

#include "Common.hpp"
#include "ConnectionMetadata.hpp"

class WebsocketEndpoint {
private:
    typedef std::map<unsigned int, ConnectionMetadata::ptr> con_list;
    client m_endpoint;
    websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_thread;
    con_list m_connection_list;
    unsigned int m_next_id;

public:
    WebsocketEndpoint();
    virtual ~WebsocketEndpoint();
    int connect(std::string const&);
    void close(unsigned int, websocketpp::close::status::value, std::string);
    void send(unsigned int, std::string);
    ConnectionMetadata::ptr get_metadata(unsigned int) const;
};

#endif /* WEBSOCKETENDPOINT_HPP_ */
