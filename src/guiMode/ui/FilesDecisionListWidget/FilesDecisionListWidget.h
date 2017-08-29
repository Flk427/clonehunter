#ifndef FILESDECISIONLISTWIDGET_H
#define FILESDECISIONLISTWIDGET_H

#include <QWidget>

namespace Ui {
class FilesDecisionListWidget;
}

class FilesDecisionListWidget : public QWidget
{
	Q_OBJECT

public:
	explicit FilesDecisionListWidget(QWidget *parent = 0);
	~FilesDecisionListWidget();

private:
	Ui::FilesDecisionListWidget *ui;
};

#endif // FILESDECISIONLISTWIDGET_H
