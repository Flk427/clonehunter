#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../types.h"
#include "../programParams.h"
#include "../GetFilesInfo.h"
#include "ui/FilesDecisionListView/FilesDecisionListView.h"

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

	void switchToBeforeScanMode();
	void switchToScaningMode();
	void switchToDuplicatesMode();

private slots:
	void on_pbStartScan_clicked();
	void scanFilesFinished(CloneHunter::DupFiles dupFiles);
	void scanFilesAborted();
};

#endif // MAINWINDOW_H
