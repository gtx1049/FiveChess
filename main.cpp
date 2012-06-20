#include <QtGui/QApplication>
#include "mainwindow.h"
#include "chessboard.h"
#include "chess.h"
#include <QMetaType>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<Chess>();

    MainWindow w;
    w.show();
    
//    ChessBoard cb;

//    cb.reFresh();
//    cb.setOneChess(Chess(0, 0, BLACK_CHESS));
//    cb.setOneChess(Chess(0, 1, BLACK_CHESS));
//    cb.setOneChess(Chess(0, 2, BLACK_CHESS));
//    cb.setOneChess(Chess(0, 3, BLACK_CHESS));
//    cb.setOneChess(Chess(0, 4, BLACK_CHESS));

//    Chess c = Chess(0, 0, BLACK_CHESS);
//    if(cb.judgeVictory(c))
//        {

//        }

//    return 0;
    return a.exec();
}
