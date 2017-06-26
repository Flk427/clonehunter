#include "FilesDecisionModel.h"

FilesDecisionModel::FilesDecisionModel()
{

}

void FilesDecisionModel::setFilesInfo(const FilesDecisionFiles& filesDecisionFiles)
{
	m_filesDecisionFiles = filesDecisionFiles;
}


QModelIndex FilesDecisionModel::index(int row, int column, const QModelIndex& parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	if (!parent.isValid())
	{
		if (row < m_filesDecisionFiles.size())
		{
			FilesDecisionFileCopiesList* p = (FilesDecisionFileCopiesList*) &m_filesDecisionFiles.at(row);

			return createIndex(row, column, p);
		}
	}

//	if (!parent.parent().isValid())
//	{
//		int pRow = parent.row();

//		if (pRow != -1 && row < m_filesDecisionFiles.at(pRow).size())
//		{
//			return createIndex(row, column, nullptr);
//		}
//	}

	return QModelIndex();
}

QModelIndex FilesDecisionModel::parent(const QModelIndex& child) const
{
	if (!child.isValid())
		return QModelIndex();

//	FilesDecisionFileInfo* fi = qobject_cast<FilesDecisionFileInfo*>(child.internalPointer());

//	if (parentItem == rootItem)
//		   return QModelIndex();

	return QModelIndex();
}

int FilesDecisionModel::rowCount(const QModelIndex& parent) const
{
	int count = 0;

	if (!parent.isValid())
	{
		count = m_filesDecisionFiles.size();
	}
	else
	{
		count = 2;

//		if (!parent.parent().isValid() && m_filesDecisionFiles.count() < parent.row())
//		{
//			count = m_filesDecisionFiles.at(parent.row()).count();
//		}
	}

	return count;
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

	if (!index.parent().isValid())
	{
		if (index.row() >= m_filesDecisionFiles.size())
		{
			return QVariant();
		}
		else
		{
			if (role == Qt::DisplayRole)
			{
				return m_filesDecisionFiles.at(index.row()).at(0).name;
			}
		}
	}

//	if (!index.parent().parent().isValid())
//	{
//		if (index.row() >= m_filesDecisionFiles.at(index.row()).size())
//		{
//			return QVariant();
//		}
//		else
//		{
//			if (role == Qt::DisplayRole)
//			{
//				return m_filesDecisionFiles.at(index.parent().row()).at(index.row()).name;
//			}
//		}
//	}

	return QVariant();
}

//bool FilesDecisionModel::setData(const QModelIndex& index, const QVariant& value, int role)
//{
//}

Qt::ItemFlags FilesDecisionModel::flags(const QModelIndex& index) const
{
	Q_UNUSED(index);
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


//QHash<int, QByteArray> FilesDecisionModel::roleNames() const
//{
//}
