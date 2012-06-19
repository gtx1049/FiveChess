#include "aianalyze.h"
#include <iostream>

int AIanalyze::level;

AIanalyze::AIanalyze()
{

}

//初始化分数棋盘, 最顶层
AIanalyze::AIanalyze(ChessBoard *mat, int thetype, int thedeep)
{
    cputype = thetype;
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
    if(thedeep > AIanalyze::level)
    {
        deep = thedeep;
        return;
    }

    cputype = thetype;
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

    currentboard[cp.row][cp.column] = cputype;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            chessboardscore[i][j] += judgeOnePos(i, j, HORIZON, cputype);
            chessboardscore[i][j] += judgeOnePos(i, j, VERTICAL, cputype);
            chessboardscore[i][j] += judgeOnePos(i, j, LEFT, cputype);
            chessboardscore[i][j] += judgeOnePos(i, j, RIGHT, cputype);
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

void AIanalyze::addScore(int score)
{
    scorecount += score;
}

ChessPos AIanalyze::analyzeCurrent()
{
    if(deep > AIanalyze::level)
    {
        return ChessPos(-1, -1);
    }

    int maxcount = LOWEST_NUM;
    ChessPos cp(0, 0);

    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(currentboard[i][j] == EMPTY_CHESS)
            {               

                if(!judgeValue(i, j))
                {
                   continue;
                }

                cp.setPos(i, j);

                int temptype = cputype;
                if(deep % 2 != 0)
                {
                    temptype = -temptype;
                }


                AIanalyze childanalyze(currentboard, temptype, deep + 1, this, ChessPos(i , j));

                childanalyze.analyzeCurrent();

                if(deep != 0)
                {
                    if(deep % 2 == 0)
                    {
                        father->addScore(-this->getScore());
                    }
                }

                if(deep == 0 && childanalyze.getScore() > maxcount)
                {
                    maxcount = childanalyze.getScore();
                    cp.setPos(i, j);
                }
            }
        }
    }



    return cp;
}

int AIanalyze::judgeOnePos(int row, int column, int direction, int type)
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
            if(nowcolumn < 0 || nowrow < 0 || nowrow == BOARD_SIZE || nowcolumn == BOARD_SIZE)
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
            return 128;
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
            return 128;
            case 5:
            return 128;
        }
    }
    return 0;
}

bool AIanalyze::judgeValue(int row, int column)
{
    if(row + 1 != BOARD_SIZE)
    {
        if(currentboard[row + 1][column] != EMPTY_CHESS)
        {
            return true;
        }
    }
    if(row - 1 >= 0)
    {
        if(currentboard[row - 1][column] != EMPTY_CHESS)
        {
            return true;
        }
    }
    if(column + 1 != BOARD_SIZE)
    {
        if(currentboard[row][column + 1] != EMPTY_CHESS)
        {
            return true;
        }
    }
    if(column - 1 >= 0)
    {
        if(currentboard[row][column - 1] != EMPTY_CHESS)
        {
            return true;
        }
    }
    if(column + 1 != BOARD_SIZE && row + 1 != BOARD_SIZE)
    {
        if(currentboard[row + 1][column + 1] != EMPTY_CHESS)
        {
            return true;
        }
    }
    if(column - 1 >= 0 && row - 1 >= 0)
    {
        if(currentboard[row - 1][column - 1] != EMPTY_CHESS)
        {
            return true;
        }
    }
    if(column - 1 >= 0 && row + 1 != BOARD_SIZE)
    {
        if(currentboard[row + 1][column - 1] != EMPTY_CHESS)
        {
            return true;
        }
    }
    if(column + 1 != BOARD_SIZE && row - 1 >= 0)
    {
        if(currentboard[row - 1][column + 1] != EMPTY_CHESS)
        {
            return true;
        }
    }
    return false;
}
