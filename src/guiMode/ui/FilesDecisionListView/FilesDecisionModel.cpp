#include "FilesDecisionModel.h"
#include <QDir>

FilesDecisionModel::FilesDecisionModel()
{
}

FilesDecisionModel::~FilesDecisionModel()
{
}

void FilesDecisionModel::setFilesInfo(const CloneHunter::DupFiles& dupFiles)
{
	m_dupFiles = dupFiles;
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
			const CloneHunter::DUPFILESINFO* childItem = &m_dupFiles.at(parent.row());

			if (childItem)
			{
				return createIndex(row, column, const_cast<CloneHunter::DUPFILESINFO*>(childItem));
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

	// Корневой элемент.
	if (child.internalPointer() == nullptr)
	{
		return QModelIndex();
	}

	CloneHunter::DUPFILESINFO* childItem = (CloneHunter::DUPFILESINFO*) child.internalPointer();
	return createIndex(childItem->parentIndex, 0, nullptr);
}

int FilesDecisionModel::rowCount(const QModelIndex& parent) const
{
	if (parent.column() > 0)
	{
		return 0;
	}

	if (!parent.isValid())
	{
		return m_dupFiles.size();
	}
	else
	{
		if (parent.internalPointer() == nullptr)
		{
			if (parent.row() < m_dupFiles.size())
			{
				return m_dupFiles[parent.row()].files.size();
			}
		}
	}

	return 0;
}

int FilesDecisionModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent)
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
		return QString("%1 (%2)").arg(m_dupFiles[index.row()].files.first().name).arg(m_dupFiles[index.row()].files.length());
	}
	else
	{
		CloneHunter::DUPFILESINFO* info = static_cast<CloneHunter::DUPFILESINFO*>(index.internalPointer());
		return info->files.at(index.row()).path + QDir::separator() + info->files.at(index.row()).name;
	}
}

Qt::ItemFlags FilesDecisionModel::flags(const QModelIndex& index) const
{
	Q_UNUSED(index)
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
