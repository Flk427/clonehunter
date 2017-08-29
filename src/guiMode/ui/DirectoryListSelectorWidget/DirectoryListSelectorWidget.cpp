#include "DirectoryListSelectorWidget.h"
#include "ui_DirectoryListSelectorWidget.h"

#include <QFileDialog>

DirectoryListSelector::DirectoryListSelector(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DirectoryListSelector)
{
	ui->setupUi(this);

	initialize();
}

DirectoryListSelector::~DirectoryListSelector()
{
	delete ui;
}

bool DirectoryListSelector::isEmpty()
{
	return m_directories.empty();
}

const QStringList&DirectoryListSelector::getDirectories()
{
	return m_directories;
}

void DirectoryListSelector::initialize()
{
	ui->pushButton->disconnect();
	ui->pushButton_2->disconnect();
	ui->pushButton_3->disconnect();

	connect(ui->pushButton, &QPushButton::clicked, this, &DirectoryListSelector::addDirectory);
	connect(ui->pushButton_2, &QPushButton::clicked, this, &DirectoryListSelector::deleteDirectory);
	connect(ui->pushButton_3, &QPushButton::clicked, this, &DirectoryListSelector::directoriesClear);
}

void DirectoryListSelector::addDirectory()
{
	QString directory = QFileDialog::getExistingDirectory();

	if (!directory.isEmpty() && !m_directories.contains(directory))
	{
		m_directories.push_back(directory);
		qSort(m_directories);
		setupListWidget();
	}
}

void DirectoryListSelector::deleteDirectory()
{
	QModelIndexList& indexes = ui->listWidget->selectionModel()->selectedIndexes();

	if (!indexes.empty())
	{
		m_directories.removeAt(indexes.first().row());
		setupListWidget();
	}
}

void DirectoryListSelector::directoriesClear()
{
	if (!m_directories.empty())
	{
		m_directories.clear();
		setupListWidget();
	}
}

void DirectoryListSelector::setupListWidget()
{
	ui->listWidget->clear();
	ui->listWidget->insertItems(0, m_directories);
	emit directoriesChanged(m_directories);
}
