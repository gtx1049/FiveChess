#ifndef CONST_H
#define CONST_H
#include <QtNetwork>
/*
  所有的常数在此定义
*/

const int BOARD_SIZE = 15;

const int BLACK_CHESS = 1;
const int WHITE_CHESS = -1;
const int EMPTY_CHESS = 0;

const bool VICTORY = true;
const bool CONTINUE = false;

const int HORIZON = 0;
const int VERTICAL = 1;
const int LEFT = 2;
const int RIGHT = 3;

const int BOARD_GRID_SIZE = 28;
const int BOARD_OFFSET_X = 85 - (BOARD_GRID_SIZE >> 1);
const int BOARD_OFFSET_Y = 135 - (BOARD_GRID_SIZE >> 1);
const int BOARD_PIX_SIZE = BOARD_GRID_SIZE * (BOARD_SIZE + 1);

const int LOCAL_SINGLE = 1;
const int LOCAL_MUTI = 2;
const int NET_MUTI = 3;
const int NONE_GAME = 4;

const int LOWEST_NUM = -9999999;
const int ALIVE_THREE = -1;
const int HAS_FOUR = -2;
const int ALIVE_THREE_SELF = -3;
const int SINGLE_FOUR = -4;
const int THREE_ONE_ALIVE = -5;
const int TWO_ONE_ALIVE = -6;
const int TWO_TWO_ALIVE = -7;

const int NETNUMBER = 6666;
const int HOSTNUMBER = 5555;

const quint16 CONNECT = 1;
const quint16 JOIN = 2;
const quint16 DOWN = 3;
const quint16 UNDO = 4;
const quint16 LIST = 5;
const QString NETIP = "localhost";
#endif // CONST_H
