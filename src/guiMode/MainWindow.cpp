#include <QDebug>
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->pbarScaning->setVisible(false);
	ui->pbStopScan->setVisible(false);
	ui->lbWaitMessage->setVisible(false);

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

void MainWindow::on_pbStartScan_clicked()
{
	QStringList directories = ui->stackedWidget->widget(0)->findChild<DirectoriesListWidget*>("directoriesListWidget")->directories();

	if (!directories.empty())
	{
		//ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
		ui->pbarScaning->setVisible(true);
		ui->pbarScaning->setValue(0);
		ui->pbStopScan->setVisible(true);
		ui->pbStartScan->setVisible(false);

		m_params.directories = directories;

		getFilesInfo->setParams(m_params);
		getFilesInfo->start();
	}
}

void MainWindow::scanFilesFinished(CloneHunter::FilesInfo filesInfo)
{
	std::for_each(filesInfo.begin(), filesInfo.end(), [&](CloneHunter::FILEINFO fi){qDebug() << fi.name;});

	ui->pbarScaning->setVisible(false);
	ui->pbStopScan->setVisible(false);
	ui->pbStartScan->setVisible(true);
}

void MainWindow::scanFilesAborted()
{
	qDebug() << "MainWindow::scanFilesAborted";

	ui->pbarScaning->setVisible(false);
	ui->pbStopScan->setVisible(false);
	ui->pbStartScan->setVisible(true);
}
