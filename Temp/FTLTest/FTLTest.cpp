// FTLTest.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "FTLTest.h"

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/mfc/TestRunner.h>
//#include <cppunit/ui/qt/QtTestRunner.h>
//#include <cppunit/ui/text/TestRunner.h>
#include <ftlGdi.h>
#include <ftlGdiPlus.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFTLTestApp

BEGIN_MESSAGE_MAP(CFTLTestApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CFTLTestApp 构造

CFTLTestApp::CFTLTestApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CFTLTestApp 对象

CFTLTestApp theApp;


// CFTLTestApp 初始化

BOOL CFTLTestApp::InitInstance()
{
    //FUNCTION_BLOCK_INIT();
    FTL::CFAutoGdiplus  autoGdiPlus;
    {
        //FAST_TRACE_OPTIONS traceOptions;
        //traceOptions.bWriteToFile = TRUE;
        //traceOptions.bDoTimings = TRUE;
        //FTL::CFFastTrace::GetInstance().SetTraceOptions(&traceOptions);

        // 如果一个运行在 Windows XP 上的应用程序清单指定要
        // 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
        //则需要 InitCommonControls()。否则，将无法创建窗口。
        InitCommonControls();

        CWinApp::InitInstance();

        AfxEnableControlContainer();

        // 标准初始化
        // 如果未使用这些功能并希望减小
        // 最终可执行文件的大小，则应移除下列
        // 不需要的特定初始化例程
        // 更改用于存储设置的注册表项
        // TODO: 应适当修改该字符串，
        // 例如修改为公司或组织名
        SetRegistryKey(_T("Local AppWizard-Generated Applications"));

        CoInitialize(NULL);
        
        FTL::CFGdiUtil::SetProcessDPIAdware();

        CPPUNIT_NS::MfcUi::TestRunner runner;
        //CPPUNIT_NS::QtUi::TestRunner runner;
        //CPPUNIT_NS::TextUi::TestRunner runner;
        runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
        runner.run();


        CoUninitialize();
    }

    //FUNCTION_BLOCK_UNINIT();

    // 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	// 而不是启动应用程序的消息泵。

	return FALSE;
}
