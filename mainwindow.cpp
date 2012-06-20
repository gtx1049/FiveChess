#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include "aianalyze.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->backStepButton, SIGNAL(clicked()), ui->playScreen, SLOT(backStep()));
    connect(ui->failButton, SIGNAL(clicked()), ui->playScreen, SLOT(loseGame()));
    connect(ui->startButton, SIGNAL(clicked()),ui->playScreen, SLOT(startGame()));

    ui->help->hide();
    ui->hostChose->hide();
    ui->playScreen->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exitButton_clicked()
{
    destroy();
}

void MainWindow::on_helpButton_clicked()
{
    ui->menu->hide();
    ui->help->show();
}

void MainWindow::on_singleButton_clicked()
{
    ui->menu->hide();
    ui->playScreen->setGameMode(LOCAL_SINGLE);
    ui->playScreen->setUserfirst(false);
    ui->playScreen->show();
}

void MainWindow::on_doubleButton_clicked()
{
    ui->menu->hide();
    ui->playScreen->setGameMode(LOCAL_MUTI);
    ui->playScreen->show();

}

void MainWindow::on_backButton_clicked()
{
    ui->hostChose->hide();
    ui->menu->show();
}

void MainWindow::on_confirmButton_clicked()
{
    ui->inputName->hide();
    ui->invitation->hide();
    ui->hostlist->show();
}

void MainWindow::on_inviteButton_clicked()
{
    ui->hostChose->hide();
    ui->playScreen->setGameMode(NET_MUTI);
    ui->playScreen->show();
}

void MainWindow::on_backButton2_clicked()
{
    ui->hostlist->hide();
    ui->inputName->show();
}

void MainWindow::on_helpBackButton_clicked()
{
    ui->help->hide();
    ui->menu->show();
}

void MainWindow::on_netButton_clicked()
{
    ui->hostChose->show();
    ui->menu->hide();
}


void MainWindow::on_failButton_clicked()
{
    ui->playScreen->hide();
    ui->menu->show();
}
