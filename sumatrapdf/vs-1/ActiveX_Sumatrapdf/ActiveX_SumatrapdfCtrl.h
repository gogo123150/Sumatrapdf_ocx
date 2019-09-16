#pragma once
// ActiveX_SumatrapdfCtrl.h : CActiveX_SumatrapdfCtrl ActiveX �ؼ����������
#include<ObjSafe.h>

// CActiveX_SumatrapdfCtrl : �й�ʵ�ֵ���Ϣ������� ActiveX_SumatrapdfCtrl.cpp��

class CActiveX_SumatrapdfCtrl : public COleControl
{
	DECLARE_DYNCREATE(CActiveX_SumatrapdfCtrl)

// ���캯��
public:
	CActiveX_SumatrapdfCtrl();
	//DECLARE_DYNCREATE(CtryISafeObjectCtrl)
	//........................................................................
	//��������Ҫ���IObjectSafety�ӿڵ����� 
/////////////////////////////////////////////////////////

	BEGIN_INTERFACE_PART(ObjSafe, IObjectSafety)

		STDMETHOD_(HRESULT, GetInterfaceSafetyOptions) (
			/* [in] */REFIID riid,
			/* [out] */DWORD __RPC_FAR *pdwSupportedOptions,
			/* [out] */DWORD __RPC_FAR *pdwEnabledOptions
			);

	STDMETHOD_(HRESULT, SetInterfaceSafetyOptions) (
		/* [in] */REFIID riid,
		/* [in] */DWORD dwOptionSetMask,
		/* [in] */DWORD dwEnabledOptions
		);
	END_INTERFACE_PART(ObjSafe);

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CActiveX_SumatrapdfCtrl();

	DECLARE_OLECREATE_EX(CActiveX_SumatrapdfCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CActiveX_SumatrapdfCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CActiveX_SumatrapdfCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CActiveX_SumatrapdfCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
public:
	enum {
		dispidSearchText = 4L,
		dispidClearWord = 3L,
		dispidSearchTextForWhole = 2L,
		dispidOpenFile = 1L
	};
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	LONG OpenFile(LPCTSTR filename);
	LONG SearchTextForWhole(LPCTSTR word, LONG color);
	LONG ClearWord(LPCTSTR word);
	LONG SearchText(LPCTSTR text, LONG color, BYTE whole, BYTE cur, LONG page);
};

