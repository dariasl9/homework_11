#include "server.hpp"
#include "session.hpp"

Server::Server(asio::io_context& io_context, short port)
    : io_context_(io_context)
    , acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
    , command_handler_(db_manager_) {
    accept();
}

void Server::accept() {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket), command_handler_)->start();
            }
            accept();
        });
}