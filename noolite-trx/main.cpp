#include <iostream>
#include <libusb-1.0/libusb.h>
#include <chrono>
#include <thread>

#include "rx2164.h"
#include "tx1132.h"
#include "loger.h"
#include "defs.h"

using namespace std;

void onEvent(int new_togl, int action, int channel, int data_format)
{
}


int main(int argc, char *argv[])
{
    if(argc >= 2 && string(argv[1]) == "-tx")
    {
        Tx1132 tx;
        return tx.runCmd(argc, argv);
    }

    RX2164 rx;

    std::function<void(int, int, int, int)> callback = std::bind(&onEvent,
                                                std::placeholders::_1, std::placeholders::_2,
                                                std::placeholders::_3, std::placeholders::_4);

    map<channelId, map<actionId, RxActionData>> _channel_actions;
    for(int ch_id = 0; ch_id < 64; ++ch_id)
    {
        for(int act_id = 0; act_id < 32; ++act_id)
        {
            _channel_actions[ch_id][act_id].script = "python3 /home/nonametr/Projects/noolite-trx/noolite-myhome/kv59.py";
            _channel_actions[ch_id][act_id].fw = true;
            _channel_actions[ch_id][act_id].fw_ext = true;
        }
    }
    rx.init(_channel_actions, callback);

    if(rx.open() != RX2164_STATE::OPENED)
    {
        traceError("Failed to open RX device");
        return 0;
    }
    if(rx.start() != RX2164_STATE::LOOPING)
    {
        traceError("Failed to start quering loop on RX device");
        return 0;
    }

    traceNotice("Press enter to exit...");

    this_thread::sleep_for(std::chrono::seconds(1000000));

    return 1;
}
