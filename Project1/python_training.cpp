//#ifdef _DEBUG
//#define _DEBUG_WAS_DEFINE 1
//#undef _DEBUG
//#endif
//
//#include<Python.h>
//#include<string>
//#include<iostream>
//#ifdef	_DEBUG_WAS_DEFINE
//#define _DEBUG 1
//#endif
//
//int main()
//{
//	Py_Initialize();
//
//	PyObject *pResult;
//	PyObject* sysPath = PySys_GetObject("path");
//	PyList_Append(sysPath, PyUnicode_FromString("D:\\GitHub\\my\\CurrencyConverter\\Project1"));
//
//	PyObject *pName = PyUnicode_FromString("python_code");
//	PyObject *pModule = PyImport_Import(pName);
//
//	if (pModule != NULL) {
//		std::cout << "Python module found\n";
//		PyObject *pDict = PyModule_GetDict(pModule);
//		PyObject *pFunc = PyDict_GetItem(pDict, PyUnicode_FromString("convert_money"));
//
//		if (pFunc != NULL) {
//			PyObject * pArgs = PyTuple_New(3);
//			PyObject * money = PyLong_FromLong(10);
//			PyObject * from = PyUnicode_FromString("USD");
//			PyObject * to = PyUnicode_FromString("EUR");
//
//			PyTuple_SetItem(pArgs, 0, money);
//			PyTuple_SetItem(pArgs, 1, from);
//			PyTuple_SetItem(pArgs, 2, to);
//			
//			pResult = PyObject_CallObject(pFunc,pArgs);
//
//			if (pResult != NULL) {
//				float res = PyFloat_AsDouble(pResult);
//
//				std::cout << res << std::endl;
//			}
//		}
//		else {
//			std::cout << "Couldn't find func\n";
//		}
//	}
//	else
//		std::cout << "Python Module not found\n";
//
//	Py_Finalize();
//	system("pause");
//	return 0;
//}