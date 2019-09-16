// ActiveX_Sumatrapdf.cpp : CActiveX_SumatrapdfApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "ActiveX_Sumatrapdf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CActiveX_SumatrapdfApp theApp;

const GUID CDECL _tlid = { 0xF57E33F0, 0xBC15, 0x4EDA, { 0x8C, 0xAE, 0x88, 0x78, 0x9, 0x92, 0xD0, 0x33 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CActiveX_SumatrapdfApp::InitInstance - DLL 初始化

BOOL CActiveX_SumatrapdfApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// CActiveX_SumatrapdfApp::ExitInstance - DLL 终止

int CActiveX_SumatrapdfApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
