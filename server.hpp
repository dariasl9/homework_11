#pragma once

#include <boost/asio.hpp>
#include "database_manager.hpp"
#include "command_handler.hpp"

namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class Server {
public:
    Server(asio::io_context& io_context, short port);
    
private:
    void accept();
    
    asio::io_context& io_context_;
    tcp::acceptor acceptor_;
    DatabaseManager db_manager_;
    CommandHandler command_handler_;
};