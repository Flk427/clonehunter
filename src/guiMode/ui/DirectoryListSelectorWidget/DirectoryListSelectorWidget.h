#ifndef DIRECTORYLISTSELECTOR_H
#define DIRECTORYLISTSELECTOR_H

#include <QWidget>
#include <QStringList>

namespace Ui {
class DirectoryListSelector;
}

class DirectoryListSelector : public QWidget
{
	Q_OBJECT

public:
	explicit DirectoryListSelector(QWidget *parent = 0);
	~DirectoryListSelector();

	bool isEmpty();
	const QStringList& getDirectories();

private:
	Ui::DirectoryListSelector *ui;

	QStringList m_directories;

	void initialize();
	void setupListWidget();

private slots:
	void addDirectory();
	void deleteDirectory();

public slots:
	void directoriesClear();

signals:
	void directoriesChanged(QStringList directories);
};

#endif // DIRECTORYLISTSELECTOR_H
