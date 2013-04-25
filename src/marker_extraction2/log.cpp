//////////////////////////////////////////////////////
// Common files for Robot applications
// 
// Copyright (c) 2002-2008. All Rights Reserved.
// Division of Applied Robot Technology KITECH
// Web: http://www.orobot.net
// Written by KwangWoong Yang<page365@gmail.com>
//
 
//#define _CRT_SECURE_NO_DEPRECATE

#include "StdAfx.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "log.h"

static int _get_current_time(char *text, int len)
{
	struct _timeb timebuffer;
	struct tm tt;

	_ftime( &timebuffer );
	tt = *localtime(&timebuffer.time);

	return _snprintf (text, len, "%02d:%02d:%02d.%03d ", 
		(int)tt.tm_hour, (int)tt.tm_min, (int)tt.tm_sec, (int)timebuffer.millitm);
}

void log(const char *format, ...)
{
    va_list arg_list;
	char log_text[1024+1] = "LOG: ";
	int n = 5;

	n += _get_current_time(log_text+n, 1024-n);
	va_start (arg_list,format);
	n += _vsnprintf (log_text+n, 1024-n, format, arg_list);
	va_end (arg_list);
	n += _snprintf (log_text+n, 1024-n, "\r\n");
	log_text[1024] = '\0';

	OutputDebugString (log_text);
}

