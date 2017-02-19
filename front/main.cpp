#include <iostream>
#include <string>

#include "http-server.h"


using std::string;


int main(int argc, char* argv[], char* env[])
{
    if (argc < 2)
    {
        ERROR << "No arguments were provied.";
        return -1;
    }

    if (argc != 2)
    {
        ERROR << "Usage: " << argv[0] << " <port>";
        return -2;
    }

    int64_t port = lexical_cast<int64_t>(argv[1]);

    if ((port < 0) || (port > (64 << 10)))
    {
        ERROR << "Port has to be a number between 0 and 65536.";
        return -3;
    }

    INFO << "Starting service on port: " << lexical_cast<string>(port);

    try {
        INFO << "Press ENTER.";
        string line;
        std::getline(std::cin, line);
    } catch (Poco::Exception e) {
        ERROR
            << "An exception with code " << lexical_cast<string>(int64_t(e.code()))
            << " has been raised.  " << e.displayText() << ".";
    }

    return 0;
}

