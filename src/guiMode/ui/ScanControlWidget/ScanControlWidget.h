#ifndef SCANCONTROLWIDGET_H
#define SCANCONTROLWIDGET_H

#include <QWidget>

namespace Ui {
class ScanControlWidget;
}

class ScanControlWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ScanControlWidget(QWidget *parent = 0);
	~ScanControlWidget();

private:
	Ui::ScanControlWidget *ui;
};

#endif // SCANCONTROLWIDGET_H
