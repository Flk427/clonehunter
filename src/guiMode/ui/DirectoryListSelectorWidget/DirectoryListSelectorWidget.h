#ifndef DIRECTORYLISTSELECTOR_H
#define DIRECTORYLISTSELECTOR_H

#include <QWidget>
#include <QStringList>

namespace Ui {
class DirectoryListSelector;
}

/*!
   \brief The DirectoryListSelector class

   Не используется модель.
 */
class DirectoryListSelector : public QWidget
{
	Q_OBJECT

public:
	explicit DirectoryListSelector(QWidget *parent = nullptr);
	~DirectoryListSelector();

	bool isEmpty();
	const QStringList& getDirectories();

private:
	Ui::DirectoryListSelector *ui;

	QStringList m_directories;

	void initialize();
	void updateListWidget();

private slots:
	void on_pbAdd_clicked();
	void on_pbDelete_clicked();

public slots:
	void directoriesClear();

signals:
	void directoriesChanged(const QStringList& directories);
};

#endif // DIRECTORYLISTSELECTOR_H
