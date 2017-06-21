#ifndef FILESDECISIONLISTVIEW_H
#define FILESDECISIONLISTVIEW_H

#include <QTreeView>
#include "FilesDecisionModel.h"

/*!
\brief The FilesDecisionListView class

Т.к. это не совсем дерево, а список файлов с атрибутами в виде путей к ним,
класс называется "списком".
*/
class FilesDecisionListView : public QTreeView
{
public:
	explicit FilesDecisionListView(QWidget* parent);
	~FilesDecisionListView();

	void setFilesInfo(const CloneHunter::FilesInfo& filesInfo);

private:
//	FilesDecisionModel* m_filesDecisionModel;
};

#endif // FILESDECISIONLISTVIEW_H
