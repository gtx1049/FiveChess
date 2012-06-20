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

    //选择进攻还是防守
    scorecount = judgeState(cputype);
    if(scorecount == HAS_FOUR)
    {
        AIanalyze::level = 1;
        return;
    }

    int usercount = judgeState(-cputype);
    if(usercount == ALIVE_THREE)
    {
        AIanalyze::level = 2;
        return;
    }

    if(usercount == SINGLE_FOUR)
    {
        AIanalyze::level = 2;
        return;
    }

    if(scorecount == ALIVE_THREE_SELF)
    {
        AIanalyze::level = 1;
        return;
    }

    if(scorecount == 0)
    {
        AIanalyze::level = 1;
        return;
    }

    if(usercount <= scorecount)
    {
        AIanalyze::level = 1;
    }
    else
    {
        AIanalyze::level = 2;
    }
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
    return 0;
}

//评估某一点是否值得落子
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
            if(max >= 96 && type == -cputype)
            {
                return ALIVE_THREE;
            }

            if(max == 64 && type == -cputype)
            {
                return SINGLE_FOUR;
            }

            //如果我方存在冲四活四，必然进行进攻
            if((max == 64 || max == 255) && type == cputype)
            {
                return HAS_FOUR;
            }

            //如果我方存在活三，对手没有或三时，则进行进攻
            if(max == 96 && type == cputype)
            {
                return ALIVE_THREE_SELF;
            }

            count += max;
        }
    }
    return count;
}
