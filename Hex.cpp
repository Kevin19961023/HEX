
// Hex.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Hex.h"
#include "MainFrm.h"

#include "HexDoc.h"
#include "HexView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//try
/*
#include <cstdio>  
#include <cstring>  
#include <string>  
#include <algorithm>  
#include <map>  
#include <vector> 
#include <iostream>
#include <sstream>
using namespace std;

const int N = 1100;  
const int INF = 0x3f3f3f3f;  
 
class CNode
{
public:
	int to;//�յ�  
    int cap; //����  
    int rev;  //�����  
	CNode(int a,int b,int c);
	~CNode(void);
};

CNode::CNode(int a,int b,int c)
{
	to = a;//�յ�  
    cap = b; //����  
    rev = c;  //�����  
}


CNode::~CNode(void)
{
}

  
vector<CNode> v[N];  
bool used[N];  
  
void add_Node(int from,int to,int cap)  //�ر������Ӱ��  
{  
    v[from].push_back(CNode(to,cap,v[to].size()));  
    v[to].push_back(CNode(from,0,v[from].size()-1));  
}  
  
int dfs(int s,int t,int f)  
{  
    if(s==t)  
        return f;  
    used[s]=true;  
    for(int i=0;i<v[s].size();i++)  
    {  
        CNode &tmp = v[s][i];  //ע��  
        if(used[tmp.to]==false && tmp.cap>0)  
        {  
            int d=dfs(tmp.to,t,min(f,tmp.cap));  
            if(d>0)  
            {  
                tmp.cap-=d;  
                v[tmp.to][tmp.rev].cap+=d;  
                return d;  
            }  
        }  
    }  
    return 0;  
}  
  
int max_flow(int s,int t)  
{  
    int flow=0;  
    for(;;){  
        memset(used,false,sizeof(used));  
        int f=dfs(s,t,INF);  
        if(f==0)  
            return flow;  
        flow+=f;  
    }  
}  
*/
////////////////////

// CHexApp

BEGIN_MESSAGE_MAP(CHexApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CHexApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CHexApp ����

CHexApp::CHexApp()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Hex.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CHexApp ����

CHexApp theApp;


// CHexApp ��ʼ��

BOOL CHexApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CHexDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CHexView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CHexApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CHexApp ��Ϣ�������


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
public:
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CHexApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CHexApp �Զ������/���淽��

void CHexApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CHexApp::LoadCustomState()
{
}

void CHexApp::SaveCustomState()
{
}

// CHexApp ��Ϣ�������





void CAboutDlg::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ 
	/*
	5 4
1 2 40
1 4 20
2 4 20
2 3 30
3 4 10
	
    int n,m;  
    n = 5;
	m = 4;
        memset(v,0,sizeof(v));  
        
            int x,y,z;  
            x = 1;y = 2;z = 40;
			add_Node(x,y,z);
			x = 1;y = 4;z = 20;
			add_Node(x,y,z);
			x = 2;y = 4;z = 20;
			add_Node(x,y,z);
			x = 2;y = 3;z = 30;
			add_Node(x,y,z);
			x = 3;y = 4;z = 10;
            add_Node(x,y,z);
			stringstream os;
				os << max_flow(1,m);
				string str = os.str();
				CString cstr;
				cstr = str.c_str();
				MessageBox((_bstr_t)cstr); 

  */
	CDialogEx::OnRButtonDblClk(nFlags, point);
}
