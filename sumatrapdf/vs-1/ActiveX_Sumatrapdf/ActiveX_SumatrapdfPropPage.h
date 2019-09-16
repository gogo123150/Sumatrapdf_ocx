#pragma once

// ActiveX_SumatrapdfPropPage.h : CActiveX_SumatrapdfPropPage 属性页类的声明。


// CActiveX_SumatrapdfPropPage : 有关实现的信息，请参阅 ActiveX_SumatrapdfPropPage.cpp。

class CActiveX_SumatrapdfPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CActiveX_SumatrapdfPropPage)
	DECLARE_OLECREATE_EX(CActiveX_SumatrapdfPropPage)

// 构造函数
public:
	CActiveX_SumatrapdfPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_ACTIVEX_SUMATRAPDF };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

