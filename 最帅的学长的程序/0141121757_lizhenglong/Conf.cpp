// Conf.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "0141121757_lizhenglong.h"
#include "Conf.h"
#include "afxdialogex.h"
#include "Ope.h"

// CConf �Ի���

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


// CConf ��Ϣ�������


void CConf::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox(_T("�������"),_T("��ʾ") );
}


BOOL CConf::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
