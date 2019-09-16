// ActiveX_SumatrapdfCtrl.cpp : CActiveX_SumatrapdfCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "ActiveX_Sumatrapdf.h"
#include "ActiveX_SumatrapdfCtrl.h"
#include "ActiveX_SumatrapdfPropPage.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CActiveX_SumatrapdfCtrl, COleControl)



// 消息映射

BEGIN_MESSAGE_MAP(CActiveX_SumatrapdfCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// 调度映射

BEGIN_DISPATCH_MAP(CActiveX_SumatrapdfCtrl, COleControl)
	DISP_FUNCTION_ID(CActiveX_SumatrapdfCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CActiveX_SumatrapdfCtrl, "OpenFile", dispidOpenFile, OpenFile, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CActiveX_SumatrapdfCtrl, "SearchTextForWhole", dispidSearchTextForWhole, SearchTextForWhole, VT_I4, VTS_BSTR VTS_I4)
	DISP_FUNCTION_ID(CActiveX_SumatrapdfCtrl, "ClearWord", dispidClearWord, ClearWord, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CActiveX_SumatrapdfCtrl, "SearchText", dispidSearchText, SearchText, VT_I4, VTS_BSTR VTS_I4 VTS_UI1 VTS_UI1 VTS_I4)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(CActiveX_SumatrapdfCtrl, COleControl)
END_EVENT_MAP()



// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CActiveX_SumatrapdfCtrl, 1)
	PROPPAGEID(CActiveX_SumatrapdfPropPage::guid)
END_PROPPAGEIDS(CActiveX_SumatrapdfCtrl)



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CActiveX_SumatrapdfCtrl, "ACTIVEX_SUMATRAP.ActiveX_SumatrapCtrl.1",
	0x1ffdcbf1, 0x7bc9, 0x4eda, 0x88, 0x34, 0x8a, 0xd1, 0xfd, 0x72, 0x22, 0x27)



// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CActiveX_SumatrapdfCtrl, _tlid, _wVerMajor, _wVerMinor)



// 接口 ID

const IID IID_DActiveX_Sumatrapdf = { 0xAA407211, 0x5BA5, 0x441A, { 0xBE, 0xE, 0x82, 0x6F, 0xA6, 0xB4, 0x8D, 0xF9 } };
const IID IID_DActiveX_SumatrapdfEvents = { 0x526A5B43, 0xBEBC, 0x43B9, { 0xA2, 0x3D, 0xAF, 0x1A, 0x2D, 0xEF, 0xF5, 0xBD } };


// 控件类型信息

static const DWORD _dwActiveX_SumatrapdfOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CActiveX_SumatrapdfCtrl, IDS_ACTIVEX_SUMATRAPDF, _dwActiveX_SumatrapdfOleMisc)

HWND ghWnd;

// CActiveX_SumatrapdfCtrl::CActiveX_SumatrapdfCtrlFactory::UpdateRegistry -
// 添加或移除 CActiveX_SumatrapdfCtrl 的系统注册表项

BOOL CActiveX_SumatrapdfCtrl::CActiveX_SumatrapdfCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_ACTIVEX_SUMATRAPDF,
			IDB_ACTIVEX_SUMATRAPDF,
			afxRegApartmentThreading,
			_dwActiveX_SumatrapdfOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}

extern int  Entry(HINSTANCE hInstance,/* HINSTANCE hPrevInstance,*/ LPSTR lpCmdLine, int nCmdShow);

// CActiveX_SumatrapdfCtrl::CActiveX_SumatrapdfCtrl - 构造函数

CActiveX_SumatrapdfCtrl::CActiveX_SumatrapdfCtrl()
{
	InitializeIIDs(&IID_DActiveX_Sumatrapdf, &IID_DActiveX_SumatrapdfEvents);
	// TODO: 在此初始化控件的实例数据。

	
}


extern void Exit();

// CActiveX_SumatrapdfCtrl::~CActiveX_SumatrapdfCtrl - 析构函数

CActiveX_SumatrapdfCtrl::~CActiveX_SumatrapdfCtrl()
{
	// TODO: 在此清理控件的实例数据。

	Exit();
}



// CActiveX_SumatrapdfCtrl::OnDraw - 绘图函数

void CActiveX_SumatrapdfCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;
	
	// TODO: 用您自己的绘图代码替换下面的代码。
	/*pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);*/
}



// CActiveX_SumatrapdfCtrl::DoPropExchange - 持久性支持

void CActiveX_SumatrapdfCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}



// CActiveX_SumatrapdfCtrl::OnResetState - 将控件重置为默认状态

void CActiveX_SumatrapdfCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}



// CActiveX_SumatrapdfCtrl::AboutBox - 向用户显示“关于”框

void CActiveX_SumatrapdfCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_ACTIVEX_SUMATRAPDF);
	dlgAbout.DoModal();
}

extern void TestChildWindow(HINSTANCE hInstance);

// CActiveX_SumatrapdfCtrl 消息处理程序


int CActiveX_SumatrapdfCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	static bool bFirst = true;
	if(bFirst)
	{
		//if(cx > 150 && cy> 100)
		{
			ghWnd = m_hWnd;
			HINSTANCE hInstance = AfxGetInstanceHandle();
			Entry(hInstance,NULL,0);

			bFirst = false;
		}
	}
	return 0;
}

extern void OnFrameSize(int cx, int cy);
void CActiveX_SumatrapdfCtrl::OnSize(UINT nType, int cx, int cy)
{
	COleControl::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	//OnMoveFrame();
	OnFrameSize(cx,cy);
	
}

extern LONG OnOpenFile(LPCTSTR filename);
LONG CActiveX_SumatrapdfCtrl::OpenFile(LPCTSTR filename)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	OnOpenFile(filename);
	return 0;
}

int JsSearchWord(LPCTSTR word,LONG color,bool Whole = true ,bool Cur = false ,int page = 1);

LONG CActiveX_SumatrapdfCtrl::SearchTextForWhole(LPCTSTR word, LONG color)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	return JsSearchWord(word, color);

	//return 0;
}

extern void ClearSearchWord(LPCTSTR word);
LONG CActiveX_SumatrapdfCtrl::ClearWord(LPCTSTR word)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	ClearSearchWord(word);

	return 0;
}


LONG CActiveX_SumatrapdfCtrl::SearchText(LPCTSTR text, LONG color, BYTE whole, BYTE cur, LONG page)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return JsSearchWord(text, color,whole?true:false,cur?true:false,page);
	
}
ULONG FAR EXPORT CActiveX_SumatrapdfCtrl::XObjSafe::AddRef()
{
	METHOD_PROLOGUE(CActiveX_SumatrapdfCtrl, ObjSafe)
		return pThis->ExternalAddRef();
}
ULONG FAR EXPORT CActiveX_SumatrapdfCtrl::XObjSafe::Release()
{
	METHOD_PROLOGUE(CActiveX_SumatrapdfCtrl, ObjSafe)
		return pThis->ExternalRelease();
}
HRESULT FAR EXPORT CActiveX_SumatrapdfCtrl::XObjSafe::QueryInterface(REFIID
	iid, void FAR* FAR* ppvObj)
{
	METHOD_PROLOGUE(CActiveX_SumatrapdfCtrl, ObjSafe)
		return (HRESULT)pThis->ExternalQueryInterface(&iid,
			ppvObj);
}
const DWORD dwSupportedBits =
INTERFACESAFE_FOR_UNTRUSTED_CALLER |
INTERFACESAFE_FOR_UNTRUSTED_DATA;
const DWORD dwNotSupportedBits = ~dwSupportedBits;
HRESULT STDMETHODCALLTYPE
CActiveX_SumatrapdfCtrl::XObjSafe::GetInterfaceSafetyOptions( /* [in]
*/ REFIID riid, /* [out] */ DWORD __RPC_FAR *pdwSupportedOptions,
/* [out] */ DWORD __RPC_FAR *pdwEnabledOptions)
{
	METHOD_PROLOGUE(CActiveX_SumatrapdfCtrl, ObjSafe)
		HRESULT retval = ResultFromScode(S_OK);
	IUnknown FAR* punkInterface;
	retval = pThis->ExternalQueryInterface(&riid, (void *
		*)&punkInterface);
	if (retval != E_NOINTERFACE) {
		punkInterface->Release();
	}
	*pdwSupportedOptions = *pdwEnabledOptions =
		dwSupportedBits;
	return retval;
}
HRESULT STDMETHODCALLTYPE
CActiveX_SumatrapdfCtrl::XObjSafe::SetInterfaceSafetyOptions( /* [in]
*/ REFIID riid, /* [in] */ DWORD dwOptionSetMask, /* [in] */ DWORD
dwEnabledOptions)
{
	METHOD_PROLOGUE(CActiveX_SumatrapdfCtrl, ObjSafe)
		IUnknown FAR* punkInterface;
	pThis->ExternalQueryInterface(&riid, (void *
		*)&punkInterface);
	if (punkInterface) {
		punkInterface->Release();
	}
	else {
		return ResultFromScode(E_NOINTERFACE);
	}
	if (dwOptionSetMask & dwNotSupportedBits) {
		return ResultFromScode(E_FAIL);
	}
	dwEnabledOptions &= dwSupportedBits;
	if ((dwOptionSetMask & dwEnabledOptions) != dwOptionSetMask)
	{
		return ResultFromScode(E_FAIL);
	}
	return ResultFromScode(S_OK);
}