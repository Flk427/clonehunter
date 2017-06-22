#include "FilesDecisionModel.h"

FilesDecisionModel::FilesDecisionModel()
{

}

void FilesDecisionModel::setFilesInfo(const CloneHunter::FilesInfo& filesInfo)
{
	m_filesDecisionFiles.clear();

	foreach (auto fileInfo, filesInfo)
	{
		FilesDecisionFileInfo info(fileInfo);

		m_filesDecisionFiles[info.hash].append(info);
	}
}


//QModelIndex FilesDecisionModel::index(int row, int column, const QModelIndex& parent) const
//{
//}

//QModelIndex FilesDecisionModel::parent(const QModelIndex& child) const
//{
//}

int FilesDecisionModel::rowCount(const QModelIndex& parent) const
{
	if (parent.isValid())
	{
//		return ???
	}
	else
	{
		return m_filesDecisionFiles.size();
	}

	return 0;
}

int FilesDecisionModel::columnCount(const QModelIndex& parent) const
{
	return 1;
}

//QVariant FilesDecisionModel::data(const QModelIndex& index, int role) const
//{
//}

//bool FilesDecisionModel::setData(const QModelIndex& index, const QVariant& value, int role)
//{
//}

//Qt::ItemFlags FilesDecisionModel::flags(const QModelIndex& index) const
//{
//}
