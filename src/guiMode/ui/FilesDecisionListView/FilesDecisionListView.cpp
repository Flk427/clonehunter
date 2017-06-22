#include "FilesDecisionListView.h"
#include <QStandardItemModel>
#include "../AutoToolTipDelegate.h"

FilesDecisionListView::FilesDecisionListView(QWidget* parent) :
	QTreeView(parent)
{
//	m_filesDecisionModel = new FilesDecisionModel();
//	setModel(m_filesDecisionModel);
	_init();
}

FilesDecisionListView::~FilesDecisionListView()
{
	//	delete m_filesDecisionModel;
}

void FilesDecisionListView::setFilesInfo(const CloneHunter::FilesInfo& filesInfo)
{
	FilesDecisionModel* m = qobject_cast<FilesDecisionModel*>(model());

	if (m)
	{
		m->setFilesInfo(filesInfo); // TODO: Заменить на класс-контейнер данных со слотами/сигналами изменения данных или модели.
	}
}

void FilesDecisionListView::_init()
{
//	setItemDelegate(new QStyledItemDelegate());

	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setModel(new QStandardItemModel());
	setItemDelegate(new AutoToolTipDelegate(this));
	setAnimated(true);

	QStandardItemModel* m = qobject_cast<QStandardItemModel*>(model());

	m->appendRow(new QStandardItem("asd"));
	m->appendRow(new QStandardItem("zxcvbnmzxcvbnmzxcvbnmzxcvbnmzxcvbnm"));
	m->appendRow(new QStandardItem("qwe"));

	m->item(1)->appendRow(new QStandardItem("1"));
	m->item(1)->appendRow(new QStandardItem("2"));
	m->item(1)->appendRows(QList<QStandardItem*>() << new QStandardItem("3") << new QStandardItem("4"));

	setHeaderHidden(true);
}
