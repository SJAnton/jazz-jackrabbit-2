#include <arpa/inet.h>

#include "server_sender.h"

#define MSG_SIZE 5

void ServerSender::run() {
    while (!wc) {
        try {
            std::vector<uint8_t> data;
            for (int i = 0; i < MSG_SIZE; i++) {
                data.push_back(q.pop());
            }
            if (wc) {
                break;
            }
            pr.send_msg(data, wc);
        } catch (const ClosedQueue &e) {

        }
    }
}
