#pragma once

// ActiveX_SumatrapdfPropPage.h : CActiveX_SumatrapdfPropPage ����ҳ���������


// CActiveX_SumatrapdfPropPage : �й�ʵ�ֵ���Ϣ������� ActiveX_SumatrapdfPropPage.cpp��

class CActiveX_SumatrapdfPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CActiveX_SumatrapdfPropPage)
	DECLARE_OLECREATE_EX(CActiveX_SumatrapdfPropPage)

// ���캯��
public:
	CActiveX_SumatrapdfPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_ACTIVEX_SUMATRAPDF };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

