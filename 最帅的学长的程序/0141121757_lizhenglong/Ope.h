#pragma once
#include "afxwin.h"


// COpe 对话框

class COpe : public CDialogEx
{
	DECLARE_DYNAMIC(COpe)

public:
	COpe(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COpe();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit6();
	CString m_total_questions;
	CString m_total_minutes;
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnEnChangeEdit9();
	CString m_max_speed;
	CString m_percentage_accuracy;
	CString m_percentage_speed;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	CComboBox m_music;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	CString nono;
	afx_msg void OnEnChangeMfceditbrowse1();
	afx_msg void OnEnChangeMfceditbrowse2();
};
