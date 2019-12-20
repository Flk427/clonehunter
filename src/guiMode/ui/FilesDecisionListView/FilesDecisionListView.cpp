#include "FilesDecisionListView.h"
#include <QStandardItemModel>
#include "../AutoToolTipDelegate.h"
#include "FilesDecisionModel.h"

FilesDecisionListView::FilesDecisionListView(QWidget* parent) :
	QTreeView(parent)
{
	_init();
}

FilesDecisionListView::~FilesDecisionListView()
{
}

void FilesDecisionListView::setFilesInfo(const CloneHunter::DupFiles& dupFiles)
{
	FilesDecisionModel* m = qobject_cast<FilesDecisionModel*>(model());

	if (m)
	{
		m->setFilesInfo(dupFiles);
	}
}

void FilesDecisionListView::_init()
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	//setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setModel(new FilesDecisionModel());
	setItemDelegate(new AutoToolTipDelegate(this));
	setAnimated(true);

	setHeaderHidden(true);
}
