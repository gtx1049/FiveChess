#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include "aianalyze.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    AIanalyze::level = 1;
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

