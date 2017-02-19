#include "http-server.h"

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#include "logging/lexical_cast.h"
#include "logging/logging.h"


void
Request_Handler_Factory::Request_Handler::handleRequest(
        Poco::Net::HTTPServerRequest& request,
        Poco::Net::HTTPServerResponse& response)
{
    response.setContentType(std::string("NO_CONTENT_TYPE"));

    std::ostream& stream = response.send();
    stream << "OK!";

    INFO << "Processed request #" << lexical_cast<std::string>(_request_count++) << ".";
}

Poco::Net::HTTPRequestHandler*
Request_Handler_Factory::createRequestHandler(
        const Poco::Net::HTTPServerRequest & request)
{
    return &_handler;
}

Http_Server::Http_Server(uint16_t port):
    _socket(port),
    _http_server(
        new Request_Handler_Factory,
        _socket,
        new Poco::Net::HTTPServerParams)
{}

