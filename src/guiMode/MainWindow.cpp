#include <QDebug>
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	switchToBeforeScanMode();

	getFilesInfo = new GetFilesInfo();
	connect(getFilesInfo, &GetFilesInfo::completed, this, &MainWindow::scanFilesFinished);
	connect(getFilesInfo, &GetFilesInfo::aborted, this, &MainWindow::scanFilesAborted);

	connect(ui->pbStopScan, &QPushButton::clicked, getFilesInfo, &GetFilesInfo::abort);
}

MainWindow::~MainWindow()
{
	delete getFilesInfo;

	delete ui;
}

void MainWindow::setParams(const CloneHunter::PROGRAMPARAMS& params)
{
	m_params = params;
}

void MainWindow::switchToBeforeScanMode()
{
	ui->stackedWidget->setCurrentIndex(0);

	ui->directoriesListWidget->setEnabled(true);

	ui->pbStartScan->setVisible(true);
	ui->pbarScaning->setVisible(false);
	ui->pbStopScan->setVisible(false);
	ui->lbWaitMessage->setVisible(false);
}

void MainWindow::switchToScaningMode()
{
	ui->directoriesListWidget->setEnabled(false);

	ui->pbarScaning->setVisible(true);
	ui->pbStopScan->setVisible(true);
	ui->pbStartScan->setVisible(false);
	ui->lbWaitMessage->setVisible(false);
}

void MainWindow::switchToDuplicatesMode()
{
	ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pbStartScan_clicked()
{
	QStringList directories = ui->directoriesListWidget->directories();

	if (!directories.empty())
	{
		m_params.directories = directories;

		ui->pbarScaning->setValue(0);
		switchToScaningMode();

		getFilesInfo->setParams(m_params);
		getFilesInfo->start();
	}
}

void MainWindow::scanFilesFinished(CloneHunter::FilesInfo filesInfo)
{
	std::for_each(filesInfo.begin(), filesInfo.end(), [&](CloneHunter::FILEINFO fi){qDebug() << fi.name;});

//	switchToDuplicatesMode();
	switchToBeforeScanMode();
}

void MainWindow::scanFilesAborted()
{
	qDebug() << "MainWindow::scanFilesAborted";

	switchToBeforeScanMode();
}
