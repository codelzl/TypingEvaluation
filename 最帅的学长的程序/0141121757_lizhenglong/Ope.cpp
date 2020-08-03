// Ope.cpp : 实现文件
//

#include "stdafx.h"
#include "0141121757_lizhenglong.h"
#include "0141121757_lizhenglongDlg.h"
#include "Ope.h"
#include "afxdialogex.h"
#include "base64.h"


// COpe 对话框

IMPLEMENT_DYNAMIC(COpe, CDialogEx)

COpe::COpe(CWnd* pParent /*=NULL*/)
	: CDialogEx(COpe::IDD, pParent)
	, m_total_questions(_T(""))
	, m_total_minutes(_T(""))
	, m_max_speed(_T(""))
	, m_percentage_accuracy(_T(""))
	, m_percentage_speed(_T(""))
	, nono(_T(""))
{

}

COpe::~COpe()
{
}

void COpe::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT8, m_total_questions);
	DDV_MaxChars(pDX, m_total_questions, 10);
	DDX_Text(pDX, IDC_EDIT6, m_total_minutes);
	DDV_MaxChars(pDX, m_total_minutes, 10);
	DDX_Text(pDX, IDC_EDIT7, m_max_speed);
	DDV_MaxChars(pDX, m_max_speed, 3);
	DDX_Text(pDX, IDC_EDIT10, m_percentage_accuracy);
	DDX_Text(pDX, IDC_EDIT9, m_percentage_speed);
	DDX_Control(pDX, IDC_COMBO3, m_music);
	DDX_Text(pDX, IDC_EDIT1, nono);
}


BEGIN_MESSAGE_MAP(COpe, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT6, &COpe::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT8, &COpe::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT7, &COpe::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT10, &COpe::OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT9, &COpe::OnEnChangeEdit9)
	ON_BN_CLICKED(IDC_BUTTON1, &COpe::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &COpe::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &COpe::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &COpe::OnEnChangeMfceditbrowse1)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE2, &COpe::OnEnChangeMfceditbrowse2)
END_MESSAGE_MAP()


// COpe 消息处理程序


void COpe::OnEnChangeEdit6()
{  UpdateData(true);
   ::WritePrivateProfileStringW(_T("ExamInfo"),_T("total_minutes"),m_total_minutes,_T("d:\\ExamInfo.ini"));
}


void COpe::OnEnChangeEdit8()
{   UpdateData(true);
   ::WritePrivateProfileStringW(_T("ExamInfo"),_T("total_questions"),m_total_questions,_T("d:\\ExamInfo.ini"));
}



void COpe::OnEnChangeEdit7()
{ UpdateData(true);
   ::WritePrivateProfileStringW(_T("ExamInfo"),_T("max_speed"),m_max_speed,_T("d:\\ExamInfo.ini"));
}


void COpe::OnEnChangeEdit10()
{ UpdateData(true);
   ::WritePrivateProfileStringW(_T("ExamInfo"),_T("percentage_accuracy"),m_percentage_accuracy,_T("d:\\ExamInfo.ini"));
}


void COpe::OnEnChangeEdit9()
{UpdateData(true);
   ::WritePrivateProfileStringW(_T("ExamInfo"),_T("percentage_speed"),m_percentage_speed,_T("d:\\ExamInfo.ini"));
}


void COpe::OnBnClickedButton1()
{   UpdateData(true);
     string sAnswer=(CStringA)nono;
     sAnswer=base64_encode(reinterpret_cast<const unsigned char*>(sAnswer.c_str()),sAnswer.length());
     nono=sAnswer.c_str();
  ::WritePrivateProfileStringW(_T("nono"),_T("nono"),nono,_T("c:\\nono.ini"));
	 MessageBox(_T("修改成功,重新打开程序生效！"),_T("提示"));
}




void COpe::OnBnClickedButton3()
{
	int iPos = m_music.GetCurSel(); 
	 CString a;
	a.Format(_T("%d"), iPos+1);
	if(iPos==0) ::WritePrivateProfileStringW(_T("ExamInfo"),_T("audio_format"),_T("mp3"),_T("d:\\ExamInfo.ini"));
	if(iPos==1) ::WritePrivateProfileStringW(_T("ExamInfo"),_T("audio_format"),_T("wma"),_T("d:\\ExamInfo.ini"));
	MessageBox(_T("修改成功，重新打开程序生效"),_T("提示"));
}





BOOL COpe::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_music.AddString(_T("mp3"));
	m_music.AddString(_T("wma"));
	return TRUE;  
}


void COpe::OnBnClickedButton2()
{
	
	MessageBox(_T("添加成功，重新打开程序生效"),_T("提示"));
}


void COpe::OnEnChangeMfceditbrowse1()
{
	CString selectedPath,str,enstr,questions;
 GetDlgItemText(IDC_MFCEDITBROWSE1, selectedPath);
  ::GetPrivateProfileStringW(_T("ExamInfo"),_T("total_questions"),_T(""),questions.GetBuffer(MAX_PATH),MAX_PATH,_T("d:\\ExamInfo.ini"));
	questions.ReleaseBuffer();
	CMy0141121757_lizhenglongDlg dlg;
	enstr.Format(_T("D:\\Exam\\%d.txt"),_ttoi(questions));
	if(PathFileExists(enstr)){
		MessageBox(_T("题目已经达到最大上限，如需添加，请增加最大题目数或删除最后一个题目"));
	}
	else{
      for(int i=1;i<=_ttoi(questions);i++)
     {
     str.Format(_T("D:\\Exam\\a%d.txt"),i);
	 enstr.Format(_T("D:\\Exam\\%d.txt"),i);
	 if(!PathFileExists(enstr))
	 {
     CopyFile(selectedPath,str,false);
	 dlg.EncodeCore(i);
     MessageBox(selectedPath);
	 break;
	 }
 }
 }
	// TODO:  在此添加控件通知处理程序代码
}


void COpe::OnEnChangeMfceditbrowse2()
{
	
		CString selectedPath,str,questions;
 GetDlgItemText(IDC_MFCEDITBROWSE2, selectedPath);
  ::GetPrivateProfileStringW(_T("ExamInfo"),_T("total_questions"),_T(""),questions.GetBuffer(MAX_PATH),MAX_PATH,_T("d:\\ExamInfo.ini"));
		questions.ReleaseBuffer();
     str.Format(_T("D:\\%d.mp3"),_ttoi(questions));
	if(PathFileExists(str)){
		MessageBox(_T("题目已经达到最大上限，如需添加，请增加最大题目数或删除最后一个题目"));
	}
	else{
 for(int i=1;i<=_ttoi(questions);i++)
 {
     str.Format(_T("D:\\%d.mp3"),i);
	 if(!PathFileExists(str))
	 {
     CopyFile(selectedPath,str,false);
     MessageBox(selectedPath);
	 break;
	 }
 }
	}
}
