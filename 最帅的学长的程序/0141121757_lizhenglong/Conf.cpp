// Conf.cpp : 实现文件
//

#include "stdafx.h"
#include "0141121757_lizhenglong.h"
#include "Conf.h"
#include "afxdialogex.h"
#include "Ope.h"

// CConf 对话框

IMPLEMENT_DYNAMIC(CConf, CDialogEx)

CConf::CConf(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConf::IDD, pParent)
	, m_mima(_T(""))
{

}

CConf::~CConf()
{
}

void CConf::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_mima);
}


BEGIN_MESSAGE_MAP(CConf, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CConf::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CConf::OnBnClickedButton1)
END_MESSAGE_MAP()


// CConf 消息处理程序


void CConf::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CConf::OnBnClickedButton1()
{
	UpdateData(true);
	if(m_mima==password)
    { COpe dlg;
	CConf::OnOK();
	dlg.DoModal();
	}
	else
		MessageBox(_T("密码错误"),_T("提示") );
}


BOOL CConf::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
