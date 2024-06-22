#include <arpa/inet.h>

#include "server_sender.h"

void ServerSender::run() {
    while (!wc) {
        try {
            //bool local_wc = wc.load();
            InfoJuego data;// = q.pop();
            if (q.try_pop(data) ){
                pr.send_game_data(data, wc);
            }
            //std::cout << "sender..." << std::endl;
            if (wc) {
                break;
            }
            
        } catch (const ClosedQueue &e) {
            wc = true;
            std::cout << "Queue cecrrada en ServerSender::run" << std::endl; 
        }
    }
}
