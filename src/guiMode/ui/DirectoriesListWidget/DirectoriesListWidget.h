#ifndef DIRECTORIESLISTWIDGET_H
#define DIRECTORIESLISTWIDGET_H

#include <QWidget>
#include <QStringListModel>

namespace Ui {
class DirectoriesListWidget;
}

class DirectoriesListWidget : public QWidget
{
	Q_OBJECT

public:
	explicit DirectoriesListWidget(QWidget *parent = nullptr);
	~DirectoriesListWidget();

	QStringList directories() const;

private:
	Ui::DirectoriesListWidget *ui;

	QStringListModel m_model;

private slots:
	void on_pbAdd_clicked();
	void on_pbRemove_clicked();
	void on_pbClear_clicked();
};

#endif // DIRECTORIESLISTWIDGET_H
