#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

////////////////////////
//
class CListWidget : public QWidget
{
public:
	explicit CListWidget(QWidget* parent = 0);
	void init();
};
//
////////////////////////

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = 0);
	~MainWindow();

	void test();
	void test2();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
