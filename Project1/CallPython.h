#pragma once
#ifdef _DEBUG
#define _DEBUG_WAS_DEFINE 1
#undef _DEBUG
#endif

#include<Python.h>

#ifdef	_DEBUG_WAS_DEFINE
#define _DEBUG 1
#endif


class CallPython
{
	PyObject *pResult; 
	PyObject* sysPath;
	PyObject *pName;
	PyObject *pModule;

public:
	CallPython();
	~CallPython();

	float convertCurrency(float,char*,char*);

};

