// ActiveX_SumatrapdfPropPage.cpp : CActiveX_SumatrapdfPropPage 属性页类的实现。

#include "stdafx.h"
#include "ActiveX_Sumatrapdf.h"
#include "ActiveX_SumatrapdfPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CActiveX_SumatrapdfPropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CActiveX_SumatrapdfPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CActiveX_SumatrapdfPropPage, "ACTIVEX_SUMATR.ActiveX_SumatrPropPage.1",
	0xef566484, 0x56fb, 0x4f18, 0x9a, 0x3e, 0xd0, 0xbf, 0xd, 0x30, 0x67, 0xb3)



// CActiveX_SumatrapdfPropPage::CActiveX_SumatrapdfPropPageFactory::UpdateRegistry -
// 添加或移除 CActiveX_SumatrapdfPropPage 的系统注册表项

BOOL CActiveX_SumatrapdfPropPage::CActiveX_SumatrapdfPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_ACTIVEX_SUMATRAPDF_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CActiveX_SumatrapdfPropPage::CActiveX_SumatrapdfPropPage - 构造函数

CActiveX_SumatrapdfPropPage::CActiveX_SumatrapdfPropPage() :
	COlePropertyPage(IDD, IDS_ACTIVEX_SUMATRAPDF_PPG_CAPTION)
{
}



// CActiveX_SumatrapdfPropPage::DoDataExchange - 在页和属性间移动数据

void CActiveX_SumatrapdfPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CActiveX_SumatrapdfPropPage 消息处理程序
