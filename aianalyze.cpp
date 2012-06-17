#include "aianalyze.h"
#include <iostream>

int AIanalyze::level;

AIanalyze::AIanalyze()
{

}

//初始化分数棋盘, 最顶层
AIanalyze::AIanalyze(ChessBoard *mat, int thetype, int thedeep)
{
    type = thetype;
    father = NULL;
    deep = thedeep;

    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            currentboard[i][j] = mat->getChessBoardMat(i, j);
        }
    }
}

AIanalyze::AIanalyze(int currentchess[BOARD_SIZE][BOARD_SIZE], int thetype, int thedeep, AIanalyze* thefather, ChessPos cp)
{
    type = thetype;
    father = thefather;
    deep = thedeep;
    scorecount = 0;

    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            currentboard[i][j] = currentchess[i][j];
            chessboardscore[i][j] = 0;
        }
    }

    currentboard[cp.row][cp.column] = type;

    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            chessboardscore[i][j] += judgeOnePos(i, j, HORIZON);
            std::cout << chessboardscore[i][j] << "h  ";
            chessboardscore[i][j] += judgeOnePos(i, j, VERTICAL);
            std::cout << chessboardscore[i][j] << "v  ";
            chessboardscore[i][j] += judgeOnePos(i, j, LEFT);
            std::cout << chessboardscore[i][j] << "l  ";
            chessboardscore[i][j] += judgeOnePos(i, j, RIGHT);
            std::cout << chessboardscore[i][j] << "r  " << endl;
            scorecount += chessboardscore[i][j];
        }
    }
}

AIanalyze::~AIanalyze()
{
}

int AIanalyze::getScore()
{
    return scorecount;
}

ChessPos AIanalyze::analyzeCurrent()
{
    int maxcount = 0;
    ChessPos cp;

    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(currentboard[i][j] == EMPTY_CHESS)
            {
                AIanalyze childanalyze(currentboard, type, deep + 1, father, ChessPos(i , j));
                if(childanalyze.getScore() > maxcount)
                {
                    maxcount = childanalyze.getScore();
                    cp.setPos(i, j);
                }
            }
        }
    }
    return cp;
}

int AIanalyze::judgeOnePos(int row, int column, int direction)
{
    if(currentboard[row][column] != type)
    {
        return 0;
    }

    //控制连子是死是活
    bool isdead = false;

    int nowrow = row;
    int nowcolumn = column;
    int offsetX = 0;
    int offsetY = 0;
    //不同的方向决定不同的偏移量
    switch(direction)
    {
        case HORIZON:
            offsetX = -1;
            break;
        case VERTICAL:
            offsetY = -1;
            break;
        case LEFT:
            offsetX = 1;
            offsetY = -1;
            break;
        case RIGHT:
            offsetX = -1;
            offsetY = -1;
            break;
    }

    //跳进循环
    bool countflag = true;
    bool upflag = true;
    int chesscount = 1;
    while(countflag)
    {
        nowrow += offsetX;
        nowcolumn += offsetY;
        //当向上时
        if(upflag)
        {
            //棋盘边缘，标志为死
            if(nowcolumn < 0 || nowrow < 0)
            {
                isdead = true;

                upflag = false;
                offsetY = -offsetY;
                offsetX = -offsetX;
                //返回原来位置
                nowrow = row;
                nowcolumn = column;
                continue;
            }
        }
        else
        {
            //在下方向时标志边缘为死
            if(nowcolumn == BOARD_SIZE || nowrow == BOARD_SIZE)
            {
                isdead = true;
                break;
            }
        }

        if(currentboard[nowrow][nowcolumn] == type)
        {
            chesscount++;
        }
        else
        {
            if(currentboard[nowrow][nowcolumn] == -type)
            {
                isdead = true;
            }

            if(!upflag)
            {
                break;
            }
            upflag = false;
            offsetX = -offsetX;
            offsetY = -offsetY;
            nowrow = row;
            nowcolumn = column;
        }
    }

    //记分标准
    if(isdead)
    {
        switch(chesscount)
        {
            case 1:
            return 0;
            case 2:
            return 1;
            case 3:
            return 4;
            case 4:
            return 8;
            case 5:
            return 64;
        }
    }
    else
    {
        switch(chesscount)
        {
            case 1:
            return 0;
            case 2:
            return 2;
            case 3:
            return 16;
            case 4:
            return 32;
            case 5:
            return 64;
        }
    }
    return 0;
}
