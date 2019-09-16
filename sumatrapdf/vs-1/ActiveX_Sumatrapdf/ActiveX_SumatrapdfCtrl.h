#pragma once
// ActiveX_SumatrapdfCtrl.h : CActiveX_SumatrapdfCtrl ActiveX 控件类的声明。
#include<ObjSafe.h>

// CActiveX_SumatrapdfCtrl : 有关实现的信息，请参阅 ActiveX_SumatrapdfCtrl.cpp。

class CActiveX_SumatrapdfCtrl : public COleControl
{
	DECLARE_DYNCREATE(CActiveX_SumatrapdfCtrl)

// 构造函数
public:
	CActiveX_SumatrapdfCtrl();
	//DECLARE_DYNCREATE(CtryISafeObjectCtrl)
	//........................................................................
	//下面是需要添加IObjectSafety接口的内容 
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

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CActiveX_SumatrapdfCtrl();

	DECLARE_OLECREATE_EX(CActiveX_SumatrapdfCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CActiveX_SumatrapdfCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CActiveX_SumatrapdfCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CActiveX_SumatrapdfCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
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

