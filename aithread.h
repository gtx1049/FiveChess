#ifndef AITHREAD_H
#define AITHREAD_H

#include <QThread>
#include "board.h"
#include "aiplayer.h"

class Board;

class AIthread : public QThread
{
    Q_OBJECT
public:
    AIthread();
    AIthread(AIplayer*, ChessBoard*, Board*);
    ~AIthread();
    virtual void run();
    AIplayer* getAIplayer();
private:
    AIplayer* theplayer;
    ChessBoard* maincb;
    Board* theboard;
signals:
    void endThink();
public slots:
    
};

#endif // AITHREAD_H
