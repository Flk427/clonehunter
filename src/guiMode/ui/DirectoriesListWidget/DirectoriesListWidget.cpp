#include "DirectoriesListWidget.h"
#include "ui_DirectoriesListWidget.h"

#include <QFileDialog>
#include <QtDebug>

DirectoriesListWidget::DirectoriesListWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DirectoriesListWidget)
{
	ui->setupUi(this);

	ui->listView->setModel(&m_model);
}

DirectoriesListWidget::~DirectoriesListWidget()
{
	delete ui;
}

QStringList DirectoriesListWidget::directories() const
{
	return m_model.stringList();
}

void DirectoriesListWidget::on_pbAdd_clicked()
{
	static QString lastDir;

	QFileDialog fileDialog(this, "Select directory", lastDir.isEmpty() ? QApplication::applicationDirPath() : lastDir);

	fileDialog.setFileMode(QFileDialog::Directory);
	fileDialog.setOption(QFileDialog::Option::ShowDirsOnly, true);

	if (fileDialog.exec() == QDialog::Accepted)
	{
		lastDir = fileDialog.directory().path();

		if(m_model.insertRow(m_model.rowCount()))
		{
			QModelIndex index = m_model.index(m_model.rowCount() - 1, 0);
			m_model.setData(index, fileDialog.selectedFiles());
		}
	}
}

void DirectoriesListWidget::on_pbRemove_clicked()
{
	m_model.removeRow(ui->listView->currentIndex().row());

	/*
	const QModelIndexList& indexes = ui->listWidget->selectionModel()->selectedIndexes();
	if (!indexes.empty())
	{
		m_directories.removeAt(indexes.first().row());
		updateListWidget();
	}
	*/
}

void DirectoriesListWidget::on_pbClear_clicked()
{
	m_model.removeRows(0, m_model.rowCount(), QModelIndex());
}
