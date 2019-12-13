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
	ui->pushButton_3->disconnect();
	connect(ui->pushButton_3, &QPushButton::clicked, this, &DirectoryListSelector::directoriesClear);
}

void DirectoryListSelector::on_pbAdd_clicked()
{
	QString directory = QFileDialog::getExistingDirectory();

	if (!directory.isEmpty() && !m_directories.contains(directory))
	{
		m_directories.push_back(directory);
		qSort(m_directories);
		updateListWidget();
	}
}

void DirectoryListSelector::on_pbDelete_clicked()
{
	const QModelIndexList& indexes = ui->listWidget->selectionModel()->selectedIndexes();

	if (!indexes.empty())
	{
		m_directories.removeAt(indexes.first().row());
		updateListWidget();
	}
}

void DirectoryListSelector::directoriesClear()
{
	if (!m_directories.empty())
	{
		m_directories.clear();
		updateListWidget();
	}
}

void DirectoryListSelector::updateListWidget()
{
	ui->listWidget->clear();
	ui->listWidget->insertItems(0, m_directories);
	emit directoriesChanged(m_directories);
}
