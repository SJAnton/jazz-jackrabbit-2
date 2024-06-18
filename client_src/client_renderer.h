#ifndef CLIENT_RENDERER_H_
#define CLIENT_RENDERER_H_

#include "interfaz_src/interfaz_grafica.h"
#include "../common_src/thread.h"


class ClientRenderer : public Thread {
    private:
        InterfazGrafica* interfaz;

    public:
        ClientRenderer(InterfazGrafica* interfaz);

        virtual void run() override;
};

#endif