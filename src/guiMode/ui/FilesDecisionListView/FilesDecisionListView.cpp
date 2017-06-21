#include "FilesDecisionListView.h"

FilesDecisionListView::FilesDecisionListView(QWidget* parent) :
	QTreeView(parent)
{
//	m_filesDecisionModel = new FilesDecisionModel();
//	setModel(m_filesDecisionModel);
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
		m->setFilesInfo(filesInfo);
	}
}
