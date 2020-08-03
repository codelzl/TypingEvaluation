
// 0141121757_lizhenglongDlg.cpp : ʵ���ļ�
//
#pragma   comment(lib, "winmm.lib")
#include "stdafx.h"
#include "0141121757_lizhenglong.h"
#include "0141121757_lizhenglongDlg.h"
#include "afxdialogex.h"
#include "Mmsystem.h"
#pragma   comment(lib, "pdflib.lib")
#include "pdflib.h"
#include "pdflib.hpp"
#include "base64.h"
#include "Ope.h"
#include "Conf.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

MCI_OPEN_PARMS op;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy0141121757_lizhenglongDlg �Ի���




CMy0141121757_lizhenglongDlg::CMy0141121757_lizhenglongDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy0141121757_lizhenglongDlg::IDD, pParent)
	, m_examid(_T(""))
	, m_userid(_T(""))
	, m_enter(_T(""))
	, theedit5focustimer(0)
	, Answer(_T(""))
	, Accuracy(0)
	, m_enterStr(_T(""))
	, wnum(0)
	, outp(0)
	, qspeed(0)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_eW = _T("");
}

void CMy0141121757_lizhenglongDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_examid);
	DDV_MaxChars(pDX, m_examid, 11);
	DDX_Text(pDX, IDC_EDIT3, m_userid);
	DDV_MaxChars(pDX, m_userid, 18);
	DDX_Text(pDX, IDC_EDIT1, m_eW);
	DDX_Control(pDX, IDC_COMBO1, m_Choose);
	DDX_Text(pDX, IDC_EDIT5, m_enter);

}

BEGIN_MESSAGE_MAP(CMy0141121757_lizhenglongDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_TIMER()
    ON_EN_CHANGE(IDC_EDIT5, &CMy0141121757_lizhenglongDlg::OnEnChangeEdit5)
	ON_EN_SETFOCUS(IDC_EDIT5, &CMy0141121757_lizhenglongDlg::OnSetfocusEdit5)
	ON_BN_CLICKED(IDC_OPE, &CMy0141121757_lizhenglongDlg::OnBnClickedOpe)
	ON_BN_CLICKED(IDC_Stest, &CMy0141121757_lizhenglongDlg::OnBnClickedStest)
	ON_BN_CLICKED(IDC_SUBMIT, &CMy0141121757_lizhenglongDlg::OnBnClickedSubmit)
	ON_BN_CLICKED(IDC_PRINT, &CMy0141121757_lizhenglongDlg::OnBnClickedPrint)
END_MESSAGE_MAP()

// CMy0141121757_lizhenglongDlg ��Ϣ�������

BOOL CMy0141121757_lizhenglongDlg::OnInitDialog()//������ʼ��
{
	CDialogEx::OnInitDialog();
    ((CEdit*)GetDlgItem(IDC_ENTRY))->SetReadOnly(true);//������Ϣ��ʼ��
	theedit5focustimer=0;
	GetDlgItem(IDC_PRINT)->EnableWindow(false);
	GetDlgItem(IDC_SUBMIT)->EnableWindow(FALSE);
    CString subTemp,questions;
	 ::GetPrivateProfileStringW(_T("ExamInfo"),_T("total_questions"),_T(""),questions.GetBuffer(MAX_PATH),MAX_PATH,_T("d:\\ExamInfo.ini"));
	questions.ReleaseBuffer();
	for(int i=1;i<=_ttoi(questions);i++)
	{
		subTemp.Format(_T("��%d��"),i);
	    m_Choose.AddString(subTemp);
	}
	CString nono;//���ù��ܵĵ�½�����Լ�����
	::GetPrivateProfileStringW(_T("nono"),_T("nono"),_T(""),nono.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\nono.ini"));
	string sAnswer=(CStringA)nono;
	password=getdecode(sAnswer).c_str();
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
    CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
    SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy0141121757_lizhenglongDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


void CMy0141121757_lizhenglongDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1)  /  2;
		int y = (rect.Height() - cyIcon + 1) /  2;
        // ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CMy0141121757_lizhenglongDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMy0141121757_lizhenglongDlg::OnTimer(UINT_PTR nIDEvent)//����ʱ�亯��
{
	int restTime;
	switch(nIDEvent)
	{case 1:{if(examTime==timerData1)
	{
		 m_eW="���Խ������Ѿ��Զ��ύ��";
		 GetDlgItem(IDC_INFO)->SetWindowText(m_eW);
		 ((CEdit*)GetDlgItem(IDC_ENTRY))->SetReadOnly(true);//ʱ�䵽��ֹͣ¼��
		 GetDlgItem(IDC_SUBMIT)->EnableWindow(false);
		GetDlgItem(IDC_PRINT)->EnableWindow(true);
		 KillTimer(1);
		 OnStop();  
	 break;
	}
		 restTime=examTime-timerData1;
		 m_eW.Format(_T("����ʱ��ʣ�ࣺ%d:%d"),restTime/60,restTime%60);
		 GetDlgItem(IDC_INFO)->SetWindowText(m_eW);
		 timerData1=timerData1+1;
	 break;
	}
	 default:
	 {break;}
	}
}



void CMy0141121757_lizhenglongDlg::OnPlay()//���ֲ��ź���
{
	CString str;
    DWORD cdlen;	//��Ƶ�ļ�����
	op.dwCallback=NULL; 
	op.lpstrAlias=NULL;		
	op.lpstrDeviceType=_T("MPEGAudio");					//�豸���ͣ�������ļ������������� 
	CString path;
	path.Format(_T("D:\\%d.mp3"),m_Choose.GetCurSel()+1);
	op.lpstrElementName=path;	                      //�ļ�·�� 
	op.wDeviceID=NULL;								 //���豸�ɹ��Ժ󱣴�����豸�ű��� 
	UINT rs;										 //���ܺ������ؽ�� 
 //����������豸���ɹ�����0�����򷵻ش���ţ������������������MCI_OPEN_ELEMENT  
	rs=mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT,(DWORD)&op);
	mciSendCommand(NULL,MCI_SET,MCI_SET_DOOR_OPEN,NULL);
	cdlen=getinfo(op.wDeviceID,MCI_STATUS_LENGTH);//��ȡ��Ƶ�ļ�����
	if(rs==0)        //�豸�򿪳ɹ��Ͳ����ļ� 
	 { 
		 MCI_PLAY_PARMS pp; 
		 pp.dwCallback=NULL; 
		 pp.dwFrom=0;      //��ʼ���ŵ�λ�� 
		 mciSendCommand(op.wDeviceID,MCI_PLAY,MCI_NOTIFY,(DWORD)&pp);
	 //�����ļ������������������ΪMCI_WAIT����򴰿ڻᱻ������Ϊ�˱����������������ΪMCI_NOTIFY 
	 }

}

DWORD CMy0141121757_lizhenglongDlg::getinfo(UINT wDeviceID, DWORD item)
{
	 MCI_STATUS_PARMS mcistatusparms;
     mcistatusparms.dwCallback=(DWORD)GetSafeHwnd();
     mcistatusparms.dwItem=item;
     mcistatusparms.dwReturn=0;
     mciSendCommand(wDeviceID,MCI_STATUS,MCI_STATUS_ITEM,(DWORD)&mcistatusparms);
     return mcistatusparms.dwReturn;
}


void CMy0141121757_lizhenglongDlg::OnStop()
{ 
 //��WM_CLOSE��Ϣ��������з���MCI_CLOSE����ر��豸
	 MCI_GENERIC_PARMS gp; 
	 gp.dwCallback=NULL; 
	 mciSendCommand(op.wDeviceID,MCI_CLOSE,MCI_WAIT,(DWORD)&gp);  
}


void CMy0141121757_lizhenglongDlg::OnEnChangeEdit5()//����ɼ�
{
    CString Percentage_Accuracy,Percentage_Speed,Max_Speed; 
	::GetPrivateProfileStringW(_T("ExamInfo"),_T("percentage_accuracy"),_T(""),Percentage_Accuracy.GetBuffer(MAX_PATH),MAX_PATH,_T("d:\\ExamInfo.ini"));
	 Percentage_Accuracy.ReleaseBuffer();
	::GetPrivateProfileStringW(_T("ExamInfo"),_T("percentage_speed"),_T(""),Percentage_Speed.GetBuffer(MAX_PATH),MAX_PATH,_T("d:\\ExamInfo.ini"));
	 Percentage_Speed.ReleaseBuffer();
	::GetPrivateProfileStringW(_T("ExamInfo"),_T("max_speed"),_T(""),Max_Speed.GetBuffer(MAX_PATH),MAX_PATH,_T("d:\\ExamInfo.ini"));
	 Max_Speed.ReleaseBuffer();    
	 double  FPercentage_Accuracy,FPercentage_Speed,FMax_Speed;
	 FPercentage_Accuracy=_tstof(Percentage_Accuracy);
     FPercentage_Speed=_tstof(Percentage_Speed);
	 FMax_Speed=_tstof(Max_Speed);
	 UpdateData();
	 m_enterStr=m_enter;
	 ChenkAccurcy(m_enterStr);
     int wordnum = m_enter.GetLength();
	 double Speed=wordnum / (timerData1/60);
	if(Speed>FMax_Speed)
		 Speed= FMax_Speed;
	     qspeed=Speed;
	double Score = FPercentage_Accuracy * Accuracy*100 + FPercentage_Speed * Speed;
	     outp=Score;
	
}


void CMy0141121757_lizhenglongDlg::OnSetfocusEdit5()
{  
	if(0==theedit5focustimer++)
	{
      m_enter="";
	  UpdateData(false);
	}
}

void CMy0141121757_lizhenglongDlg::ChenkAccurcy(CString testStr)//׼ȷ�ʼ���
{
	int strA = Answer.GetLength();
	int strT = testStr.GetLength();

	int **dif = new int*[strA+1];
	for (int i = 0; i < strA + 1; i++)
		dif[i] = new int[strT+1];

	for (int a = 0; a <= strA; a++)
		dif[a][0] = a;
	for (int a = 0l; a <= strT; a++)
		dif[0][a] = a;

	int temp;
	for (int i = 1; i <= strA; i++){
	
		for (int j = 1; j <= strT; j++){
		
			if (Answer.GetAt(i - 1) == testStr.GetAt(j - 1)){
			
				temp = 0;
			}
			else{
			
				temp = 1;
			}

			dif[i][j] = min(min(dif[i - 1][j - 1] + temp, dif[i][j - 1] + 1), dif[i - 1][j] + 1);

		}
	}

	Accuracy = 1 - (double)dif[strA][strT] / max(strA,strT);

}


string CMy0141121757_lizhenglongDlg::getencode(string Answer)//���ܺ���
{   
	string encodeAnswer=base64_encode(reinterpret_cast<const unsigned char*>(Answer.c_str()),Answer.length());
    return encodeAnswer;

}


string CMy0141121757_lizhenglongDlg::getdecode(string Answer)//���ܺ���
{ 
	string nAnswer=base64_decode(Answer);
	return nAnswer;

}


int CMy0141121757_lizhenglongDlg::writeAnswer(string path,string answer)//д�ļ�
{
  ofstream fout;
  fout.open(path,ios_base::out);
	if(fout.is_open())
		{
			fout<<answer;fout.close();
		}
	else
		{
			return 0;
		}
		
	return 1;

}


void CMy0141121757_lizhenglongDlg::EncodeCore(int i)//��a1.txt��ʽ��׼�𰸶������������Ϊ1.txt��ʽ����ɾ��ԭ�еı�׼��a1.txt
{  
	CString subNum,filePath;
	/*::GetPrivateProfileStringW(_T("ExamInfo"),_T("total_questions"),_T(""),subNum.GetBuffer(MAX_PATH),MAX_PATH,_T("d:\\ExamInfo.ini"));
	subNum.ReleaseBuffer();//��������Ŀ��
	for(int i=1;i<=_ttoi(subNum);i++)
	{*/
		filePath.Format(_T("D:\\Exam/a%d.txt"),i);//������׼��
		CString path=filePath;
		CFile file(path,CFile::modeRead);
		int fileLen=(int)file.GetLength();
		CStringA strTemp;
		char* pBuf=strTemp.GetBuffer(fileLen+1);
		file.Read(pBuf,fileLen);
		pBuf[fileLen]='\0';
		strTemp.ReleaseBuffer();
		file.Close();
		Answer=(CString)strTemp;
	    string sAnswer=(CStringA)Answer;
		sAnswer=getencode(sAnswer);//���ü��ܺ��������м���
	    filePath.Format(_T("D:\\Exam/%d.txt"),i);
		string filepath=(CStringA)filePath;
		writeAnswer(filepath,sAnswer);//���ܴ�д��a.txt
		filePath.Format(_T("D:\\Exam/a%d.txt"),i);//ɾ��δ���ܴ�
		DeleteFile(filePath);	
}



void CMy0141121757_lizhenglongDlg::OnBnClickedOpe()//�������õ�½�������
{   
	CConf dlg;
	dlg.DoModal();
}




void CMy0141121757_lizhenglongDlg::Checkuserid(void)//���֤��ϢУ�麯��
{   CString str;
    m_Choose.GetLBText(m_Choose.GetCurSel(), str);   
    int weight[]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
	char validate[]={ '1','0','X','9','8','7','6','5','4','3','2'};  
	int sum=0;
	int mode=0;
	if (m_userid.GetLength()==18)
	{
		for(int i=0;i<m_userid.GetLength()-1;i++)
		{
			sum=sum+(m_userid[i]-'0')*weight[i];
		}
		mode=sum%11;
		if (validate[mode]==m_userid[17])
		{    MessageBox(str,_T("��ѡ�����Ŀ���Ϊ��")); 
		     MessageBox(_T("��ȷ����ʼ����"),_T("��ʾ") ); 
			SetTimer(1,1000,NULL);
			GetDlgItem(IDC_Stest)->EnableWindow(FALSE);
			GetDlgItem(IDC_Ezkz)->EnableWindow(FALSE);
			GetDlgItem(IDC_ESFZ)->EnableWindow(FALSE);
			GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
			OnPlay();
			m_enter="���Կ�ʼ�ˣ���������������";
		    GetDlgItem(IDC_SUBMIT)->EnableWindow(TRUE);
		    ((CEdit*)GetDlgItem(IDC_ENTRY))->SetReadOnly(false);
			UpdateData(FALSE);

		return;
        }
	}
	
	MessageBox(_T("���֤����Ϣ����,���������룡����"),_T("��ʾ") ); 
}


void CMy0141121757_lizhenglongDlg::Checkexamid(void)//׼��֤��ϢУ�麯��
{
	
	if(m_examid.IsEmpty())
	{
		
		MessageBox(_T("������11λ׼��֤�ţ�"),_T("��ʾ") ); 
		return;
	}
		if (m_examid.GetLength()!=11)
	{
		
		MessageBox(_T("������11λ׼��֤�ţ�"),_T("��ʾ") ); 
		return;
		
	}
		else	Checkuserid();//����׼��֤���Ժ󣬵������֤��ϢУ�麯��
}


CString CMy0141121757_lizhenglongDlg::readAnswer(CString path)//���ļ�����
{
    CFile file(path,CFile::modeRead);
	int fileLen=(int)file.GetLength();
	CStringA strTemp;
	char* pBuf=strTemp.GetBuffer(fileLen+1);
	file.Read(pBuf,fileLen);
	pBuf[fileLen]='\0';
	strTemp.ReleaseBuffer();
	file.Close();
    return (CString)strTemp;
}


void CMy0141121757_lizhenglongDlg::OnBnClickedStest()//�㿪ʼ���Զ�Ӧ��ť�ĺ���
{
	CString Num,pathA;
	::GetPrivateProfileStringW(_T("ExamInfo"),_T("total_questions"),_T(""),Num.GetBuffer(MAX_PATH),MAX_PATH,_T("d:\\ExamInfo.ini"));
	Num.ReleaseBuffer();//��������Ŀ��
	CString texamtime;
	::GetPrivateProfileStringW(_T("ExamInfo"),_T("total_minutes"),_T(""),texamtime.GetBuffer(MAX_PATH),MAX_PATH,_T("d:\\ExamInfo.ini"));
	texamtime.ReleaseBuffer();
	examTime=_ttoi(texamtime)*60;
	timerData1=0;
    UpdateData();
	CString questions;
	::GetPrivateProfileStringW(_T("ExamInfo"),_T("total_questions"),_T(""),questions.GetBuffer(MAX_PATH),MAX_PATH,_T("d:\\ExamInfo.ini"));
	questions.ReleaseBuffer();
    int nCount = _ttoi(questions);                       //��ȡComboBox��Ԫ�ظ��� 
    int iPos = m_Choose.GetCurSel();                             //��ǰѡ�е�Ԫ������
    CString str;
    m_Choose.GetLBText(m_Choose.GetCurSel(), str);  //��ǰѡ�е��ַ��������
    CString a;
	a.Format(_T("%d"), iPos+1);//��ѡ�����Ŀ���
    CString subNum,filePath;
    filePath.Format(_T("D://Exam/%d.txt"),m_Choose.GetCurSel()+1);
    Answer=readAnswer(filePath);//������txt��Ϣ
    string sAnswer=(CStringA)Answer;//cstringתstring
	Answer=getdecode(sAnswer).c_str();
    Checkexamid();//У��׼��֤��
}


void CMy0141121757_lizhenglongDlg::OnBnClickedSubmit()//���ύ���Զ�Ӧ��ť�ĺ���
{
	if(MessageBox(_T("�ύ֮�����ı��ο��Խ�������ȷ���ύô"),_T("��ʾ"),MB_ICONEXCLAMATION|MB_OKCANCEL)==IDOK)
	{
		GetDlgItem(IDC_PRINT)->EnableWindow(true);
		GetDlgItem(IDC_ENTRY)->EnableWindow(false);
		GetDlgItem(IDC_SUBMIT)->EnableWindow(false);
		OnStop();//�ύ�����Ժ�ֹͣ���ֲ���
		KillTimer(1);
		m_eW.Format(_T("������ʱ��%d:%d"),int(timerData1)/60,int(timerData1)%60);
		GetDlgItem(IDC_INFO)->SetWindowText(m_eW);
	}

}


void CMy0141121757_lizhenglongDlg::OnBnClickedPrint()//��ӡPDF����
{
	CString strTemp;
	PDF *p=NULL;
	UpdateData(true);
	int         i = 0, j = 0, Left = 50, Top = 800, Right = 545;
	int         Font_E = 0, Font_CS = 0, Font_CS2 = 0, TextFlow = 0;
	if ((p = PDF_new()) == (PDF *) 0)
	{
        MessageBox(_T("Couldn��t create PDFlib object (out of memory)!��n"));
        return;
	}
    PDF_TRY(p)
	{	
		PDF_set_parameter(p, "errorpolicy", "return");
		PDF_set_parameter(p, "hypertextencoding", "host");
        if (PDF_begin_document(p, "D://pdflib_report.pdf", 0, "") == -1)
		{
			strTemp.Format(_T("Error: %s��n"), PDF_get_errmsg(p));
            MessageBox(strTemp);
            return;
        }
		
        PDF_set_info(p,"Creator", "pdflib");
        PDF_set_info(p, "Author", "www.pdflib.com");
        PDF_set_info(p, "Title", "The report of student");
        PDF_begin_page_ext(p, a4_width, a4_height, " ");
		Font_E = PDF_load_font(p, "Helvetica-Bold", 0, "winansi", "");
		Font_CS = PDF_load_font(p, "\xEF\xBB\xBF\xE9\xBB\x91\xE4\xBD\x93", 0, "unicode", "");
       PDF_setfont(p,Font_CS, 20);
		PDF_set_text_pos(p,Left,Top);
		strTemp=_T("׼��֤��:");//��ӡ׼��֤��Ϣ
	    PDF_show2(p,(LPSTR)strTemp.GetBuffer(),strTemp.GetLength()*2);
		Top=Top-30;
	    PDF_continue_text2(p,(LPSTR)m_examid.GetBuffer(),m_examid.GetLength()*2);
		Top=Top-30;
		strTemp=_T("���֤��:");//��ӡ���֤��Ϣ
		PDF_continue_text2(p,(LPSTR)strTemp.GetBuffer(),strTemp.GetLength()*2);
		Top=Top-30;
	    PDF_continue_text2(p,(LPSTR)m_userid.GetBuffer(),m_userid.GetLength()*2);
		Top=Top-30;
		strTemp=_T("����׼ȷ�ʣ�%����");//��ӡ׼ȷ����Ϣ
		PDF_continue_text2(p,(LPSTR)strTemp.GetBuffer(),strTemp.GetLength()*2);
		Top=Top-30;
		strTemp.Format(_T("%f"),(Accuracy*100));
	    PDF_continue_text2(p,(LPSTR)strTemp.GetBuffer(),strTemp.GetLength()*2);
		Top=Top-30;
		strTemp="              ";
	    PDF_continue_text2(p,(LPSTR)strTemp.GetBuffer(),strTemp.GetLength()*2);
		Top=Top-10;
	    strTemp=_T("�����ٶȣ�����/���ӣ���");//��ӡ�����ٶ���Ϣ
		PDF_continue_text2(p,(LPSTR)strTemp.GetBuffer(),strTemp.GetLength()*2);
		Top=Top-30;
		strTemp.Format(_T("%f"),qspeed);
	    PDF_continue_text2(p,(LPSTR)strTemp.GetBuffer(),strTemp.GetLength()*2);
		Top=Top-30;
		strTemp="              ";
	    PDF_continue_text2(p,(LPSTR)strTemp.GetBuffer(),strTemp.GetLength()*2);
		Top=Top-10;
        strTemp=_T("���ο��Գɼ�Ϊ��");//��ӡ�ɼ���Ϣ
		PDF_continue_text2(p,(LPSTR)strTemp.GetBuffer(),strTemp.GetLength()*2);
		Top=Top-30;
		strTemp.Format(_T("%f"),outp);
	    PDF_continue_text2(p,(LPSTR)strTemp.GetBuffer(),strTemp.GetLength()*2);
		Top=Top-30;
		strTemp="              ";
	    PDF_continue_text2(p,(LPSTR)strTemp.GetBuffer(),strTemp.GetLength()*2);
		Top=Top-10;
		strTemp="�����Ǳ��ο��Ե�¼�����ݣ�";//��ӡ����¼����Ϣ
	    PDF_continue_text2(p,(LPSTR)strTemp.GetBuffer(),strTemp.GetLength()*2);
		Top=Top-30;
		PDF_setfont(p,Font_CS, 15);
		int len=m_enter.GetLength();
	    for(int i =0;i<len;i=i+31)
		{
			strTemp=m_enter.Left(31);
			m_enter.Delete(0,31);
			PDF_continue_text2(p,(LPSTR)strTemp.GetBuffer(),strTemp.GetLength()*2);
			Top=Top-30;
	
		}
	    PDF_end_page_ext(p, "");
        PDF_end_document(p, "");
	}
	PDF_CATCH(p) 
	{
        MessageBox(_T("PDFlib exception occurred in pdflib_report sample:��n"));
		strTemp.Format(_T("[%d] %s: %s��n"),PDF_get_errnum(p), PDF_get_apiname(p), PDF_get_errmsg(p));
        MessageBox(strTemp);
        PDF_delete(p);
        return;
    }
    PDF_delete(p);
     MessageBox(_T("��ӡ��ϣ������ɼ���Ϣ������D�̣��㡰ȷ�����������ɼ�PDF"),_T("��ʾ") );
	 ShellExecute(NULL,_T("open"),_T("D://pdflib_report.pdf"),NULL,NULL,SW_SHOWMAXIMIZED);///��ӡ�������ʹ��Ĭ��pdf�Ķ�����ȫ����
    return;
}



