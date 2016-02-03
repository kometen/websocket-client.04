/*
 * ConnectionMedata.hpp
 *
 *  Created on: 02/02/2016
 *      Author: claus
 */

#ifndef CONNECTIONMETADATA_HPP_
#define CONNECTIONMETADATA_HPP_

#include "Common.hpp"

class ConnectionMetadata {
private:
    unsigned int m_id;
    websocketpp::connection_hdl m_hdl;
    std::string m_status;
    std::string m_uri;
    std::string m_server;
    std::string m_error_reason;
    std::vector<std::string> m_messages;

public:
    typedef websocketpp::lib::shared_ptr<ConnectionMetadata> ptr;

    ConnectionMetadata(unsigned int, websocketpp::connection_hdl, std::string);
    void on_open(client*, websocketpp::connection_hdl);
    void on_fail(client*, websocketpp::connection_hdl);
    void on_close(client*, websocketpp::connection_hdl);
    void on_message(websocketpp::connection_hdl, client::message_ptr);
    websocketpp::connection_hdl get_hdl();
    unsigned int get_id();
    std::string get_status() const;
    void record_sent_message(std::string);
    friend std::ostream& operator<<(std::ostream&, ConnectionMetadata const&);

    virtual ~ConnectionMetadata();
};

#endif /* CONNECTIONMETADATA_HPP_ */
