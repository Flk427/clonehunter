#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pbStartScan_clicked()
{
	ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}
