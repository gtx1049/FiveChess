#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QtGui>
#include "chessboard.h"
#include "const.h"
#include "player.h"

/*
    由QWiget继承下来点棋盘，负责接受棋盘事件
*/

//声明ChessBoard
class ChessBoard;
class AIplayer;
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
    void releasePlayer();
private:
    ChessBoard* maincb;
    QWidget* parentwidget;
    Player* player;
    AIplayer* playerAI;
private:
    int gamemode;

signals:
    
public slots:
    
};

#endif // BOARD_H
