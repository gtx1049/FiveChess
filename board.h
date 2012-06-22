#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QtGui>
#include "chessboard.h"
#include "const.h"
#include "player.h"
#include "aithread.h"
#include "tcpsender.h"

/*
    由QWiget继承下来点棋盘，负责接受棋盘事件
*/

//声明ChessBoard
class ChessBoard;
class AIthread;
class Player;

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);
    ~Board();

    void setStyleSheet(const QString &styleSheet);
    void setObjectName(const QString &name);
    void setGeometry(const QRect &);

    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    void setGameMode(int);
    void setUserfirst(bool);
    void releasePlayer();

    void acceptTcp(QTcpSocket *tcpSocket);

    Player* getNetPlayer();
    ChessBoard* getChessBoard();
private:
    ChessBoard* maincb;
    QWidget* parentwidget;
    Player* player;
    AIthread* playerAI;
    TcpSender *tcpSender;
    Player* guest;
private:
    int gamemode;
    bool start;

signals:
    
public slots:
    void repaintScreen();
    void judgeVictoryOfAI(Chess);
    void backStep();
    void loseGame();
    void startGame();
};

#endif // BOARD_H
