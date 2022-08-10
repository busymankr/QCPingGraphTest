#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnStartStop_clicked()
{
    if (ui->btnStartStop->text().compare("Start") == 0) {
        ui->wQCPingGraph->setIP("www.google.com");
        ui->wQCPingGraph->ping(true);
        ui->btnStartStop->setText("Stop");
    }
    else {
        ui->wQCPingGraph->ping(false);
        ui->btnStartStop->setText("Start");
    }
}
