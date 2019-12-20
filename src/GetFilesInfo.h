#ifndef GETFILESINFO_H
#define GETFILESINFO_H

#include <QObject>
#include <QThread>
#include "types.h"
#include "programParams.h"
#include "GetFilesInfoProcess.h"

/*!
\brief Чтение атрибутов файлов.

Запускает в отдельном потоке чтение атрибутов файлов.
По завершению работы посылает один из сигналов: `completed` или `aborted`.
Результат возвращается в сигнале `completed`.
Сигнал `aborted` посылается при принудительом завершении работы.
*/
class GetFilesInfo : public QObject
{
	Q_OBJECT
public:
	explicit GetFilesInfo(QObject *parent = nullptr);
	virtual ~GetFilesInfo();

	void setParams(const CloneHunter::PROGRAMPARAMS& params);

private:
	QThread* m_thread;
	CloneHunter::PROGRAMPARAMS m_params;
	CloneHunter::FilesInfo m_filesInfo;

	GetFilesInfoProcess* m_threadProcess;

	void createThreadProcess(QThread* thread);

public slots:
	void start();
	void abort();

signals:
	//! Сигнал об успешном завершении.
	void completed(CloneHunter::DupFiles);
	//! Сигнал о прерывании поиска.
	void aborted();
	void notifyProgress(unsigned percent);
};

#endif // GETFILESINFO_H
