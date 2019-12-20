#ifndef GETFILESINFOPROCESS_H
#define GETFILESINFOPROCESS_H

#include <QObject>
#include "programParams.h"
#include "types.h"

class GetFilesInfoProcess : public QObject
{
	Q_OBJECT
public:
	explicit GetFilesInfoProcess(const CloneHunter::PROGRAMPARAMS& params);
	virtual ~GetFilesInfoProcess();

signals:
	//! Сигнал потоку о завершении работы.
	void finished();
	//! Сигнал с результатами работы.
	void notifyFilesInfo(CloneHunter::DupFiles);
	//! Сигнал о прерывании поиска.
	void notifyAbort();
	void notifyProgress(unsigned percent);

public slots:
	void process();
	void abort();

private:
	bool m_stop;
	CloneHunter::PROGRAMPARAMS m_params;
	CloneHunter::FilesInfo m_filesInfo;

	void getFilesInfo(const CloneHunter::PROGRAMPARAMS& params, CloneHunter::FilesInfo& filesInfo);
	CloneHunter::FilesInfo readDir(const QString& path);
	void searchDeep(CloneHunter::FilesInfo& filesInfo, const CloneHunter::PROGRAMPARAMS& params);
	void calcFilesMd5(CloneHunter::FilesInfo& filesInfo, const CloneHunter::PROGRAMPARAMS& params);
	CloneHunter::DupFiles getDupFiles(const CloneHunter::FilesInfo& filesInfo);
};

#endif // GETFILESINFOPROCESS_H
