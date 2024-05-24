#include <arpa/inet.h>

#include "server_sender.h"

#define MAX_ENEMIES 5

void ServerSender::run() {
    uint8_t enemies_last = MAX_ENEMIES;
    while (!wc) {
        try {
            uint8_t enemies_current = q.pop();
            if (wc) {
                break;
            }
            //pr.send_msg(enemies_current, enemies_last, wc);
        } catch (const ClosedQueue &e) {

        }
    }
}
