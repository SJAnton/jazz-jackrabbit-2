#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include "../common_src/thread.h"
#include "interfaz_grafica.h"

class EventHandler : public Thread
{
private:
    ClientPlayer &cliente;
    InterfazGrafica &interfaz;
    
public:
    EventHandler(InterfazGrafica &interfaz, ClientPlayer &clientPlayer);

    void run() override;
};


#endif
