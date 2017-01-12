#include "tx1132.h"
#include <libusb-1.0/libusb.h>

#define DEV_VID 0x16c0 //0x5824
#define DEV_PID 0x05df //0x1503
#define DEV_CONFIG 1
#define DEV_INTF 0

bool Tx1132::on(u_char ch_id)
{
    _action[1] = 2;

    return _execute(ch_id);
}

bool Tx1132::off(u_char ch_id)
{
    _action[1] = 0;

    return _execute(ch_id);
}

bool Tx1132::switchOnOff(u_char ch_id)
{
    _action[1] = 4;

    return _execute(ch_id);
}

bool Tx1132::setLvl(u_char ch_id, u_char lvl)
{
    _action[1] = 6;
    _action[2] = 1;
    _action[5]= lvl;

    return _execute(ch_id);
}

bool Tx1132::bind(u_char ch_id)
{
    _action[1] = 15;

    return _execute(ch_id);
}

bool Tx1132::unBind(u_char ch_id)
{
    _action[1] = 9;

    return _execute(ch_id);
}

bool Tx1132::loadPreset(u_char ch_id)
{
    _action[1] = 7;

    return _execute(ch_id);
}

bool Tx1132::savePreset(u_char ch_id)
{
    _action[1] = 8;

    return _execute(ch_id);
}

bool Tx1132::stopChange(u_char ch_id)
{
    _action[1] = 10;

    return _execute(ch_id);
}

bool Tx1132::rollColor(u_char ch_id)
{
    _action[1] = 16;
    _action[2] = 4;

    return _execute(ch_id);
}

bool Tx1132::switchColor(u_char ch_id)
{
    _action[1] = 17;
    _action[2] = 4;

    return _execute(ch_id);
}

bool Tx1132::switchMode(u_char ch_id)
{
    _action[1] = 18;
    _action[2] = 4;

    return _execute(ch_id);
}

bool Tx1132::switchSpeedChangeColor(u_char ch_id)
{
    _action[1] = 19;
    _action[2] = 4;

    return _execute(ch_id);
}

bool Tx1132::setColor(u_char ch_id, u_char r, u_char g, u_char b)
{
    _action[1] = 6;
    _action[2] = 3;
    _action[5] = r;
    _action[6] = g;
    _action[7] = b;

    return _execute(ch_id);
}

bool Tx1132::_execute(u_char ch_id)
{
    int ret;
    _action[4] = ch_id;

    libusb_init(NULL);
    libusb_set_debug(NULL, 3);
     libusb_device_handle *handle = libusb_open_device_with_vid_pid(NULL, DEV_VID, DEV_PID);
     if (handle == NULL) {
         perror("Can't open noolite `Tx` device");
         libusb_exit(NULL);
         return false;
     }
     if (libusb_kernel_driver_active(handle,DEV_INTF))
          libusb_detach_kernel_driver(handle, DEV_INTF);
     if ((ret = libusb_set_configuration(handle, DEV_CONFIG)) < 0)
     {
          perror("Failed to configure device");
          libusb_close(handle);
          libusb_exit(NULL);
          if (ret == LIBUSB_ERROR_BUSY)
              printf("B\n");
          printf("ret:%i\n", ret);
          return 0;
     }
     if (libusb_claim_interface(handle,  DEV_INTF) < 0)
     {
          perror("Failed to claim interface!");
          libusb_close(handle);
          libusb_exit(NULL);
          return 0;
     }

     ret = libusb_control_transfer(handle, LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE|LIBUSB_ENDPOINT_OUT, 0x9, 0x300, 0, _action, 8, 100);

     libusb_attach_kernel_driver(handle, DEV_INTF);
     libusb_close(handle);
     libusb_exit(NULL);
     return true;
}
