// ActiveX_SumatrapdfPropPage.cpp : CActiveX_SumatrapdfPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "ActiveX_Sumatrapdf.h"
#include "ActiveX_SumatrapdfPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CActiveX_SumatrapdfPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CActiveX_SumatrapdfPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CActiveX_SumatrapdfPropPage, "ACTIVEX_SUMATR.ActiveX_SumatrPropPage.1",
	0xef566484, 0x56fb, 0x4f18, 0x9a, 0x3e, 0xd0, 0xbf, 0xd, 0x30, 0x67, 0xb3)



// CActiveX_SumatrapdfPropPage::CActiveX_SumatrapdfPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CActiveX_SumatrapdfPropPage ��ϵͳע�����

BOOL CActiveX_SumatrapdfPropPage::CActiveX_SumatrapdfPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_ACTIVEX_SUMATRAPDF_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CActiveX_SumatrapdfPropPage::CActiveX_SumatrapdfPropPage - ���캯��

CActiveX_SumatrapdfPropPage::CActiveX_SumatrapdfPropPage() :
	COlePropertyPage(IDD, IDS_ACTIVEX_SUMATRAPDF_PPG_CAPTION)
{
}



// CActiveX_SumatrapdfPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CActiveX_SumatrapdfPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CActiveX_SumatrapdfPropPage ��Ϣ�������
