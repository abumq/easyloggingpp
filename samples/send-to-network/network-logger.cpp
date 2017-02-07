 //
 //
 // This file is part of Easylogging++ samples
 // Send to network log
 //
 // Revision 1.0
 // @author mkhan3189
 //
 // Compile: g++ network-logger.cpp easylogging++.cc -o bin/network-logger.cpp.bin -std=c++11 -pthread -I /opt/local/include -L/opt/local/lib -lboost_system -Wno-deprecated-declarations
 //

#include "easylogging++.h"

#include <boost/asio.hpp>

INITIALIZE_EASYLOGGINGPP


// Following Client struct adapted from http://stackoverflow.com/questions/27672591/boost-asio-send-and-receive-messages
struct Client
{
    boost::asio::io_service& io_service;
    boost::asio::ip::tcp::socket socket;

    Client(boost::asio::io_service& svc, std::string const& host, std::string const& port) 
        : io_service(svc), socket(io_service) 
    {
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::iterator endpoint = resolver.resolve(boost::asio::ip::tcp::resolver::query(host, port));
        boost::asio::connect(this->socket, endpoint);
    };

    void send(std::string const& message) {
        socket.send(boost::asio::buffer(message));
    }
};

class NetworkDispatcher : public el::LogDispatchCallback
{
public:
	// Setters
	void setHost(const std::string& host) {
		m_host = host;
	}
	void setPort(int port) {
		m_port = port;
	}
protected:
  void handle(const el::LogDispatchData* data) noexcept override
  {
	  m_data = data;
	  // Dispatch using default log builder of logger
	  dispatch(m_data->logMessage()->logger()->logBuilder()->build(m_data->logMessage(),
	             m_data->dispatchAction() == el::base::DispatchAction::NormalLog));
  }
private:
  const el::LogDispatchData* m_data;
  std::string m_host;
  int m_port;
  
  void dispatch(el::base::type::string_t&& logLine) noexcept
  {
	  boost::asio::io_service svc;
	  Client client(svc, m_host, std::to_string(m_port));

	  client.send(logLine);
  }
};


int main() {
	    el::Helpers::installLogDispatchCallback<NetworkDispatcher>("NetworkDispatcher");
		// Set server params
		NetworkDispatcher* dispatcher = el::Helpers::logDispatchCallback<NetworkDispatcher>("NetworkDispatcher");
		dispatcher->setEnabled(true);
		dispatcher->setHost("127.0.0.1");
		dispatcher->setPort(9090);
		
		// Start logging and normal program...
		LOG(INFO) << "First network log";
		
		// You can even use a different logger, say "network" and send using a different log pattern
}