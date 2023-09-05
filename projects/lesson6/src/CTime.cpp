/*
 * CTime.cpp
 *
 *  Created on: 13.08.2011
 *      Author: sergey
 */

#include "stdafx.h"

#include "CTime.h"

//--------------------------------------
CTime::CTime()
{
	Reset();
}

//--------------------------------------
void CTime::Reset()
{
#ifdef WIN32
	QueryPerformanceCounter((LARGE_INTEGER*)&m_start);
#endif
#ifdef LINUX
	clock_gettime(CLOCK_REALTIME,&m_start);
#endif
}

//--------------------------------------
double CTime::getDelta()
{
#ifdef WIN32
	static __int64 end;
	QueryPerformanceCounter((LARGE_INTEGER*)&end);

	__int64 freq;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	return (double)((end-m_start))/freq;

#endif
#ifdef LINUX
	clock_gettime(CLOCK_REALTIME,&m_time);
	return static_cast<double>((m_time.tv_sec-m_start.tv_sec)+(m_time.tv_nsec-m_start.tv_nsec)/1000000000.0);
#endif
}
