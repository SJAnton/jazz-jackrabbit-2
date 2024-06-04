#include <arpa/inet.h>

#include "server_sender.h"

void ServerSender::run() {
    while (!wc) {
        try {
            InfoJuego data = q.pop();
            if (wc) {
                break;
            }
            pr.send_game_data(data, wc);
        } catch (const ClosedQueue &e) {

        }
    }
}
