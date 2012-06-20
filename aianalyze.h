#ifndef AIANALYZE_H
#define AIANALYZE_H

#include"chessboard.h"
#include"const.h"
#include"struct.h"

class AIanalyze
{
public:
    AIanalyze();
    AIanalyze(ChessBoard*, int, int);
    AIanalyze(int[BOARD_SIZE][BOARD_SIZE], int, int, AIanalyze*, ChessPos);
    ~AIanalyze();
    int getScore();
    void setScore(int);
    ChessPos analyzeCurrent();
private:
    int judgeOnePos(int row, int column, int direction, int type);
    bool judgeValue(int row, int colum);
    int judgeState(int type);
private:
    AIanalyze* father;
    int chessboardscore[BOARD_SIZE][BOARD_SIZE][4];
    int currentboard[BOARD_SIZE][BOARD_SIZE];
    ChessPos nowchess;
    int scorecount;
    int deep;
    int cputype;
public:
    static int level;
};

#endif // AIANALYZE_H
