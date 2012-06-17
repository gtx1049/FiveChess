#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_exitButton_clicked();

    void on_helpButton_clicked();

    void on_singleButton_clicked();

    void on_doubleButton_clicked();

    void on_backButton_clicked();

    void on_confirmButton_clicked();

    void on_inviteButton_clicked();

    void on_backButton2_clicked();

    void on_helpBackButton_clicked();

    void on_netButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
