import argparse
from enum import Enum

parser = argparse.ArgumentParser()
parser.add_argument("--ch", type=int, help="rx channel", required=True)
parser.add_argument("--act", type=int, help="action", required=True)
parser.add_argument("--togl", type=int, help="togl input data value")
parser.add_argument("--df", type=int, help="data format")
parser.add_argument("--arg_1", type=int, help="input argument 1")
parser.add_argument("--arg_2", type=int, help="input argument 2")
parser.add_argument("--arg_3", type=int, help="input argument 3")
parser.add_argument("--arg_4", type=int, help="input argument 4")
args = parser.parse_args()

class ACTION(Enum):
    TURN_OFF = 0
    SLOW_TURN_OFF =1
    TURN_ON = 2
    SLOW_TURN_ON = 3
    SWITCH = 4
    REVERT_SLOW_TURN = 5
    SET_LEVEL = 6
    RUN_SCENE = 7
    RECORD_SCENE = 8
    UNBIND = 9
    STOP_DIM_BRIGHT = 10
    BIND = 15
    SLOW_RGB_CHANGE = 16
    SWITCH_COLOR = 17
    SWITCH_MODE = 18
    SWITCH_SPEED_MODE = 19
    BATTERY_LOW = 20
    TEMPERATURE = 21

    def __int__(self):
        return self.value

class RX_DEVICE(Enum):
    LIVING_ROOM_CTL = 0
    WORK_PLACE_CTL = 1
    UNKNOWN_PLACE_2 = 2
    UNKNOWN_PLACE_3 = 3
    UNKNOWN_PLACE_4 = 4
    BATHROOM_CTL = 5
    BATHROOM_FAN_CTL = 6
    KITCHEN_CTL = 7
    BALCONY_CTL = 8
    CORRIDOR_CTL = 9
    BOILER_CTL = 10
    CONDITIONING_CTL = 11

    def __int__(self):
        return self.value

print(RX_DEVICE(args.ch))
if ( args.ch == RX_DEVICE.LIVING_ROOM_CTL.value ) :
    print("doing action in => ", RX_DEVICE.LIVING_ROOM_CTL)