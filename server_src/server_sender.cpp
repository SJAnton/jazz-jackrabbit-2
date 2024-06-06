#include <arpa/inet.h>

#include "server_sender.h"

#define END_BYTE 0xFF

void ServerSender::run() {
    while (!wc) {
        try {
            QueueData data = q.pop();
            if (wc) {
                break;
            }
            pr.send_game_data(data, wc);
        } catch (const ClosedQueue &e) {

        }
    }
}
