#include "board.h"
#include "aiplayer.h"
#include "netplayer.h"
#include "localplayer.h"
#include "aithread.h"
#include "message.h"
#include <iostream>

Board::Board(QWidget *parent) :
    QWidget(parent)
{
    parentwidget = parent;
    maincb = new ChessBoard();
    maincb->reFresh();
    gamemode = NONE_GAME;
    start = false;
}

Board::~Board()
{
    if(player != NULL)
    {
        delete player;
    }
    if(playerAI != NULL)
    {
        delete playerAI;
    }
    delete maincb;
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

    if(!start && gamemode != NET_MUTI)
    {
        return;
    }

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

    if(maincb->hasChess(row, column))
    {
        return;
    }

    if(gamemode == LOCAL_SINGLE)
    {
        if(playerAI->getAIplayer()->getActive())
        {
            QMessageBox::about(NULL, "xx", "Thinking!");
            return;
        }
    }
    //最后一次落子
    Chess lastchess;
    if(gamemode != NET_MUTI)
    {
        lastchess = player->doAct(ChessPos(row, column), maincb);
    }

    repaint();

    //在三种模式下选择应该做的事
    switch(gamemode)
    {
        case LOCAL_SINGLE:
            playerAI->start();
            break;
        case LOCAL_MUTI:
            player->setChesstype(-player->getChesstype());
            break;
        case NET_MUTI:

            if(player->getActive() && !maincb->hasChess(row,column))
            {
                lastchess = player->doAct(ChessPos(row, column), maincb);
                repaint();
                Message message;
                message.status = DOWN;
                message.point.x = row;
                message.point.y = column;
                tcpSender->sendStep(message);
                player->setActive(false);
            }
            else
            {
                return;
            }
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
        playerAI = new AIthread(new AIplayer(WHITE_CHESS), maincb, this);

    }
    else if(target == LOCAL_MUTI)
    {
        player = new LocalPlayer(BLACK_CHESS);
    }
    else if(target == NET_MUTI)
    {
        player = new NetPlayer(BLACK_CHESS);
        player->setActive(true);
    }
}

void Board::setUserfirst(bool userfirst)
{
    if(!userfirst)
    {
        player->setChesstype(WHITE_CHESS);
        playerAI->getAIplayer()->setChesstype(BLACK_CHESS);
        maincb->setOneChess(Chess(7, 7, BLACK_CHESS));
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

Player *Board::getNetPlayer()
{
    return player;
}

ChessBoard *Board::getChessBoard()
{
    return maincb;
}

void Board::acceptTcp(QTcpSocket *tcpSocket)
{
    tcpSender = new TcpSender(tcpSocket);
}

void Board::repaintScreen()
{
    repaint();
}

void Board::judgeVictoryOfAI(Chess lastchess)
{
    if(maincb->judgeVictory(lastchess))
    {
        QMessageBox::about(NULL, "xx", "You Lose!");
    }
}

//悔棋响应函数
void Board::backStep()
{
    if(gamemode == LOCAL_SINGLE)
    {
        if(playerAI->getAIplayer()->getActive())
        {
            return;
        }
    }

    if(!maincb->backStep())
    {
        QMessageBox::about(NULL, "xx", "You can't!");
    }
    repaint();
}

//认输响应函数
void Board::loseGame()
{
    start = false;
    maincb->reFresh();
    repaint();
    //std::cout << "fresh" << endl;
}

void Board::startGame()
{
    start = true;
}




