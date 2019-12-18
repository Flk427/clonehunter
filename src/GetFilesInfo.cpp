#include <QDebug>
#include "GetFilesInfo.h"

GetFilesInfo::GetFilesInfo(QObject *parent) : QObject(parent),
	m_thread(nullptr),
	m_threadProcess(nullptr)
{
}

GetFilesInfo::~GetFilesInfo()
{
	qDebug() << "GetFilesInfo::~GetFilesInfo";
}

void GetFilesInfo::setParams(const CloneHunter::PROGRAMPARAMS& params)
{
	m_params = params;
}

void GetFilesInfo::start()
{
	m_thread = new QThread();
	createThreadProcess(m_thread);
	m_thread->start();
}

void GetFilesInfo::abort()
{
	qDebug() << "GetFilesInfo::abort";

	if (m_threadProcess != nullptr)
	{
		m_threadProcess->abort();
		m_threadProcess = nullptr;
	}
	else
	{
		emit aborted();
	}
}

void GetFilesInfo::createThreadProcess(QThread* thread)
{
	m_threadProcess = new GetFilesInfoProcess(m_params);

	connect(thread, &QThread::started, m_threadProcess, &GetFilesInfoProcess::process);
	connect(thread, &QThread::finished, thread, &QThread::deleteLater);

	connect(m_threadProcess, &GetFilesInfoProcess::finished, thread, &QThread::quit);
	connect(m_threadProcess, &GetFilesInfoProcess::finished, m_threadProcess, &GetFilesInfoProcess::deleteLater);

	connect(m_threadProcess, &GetFilesInfoProcess::notifyAbort, this, &GetFilesInfo::aborted);
	connect(m_threadProcess, &GetFilesInfoProcess::notifyFilesInfo, this, &GetFilesInfo::completed);

	m_threadProcess->moveToThread(thread);
}
