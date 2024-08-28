#include "WiCo.h"

void WiCo::setWebStructure()
{
    if (!isWebserverRunning)
        return;

    server->on("/", []() {});
}