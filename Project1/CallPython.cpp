#include "CallPython.h"

CallPython::CallPython() : pResult(NULL)
{
	Py_Initialize();

	sysPath = PySys_GetObject("path");
	PyList_Append(sysPath, PyUnicode_FromString("D:\\GitHub\\my\\CurrencyConverter\\Project1"));

	PyObject *pName = PyUnicode_FromString("python_code");
	PyObject *pModule = PyImport_Import(pName);
}


CallPython::~CallPython()
{
	Py_DECREF(pName);
	Py_DECREF(pModule);
	Py_DECREF(pResult);
	Py_DECREF(sysPath);
	Py_Finalize();
}

float CallPython::convertCurrency(float money_amount, char *from_currency, char *to_currency)
{
	if (pModule != NULL) {
		PyObject *pDict = PyModule_GetDict(pModule);
		PyObject *pFunc = PyDict_GetItem(pDict, PyUnicode_FromString("convert_money"));

		if (pFunc != NULL) {
			PyObject * pArgs = PyTuple_New(3);
			PyObject * money = PyFloat_FromDouble(money_amount);
			PyObject * from = PyUnicode_FromString((const char *)from_currency);
			PyObject * to = PyUnicode_FromString((const char *)to_currency);

			PyTuple_SetItem(pArgs, 0, money);
			PyTuple_SetItem(pArgs, 1, from);
			PyTuple_SetItem(pArgs, 2, to);

			pResult = PyObject_CallObject(pFunc, pArgs);

			if (pResult != NULL) {
				float res = PyFloat_AsDouble(pResult);

				return res;
			}
		}
		else
			return -100000;
	}
	else
		return -20000;
}
