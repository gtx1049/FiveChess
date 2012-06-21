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
    scorecount = 0;

    //对于记分盘的初始化
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            currentboard[i][j] = mat->getChessBoardMat(i, j);
            chessboardscore[i][j][HORIZON] = 0;
            chessboardscore[i][j][VERTICAL] = 0;
            chessboardscore[i][j][LEFT] = 0;
            chessboardscore[i][j][RIGHT] = 0;
        }
    }
    makeDecision();

}

void AIanalyze::makeDecision()
{
    //选择进攻还是防守,当自己存在4，必须进攻
    scorecount = judgeState(cputype);
    if(scorecount == HAS_FOUR)
    {
        AIanalyze::level = 1;
        return;
    }

    int usercount = judgeState(-cputype);
    //当对手存在4，必须防守
    if(usercount == SINGLE_FOUR)
    {
        AIanalyze::level = 2;
        return;
    }

    //当存在二活二，必须防守
    if(usercount == TWO_TWO_ALIVE)
    {
        AIanalyze::level = 2;
        return;
    }

    //对手不存在4，自己有活三，则进攻
    if(scorecount == ALIVE_THREE_SELF)
    {
        AIanalyze::level = 1;
        return;
    }

    //当存在活二加一，必须防守
    if(usercount == TWO_ONE_ALIVE)
    {
        AIanalyze::level = 2;
        return;
    }

    //当对手存在3，必须防守
    if(usercount == ALIVE_THREE)
    {
        AIanalyze::level = 2;
        //cout << "defend alive 3" << endl;
        return;
    }

    //当对手有三活一,必须防守
    if(usercount == THREE_ONE_ALIVE)
    {
        AIanalyze::level = 2;
        cout << "defend alive 3" << endl;
        return;
    }

    //以上条件都不满足时，选择进攻
    AIanalyze::level = 1;
//    if(usercount <= scorecount)
//    {
//        AIanalyze::level = 1;
//    }
//    else
//    {
//        AIanalyze::level = 2;
//    }
}

AIanalyze::AIanalyze(int currentchess[BOARD_SIZE][BOARD_SIZE], int thetype, int thedeep, AIanalyze* thefather, ChessPos cp)
{
    //同样，当层数过大时回退
    if(thedeep > AIanalyze::level)
    {
        deep = thedeep;
        return;
    }

    cputype = thetype;
    father = thefather;
    deep = thedeep;
    scorecount = 0;
    //初始化自己的棋盘
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            currentboard[i][j] = currentchess[i][j];
            chessboardscore[i][j][HORIZON] = 0;
            chessboardscore[i][j][VERTICAL] = 0;
            chessboardscore[i][j][LEFT] = 0;
            chessboardscore[i][j][RIGHT] = 0;
        }
    }

    //预测落子并记分
    currentboard[cp.row][cp.column] = cputype;

    int i = cp.row;
    int j = cp.column;

    //只计算落子位置的分数
    chessboardscore[i][j][HORIZON] = judgeOnePos(i, j, HORIZON, cputype);
    chessboardscore[i][j][VERTICAL] = judgeOnePos(i, j, VERTICAL, cputype);
    chessboardscore[i][j][LEFT] = judgeOnePos(i, j, LEFT, cputype);
    chessboardscore[i][j][RIGHT] = judgeOnePos(i, j, RIGHT, cputype);
    scorecount += (chessboardscore[i][j][HORIZON] + chessboardscore[i][j][VERTICAL] + chessboardscore[i][j][LEFT] + chessboardscore[i][j][RIGHT]);

}

AIanalyze::~AIanalyze()
{
}

int AIanalyze::getScore()
{
    return scorecount;
}

void AIanalyze::setScore(int score)
{
    scorecount = score;
}

ChessPos AIanalyze::analyzeCurrent()
{
    //递归函数，当层数大于定义时退出
    if(deep > AIanalyze::level)
    {
        return ChessPos(-1, -1);
    }

    //记录最大数
    int maxcount = LOWEST_NUM;
    ChessPos cp(0, 0);

    //第一步是否已下，防止不返回落点时，只在初始点出现
    bool firststep = false;

    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(currentboard[i][j] == EMPTY_CHESS)
            {               
                //只判断落子后对局势产生影响的点
                if(!judgeValue(i, j))
                {
                   continue;
                }
                if(!firststep)
                {
                    cp.setPos(i, j);
                    firststep = true;
                }

                //当为用户落子时，棋子类型改为反色
                int temptype = cputype;
                if(deep % 2 != 0)
                {
                    temptype = -temptype;
                }

                //子节点，生成预测后棋盘及局势
                AIanalyze childanalyze(currentboard, temptype, deep + 1, this, ChessPos(i , j));
                //字节点递归调用
                childanalyze.analyzeCurrent();

                if(deep != 0)
                {
                    if(deep % 2 == 0 && this->getScore() > (-father->getScore()))
                    {
                        //maxcount = this->getScore();
                        father->setScore(-this->getScore());
                    }
                }

                //选择最优步
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

    //控制连子是死是活,分为上行和下行
    bool updead = false;
    bool downdead = false;

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
                updead = true;

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
                downdead = true;
                break;
            }
        }

        if(currentboard[nowrow][nowcolumn] == type)
        {
            chesscount++;
        }
        else
        {
            //当两端为对方棋子，根据方向决定死的情况
            if(currentboard[nowrow][nowcolumn] == -type)
            {
                if(upflag)
                {
                    updead = true;
                }
                else
                {
                    downdead = true;
                }
            }


            //判断是否存在三加一
            else if(currentboard[nowrow][nowcolumn] == EMPTY_CHESS && deep == 0)
            {
                int blankX = nowrow + offsetX;
                int blankY = nowcolumn + offsetY;
                if(blankX < BOARD_SIZE && blankX >= 0 && blankY < BOARD_SIZE && blankY >= 0)
                {
                    if(chesscount == 3 && currentboard[blankX][blankY] == -cputype)
                    {
                        return 5;
                    }

                    //判断二活二
                    if(chesscount == 2 && currentboard[blankX][blankY] == -cputype)
                    {
                        int u2to2X = blankX + offsetX;
                        int u2to2Y = blankY + offsetY;
                        if(u2to2X < BOARD_SIZE && u2to2X >= 0 && u2to2Y < BOARD_SIZE && u2to2Y >= 0)
                        {
                            if(currentboard[u2to2X][u2to2Y] == -cputype)
                            {
                                return 9;
                            }
                        }
                    }

                    //判断是否存在二加一
                    if(chesscount == 2 && currentboard[blankX][blankY] == -cputype)
                    {
                        int u2to1X = blankX + offsetX;
                        int u2to1Y = blankY + offsetY;
                        if(u2to1X < BOARD_SIZE && u2to1X >= 0 && u2to1Y < BOARD_SIZE && u2to1Y >= 0)
                        {
                            int u1to2X = nowrow - 3 * offsetX;
                            int u1to2Y = nowcolumn - 3 * offsetY;
                            if(u1to2X < BOARD_SIZE && u1to2X >= 0 && u1to2Y < BOARD_SIZE && u1to2Y >= 0)
                            {
                                if(currentboard[u2to1X][u2to1Y] == EMPTY_CHESS && currentboard[u1to2X][u1to2Y] == EMPTY_CHESS)
                                {
                                    return 7;
                                }
                            }
                        }
                    }
                }

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
    if( (updead && !downdead) || (!updead && downdead))
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
            return 64;
            case 5:
            return 512;
        }
    }
    else if(!updead && !downdead)
    {
        switch(chesscount)
        {
            case 1:
            return 0;
            case 2:
            return 2;
            case 3:
            return 96;
            case 4:
            return 255;
            case 5:
            return 512;
        }
    }
    else if(updead && downdead)
    {
        switch(chesscount)
        {
            case 1:
            return 0;
            case 2:
            return 1;
            case 3:
            return 2;
            case 4:
            return 32;
            case 5:
            return 512;
        }
    }
    return 0;
}

//评估某一点是否值得落子，大大提高了计算速度
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

//判断当前局势的函数，累加所有棋子点的最高分
int AIanalyze::judgeState(int type)
{
    int count = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            chessboardscore[i][j][HORIZON] = judgeOnePos(i, j, HORIZON, type);
            chessboardscore[i][j][VERTICAL] = judgeOnePos(i, j, VERTICAL, type);
            chessboardscore[i][j][LEFT] = judgeOnePos(i, j, LEFT, type);
            chessboardscore[i][j][RIGHT] = judgeOnePos(i, j, RIGHT, type);

            int max = 0;
            for(int q = 0; q < 4; q++)
            {
                if(chessboardscore[i][j][q] > max)
                {
                    max = chessboardscore[i][j][q];
                }
            }

            //当对手存在活三，必须进行防守
            if(type == -cputype)
            {
                for(int q = 0; q < 4; q++)
                {
                    if(chessboardscore[i][j][q] == 96)
                    {
                        return ALIVE_THREE;
                    }
                }
            }

            if(type == -cputype)
            {
                for(int q = 0; q < 4; q++)
                {
                    if(chessboardscore[i][j][q] == 64)
                    {
                        return SINGLE_FOUR;
                    }
                }
            }

            //存在三活一，防守
            if(type == -cputype)
            {
                for(int q = 0; q < 4; q++)
                {
                    if(chessboardscore[i][j][q] == 5)
                    {
                        return THREE_ONE_ALIVE;
                    }
                }
            }

            //二活一
            if(type == -cputype)
            {
                for(int q = 0; q < 4; q++)
                {
                    if(chessboardscore[i][j][q] == 7)
                    {
                        return TWO_ONE_ALIVE;
                    }
                }
            }

            //二活二
            if(type == -cputype)
            {
                for(int q = 0; q < 4; q++)
                {
                    if(chessboardscore[i][j][q] == 9)
                    {
                        return TWO_TWO_ALIVE;
                    }
                }
            }

            //如果我方存在冲四活四，必然进行进攻
            if(type == cputype)
            {
                for(int q = 0; q < 4; q++)
                {
                    if(chessboardscore[i][j][q] == 64 || chessboardscore[i][j][q] == 255)
                    {
                        return HAS_FOUR;
                    }
                }
            }


            //如果我方存在活三，对手没有活三时，则进行进攻
            if(type == cputype)
            {
                for(int q = 0; q < 4; q++)
                {
                    if(chessboardscore[i][j][q] == 96)
                    {
                        return ALIVE_THREE_SELF;
                    }
                }
            }


            count += max;
        }
    }
    return count;
}
