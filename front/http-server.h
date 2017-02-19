#ifndef HTTP_SERVER_H__INCLUDED
#define HTTP_SERVER_H__INCLUDED


#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#include "logging/logging.h"


class Request_Handler_Factory: public Poco::Net::HTTPRequestHandlerFactory
{
    class Request_Handler: public Poco::Net::HTTPRequestHandler
    {
        private:
            uint64_t _request_count;

            virtual void handleRequest(
                    Poco::Net::HTTPServerRequest& request,
                    Poco::Net::HTTPServerResponse& response);
    };

    Request_Handler _handler;

    virtual Poco::Net::HTTPRequestHandler* createRequestHandler(
                const Poco::Net::HTTPServerRequest & request);
};

class Http_Server
{
    private:
        Poco::Net::ServerSocket _socket;
        Poco::Net::HTTPServer _http_server;

    public:
        Http_Server(uint16_t port);
};

#endif  // HTTP_SERVER_H__INCLUDED

