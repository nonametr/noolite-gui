#ifndef TX1132_H
#define TX1132_H

#include <string>

class Tx1132
{
public:
    Tx1132() = default;
    virtual ~Tx1132() = default;

    bool on(u_char ch_id);
    bool off(u_char ch_id);
    bool switchOnOff(u_char ch_id);
    bool setLvl(u_char ch_id, u_char lvl);
    bool bind(u_char ch_id);
    bool unBind(u_char ch_id);
    bool loadPreset(u_char ch_id);
    bool savePreset(u_char ch_id);
    bool stopChange(u_char ch_id);
    bool rollColor(u_char ch_id);
    bool switchColor(u_char ch_id);
    bool switchMode(u_char ch_id);
    bool switchSpeedChangeColor(u_char ch_id);
    bool setColor(u_char ch_id, u_char r, u_char g, u_char b);

private:
    bool _execute(u_char ch_id);
    unsigned char _action[8] = {0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
};

#endif // TX1132_H
