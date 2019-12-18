#include <QDir>
#include <QFile>
#include <QDebug>
#include "GetFilesInfoProcess.h"

GetFilesInfoProcess::GetFilesInfoProcess(const CloneHunter::PROGRAMPARAMS& params) : QObject(nullptr),
	m_stop(true),
	m_params(params)
{
	qRegisterMetaType<CloneHunter::FilesInfo>("CloneHunter::FilesInfo");
}

GetFilesInfoProcess::~GetFilesInfoProcess()
{
	qDebug() << "GetFilesInfoProcess::~GetFilesInfoProcess";
}

void GetFilesInfoProcess::process()
{
	m_stop = false;

	m_filesInfo.clear();
	getFilesInfo(m_params, m_filesInfo);
	emit finished();
}

void GetFilesInfoProcess::abort()
{
	qDebug() << "GetFilesInfoProcess::abort";
	m_stop = true;
}

void GetFilesInfoProcess::getFilesInfo(const CloneHunter::PROGRAMPARAMS& params, CloneHunter::FilesInfo& filesInfo)
{
	for(auto it=params.directories.begin(); it!=params.directories.end(); ++it)
	{
		CloneHunter::FilesInfo directoryFilesInfo = readDir(*it /*, params.min, params.max*/);
		filesInfo.append(directoryFilesInfo);

		if (m_stop)
		{
			emit notifyAbort();
			return;
		}
	}

	emit notifyFilesInfo(filesInfo);
}

CloneHunter::FilesInfo GetFilesInfoProcess::readDir(const QString& path)
{
	CloneHunter::FilesInfo filesInfo;
	CloneHunter::FILEINFO file;

	qDebug() << "Scan: " << path;

	QDir dir;
	dir.setPath(path);

	QFileInfoList entries = dir.entryInfoList(QDir::AllDirs | QDir::Files | QDir::NoSymLinks | QDir::Hidden | QDir::NoDotAndDotDot); // exclude "." and ".."

	for (int i = 0; i < entries.count(); i++)
	{
		QFileInfo fileInfo = entries[i];

		if (fileInfo.isDir())
		{
			if (path.endsWith('/') || path.endsWith('\\'))
			{
				filesInfo.append(readDir(path + fileInfo.fileName()/*, min, max*/));
			}
			else
			{
				filesInfo.append(readDir(path + QDir::separator() + fileInfo.fileName()/*, min, max*/));
			}
		}
		else
		{
			qDebug() << "file: " << fileInfo.fileName();

			file.size = fileInfo.size();
			file.path = fileInfo.absolutePath();
			file.name =  fileInfo.fileName();
			file.lastModified = fileInfo.lastModified();
			filesInfo.push_back(file);

			//_sleep(100);
		}

		if (m_stop)
		{
			break;
		}
	}

	return filesInfo;
}
