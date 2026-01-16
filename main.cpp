#include <iostream>
#include <boost/asio.hpp>
#include "server.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: join_server <port>\n";
        return 1;
    }
    
    try {
        short port = std::stoi(argv[1]);
        asio::io_context io_context;
        Server server(io_context, port);
        
        std::cout << "Server started on port " << port << std::endl;
        io_context.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}