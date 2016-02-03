//============================================================================
// Name        : 04.cpp
// Author      : Claus Guttesen
// Version     :
// Copyright   : A websocket-server using MS GSL
// Description : Hello World in C++, Ansi-style
//============================================================================

// https://github.com/zaphoyd/websocketpp/blob/master/examples/utility_client/utility_client.cpp

#include "WebsocketEndpoint.hpp"
//#include "ConnectionMetadata.hpp"

std::ostream& operator<<(std::ostream& out, ConnectionMetadata const& data) {
    out << "> URI: " << data.m_uri << std::endl
        << "> Status: " << data.m_status << std::endl
        << "> Remote Server: " << (data.m_server.empty() ? "None Specified" : data.m_server) << std::endl
        << "> Error/close readon: " << (data.m_error_reason.empty() ? "N/A" : data.m_error_reason) << std::endl;
    out << "> Messages Processed: (" << data.m_messages.size() << ")" << std::endl;

    std::vector<std::string>::const_iterator it;
    for (it = data.m_messages.begin(); it != data.m_messages.end(); ++it) {
        out << *it << std::endl;
    }

    return out;
}

using namespace std;

int main() {
	cout << "Blåbærsyltetøj" << endl;
	auto done = false;
	string input;
	WebsocketEndpoint endpoint;

	while (!done) {
	    cout << "Enter Command: ";
	    getline(cin, input);

	    if (input == "quit") {
	        done = true;
	    } else if (input == "help") {
	        cout
	            << endl << "Command List:" << endl
	            << "connect <ws uri>" << endl
	            << "send <connection id> <message>" << endl
	            << "close <connection id> [<close code:default=1000>] [<close reason>" << endl
	            << "show <connection id>" << endl
	            << "help: Display this help text" << endl
	            << "quit: Exit the program" << endl << endl;
	    } else if (input.substr(0,7) == "connect") {
	        int id = endpoint.connect(input.substr(8));
	        if (id != -1) {
	            cout << "Created connection with id " << id << endl;
	        }
	    } else if (input.substr(0,4) == "send") {
	        stringstream ss(input);

	        string cmd;
	        int id;
	        string message {};

	        ss >> cmd >> id;
	        getline(ss, message);

	        endpoint.send(id, message);
	    } else if (input.substr(0,5) == "close") {
	        stringstream ss(input);

	        string cmd;
	        int id;
	        int close_code = websocketpp::close::status::normal;
	        string reason {};
	        ss >> cmd >> id >> close_code;
	    } else if (input.substr(0,4) == "show") {
	        int id = atoi(input.substr(5).c_str());

	        ConnectionMetadata::ptr metadata = endpoint.get_metadata(id);
	        if (metadata) {
	            cout << *metadata << endl;
	        } else {
	            cout << "> Unknown connection id " << id << endl;
	        }
	    } else {
	        cout << "> Unrecognized Command" << endl;
	    }
	}
	return 0;
}
