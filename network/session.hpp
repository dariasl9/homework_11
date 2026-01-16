#pragma once

#include <boost/asio.hpp>
#include <memory>
#include "command_handler.hpp"

namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket, CommandHandler& handler);
    void start();

private:
    void read();
    
    tcp::socket socket_;
    asio::streambuf buffer_;
    CommandHandler& handler_;
};