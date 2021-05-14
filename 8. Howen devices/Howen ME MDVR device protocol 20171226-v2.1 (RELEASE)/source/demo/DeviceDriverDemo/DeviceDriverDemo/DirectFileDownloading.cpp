
#include "stdafx.h"
#include "DirectFileDownloading.h"
#include <string>

#pragma warning(disable:4996)

DirectFileDownloading*	DirectFileDownloading::_cur = NULL;

DirectFileDownloading::DirectFileDownloading()
{
	m_file = NULL;
	DirectFileDownloading::_cur = this;
}

DirectFileDownloading::~DirectFileDownloading()
{

}

//返回已经下载的文件长度
//return the size of file had downloaded
int DirectFileDownloading::startWork(const char* fileName)
{
	std::string directDownFileName;

	const char* lastFlag = strrchr(fileName, '/');
	if (NULL == lastFlag)
		lastFlag = strrchr(fileName, '\\');

	if (NULL == lastFlag)
		return 0;

	lastFlag += 1;

	extern std::string getCurrentPath();
	std::string _currentPath = getCurrentPath() + "\\download\\";

	if (NULL != lastFlag)
	{
		directDownFileName = _currentPath;
		directDownFileName += lastFlag;
	}
	else
	{
		directDownFileName = _currentPath;
		directDownFileName += fileName;
	}

	m_file = ::fopen(directDownFileName.c_str(), "a+b");
	if (NULL == m_file)
		return 0;

	::fseek(m_file, 0, SEEK_END);
	int length = ftell(m_file);

	return length;
}

void DirectFileDownloading::stopWork()
{
	if (NULL == m_file)
		return;

	::fclose(m_file);
	m_file = NULL;

	AfxMessageBox(_T("downloading finished."));
}

void DirectFileDownloading::writeData(const char* buffer, int length)
{
	if (NULL == m_file)
		return;

	::fwrite(buffer, length, 1, m_file);
}

//是否工作中
//working status
bool DirectFileDownloading::isWorking()
{
	if (NULL == m_file)
		return false;

	return true;
}