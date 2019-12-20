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
		if (parent.parent() == QModelIndex())
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

	switch (role)
	{
		case Qt::DisplayRole:
			if (index.parent() == QModelIndex())
			{
				return QString("%1 (файлов: %2, размер: %3)")
						.arg(m_dupFiles[index.row()].files.first().name)
						.arg(m_dupFiles[index.row()].files.length())
						.arg(m_dupFiles[index.row()].size);
			}
			else
			{
				CloneHunter::DUPFILESINFO* info = static_cast<CloneHunter::DUPFILESINFO*>(index.internalPointer());
				return info->files.at(index.row()).path + QDir::separator() + info->files.at(index.row()).name;
			}

//		case Qt::ToolTipRole:
//			return "tool tip";

		case Qt::UserRole+3:
			if (index.parent() == QModelIndex())
			{
				QStringList filesPaths;

				for(auto it=m_dupFiles[index.row()].files.begin(); it!=m_dupFiles[index.row()].files.end(); ++it)
				{
					filesPaths.push_back(QString((*it).path + QDir::separator() + (*it).name).toHtmlEscaped());
				}

				return QString("<div><pre>Файлов: %1<br>Размер: %2<br>%3</pre></div>")
						.arg(m_dupFiles[index.row()].files.length())
						.arg(m_dupFiles[index.row()].size)
						.arg(filesPaths.join("<br>"));
			}
			else
			{
				CloneHunter::DUPFILESINFO* info = static_cast<CloneHunter::DUPFILESINFO*>(index.internalPointer());
				return info->files.at(index.row()).path + QDir::separator() + info->files.at(index.row()).name;
			}
	}

	return QVariant();
}

Qt::ItemFlags FilesDecisionModel::flags(const QModelIndex& index) const
{
	Q_UNUSED(index)
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
