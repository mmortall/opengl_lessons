// Copyright (C) 2011-2012 Sergey Taraban

#ifndef CTIME_H_
#define CTIME_H_

class CTime
{
public:
	CTime();

	unsigned long getTick();
	void Reset();
	double getDelta();

#ifdef WIN32
	__int64 m_start;
#endif

#ifdef LINUX
	timespec m_time;
	timespec m_start;
#endif
};

#endif /* CTIME_H_ */
