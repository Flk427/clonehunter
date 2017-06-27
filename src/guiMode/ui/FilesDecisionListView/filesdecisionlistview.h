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
	//explicit FilesDecisionListView(QWidget* parent);
	explicit FilesDecisionListView(TreeRootItem* root, QWidget* parent);
	~FilesDecisionListView();

	//void setFilesInfo(const FilesDecisionFiles& filesDecisionFiles);
	void setFilesInfo(TreeRootItem* root);

private:
//	FilesDecisionModel* m_filesDecisionModel;
	void _init(TreeRootItem* root);
};

#endif // FILESDECISIONLISTVIEW_H
