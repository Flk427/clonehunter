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
	void notifyFilesInfo(CloneHunter::FilesInfo filesInfo);
	//! Сигнал о прерывании поиска.
	void notifyAbort();

public slots:
	void process();
	void abort();

	void getFilesInfo(const CloneHunter::PROGRAMPARAMS& params, CloneHunter::FilesInfo& filesInfo);
	CloneHunter::FilesInfo readDir(const QString& path);

private:
	bool m_stop;
	CloneHunter::PROGRAMPARAMS m_params;
	CloneHunter::FilesInfo m_filesInfo;
};

#endif // GETFILESINFOPROCESS_H
