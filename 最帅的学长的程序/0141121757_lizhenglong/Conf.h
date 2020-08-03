#pragma once


// CConf 对话框

class CConf : public CDialogEx
{
	DECLARE_DYNAMIC(CConf)

public:
	CConf(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CConf();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_mima;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
};
