#pragma once


// CConf �Ի���

class CConf : public CDialogEx
{
	DECLARE_DYNAMIC(CConf)

public:
	CConf(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConf();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_mima;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
};
