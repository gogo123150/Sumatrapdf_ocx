#pragma once

// ActiveX_Sumatrapdf.h : ActiveX_Sumatrapdf.DLL ����ͷ�ļ�

#if !defined( __AFXCTL_H__ )
#error "�ڰ������ļ�֮ǰ������afxctl.h��"
#endif

#include "resource.h"       // ������


// CActiveX_SumatrapdfApp : �й�ʵ�ֵ���Ϣ������� ActiveX_Sumatrapdf.cpp��

class CActiveX_SumatrapdfApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

