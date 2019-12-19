#include <QDir>
#include <QFile>
#include <QDebug>
#include <QCryptographicHash>
#include "GetFilesInfoProcess.h"
#include "consoleMode/consoleMode.h"
#include "getFiles.h"
#include "calcMd5.h"

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

	int totalFilesCount = m_filesInfo.count();

	CloneHunter::consoleOut(QString(QObject::tr("Total files: %1")).arg(totalFilesCount));

	if (!m_stop && !m_filesInfo.empty())
	{
		searchDeep(m_filesInfo, m_params);

		if (!m_stop)
		{
			CloneHunter::printDupFiles(m_filesInfo, false);
			emit notifyFilesInfo(m_filesInfo);
		}
	}

	if (m_stop)
	{
		emit notifyAbort();
	}

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
			return;
		}
	}
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

void GetFilesInfoProcess::searchDeep(CloneHunter::FilesInfo& filesInfo, const CloneHunter::PROGRAMPARAMS& params)
{
	CloneHunter::consoleOut(QObject::tr("Sort by size"));
	sortFilesInfoBySize(filesInfo);

	CloneHunter::consoleOut(QObject::tr("Filter by size"));
	removeUniqueSizes(filesInfo);

	CloneHunter::consoleOut(QString(QObject::tr("Files count: %1")).arg(filesInfo.size()));

	// For sequental file access.
	sortFilesInfoByPath(filesInfo);

	CloneHunter::consoleOut(QObject::tr("Calc MD5"));
	this->calcFilesMd5(filesInfo, params);

	CloneHunter::consoleOut(QObject::tr("Sort by MD5"));
	sortFilesInfoByMd5(filesInfo);

	CloneHunter::consoleOut(QObject::tr("Filter by MD5"));
	removeUniqueMd5(filesInfo);

	CloneHunter::consoleOut(QString(QObject::tr("Files count: %1")).arg(filesInfo.size()));

	if (params.sort)
	{
		sortFilesInfoByPath(filesInfo);
	}
}

void GetFilesInfoProcess::calcFilesMd5(CloneHunter::FilesInfo& filesInfo, const CloneHunter::PROGRAMPARAMS& params)
{
	qint64 totalSize = CloneHunter::getFileSizes(filesInfo, params);
	qint64 scannedSize(0);
	unsigned oldCto = 99;
	unsigned i(0);

	CloneHunter::consoleOut(QString(QObject::tr("Total size: %1 Count: %2")).arg(totalSize).arg(filesInfo.size()));

	for (CloneHunter::FilesInfo::iterator it = filesInfo.begin(); it != filesInfo.end(); ++it)
	{
		i++;

		if (it->size != 0 && it->size >= params.min && (it->size <= params.max))
		{
			QFile file;
			file.setFileName(it->path + "/" + it->name);

			if (file.open(QIODevice::ReadOnly))
			{
				QByteArray content;
				QCryptographicHash hash(QCryptographicHash::Md5);
				hash.reset();

				do
				{
					if (m_stop)
					{
						return;
					}

					content = file.read(8*1024*1024);

					if (content.size() != 0)
					{
						hash.addData(content);

						{ // TODO: вынести отдельно
							scannedSize += content.size();
							unsigned cto = (100.0 * scannedSize / totalSize);

							emit notifyProgress(cto);

							if (oldCto / 10 != cto / 10)
							{
								oldCto = cto;
								CloneHunter::consoleOut(QString("%1%").arg(cto - cto % 10));
							}
						}
					}
				}
				while (content.size() != 0);

				file.close();
//				QByteArray md5hash = hash.result();
//				it->md5 = QString(md5hash.toHex());
				it->md5 = hash.result();
			}
		}
	}
}
