#include "board.h"
#include "aiplayer.h"
#include "netplayer.h"
#include "localplayer.h"

Board::Board(QWidget *parent) :
    QWidget(parent)
{
    parentwidget = parent;
    maincb = new ChessBoard();
    maincb->reFresh();
    gamemode = NONE_GAME;
}

//当外部调用这些函数，使之能够跳到基类的函数运行
void Board::setStyleSheet(const QString &styleSheet)
{
    parentwidget->setStyleSheet(styleSheet);
}

void Board::setObjectName(const QString &name)
{
    parentwidget->setObjectName(name);
}

void Board::setGeometry(const QRect &rect)
{
    parentwidget->setGeometry(rect);
}

//相应鼠标点击事件，当鼠标按下时，计算按下点在棋盘中的位置，绘制棋子
//每次鼠标点击都是游戏进程的关键点，在他之后，决定游戏的下一步逻辑，分为三种模式
//落子后会对输赢情况进行判断
void Board::mousePressEvent(QMouseEvent *mpe)
{
    int x = mpe->pos().x() - BOARD_OFFSET_X;
    int y = mpe->pos().y() - BOARD_OFFSET_Y;

    if(x < 0 || x >= BOARD_PIX_SIZE)
    {
        return;
    }
    if(y < 0 || y >= BOARD_PIX_SIZE)
    {
        return;
    }

    int row = x / BOARD_GRID_SIZE;
    int column = y / BOARD_GRID_SIZE;

    //最后一次落子
    Chess lastchess = player->doAct(ChessPos(row, column), maincb);

    repaint();

    //在三种模式下选择应该做的事
    switch(gamemode)
    {
        case LOCAL_SINGLE:
            playerAI->doAct(playerAI->thinkStrategy(), maincb);
            repaint();
            break;
        case LOCAL_MUTI:
            break;
        case NET_MUTI:
            break;
    }

    if(maincb->judgeVictory(lastchess))
    {
        QMessageBox::about(NULL, "xx", "You Win!");
    }
}

//绘制棋盘
void Board::paintEvent(QPaintEvent *)
{
    maincb->displayBoard(this);
}

//设定游戏模式，建立玩家类型
void Board::setGameMode(int target)
{
    gamemode = target;
    if(target == LOCAL_SINGLE)
    {
        player = new LocalPlayer(BLACK_CHESS);
        playerAI = new AIplayer(WHITE_CHESS);
    }
    else if(target == LOCAL_MUTI)
    {
        player = new NetPlayer(WHITE_CHESS);
    }
}

//释放玩家所占用的内存
void Board::releasePlayer()
{
    delete player;
    if(playerAI != NULL)
    {
        delete playerAI;
    }
}




