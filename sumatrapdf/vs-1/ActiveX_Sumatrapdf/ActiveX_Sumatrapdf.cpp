// ActiveX_Sumatrapdf.cpp : CActiveX_SumatrapdfApp �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "ActiveX_Sumatrapdf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CActiveX_SumatrapdfApp theApp;

const GUID CDECL _tlid = { 0xF57E33F0, 0xBC15, 0x4EDA, { 0x8C, 0xAE, 0x88, 0x78, 0x9, 0x92, 0xD0, 0x33 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CActiveX_SumatrapdfApp::InitInstance - DLL ��ʼ��

BOOL CActiveX_SumatrapdfApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CActiveX_SumatrapdfApp::ExitInstance - DLL ��ֹ

int CActiveX_SumatrapdfApp::ExitInstance()
{
	// TODO: �ڴ�������Լ���ģ����ֹ���롣

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
