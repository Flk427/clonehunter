#include "FilesDecisionModel.h"
#include <QDir>

FilesDecisionModel::FilesDecisionModel()
{
}

FilesDecisionModel::~FilesDecisionModel()
{
	qDeleteAll(m_filesDecisionFiles);
}

void FilesDecisionModel::setFilesInfo(const FilesDecisionFiles& filesDecisionFiles)
{
	qDeleteAll(m_filesDecisionFiles);
	m_filesDecisionFiles = filesDecisionFiles;
}

QModelIndex FilesDecisionModel::index(int row, int column, const QModelIndex& parent) const
{
	if (!hasIndex(row, column, parent))
	{
		return QModelIndex();
	}

	if (!parent.isValid())
	{
		return createIndex(row, column, nullptr);
	}
	else
	{
		if (parent.internalPointer() == nullptr)
		{
			FilesDecisionFileCopiesList* childItem = m_filesDecisionFiles.at(parent.row());

			if (childItem)
			{
				return createIndex(row, column, childItem);
			}
		}
	}

	return QModelIndex();
}

QModelIndex FilesDecisionModel::parent(const QModelIndex& child) const
{
	if (!child.isValid())
	{
		return QModelIndex();
	}

	if (child.internalPointer() == nullptr)
	{
		return QModelIndex();
	}

	FilesDecisionFileCopiesList* childItem = (FilesDecisionFileCopiesList*) child.internalPointer();

	//return dynamic_cast<TreeRootItem*>(m_parentItem)->childItems().indexOf(const_cast<TreeInnerItem*>(this));

	int childIndex = m_filesDecisionFiles.indexOf(childItem);
	return createIndex(childIndex, 0, nullptr);
//	return createIndex(childItem->or, 0, nullptr);
//	return QModelIndex();
}

int FilesDecisionModel::rowCount(const QModelIndex& parent) const
{
	if (parent.column() > 0)
	{
		return 0;
	}

	if (!parent.isValid())
	{
		return m_filesDecisionFiles.size();
	}
	else
	{
		if (parent.internalPointer() == nullptr)
		{
			if (parent.row() < m_filesDecisionFiles.size())
			{
				return m_filesDecisionFiles.at(parent.row())->size();
			}
		}
	}

	return 0;
}

int FilesDecisionModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return 1;
}

QVariant FilesDecisionModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	if (role != Qt::DisplayRole)
	{
		return QVariant();
	}

	if (index.internalPointer() == nullptr)
	{
		return m_filesDecisionFiles.at(index.row())->at(0).name;
	}
	else
	{
		FilesDecisionFileCopiesList* item = static_cast<FilesDecisionFileCopiesList*>(index.internalPointer());
		FilesDecisionFileInfo info = item->at(index.row());
		return info.path + QDir::separator() + info.name;
	}
}

Qt::ItemFlags FilesDecisionModel::flags(const QModelIndex& index) const
{
	Q_UNUSED(index);
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
