#include "WiCo.h"

void WiCo::startWebServer()
{
    if (isWebserverRunning)
    {
        stopWebServer();
    }
    server = new ESP8266WebServer(80);
    server->begin();
    isWebserverRunning = true;
}

void WiCo::stopWebServer()
{
    if (isWebserverRunning)
    {
        server->close();
        if (server)
        {
            delete server;
            server = nullptr;
        }
    }
    isWebserverRunning = false;
}

void WiCo::handleWebServer()
{
    server->handleClient();
}