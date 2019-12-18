#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->pbStopScan->setVisible(false);
	ui->lbWaitMessage->setVisible(false);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pbStartScan_clicked()
{
	//ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
	ui->pbStopScan->setVisible(true);
	ui->pbStartScan->setVisible(false);
}
