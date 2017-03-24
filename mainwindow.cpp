#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
ui->label->setText("Time:");
ui->label_2->setText("Volume:");
ui->label_3->setText("High:");
ui->label_4->setText("Low:");
ui->label_5->setText("Open:");
ui->label_6->setText("Last:");
ui->label_7->setText("Ask:");
ui->label_8->setText("Bid:");
ui->label_9->setText("Vwap:");
}
