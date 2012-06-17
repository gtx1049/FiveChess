#include "chessboard.h"

//构造函数
ChessBoard::ChessBoard()
{
}

ChessBoard::~ChessBoard()
{
}

//刷新整个棋盘
void ChessBoard::reFresh()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            this->chessboardmat[i][j] = EMPTY_CHESS;
        }
    }
}

//指定一个棋子
void ChessBoard::setOneChess(Chess chess)
{
    int row = chess.getRow();
    int column = chess.getColumn();

    this->chessboardmat[row][column] = chess.getChessType();

    steps.push_back(chess);
}

//悔棋
bool ChessBoard::backStep()
{
    if(steps.size() < 2)
    {
        return false;
    }

    for(int i = 0; i < 2; i++)
    {
        vector<Chess>::iterator it = steps.end() - 1;
        Chess chess = *it;

        int row = chess.getRow();
        int column = chess.getColumn();
        this->chessboardmat[row][column] = EMPTY_CHESS;

        steps.pop_back();
    }
    return true;
}

//每当落子后，判断胜负
bool ChessBoard::judgeVictory(Chess& lastchess)
{
    int row = lastchess.getRow();
    int column = lastchess.getColumn();
    int type = lastchess.getChessType();

    //垂直方向
    if(fiveInDirection(row, column, type, VERTICAL))
    {
        return VICTORY;
    }
    //水平方向
    if(fiveInDirection(row, column, type, HORIZON))
    {
        return VICTORY;
    }
    //右斜方向
    if(fiveInDirection(row, column, type, RIGHT))
    {
        return VICTORY;
    }
    //左斜方向
    if(fiveInDirection(row, column, type, LEFT))
    {
        return VICTORY;
    }

    return CONTINUE;
}

void ChessBoard::waitAct()
{
}

//根据棋盘对窗口进行绘制
void ChessBoard::displayBoard(Board *board)
{
    QPainter painter;
    painter.begin(board);
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(chessboardmat[i][j] == BLACK_CHESS)
            {
                QImage img("img/blackChess.png");
                painter.drawImage(i * BOARD_GRID_SIZE + BOARD_OFFSET_X, j * BOARD_GRID_SIZE + BOARD_OFFSET_Y, img);
            }
            else if(chessboardmat[i][j] == WHITE_CHESS)
            {
                QImage img("img/whiteChess.png");
                painter.drawImage(i * BOARD_GRID_SIZE + BOARD_OFFSET_X, j * BOARD_GRID_SIZE + BOARD_OFFSET_Y, img);
            }
        }
    }
    painter.end();
}

int ChessBoard::getChessBoardMat(int row, int column)
{
    return chessboardmat[row][column];
}

bool ChessBoard::hasChess(int row, int column)
{
    if(chessboardmat[row][column] != EMPTY_CHESS)
    {
        return true;
    }
    return false;
}

//通过方向判断五子连珠的函数
bool ChessBoard::fiveInDirection(int row, int column, int type, int direction)
{
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
    bool upflag = true;
    int chesscount = 1;
    while(chesscount < 5)
    {
        nowrow += offsetX;
        nowcolumn += offsetY;
        if(upflag)
        {
            if(nowcolumn < 0 || nowrow < 0)
            {
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
                return false;
            }
        }

        if(chessboardmat[nowrow][nowcolumn] == type)
        {
            chesscount++;
        }
        else
        {
            if(!upflag)
            {
                return false;
            }
            upflag = false;
            offsetX = -offsetX;
            offsetY = -offsetY;
            nowrow = row;
            nowcolumn = column;
        }
    }
    return true;
}
