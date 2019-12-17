#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>

namespace Ui {
class TestWindow;
}

////////////////////////
//
class CListWidget : public QWidget
{
public:
	explicit CListWidget(QWidget* parent = nullptr);
	void init();
};
//
////////////////////////

class TestWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit TestWindow(QWidget* parent = nullptr);
	~TestWindow();

	void test();
	void test2();

private:
	Ui::TestWindow *ui;
};

#endif // TESTWINDOW_H
