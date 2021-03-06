#ifndef FTL_CONTROLS_H
#define FTL_CONTROLS_H
#pragma once
//TODO: WTL 中的 CHAIN_MSG_MAP_ALT(CRichEditCommands<CFirstRibbonView>, 1) 

#include "ftlDefine.h"

#ifndef __ATLCTRLS_H__
#  error ftlControls.h requires WTL( atlctrls.h )
#endif //__ATLCTRLS_H__
#include <atlbase.h>
#include <atlimage.h>
#include <atlgdi.h>

#include <ftlWindow.h>
#include <ftlcom.h>

#include <atlcrack.h>
#include <atlctrls.h>

//控件内部处理 LButtonUp 时，可以通过以下代码向父窗体发送点击消息
/*
//参见 WTL.CBitmapButtonImpl.OnLButtonUp
bool bHover = IsHoverMode();
if(!bHover)
{
   lRet = DefWindowProc(uMsg, wParam, lParam);
}
if(::GetCapture() == m_hWnd)
{
	if(bHover && m_fPressed == 1)
	{
		::SendMessage(GetParent(), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
    }
	::ReleaseCapture();
}
*/

/***********************************************************************************************************
* http://www.functionx.com/visualc/applications/deskpad.htm
* http://blog.csdn.net/takikoyx/article/details/6311807
* 更改 atlctrls 中 CRichEditCtrlT 源码支持高版本的 MSFTEDIT_CLASS RICHEDIT_CLASS
* 
* riched32.dll -> riched20.dll/riched32.dll(模拟) -> msftedit.dll/riched20.dll  -- 98以后的系统， riched20.dll 都好用？
* 为了使用新版本的RichEdit -- 通过定义 _RICHEDIT_VER 宏并包含 RichEdit.H 是否可以？ afxwin 定义为 0x0210
*   1.需要手工更改RC文件： 如 RichEdit20w（RICHED20.DLL 中的 2.0 控件） -> RICHEDIT50W(Msftedit 中的 4.1 控件)
*     或直接放一个 "Custom Control"，然后将ClassName 改为 RICHEDIT50W ? RichEdit20a(哪个版本？）
*   2.在 App 的构造中 LoadLibrary(_T("msftedit.dll")); 析构中 FreeLibrary,
*   3.在 InitInstance 中仍然需要调用 AfxInitRichEdit2 ? -- 实测表明不需要，而且其实现也是加载 RICHED20.DLL 或 RICHED32.DLL
* 更改WTL源码，使用高版本RichEdit(TODO: 更改成根据 _RICHEDIT_VER 宏自动适应？ )
*   0.定义 _RICHEDIT_VER 为高版本，如 0x0500 
*   1.更改 atlctrls.h 中 CRichEditCtrlT 类,
*     GetWndClassName() { return TEXT("RICHEDIT50W"); }
*     GetLibraryName() { return _T("msftedit.dll"); }
*   2.初始化时调用 HMODULE hInstRich = ::LoadLibrary(CRichEditCtrl::GetLibraryName()); 
*   3.结束前 ::FreeLibrary(hInstRich);
*
* 默认时，当用户切换键盘布局(keyboard layout -- 比如中英韩等？)，会自动切换字体(auto font feature)，造成程序出现问题(比如换行后自动改变字体？)，为了关闭该功能：
*   LRESULT lres = SendMessage(hRE, EM_GETLANGOPTIONS, 0, 0);
*   lres &= ~( IMF_AUTOFONT | IMF_AUTOFONTSIZEADJUST) ;
*   SendMessage(hRE, EM_SETLANGOPTIONS, 0, lres);
*   缺省时是：IMF_AUTOFONT 
*             IMF_DUALFONT |   
* 
* TODO:使用中日韩等IME输入法时，
*   1.正确实现 TxImmGetContext/TxImmReleaseContext
*   2.必须将 IME 相关的消息发送给RichEdit进行处理，否则可能出现 韩文的选字符号位置不正确的bug(出现在屏幕的左上角)
*     if ((WM_IME_SETCONTEXT <= uMsg && uMsg <= WM_IME_KEYUP) || WM_IME_STARTCOMPOSITION == uMsg || WM_IME_ENDCOMPOSITION == uMsg || WM_IME_COMPOSITION == uMsg)
*     { m_spTextServices->TxSendMessage(uMsg, wParam, lParam, &lResult); }
*
* Rich Text Edit Control ( RichEdit.H, 在标准 EDIT 控件的基础上扩展 )， 
* 为了使用RichEdit，需要先加载对应的DLL，MFC下调用AfxInitRichEdit ，
*                                        WTL下调用(可能不对) LoadLibrary(CRichEditCtrl::GetLibraryName());
*   IID_ITextServices 
*     系统在textserv.h预定义的（E_NOINTERFACE）                -- {957C25FF-0149-25FF-7895-4901FF25AC8A}
*     自定义或通过GetProcAddress(IID_ITextServices)得到的  -- 8D33F740-CF58-11CE-A89D-00AA006CADC5
*     
+		IID_ITS         	{3B032DE9-017F-25FF-AC2A-7F01FF25B02A}	-- 会返回 E_NOINTERFACE
+		IID_ITextServices	{357825FF-017F-25FF-AC2A-7F01FF25B02A}	_GUID


*     CreateTextServices 
*       riched20.dll!CTxtEdit::Init 中会通过QI查询这个接口：{13E670F5-1A5A-11CF-ABEB-00AA00B65EA1}
*       MsftEdit.dll!CTxtEdit::Init                         {13E670F5-1A5A-11CF-ABEB-00AA00B65EA1}
*
* 有多个版本(可能不对，需要确认)
*   1.0 -- RichEd32.dll (Win95)
*   2.0 -- RICHED20.DLL (Win95/Win98), 不再支持一些在亚洲语言版本的Rich Edit 1.0中支持的消息
*          (如 EM_CONVPOSITION、EM_SETIMECOLOR、EM_SETPUNCTUATION 等)
*   3.0 -- RichEd20.dll(WinXP)
*          Rich Edit 3.0支持Hex To Unicode IME，允许用户采用一种或两种热键方式在十六进制字符和Unicode字符间互换。
*          Word 使用 Alt+x 可将光标前的文字转换成 UNICODE 对应的值；
*   1.0包装(Wrapper Dll for Richedit 1.0) -- riched32.dll(XP/Vista)
*  
*   4.1 -- MsftEdit.dll (WinXP SP1/Vista)
*   5.?? -- Win7(MsftEdit.dll)
*   6.1 -- Win7
*
*
*   CHARFORMAT2(EM_SETCHARFORMAT) -- 字符格式，如 字体、尺寸、颜色以及如粗体、斜体和保护(父窗口接受到EN_PROTECTED的通知)等
*   PARAFORMAT2(EM_SETPARAFORMAT) -- 段落格式，如 对齐、跳格、缩进和编号
*   包含嵌入的COM对象
*   类型:
*     ES_SELECTIONBAR -- 
*   消息(EM_) -- 
*     EM_EXLIMITTEXT -- 一个Rich Edit控件不可能包含超过32K字节的文本，除非你使用EM_EXLIMITTEXT消息扩展了这个限制
*     EM_SETTEXTEX -- 设置文本，可通过RTF指定格式，如插入表格等
*     EM_SETOLEINTERFACE -- 
*   通知（EN_) -- 注意需要用 EM_SETEVENTMASK 设置能发送的通知类型, 标准控件是父窗口处理，无窗口是 ITextHost::TxNotify
*     注意：有两种类型的通知， direct and delayed
*     EN_MSGFILTER -- 过滤所有的键盘和鼠标输入，父窗体可以防止键盘和鼠标消息被处理(在ITextHost中不发送,参见MSDN)
*     EN_SELCHANGE -- 父窗口可检测当前选中内容何时被改变
*     EN_REQUESTRESIZE(无底,bottomless) -- 在任何时候若其内容大小改变，它将向其父窗体发送EN_REQUESTRESIZE通知，
*        可调整控件的大小以便它总是与其内容大小匹配，可通过发送 EM_REQUESTRESIZE 消息强制发送该通知(在 WM_SIZE 时很有用)
*   断字处理函数 -- (用户可通过 EM_SETWORDBREAKPROC 自定义) 查找单词间分隔符以及判断何处可以换行
*   
*   剪贴板格式(注册了两种)
*     1.富文本格式(CF_RTF)
*     2.RichEdit 文本与对象(CF_RETEXTOBJ)
*   流(Stream) -- 向控件传入或者传出数据
*     EM_STREAMIN -- 将数据读入控件(数据传入)，控件将重复调用应用程序的回调函数，该函数每次传入数据的一部分到缓冲区中
*     EM_STREAMOUT -- 保存控件内容(数据传出)，控件将重复写入缓冲区然后调用应用程序的回调函数。
*     
*     
* ITextHost -- 无窗口
* 
* CToolTipCtrl -- 
***********************************************************************************************************/

/***********************************************************************************************************
* CListCtrl(TODO:合并到MFCStudy.h中) -- MSDN中虚列表的Sample：VS2008SP1Sample\C++\MFC\general\DBVList
*   改变行高 -- ? ON_WM_MEASUREITEM_REFLECT, 虚函数 MeasureItem 中设置 lpMeasureItemStruct->itemHeight
*   
* 实现真彩色(256色)的工具条(MFC -- http://www.codeguru.com/cpp/controls/toolbar/article.php/c2537/FullFeatured-24bit-Color-Toolbar.htm)
*   1.系统默认 -- 是16色(nColorTableSize)，是名为 IDR_MAINFRAME 的Toolbar 型资源，所有的按钮以bmp格式整体保存，资源编辑器不支持大于16色的位图。
*   2.真彩色 -- 通过图像处理软件制作类似的图像，以位图形式加载到图像列表，并通过 SetImageList 指定为工具条的图标来源。
*     HBITMAP hBmp =  (HBITMAP)LoadImage(,MAKEINTRESOURCE(IDB_TOOLBAR), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS);
*     CBitmap bmp; bmp.Attach(hBmp);
*     m_ilToolBar.Create(32,32, ILC_COLOR8, 4, 4);  //ILC_COLOR8 表明是256色，对应的还有 ILC_COLOR24、ILC_COLOR32 等
*     m_ilToolBar.Add(&bmp,(CBitmap*)NULL);
*     m_wndToolBar.GetToolBarCtrl().SetImageList(&m_ilToolBar); //指定图标来源
*     注意：
*       1.新创建的位图需要和代码中操作的 IDR_MAINFRAME 资源又相同的布局，才不会出现逻辑错误。
*       2.这种方式创建的工具条似乎不能很好的支持 禁止、高亮  -- 但MFC提供了 SetDisabledImageList/SetHotImageList 方法
*       3.运行时像素颜色为 light gray(RGB (192, 192, 192))在运行时会被用户选择按钮的颜色替换 -- 需要设置成透明的？
*
* 树型控件(CTreeViewCtrlExT)
*   注意:
*   1.资源中设置Tree的 TVS_CHECKBOXES 属性后，在OnInitDialog中调用 SetCheck 无效。
*     原因：Init时其ImageList还是空的(State Icon)没有加载，初始化结束后Icon数为3(m_tree.GetImageList(TVSIL_STATE).GetImageCount())
*            http://blog.csdn.net/dongchongyang/article/details/9142559
*     解决方法:
*       方法a.通过ModifyStyle设置才行(最好先通过代码取消一次，避免.rc中已经设置成一模一样的)
*       方法b.指定自定义的图像列表: m_Tree.SetImageList(&m_ImageList, TVSIL_STATE);
***********************************************************************************************************/

/***********************************************************************************************************
* 通过 UICC.xsd 可以查看 Ribbon.xml 文件的语法规则, 
*   MSDN 的帮助：http://msdn.microsoft.com/en-us/library/dd371191(VS.85).aspx
*   例子: http://www.codeproject.com/Articles/32785/Windows-7-Ribbon-The-Time-Has-Come-Your-Win32-Appl
*         
* Ribbon -- 命令工具条，将软件的功能集成到窗口上方的一系列标签（tabs）中，用于代替传统的菜单栏和工具栏
*   CMFCRibbonCategory -- 即Tab(Core + Contextual) 
*     CMFCRibbonPanel -- 即Group
*       CMFCRibbonBaseElement -- 具体元素，如Button、CheckBox 等   
*   Gallery 控件可以对命令的执行效果进行直观的预览，可以大大减少用户尝试各种参数找到合适格式的过程。
*   QAT(Quick Access Toolbar) --
* 
* MFC 中提供了 CMFCRibbonButton、CMFCRibbonGallery 等类
* WTL中没有提供Slider?
* 将 "propsys.dll;dwmapi.dll" 设置为了Delay Loaded(延迟加载)，保证在WinXP上不出错 
* 
* BEGIN_RIBBON_CONTROL_MAP -- RIBBON_CONTROL  -- END_RIBBON_CONTROL_MAP
***********************************************************************************************************/



//声明可以和 DDX_CONTROL 一起工作的 CWindowImpl 派生类
//  如：DDX_CONTROL_IMPL(CListViewCtrl)，这样就有了一个名为 CListViewCtrl_DDX 的类，
//      功能与 CListViewCtrl 一样，但是可以被 DDX_CONTROL 接受。

#define DDX_CONTROL_IMPL(x) \
    class x##_DDX : public CWindowImpl<x##_DDX, x> \
    { public: DECLARE_EMPTY_MSG_MAP() }; 


namespace FTL
{
	FTLEXPORT class CFControlUtil
	{
	public:
		FTLINLINE static LPCTSTR GetEditNotifyCodeString(CFStringFormater& formater, DWORD iNotify, void *pv);

		//tomeTrue 或 tomFalse
		FTLINLINE static LPCTSTR GetRichEditTomBoolString(long nValue);

		//获取Story的类型（MainText、Comments、Footnotes 等)
		FTLINLINE static LPCTSTR GetRichEditStoryTypeString(long nStoryType);
		FTLINLINE static LPCTSTR GetRichEditAnimationTypeString(long nAnimation);
		FTLINLINE static LPCTSTR GetRichEditUnderLineStyleString(long nUnderLine);
		FTLINLINE static LPCTSTR GetRichEditColorString(FTL::CFStringFormater& formater, long nColor);

		//获得 RichEditCtrl 中 CHARFORMAT 的信息 -- 也可用于 Effect（部分的 CFE_ 和 CFM_）
		FTLINLINE static LPCTSTR GetCharFormatEffectAndMaskString(FTL::CFStringFormater& formater, DWORD dwMasks, LPCTSTR pszDivide = TEXT("|"));

		//获得 RichEditCtrl 中 PARAFORMAT 的信息 -- 也用于Effect?
		FTLINLINE static LPCTSTR GetParaFormatEffectAndMaskString(FTL::CFStringFormater& formater, DWORD dwMasks, LPCTSTR pszDivide = TEXT("|"));

		//获得 RichEditCtrl 中的 PropertyBits 信息(TxGetPropertyBits)
		FTLINLINE static LPCTSTR GetRichEditPropertyBits(FTL::CFStringFormater& formater, DWORD dwBits, LPCTSTR pszDivide = TEXT("|"));

		//设置ListBox水平滚动范围
		FTLINLINE static BOOL UpdateListboxHorizontalExtent(HWND hwndListbox, INT nPadding = 0);

        //带CheckBox的TreeCtrl，将父节点选中时，同时更改其全部子节点
        //递归遍历所选项的子项进行修改
        FTLINLINE static BOOL CheckTreeSubItems(HWND hWndTree, HTREEITEM hParent, BOOL bCheck);
	};

	//RichEdit 中的 ITextRange
	class CFTextRangeDumper : public CFInterfaceDumperBase<CFTextRangeDumper>
	{
		DISABLE_COPY_AND_ASSIGNMENT(CFTextRangeDumper);
	public:
		FTLINLINE explicit CFTextRangeDumper(IUnknown* pObj, IInformationOutput* pInfoOutput, int nIndent)
			:CFInterfaceDumperBase<CFTextRangeDumper>(pObj, pInfoOutput, nIndent){}
	public:
		FTLINLINE HRESULT GetObjInfo(IInformationOutput* pInfoOutput);
	};

	class CFTextFontDumper : public CFInterfaceDumperBase<CFTextFontDumper>
	{
		DISABLE_COPY_AND_ASSIGNMENT(CFTextFontDumper);
	public:
		FTLINLINE explicit CFTextFontDumper(IUnknown* pObj, IInformationOutput* pInfoOutput, int nIndent)
			:CFInterfaceDumperBase<CFTextFontDumper>(pObj, pInfoOutput, nIndent){}
	public:
		FTLINLINE HRESULT GetObjInfo(IInformationOutput* pInfoOutput);
	};

	//显示文件名路径的窗口 -- 显示成带省略号的，并且有 Tooltip
	//未写完和测试
	class CFileNameWnd : public CWindowImpl<CFileNameWnd>
	{
	public:
		BEGIN_MSG_MAP(CFileNameWnd)
			MESSAGE_HANDLER(WM_CREATE, OnCreate)
		END_MSG_MAP()
	protected:
		LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
		{
			m_tooltip.Create(m_hWnd);
			//CToolInfo ti(0, m_hWnd, m_nToolTipID, &rcClient, NULL);
			//DrawText 的 DT_CALCRECT 可计算Rect的返回值，确认是否要 Tooltip::UpdateTipText 和 Active
			//后期可用 DT_PATH_ELLIPSIS 绘制，
			//父窗体处理鼠标消息，给 Tooltip 处理： if(m_tooltip.IsWindow()) { m_tooltip.RelayEvent(...); }
		}
		
	private:
		CToolTipCtrl	m_tooltip;
	};

	//自动出现垂直滚动条的 EDIT，需要先将属性设置为： ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN
	class CFEditEx : public CWindowImpl<CFEditEx, CEdit> //<ATL::CWindowImpl>
	{
		enum  {	UWM_CHECKTEXT = WM_USER + 100 };
	public:
		FTLINLINE CFEditEx(void);
		FTLINLINE ~CFEditEx(void);
	public:
		BEGIN_MSG_MAP_EX(CFEditEx)
			//DUMP_WINDOWS_MSG(__FILE__LINE__, DEFAULT_DUMP_FILTER_MESSAGE | DUMP_FILTER_KEYDOWN, uMsg, wParam, lParam)
			MSG_WM_CHAR(OnChar)
			MESSAGE_HANDLER(UWM_CHECKTEXT, OnCheckText)
		END_MSG_MAP()
	private:
		FTLINLINE void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
		FTLINLINE LRESULT OnCheckText(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

		FTLINLINE void ShowHorizScrollBar(BOOL bShow = TRUE);
		FTLINLINE void ShowVertScrollBar(BOOL bShow = TRUE);
	private:
		BOOL m_bShowHoriz;
		BOOL m_bShowVert;
	};

    class CCheckedTreeViewCtrlEx : public CTreeViewCtrlEx
    {
    public:
        CCheckedTreeViewCtrlEx();
        ~CCheckedTreeViewCtrlEx();
    public:
    };

    struct FScrollSkinInfo
    {
        CImage* pBtnVUp;
        CImage* pBtnVDown;
    };

    class CFSkinComboBox : public CWindowImpl<CFSkinComboBox, CComboBox>
    {
    public:
        CFSkinComboBox()
        {
            m_hWndList = NULL;
            m_pSkinInfo = NULL;
        }
        virtual ~CFSkinComboBox()
        {

        }

        BEGIN_MSG_MAP_EX(CFSkinComboBox)
#ifdef FTL_DEBUG
            //DUMP_WINDOWS_MSG(__FILE__LINE__, DEFAULT_DUMP_FILTER_MESSAGE, uMsg, wParam, lParam)
#endif 
            REFLECTED_COMMAND_CODE_HANDLER_EX(CBN_DROPDOWN, OnCbnDropDown)
            REFLECTED_COMMAND_CODE_HANDLER_EX(CBN_CLOSEUP, OnCbnCloseup)
            MSG_WM_CTLCOLORLISTBOX(OnCtlColorListBox)
            //MSG_WM_CREATE(OnCreate)
        END_MSG_MAP()

        FTLINLINE LRESULT OnCbnDropDown(UINT uNotifyCode, int nID, CWindow wndCtl);
        FTLINLINE LRESULT OnCbnCloseup(UINT uNotifyCode, int nID, CWindow wndCtl);
        FTLINLINE HBRUSH OnCtlColorListBox(CDCHandle dc, CListBox listBox);
        FTLINLINE BOOL SkinScroll(const FScrollSkinInfo* pSkinInfo);
        FTLINLINE void UnSkinScroll();
    protected:
        HWND	m_hWndList;
        const FScrollSkinInfo*    m_pSkinInfo;
    };

    //template </*class T,*/ class TBase = WTL::CScrollBar, class TWinTraits = ATL::CControlWinTraits>
    class CFSkinScrollBar : public ATL::CWindowImpl<CFSkinScrollBar, WTL::CScrollBar>
    {
    public:
        BEGIN_MSG_MAP_EX(CFSkinScrollBar)
            MSG_WM_CREATE(OnCreate)
            //MSG_WM_ERASEBKGND(OnEraseBkgnd)
            //CHAIN_MSG_MAP(CZoomScrollWindowImpl<CScrollImageViewView>) // CScrollWindowImpl<CScrollImageViewView>)
        END_MSG_MAP()
    public:
        FTLINLINE CFSkinScrollBar();
        FTLINLINE ~CFSkinScrollBar();
        FTLINLINE int OnCreate(LPCREATESTRUCT lpCreateStruct);
    private:
        FScrollSkinInfo    m_SkinInfo;
    };

    class CFSkinScrollWindow : public ATL::CWindowImpl<CFSkinScrollWindow, ATL::CWindow>
    {
    public:
        FTLINLINE CFSkinScrollWindow();
        FTLINLINE virtual ~CFSkinScrollWindow();

        BEGIN_MSG_MAP_EX(CFSkinScrollWindow)
        END_MSG_MAP()
    public:
        FTLINLINE BOOL SkinScroll(HWND hWnd, const FScrollSkinInfo* pSkinInfo);
        FTLINLINE void UnSkinScroll();
    public:
        int                 m_nScrollWidth;
        CFSkinScrollBar     m_ScrollBarVert;
        CFSkinScrollBar     m_ScrollBarHorz;
        ATL::CWindow        m_wndMiddle;
        WNDPROC             m_funOldProc;
        FTLINLINE static LRESULT CALLBACK HookWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
    };

    extern "C" FTLINLINE CFSkinScrollWindow* SkinWndScroll(HWND hWnd, const FScrollSkinInfo* pScrollSkinInfo);
    extern "C" FTLINLINE BOOL UnSkinWndScroll(HWND  hWnd);
}

#endif //FTL_CONTROLS_H

#ifndef USE_EXPORT
#  include "ftlControls.hpp"
#endif