
// 0141121757_lizhenglongDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include<string>
#include<fstream>
#include<iostream>
using namespace std;


// CMy0141121757_lizhenglongDlg 对话框
class CMy0141121757_lizhenglongDlg : public CDialogEx
{
// 构造
public:
	CMy0141121757_lizhenglongDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY0141121757_LIZHENGLONG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_examid;
	CString m_userid;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	double examTime;
	double timerData1;
	CString m_eW;
	CComboBox m_Choose;
	void OnPlay(void);
	DWORD getinfo(UINT wDeviceID, DWORD item);
	void OnStop(void);
	CString m_enter;
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnSetfocusEdit5();
	int theedit5focustimer;
	void ChenkAccurcy(CString testStr);
	CString Answer;
	double Accuracy;
	CString m_enterStr;
	int wnum;
	double outp;
	double qspeed;
	string getencode(string Answer);
	string getdecode(string Answer);
	int writeAnswer(string path,string answer);
	void EncodeCore(int i);
	afx_msg void OnBnClickedOpe();
	void Checkuserid(void);
	void Checkexamid(void);
	CString readAnswer(CString path);
	afx_msg void OnBnClickedStest();
	afx_msg void OnBnClickedSubmit();
	afx_msg void OnBnClickedPrint();
	afx_msg void OnEnChangeEntry();
};
