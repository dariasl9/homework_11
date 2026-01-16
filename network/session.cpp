#include "session.hpp"
#include <iostream>

Session::Session(tcp::socket socket, CommandHandler& handler)
    : socket_(std::move(socket)), handler_(handler) {}

void Session::start() {
    read();
}

void Session::read() {
    auto self(shared_from_this());
    asio::async_read_until(socket_, buffer_, '\n',
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::istream is(&buffer_);
                std::string command;
                std::getline(is, command);
                
                if (!command.empty() && command.back() == '\r') {
                    command.pop_back();
                }
                
                std::string response = handler_.handle(command);
                
                asio::async_write(socket_, asio::buffer(response),
                    [this, self](boost::system::error_code ec, std::size_t) {
                        if (!ec) {
                            read();
                        }
                    });
            }
        });
}