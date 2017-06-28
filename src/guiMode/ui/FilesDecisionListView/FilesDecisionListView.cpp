#include "FilesDecisionListView.h"
#include <QStandardItemModel>
#include "../AutoToolTipDelegate.h"
#include "FilesDecisionModel.h"

FilesDecisionListView::FilesDecisionListView(QWidget* parent) :
	QTreeView(parent)
{
//	m_filesDecisionModel = new FilesDecisionModel();
//	setModel(m_filesDecisionModel);
	_init();

//	FilesDecisionModel* m = qobject_cast<FilesDecisionModel*>(model());

//	if (m)
//	{
//		m->setFilesInfo(root);
//	}
}

FilesDecisionListView::~FilesDecisionListView()
{
	//	delete m_filesDecisionModel;
}

void FilesDecisionListView::setFilesInfo(const FilesDecisionFiles& filesDecisionFiles)
{
	FilesDecisionModel* m = qobject_cast<FilesDecisionModel*>(model());

	if (m)
	{
		m->setFilesInfo(filesDecisionFiles);
	}
}

/*!
\brief FilesDecisionListView::setFilesInfo
\param filesDecisionFiles Список списков структур FilesDecisionFileInfo.
*/
//void FilesDecisionListView::setFilesInfo(const FilesDecisionFiles& filesDecisionFiles)
//{
//	FilesDecisionModel* m = qobject_cast<FilesDecisionModel*>(model());

//	if (m)
//	{
//		m->setFilesInfo(filesDecisionFiles);
//	}
//}

void FilesDecisionListView::_init()
{
//	setItemDelegate(new QStyledItemDelegate());

	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setModel(new FilesDecisionModel());
	setItemDelegate(new AutoToolTipDelegate(this));
	setAnimated(true);

//	setModel(new QStandardItemModel());
//	QStandardItemModel* m = qobject_cast<QStandardItemModel*>(model());
//	m->appendRow(new QStandardItem("asd"));
//	m->appendRow(new QStandardItem("zxcvbnmzxcvbnmzxcvbnmzxcvbnmzxcvbnm"));
//	m->appendRow(new QStandardItem("qwe"));
//	m->item(1)->appendRow(new QStandardItem("1"));
//	m->item(1)->appendRow(new QStandardItem("2"));
//	m->item(1)->appendRows(QList<QStandardItem*>() << new QStandardItem("3") << new QStandardItem("4"));

	setHeaderHidden(true);
}
