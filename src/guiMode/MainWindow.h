#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../types.h"
#include "../programParams.h"
#include "../GetFilesInfo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

	void setParams(const CloneHunter::PROGRAMPARAMS& params);

private:
	Ui::MainWindow *ui;

	CloneHunter::PROGRAMPARAMS m_params;
	CloneHunter::FilesInfo m_filesInfo;
	GetFilesInfo* getFilesInfo;

private slots:
	void on_pbStartScan_clicked();
	void scanFilesFinished(CloneHunter::FilesInfo filesInfo);
	void scanFilesAborted();
};

#endif // MAINWINDOW_H
