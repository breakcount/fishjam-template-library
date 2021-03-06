#ifndef FTL_IDE_TOOLS_H
#define FTL_IDE_TOOLS_H

#pragma once

#ifndef FTL_BASE_H
#  error ftlIDETools.h requires ftlbase.h to be included first
#endif

//国外程序员整理的 C++ 资源大全 -- http://blog.jobbole.com/78901/

/******************************************************************************************************************************
* BigBlueButton -- 开源视频会议系统(sourceforge上下载)
*   使用 ActionScript 开发的远程教育平台, 服务器端用到的项目包括有 ActiveMQ,Asterisk,Nginx,Tomcat等
*   服务器端(8.0)运行在Ubuntu 10.04 32-bit 或者 64-bit.  部署bbb服务器端有两种方式:
*     1.安装包安装
*     2.安装bbb虚拟机: VirtualBox + 桥接, 初始用户/密码是 firstuser/default
******************************************************************************************************************************/

/***********************************************************************************************
* TODO:
*   各种编辑器推荐保存的文件类型:
*   1.VS -- 带签名的UTF8
*   2.Eclipse -- 不带签名的UTF8(Ant 不支持签名)
*   3.Go语言 -- 
*
* 代码静态分析(编译警告)时必须更改的项:
*   C4700 -- uninitialized local variable 'Xxx' used
*   C6001 -- Using uninitialized memory 'Xxx'
***********************************************************************************************/


/***********************************************************************************************
* 常见功能的 Tip --http://www.watch-life.net/visual-studio/visual-studio-2008-tip-day-index.html
*   选择矩形代码区域(列模式)：Alt + 鼠标
*   格式化当前文档：Ctrl+K, Ctrl+D; 格式化选中文本：Ctrl+K, Ctrl+F -- 问题：怎么设置格式化的规则?
*   折叠到定义：Ctrl+M, Ctrl+O, 可以快速浏览所有的方法
*   在Tooltip中显示快捷键：自定义->工具栏->在屏幕提示中显示快捷键
*
* IDE -- 统一开发环境
*   VS6--Windows 9x平台下VS的最后版本
*   VS2002(7.0)--.NET Framework 1.0,引入了托管代码, 在.NET环境下程序编译为MSIL（微软中间语言）而不是机器语言
*   VS2003(7.1)--支持新版本的.NET 1.1, 第一个稳定版本
*   VS2005(8.0)--.NET 2.0, 此时, 微软移掉了其产品的“.NET”前缀, 如Visual Studio和Visual Basic
*   VS2008(9.0)--第一个支持不同的.NET版本, 包括2.0, 3.0和3.5, 支持WPF, WCF和WF的开发, 
*     具有 LINQ, Silverlight 等新特性
*   VS2010()--
* 版本
* 
* Windows SDK
*   7.0 -- Microsoft Windows SDK for Windows 7 and .NET Framework 3.5 SP1
*          http://www.microsoft.com/en-us/download/details.aspx?id=18950
*   7.1 -- Microsoft Windows SDK for Windows 7 and .NET Framework 4
*          http://www.microsoft.com/en-us/download/details.aspx?id=8442
*
* 升级IE后使用MFC等向导时弹出脚本错误的问题:
*   http://blogs.msdn.com/b/vcblog/archive/2009/03/28/some-vs2005-and-vs2008-wizards-pop-up-script-error.aspx
*   解决方法(需要重启)：
*     [HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings\Zones\1000]
*        "1207"=dword:00000000
************************************************************************************************/

/************************************************************************************************
* 静态库的查看, 搜索工具 -- libdump(有源码)
* 
* How to: Deploy using XCopy -- http://msdn.microsoft.com/en-us/library/ms235291(VS.80).aspx
* 
* 依赖于 CRT, MFC 等多个版本时的重定向 -- 缺少 DebugCRT.9.0.30729.6161 等无法运行程序的问题
* 1.拷贝对应版本的  Microsoft.VC90.CRT.manifest,  msvcr90.dll, msvcp90.dll 等文件到 可执行程序目录 -- 可解决大部分问题
* 2.生成 程序名.exe.config 文件(即 Application Config File, 应用程序运行时的配置信息), 内容框架如下（调整其中的 name , oldVersion, newVersion 等）：
*   <?xml version="1.0"?>
*   <configuration>
*     <windows>    <!-- 注意此处原来是 runtime(指定  .NET assemblies ?) -->
*       <assemblyBinding xmlns="urn:schemas-microsoft-com:asm.v1">
*         <dependentAssembly>
*           <assemblyIdentity type="win32" name="Microsoft.VC90.DebugCRT" processorArchitecture="x86" publicKeyToken="1fc8b3b9a1e18e3b"  /> 
*             <bindingRedirect oldVersion="9.0.30729.6161" newVersion="9.0.21022.8"/>  
*             <bindingRedirect oldVersion="9.0.30729.1" newVersion="9.0.21022.8"/>  
*           </dependentAssembly>
*       </assemblyBinding>
*     </windows>
*   </configuration>
*
* 以前测试过但影响面太大的方法是更改 winsxs 中的文件（(需要更改 WinSxs 的所有者才能修改)
* 修改 C:\Windows\winsxs\Manifests\x86_policy.9.0.microsoft.vc90.debugcrt_1fc8b3b9a1e18e3b_9.0.30729.1_none_61305e07e4f1bc01.manifest 文件, 
*   原来只有两行：
*  		<bindingRedirect  oldVersion="9.0.20718.0-9.0.21022.8" newVersion="9.0.30729.1"/>
*       <bindingRedirect  oldVersion="9.0.30201.0-9.0.30729.1" newVersion="9.0.30729.1"/>
*   加入了新的 
*       <bindingRedirect  oldVersion="9.0.30729.6161-9.0.30729.6161" newVersion="9.0.30729.1"/>
*   注：这个文件是从 SxsTrace 生成的日志文件中找出来的。
*       bindingRedirect 指定 所有旧版本范围的客户需求映射到指定的新版本库, 也可对别的字段进行映射？方式为 old + 关键字 ?
* WinSxs(Windows Side-by-Side assembly, 视窗并行程序集)
*
* 本地加载
*   A.拷贝系统的 manifest 文件到应用程序本地文件夹中,更名为 <assemblyName>.manifest,  如 Microsoft.VC90.CRT.manifest, 将对应的 DLL 文件(如 msvcr90.dll,msvcp90.dll 等）拷贝到相同的目录
*   B.也可以建立 <assemblyName> 文件夹, 并拷贝如  <assemblyName>.manifest 和 对应的 DLL 文件
* 
* ManiFest -- 有两部分
*   客户端 -- 开发编译的Exe, Dll等, 指定该文件依赖的DLL信息, 主要有 type,version, processorArchitecture, publicKeyToken 等信息
*   服务器端 -- 微软等开发的 DLL, 指定该文件的强命名信息, 里面通过 file( hashalg/hash/DigestValue 等) 指定了相关的身份验证信息
*
* policy（策略文件来确认映射关系）-- 
*  
* 强命名的信息
*   type -- 系统类型, 如 win32, win32-policy
*   name -- 该 assemblyIdentity  的名称信息,  如 Microsoft.VC80.CRT 或 policy.8.0.Microsoft.VC80.CRT 等
*   version -- 版本号（这个就是多个版本的 DLL,  改这个？）
*   processorArchitecture -- 平台环境, 如 x86, ia64 等
*   publicKeyToken -- 公钥(用于对软件签名的？相同开发部的相同? 微软的 ATL/CRT/OPENMP 等 都是 "1fc8b3b9a1e18e3b", 但 Common-Controls 是 6595b64144ccf1df)
*
*   hash -- 文件的Hash签名, 每个文件唯一, 确保文件的完整性 -- 如果想多个版本合一(bindingRedirect), 是否必须更改这个？
* 
* 
*   对于应用程序而言, Manifest可以是一个和exe/dll文件同一目录下的. manifest 文件, 
*   也可以是作为一个资源嵌入可执行文件中(Embed Manifest)：
*     Exe 中资源ID为 1( CREATEPROCESS_MANIFEST_RESOURCE_ID )
*     Dll 中资源ID为 2( ISOLATIONAWARE_MANIFEST_RESOURCE_ID )
*     问题：3( ISOLATIONAWARE_NOSTATICIMPORT_MANIFEST_RESOURCE_ID ) 有什么用?
*           24( RT_MANIFEST ) 有什么用?
*   
*   资源(.rc)文件的信息
*     VarFileInfo
*        Translation -- 文件属性中显示的语言(英文为"0x0409 0x04B0", 中文为"0x0804 0x04B0")
*     StringFileInfo
*        每个语言对应的信息(如 BLOCK "040904B0" 对应英文)
*     
*       
*
*   WinXP以前的Windows会忽略 manifest 的内容。
*   VS2010 又不再使用manifest了？
*
*   注意：VC开发环境中有 atlassem.h, crtassem.h, MFCassem.h 等文件, 其中定义了当前编译环境下会使用的 manifest,  
*         也可以在文件中通过如下的代码指定 -- #pragma comment(linker, "/manifestdependency  ...)
*           如 stdafx.h 中指定 Microsoft.Windows.Common-Controls
*   
* manifest 中的 assemblyIdentity 信息和 winsxs 中文件的关系( 强文件名信息 -- 系统中可以有多个不同版本的相同的库共存而不会发生冲突)
*   xml中的信息：<assemblyIdentity type="win32" name="Microsoft.VC90.CRT" version="9.0.21022.8" processorArchitecture="x86" publicKeyToken="1fc8b3b9a1e18e3b"></assemblyIdentity>
*   对应文件为 ：C:\Windows\winsxs\x86_microsoft.vc90.crt_1fc8b3b9a1e18e3b_9.0.21022.8_none_bcb86ed6ac711f91\msvcp90.dll
*            即：C:\Windows\winsxs\<processorArchitecture>_<name>_<publicKeyToken>_<version>_<???>_<???>\xxx.dll
* 
* "Unable to start program" 问题的解决(使用 SxsTrace 工具, 只有 Vista/Win7 下有 ?)
*  1.以管理员账号启动 cmd.exe, 并切换到目的程序的目录下
*  2.SxsTrace Trace -logfile:SxsTrace.etl
*  3.执行 会出错的程序
*  4.SxsTrace Parse -logfile:SxsTrace.etl -outfile:SxsTrace.txt,  生成对 mainfest 解析的日志文件。
*  5.分析日志文件, 从中查找“错误/Error” 等关键字, 对于提示的错误文件通过 EveryThing 等工具进行查找确认
*    例(SxsTrace分析出来的错误信息)
*    错误: 无法解析参考 Microsoft.VC90.DebugCRT,processorArchitecture="x86",publicKeyToken="1fc8b3b9a1e18e3b",type="win32",version="9.0.30729.6161"。
*    分析：Debug 中 XXX.exe.embed.manifest 和 XXX.exe.intermediate.manifest 中依赖了本机上不存在的 Microsoft.VC90.DebugCRT 版本
*         (本机的 WinSXS 中只有 9.0.21022.8 和 9.0.30729.1 的 x86_microsoft.vc90.debugcrt 版本, 但清单文件中依赖了 9.0.30729.6161 版本)
*    原因：所链接的静态库使用了 9.0.30729.6161(可通过 dumpbin /all 并重定向结果后查找 manifestdependency 确认)
*      
*   VS90SP1-KB2538241-x86.exe(MFC Security Update) -- http://www.microsoft.com/zh-CN/download/details.aspx?id=26360
*   vcredist_x86.exe 文件各版本的下载路径
*      9.0.30729.1(VS2008 SP1) -- http://www.microsoft.com/en-us/download/confirmation.aspx?id=5582
*      9.0.30729.6161(KB2538243/MS11-025) --  http://www.microsoft.com/en-us/download/details.aspx?id=26368
* 
* Fuslogvw.exe -- Assembly Binding Log Viewer,怎么用？
* PDBCopy.exe -- 复制调试符号
* SvcTraceViewer.exe -- 查看系统日志的工具?
************************************************************************************************/

/******************************************************************************************************************************
* 利用 SxsTrace 确认这个问题的根本原因?
* VS2008 升级
* 1.升级后因为 manifest 文件出现问题(processorArchitecture等出现问题, 错误为0xc000007b), 
*   程序无法启动, 需要从工程中删除manifest文件, 在stdafx.h中添加如下代码：
#ifdef _UNICODE
#  if defined _M_IX86
#    pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#  elif defined _M_IA64
#    pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#  elif defined _M_X64
#    pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#  else
#    pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#  endif
#endif
******************************************************************************************************************************/


//判断指定IP的机器信息(如机器名)： nbtstat -a IP

#pragma TODO(考虑参考一下 ATL_DLL_ 的用法)
// 如果定义了改宏, 工程将使用ATL.DLL；否则, ATLIMPL.CPP 文件将把实现作为模版库的一部分包含

namespace FTL
{
    //Wp64 警告, 新的IDE是不是没有这个限制了？
    // Gotta love it.  I've NEVER found a way to cast away the /Wp64
    // warnings with the functions Microsoft tells you to use for
    // Win64 readiness!
#pragma warning ( disable : 4244 )
    //代码(如 SetWindowLongPtr)
#pragma warning ( default: 4244 )

    /*************************************************************************************************************************
    * IDE常用命令和工具
    *   nmake
    *   dumpbin 输出可执行文件(EXE, DLL)的信息。
    *     dumpbin /headers xxx.lib 后查看 "FILE HEADER VALUES" 的信息, 可以知道对应的文件是 x86/x64 的
    *     查找 x86/x64 lib 库混用: dumpbin /headers *.lib > check.txt 后全文搜索 “Dump of file", 然后查看后面 machine 类型
    *   mt.exe -- manifest 的控制工具
    *     mt.exe -inputresource:ExePath;#1 -out:extracted.manifest <== 导出 Exe 中的 manifest
    *   undname <== C++函数名解析
    *   系统设备扫描工具 -- gmer.exe
    *   Inspect -- MS提供的类似Spy的工具, 能看到窗体, IAccessible 等信息
    *   AccExplorer32窗口属性查看工具(类似Spy++) -- 可查看DirectUI界面(如 MSN), 但查不了DUIlib 或 QQ等的
    *   命名管道扫描工具 -- pipelist.exe(http://technet.microsoft.com/zh-cn/sysinternals/dd581625)
    *   
    *************************************************************************************************************************/

    /*************************************************************************************************************************
    * 010Editor -- 编辑和查看二进制文件的工具, 可以通过模板分析文件。可以配置使得打开特定类型文件时自动使用对应的模版。
    *   语法
    *     0.可通过 #include "Vector.bt" 的语法包含预定义的模版文件, 实现重用
    *     1.只要声明变量, 变量就会映射到文件当前位置的数据。除非通过关键字 "local" 声明。
    *       char|wchar_t str[] 或 string|wstring str; -- 动态匹配NULL结尾的字符串(读取字符内容直到遇到NULL)
    *     2.十六进制: 0xff, 25h; 二进制: 0b011; 12u 表无符号整数; -1L 表示int64; 0.2表8字节的double; 0.2f 表4字节的float 
    *     3.变量名后可以通过 <xxx=yyy> 指定特定的属性, 如：
    *       bgcolor=<color>, -- 指定当前变量的背景色, SetBackColor() 函数指定当前位置开始的背景色
    *       comment="xxxx", 
    *       fgcolor=<color>, -- 指定当前变量的前景色。()
    *       format=hex|decimal|octal|binary,
    *       hidden=true|false,
    *       open=true|false|suppress, 
    *       read=<function_name>, 
    *     4.颜色值可以通过 0x0000FF(BGR格式) 等十六进制格式 或 cBlack|cLtGray|cRed|cNone 等常量指定
    *     5.可通过 struct|union 等定义结构体, 其中可以包含 if|for|while 等控制语句, 可以嵌套并使用数组(参见 ?).
    *       定义结构时可以指定参数, 如 typedef struct (int arraySize) { int id; int array[arraySize];}VarSizeStruct 
    *       然后当声明变量时可通过参数指定大小。
    *     6.两个位域填充模式(bitfield modes) -- 会影响结构体的位域模式( ushort r:5; ushort g:5; ushort b:5 }
    *       TODO:因为位域模式的自动填充比较复杂, 最好在定义 结构体的位域数据时就将所有位都定义好, 避免由系统填充
    *       [padded bitfields] | unpadded bitfields
    *     7.自定义函数:
    *       <return type> <function name> ( <argument_list> ) { <statements> }
    *   限制:
    *     1.不能使用指针;
    *     2.不支持多维数组(也包括strings数组), 但可通过 结构体+数组 的方式模拟
    *   内置函数 -- 参数默认为值传递, 可通过 & 表示引用传递
    *     BigEndian|LittleEndian -- 设置大端(缺省为 packed left-to-right)|小端(缺省为 packed right-to-left)
    *     BitfieldRightToLeft|BitfieldLeftToRight -- 设置位域模式时的读取方式
    *     BitfieldDisablePadding|BitfieldEnablePadding -- 切换位域的填充模式
    *     FSeek(pos) -- 定位到指定地址, 返回0表示成功
    *     FSkip(offset) -- 偏移
    *     FTell() -- 返回文的当前位置
    *     FEof() -- 返回是否到达文件结尾
    *     FileSize() -- 文件大小
    *     Printf|Warning("string='%s', lenght=%d\n", str, Strlen(str)); -- 
    *     ReadBytes(内存变量,
    *     ReadByte|ReadShort|ReadInt|ReadFloat|ReadQuad -- 从指定地址直接读取数据(不通过定义变量的方式)
    *     SetBackColor|SetColor|SetForeColor -- 指定当前位置开始的默认颜色
    *     Strchr|Strlen|SubStr -- 字符串函数
    *     SwapBytes(data_type) -- TODO:交换变量的字节? 比如 0x1234 => 0x3412 ?
    *   用法:
    *     while(!FEof()){ 分析脚本 } -- 分析到文件结尾
    *   最佳实践:
    *     1.对于长的数组, 可以在后面增加 <optimize=true> 进行优化(参见 BMP )
    *   示例:
    *      1.Bmp分析中行的4字节对齐:
    *        local int bytesPerLine = (int)Ceil( bmih.biWidth * bmih.biBitCount / 8.0 );
    *        local int padding      = 4 - (bytesPerLine % 4);
    *        if( padding == 4 )
    *          padding = 0;
    *************************************************************************************************************************/

    /*************************************************************************************************************************
    * Avalanche -- 一个(HTTP)压力测试的硬件。
    * FileZilla -- 开源的FTP服务端和客户端, 通过程序(FileZilla Server Interface)远程管理
    *   (TODO: 官网下载的是downloader, https://www.filezilla.cn/ 才下载到安装包) 
    *   
    *   
    *************************************************************************************************************************/

    /*************************************************************************************************************************
    * C++ Test,一个集成解决方案, 可进行
    *   a.静态分析(Static Analysis) -- 静态分析代码,检查与指定代码规范规则的一致性
    *   b.单元测试(Unit Testing) -- 可以自动生成大量单元测试用例, 并可执行异常, 功能, 回归等多种测试, 
    *     可测量测试覆盖率。在测试框架内, 提供对私有和保护成员数据以及成员函数的访问。
    *     通过桩函数(函数名前缀CppTest_Stub_)提供被调函数的占位, 使得可以独立地进行单元测试而不依赖外部文件或函数。
    *   c.嵌入式支持(Embedded Support)
    *   d.代码复审(Code Review)
    *   e.自定义规则创建(Rule Wizard) -- 以图形化的方式（通过创建流程图形方式）或者自动创建规则（通过提供演示样本规则违例的代码）。
    *     需要 python 的支持?
    *   f.组件测试?[原生测试导入?(Native Tests Import)]
    *   g.BugDetective(服务器版提供) -- 模拟应用程序执行路径, 以识别可能触发运行时缺陷的路径, 涉及到识别和跟踪复杂路径, 
    *   h.命令行界面(Desktop/Extended Command Line Mode)
    *
    * TCM(Team Configuration Manager -- 团队配置管理器),确保所有团队成员都能访问相应团队的 Test Configuration（测试配置）, 
    *   suppressions(抑制), 规则文件和测试用例文件, 然后由各个相关人员进行Import。
    *   优化的团队配置方式是：
    *     在团队构建机器上安装一套 C++test（Server Edition）-- 每晚自动运行,验证输入的代码,将结果发送到GRS和相关人员.
    *     在每台开发人员工作站上安装一套 C++test（Developer Edition） -- 测试自己编写或修改的代码,并输入源码控制器.
    *     在架构设计师机器上安装一套 C++test（Architect Edition）, 
    *     在团队构建机器或另一台团队机器上安装一套 Team Configuration Manager（团队配置管理器）。
    *   步骤：
    *     1.创建静默安装的配置（不显示向导, 按照设置进行安装和配置）-- 安装一次后, 会生成 setup.iss文件, 将其
    *       赋值到需要安装的机器上, 并使用 -s 标志调用 setup.exe
    *     2.将所有 C++test 连接至源码控制器(可以确定代码作者,从代码库中获取统一的代码):
    *       Preferences->Scope and Authorship 和 Source Control
    *     2.将所有 C++test 安装连接至 TCM(提供文件共享和文件管理):Preferences->Team
    *     3.将 C++test 服务器连接至 GRS(提供仪表板, 报告和度量值,可帮助评估项目总体质量和准备情况).
    *     4.配置团队测试配置和规则
    *     5.配置作者设置
    *     6.运行初始测试和减少噪音
    *     7.通过源码控制器共享项目和测试资源
    *     8.配置自动夜间测试

    * 规则按主题分类(如安全性, 优化, 初始化等),按严重性分级.
    * 分析期间在Test Configuration中所选择的规则会接受检查, 但匹配Suppressions(抑制)条件的结果将不会显示出来.
    * 既可以通过IDE运行,也可以通过命令行界面, 批处理方式进行回归测试。
    * 可以支持嵌入式平台和交叉编译器, 可以和 Eclipse + CDT 一起工作。
    * GRS(组报告系统)--是一个决策支持系统,使得软件开发流程具有可视性和受控性

    * 命令行(cpptestcli.exe)--可命令行运行,将结果发送给GRS和TCM.
    * AEP(自动错误预防)--自动化以下五步骤:识别错误->找到错误原因->定位产品产生错误的地方->修改现有的实践->监视流程
    *
    * C++Test规则所代表的代码问题共分为5种严重程度:
    *   1.I   -- Informational
    *   2.PV  -- Possible Violation
    *   3.V	  -- Violation
    *   4.PSV -- Possible Severe Violation
    *   5.SV  -- Severe Violation
    *
    *************************************************************************************************************************/

    /*************************************************************************************************************************
    * ClearCase(CC) -- 
    *   IBM的版本控制系统, 采用C/S结构, 支持大型, 并发开发, 支持跨平台(Win/Linux)操作, 有一个基于eclipse的CCRC(CC Remote Control)工具, 
    *   其使用了名为 MVFS 的虚拟文件系统(Clear Case Virtual File System)
    *
    *   VOB(Versioned Object Base) -- 版本对象库, 包括了进行版本控制的文件和目录(Element)和用来管理的元数据(Metadata), 保存在
    *     服务器端, 用户对VOB的所有操作都需要通过View（视图）来实现
    *   View -- 客户端操作的视图, 有两种：
    *     动态Dynamic : 远端镜像, 实时更新, 适合管理人员
    *     静态Snapshot : 本地镜像, 手动更新, 适合开发人员
    *   Version -- 客户端每次 CheckOut->Edit->CheckIn 都会生成一个新Version
    *   Version Tree(版本树) -- 一个元素的所有版本组成的树状结构, 展示了元素版本的演化情况
    *   Label(标签) -- 贴在某一版本上的标识, 通常转测试时需要打标签（标签名同版本号一致）, 以后可以快速定位代码集合
    *   Bracnch(分支) -- 关联了VOB库中所有元素特定版本的集合, 可实现不同版本的并行开发（用方框表示） -- 注意和Label的区别
    *   配置规格(Config Spec) -- 确定从VOB到本地View的元素及其版本获取的细节, 保存在每个profile中
    *     CCRC中：环境->显示ClearCase视图配置->版本选择规则 -> 输入对应的元素版本规则, 如最新（latest）
    *************************************************************************************************************************/

    /*************************************************************************************************************************
    * CppUnit --
    *    VS2008编译时出现错误：
    *      1.error C3505: cannot load type library '{80CC9F66-E7D8-4DDD-85B6-D9E6CD0E93E2}
    *        将对应错误行 (MsDevCallerListCtrl.cpp:67 ) 的 version("7.0")  改为 version("9.0") 即可
    *      2.TestRunnerDSPlugInD.dll.intermediate.manifest 中报告错误 general error c1010070: Failed to load and parse the manifest
    *
    *************************************************************************************************************************/

    /*************************************************************************************************************************
    * curl-loader -- http://curl-loader.sourceforge.net
    *   视频：http://www.boobooke.com/v/bbk1808/
    *         http://www.boobooke.com/v/bbk1809/
    *         http://www.boobooke.com/v/bbk1835/
    *   一个用C语言编写的 Web 应用测试和模拟负载工具, 一个进程可以模拟2.5K~10K的客户端并发请求, 
    *   并且每个请求来自不同的IP地址(类似LoadRunner的IP伪装), 支持用户认证, 登录等Web交换过程。
    *   能通过 libcurl 库支持 sftp, telnet, tftp, ssh, scp 等协议
    * 安装(必须使用root用户)：
    *   tar -zxvf 解压后 make 即可
    *   ./curl-loader -f 配置文件 [选项]
    * 配置文件(conf-examples)
    * 选项
    *   -c :连接时的超时
    *   -d :详细日志(交互的数据会保存到文本, 适合文本交互)
    *   -i 采样时间, 默认3秒
    *   -f 配置文件: 
    *   -r :禁止重用TCP连接(关闭后重新打开)
    *   -t 线程数:在多CPU, 多核CPU时可以产生更大压力( cat /proc/cpuinfo )
    *   -v :verbose
    *   -u -- 
    * 压力图示
    *   D -- 响应时间(ms)
    *   Response Time(响应时间)
    *   Throughtput(吞吐率), 分为Ti(nput)和To(utput)
    *************************************************************************************************************************/

    /*************************************************************************************************************************
    * Devpartner(VC6) -- 动态测试工具, 主要应用于白盒测试, 常用于单元测试阶段和集成测试阶段。
    * 只能检查被执行过的代码中是否存在错误, 在开始使用BoundsChecker前, 制定覆盖全面的测试用例
    * 非常重要(使用 TrueCoverage )。
    * 有三个独立的子功能：
    *  1.BoundsChecker --Run-Time错误检测
    *    两种使用模式：
    *    a.ActiveCheck -- 方便快捷, 但能检测的错误种类有限(内存和资源泄露, API函数使用错误)
    *    b.FinalCheck()-- 具有所有检错功能(内存操作溢出),但程序运行速度变慢。使用BC的编译连接器Rebuild程序。
    *  2.TrueCoverage -- (语句)覆盖率统计工具, 可用于补充测试用例。
    *    其多次的测试结果可以合并。
    *    选中“Instrument inline function”-- 可以测试内联函数的覆盖率(可用于检查模版的效率？)
    *  3.TrueTime -- 性能测试工具。
    *    为性能数据提供了四种不同的单位(Scale), 分别是：CPU时钟周期, 微妙, 毫秒, 秒.
    *    使用"Quantum"技术, 只计算花费应用程序的线程上的时间片。
    *    其“Real”显示的时间是“包括系统中同时运行着的其他应用程序的线程所耗费的时间(墙上时间？)”
    * 
    *
    *************************************************************************************************************************/


    /*******************************************************************************************************************************
    * 文档工具doxygen -- 把遵守某种格式的注释自动转化为对应的文档 http://www.stack.nl/~dimitri/doxygen/index.html
    * 步骤：
    *   1.为Project 建立配置文档 -- 可以使用辅助工具 Doxygen Wizard 生成(或命令行 ：doxygen -g 文档名 建立一份缺省的配置文档)
    *     一些 Key 与值的设定。每个设定为一行。若第一行开头为"#" 表示该行为批注。
    *     TAG = value [value, ...] 或 TAG += value [value, ...]
    *     常用 TAG 选项:
    *       PROJECT_NAME -- Project 的名字, 以一个单字为主, 多个单字请使用双引号括住
    *       PROJECT_VERSION -- Project的版本号码
    *       OUTPUT_DIRECTORY -- 输出路径。如果没有填这个路径, 将会以目前所在路径来作为输出路径
    *       OUTPUT_LANGUAGE -- 预设为English, 可以使用Chinese-Traditional 来输出中文繁体
    *       INPUT -- 指定加载或找寻要处理的程序代码档案路径。这边是一个表列式的型态。并且可指定档案及路径。
    *         举例来说若您有a.c, b.c, c.c 三个档案。您可使用INPUT = a.c, b.c, c.c 的方式。
    *         若您给定一个目录, 该目录下面所有档案都会被处理。
    *       FILE_PATTERNS -- 文件扩展名。如果您的 INPUT Tag 中指定了目录。您可以透过这个Tag来要求Doxygen在处理时, 
    *         只针对特定的文件进行动作。例如：您希望对目录下的扩展名为.c, .cpp及.h的档案作处理。
    *         您可设定 FILE_PATTERNS = *.c, *.cpp, *.h。
    *       RECURSIVE -- 布尔值, 只接受YES或NO。当设定为YES时, INPUT所指定目录的所有子目录都会被处理。    
    *       EXCLUDE -- 如果您有某几个特定档案或是目录, 不希望经过Doxygen处理。您可在这个Tag中指定。
    *       EXCLUDE_PATTERNS -- 类似于FILE_PATTERNS的用法, 只是这个Tag是供EXCLUDE所使用。
    *       SOURCE_BROWSER -- 如果设定为YES, 则 Doxygen 会产生出源文件的列表, 以供查阅。
    *       INLINE_SOURCES -- 如果设定为YES , 则程序代码也会被嵌入于说明文件中。
    *       ALPHABETICAL_INDEX -- 如果设定为YES, 则一个依照字母排序的列表会加入在产生的文件中。
    *       GENERATE_HTML -- 若设定为YES,会产生HTML版本的说明文件。HTML文件是Doxygen预设产生的格式之一
    *       HTML_OUTPUT -- HTML文件的输出目录。这是一个相对路径, 所以实际的路径为 OUTPUT_DIRECTORY 加上 HTML_OUTPUT 。这个设定预设为html。       
    *       HTML_FILE_EXTENSION -- HTML文件的扩展名。预设为.html。
    *       HTML_HEADER -- 要使用在每一页HTML文件中的Header。如果没有指定, Doxygen会使用自己预设的Header。 
    *       HTML_FOOTER -- 要使用在每一页HTML文件中的Footer。如果没有指定, Doxygen会使用自己预设的Footer。 
    *       HTML_STYLESHEET -- 您可给定一个CSS 的设定, 让HTML的输出结果更完美。
    *       GENERATE_HTMLHELP -- 如设定为YES, Doxygen会产生一个索引文件。这个索引文件在您需要制作 windows 上的HTML格式的HELP档案时会用的上。
    *       GENERATE_TREEVIEW -- 若设定为YES, Doxygen会帮您产生一个树状结构, 在画面左侧。这个树状结构是以JavaScript所写成。所以需要新版的Browser才能正确显示。
    *       TREEVIEW_WIDTH -- 用来设定树状结构在画面上的宽度。
    *       GENERATE_LATEX -- 设定为YES 时, 会产生LaTeX 的文件。不过您的系统必需要有安装LaTeX 的相关工具。  
    *       LATEX_OUTPUT -- LaTeX文件的输出目录, 与HTML_OUTPUT用法相同, 一样是指在OUTPUT_DIRECTORY之下的路径。预设为latex。                         
    *       LATEX_CMD_NAME -- LaTeX程序的命令名称及档案所在。预设为latex 
    *       GENERATE_RTF -- 若设定为YES , 则会产生RTF 格式的说明档。
    *       RTF_OUTPUT -- 与HTML_OUTPUT 用法相同, 用来指定RTF 输出档案路径。预设为rtf。
    *       GENERATE_MAN -- 若设定为YES , 则会产生Unix Man Page 格式的说明文件。
    *       MAN_OUTPUT -- 与HTML_OUTPUT 用法相同, 用来指定Man Page的输出目录。预设为man。
    *       GENERATE_XML -- 若设定为YES , 则会产生XML 格式的说明文件。
    *       ENABLE_PREPROCESSING -- 若设定为YES , 则Doxygen 会启动C 的前置处理器来处理原始档。
    *       PREDEFINED -- 可以让您自行定义一些宏。类似于gcc 中的-D选项
    *   2.在程序代码中加上符合Doxygen所定义批注格式
    *     原则上, Doxygen 仅处理与程序结构有关的注释, 如 文件, 类, 结构, 函数, 变量, 宏 等的注释。而忽略函数内变量, 代码等的注释。
    *     通常一个注释块包括一个简要说明（brief）和一个详细说明（detailed）, 遇到头文件中各种类型定义, 关键变量, 宏的定义, 
    *     doxygen提供了group的概念, 生成的模块的注释会单独放在一个模块的页面中(defgroup)。：
    *     任何其他代码项（比如类, 函数, 甚至文件）如果要加入到某个模块, 可以在其doxygen注释中使用ingroup命令即可。
    *     Group之间使用ingroup命令, 可以组成树状关系。
    *
    *       在其前使用 @brief 定义其简要说明, 空一行后继续写其详细的注释即可。
    *     / **
    *      * @brief [some brief description ]
    *      *      [ brief description more. ]
    *      * @param
    *      * 
    *      * /
    *     或以下格式：
    *       /// 注释；
    *       //! 注释
    * 
    *     Doxygen常用注释命令：
    *        @addtogroup ？？？
    *        @author 作者
    *        @brief  简要说明
    *        @bug 存在的Bug说明
    *        @code 注释中说明的代码 -- 到 @endcode 结束
    *        @date 日期
    *        @defgroup 组名 组描述
    *        @deprecated -- 说明是不再支持的
    *        @exception 异常对象 [异常说明]
    *        @file 文件名
    *        @ingroup [group_name] -- 定义一个特定的注释组
    *        @image html "需要插入的图片文件名"'
    *        @name 类似注释的名字
    *        @note 注意事项
    *        @param 参数名 [in|out|in,out] 参数说明
    *        @post 码项之后的使用条件
    *        @pre 前提条件
    *        @relates 非成员函数的名字 -- 通常用做把非成员函数的注释文档包含在类的说明文档中
    *        @see 引用链接
    *        @since 版本或日期 -- 通常用来说明从什么版本, 时间写此部分代码
    *        @version 版本
    *        @warning 警告信息
    *        @return 返回值说明
    *        @retval value 特定返回值的意义
    *        @todo 要做的事情说明
    *    扩展：
    *        @par requirements  -- 需要的环境
    *        @par license
    *    列表：
    *        @return 
    *         <dl>
    *           <dt>escSuccess</dt> <dd>描述信息</dd>
    *           <dt>escInvalidParameter</dt> <dd>描述信息</dd>
    *         </dl>
    *   3.使用Doxygen来产生文档
    *     如果要生成CHM格式的文档, 必须在“HHC_LOCATION”中指定 HTML Help Workshop 的 hhc.exe 的路径
    *
    * 其他
    *   GhostDoc -- VS的免费插件, 帮助开发人员编写XML格式的注释文档
    *******************************************************************************************************************************/

    /*******************************************************************************************************************************
    * http://www.cnblogs.com/TankXiao/archive/2012/02/06/2337728.html
    * Fiddler(http调试代理)--记录并检查所有客户端和服务器之间的http/https通讯, 
    *   查看所有进出数据,可以检视, 设置断点, 修改输入输出数据等。包含了一个强大的基于事件脚本的子系统, 能使用JScript.NET语言进行扩展
    *   工作原理：以代理web服务器的形式工作, 使用127.0.0.1:8888, 启动时自动设置代理, 退出时自动注销代理。
    *   
    *   常见设置
    *     1.捕获HTTPS(缺省禁用) -- Tool->Fiddler Options->HTTPS tab->选中对应的复选框("Decrypt HTTPS traffic", "Ignore server certificate errors"等)
    *     2.监控特定程序
    *       Firefox/Chrome -- 手工设置其使用 127.0.0.1:8888 的Http代理
    *       VS调试ASP.NET -- 在localhost后面加个点号即可, 如 http://localhost:2391/Default.aspx => http://localhost.:2391/Default.aspx
    *     3.设置断点(中断时可修改其中的任何内容)
    *       方法1: Rules->Automatic Breakpoint->Before Requests, 会中断所有的会话
    *       方法2: 在 QuickExec 命令行处输入 bpu URL 即可在只访问指定URL时中断。直接输入 bpu 可清除断点
    *               输入 bpafter URL 可在Response时中断
    *     4.利用“远程连接”功能来实现Fiddle捕获Mac系统发出的HTTP/HTTPS(TODO: 不用虚拟机, 用其他人的机器也行?)
    *       a.Mac中安装虚拟机(如VMware);
    *       b.虚拟机中安装Windows系统, 并安装Fiddle软件;
    *       c.虚拟机的网络使用“Bridged” 模式 -- 虚拟机中的Windows拥有独立的IP地址。
    *       d.设置Fiddle -- Tools->Options->Connections->Allow remote computers to connect
    *       e.配置Mac, 把代理服务器指向Fiddler所在的Windows -- System Preferences ->Network->Advanced...->Proxies
    * 
    *   常见工具
    *     AutoResponder -- 允许你从本地返回文件, 而不用将http request 发送到服务器上
    *        将需要替换成本地文件的会话拖动到AutoResponder, 并选中Enable automatic reaponses 和Unmatched requests passthrough
    *     Composer -- 可以创建和发送自定义的HTTP Request
    *     Filter -- 过滤会话
    *     Script -- 
    *       1.安装SyntaxView:Inspectors tab->Get SyntaxView tab->Download and Install SyntaxView Now,
    *         安装成功且重启后会多了一个Fiddler Script Tab, 可在其中编写 OnBeforeRequest 等事件时的脚本, 
    *         在脚本中甚至可以自动修改Request或Response的内容(CustomRules.js).
    *******************************************************************************************************************************/

    /******************************************************************************************************************************
    * Git -- 最早用于linux内核开发的开源的分布式版本控制系统, 不需要服务器端软件的支持
    *   集中式(SVN) -- 核心是服务器, 有非常明确的权限管理机制(分支访问限制), 不适合开源开发
    *   分布式(Git) -- 开发者可以本地离线工作(提交, 合并, 创建分支等, 每个开发者机器上都有一个服务器的数据库, clone -> pull/fetch),
    *     然后本地修改后生成补丁通过邮件提交或反馈给主开发者, 主开发者确认后合并到公共服务器( push/ pull )
    *   git最为出色的是它的合并跟踪(merge tracing)能力
    *   git没有提供权限管理功能, 需要通过ssh设置
    *   Git中的相关概念
    *     分支(branch) -- master是默认的分支,git假设在master上开始并展开工作, 除非创建自己的分支
    *     索引(Ref) -- 
    *
    *   相关命令(git, 使用 git help 命令 可以显示详细的HTML帮助)
    *     add 文件或目录 [-A] -- 把想提交的文件add上, -A 表示添加未跟踪的文件
    *     branch <分支名>-- 分支操作, 如 创建分支[默认], 查看分支(--list), 删除分支[-d]
    *     checkout [分支名] -- ★切换分支★, 如刚用 branch 建立的 temp 分支,  或默认的 master 分支
    *     clone 远程目录 本地目录 -- 从服务器上克隆数据库（包括代码和版本信息）到单机上
    *     commit -m "注释信息" -- 提交到本地数据库
    *     config -- 配置相关信息, 例如 user.email 和 user.name, commit代码以前必须要设置"--global"范围的配置信息
    *     diff [分支1] [分支2] > patch -- 比较两个分支, 可通过重定向生成补丁
    *     fetch -- 从服务器下载数据库, 并放到新分支, 不跟自己的数据库合并, 通常用于解决冲突前先比较一下
    *     init -- 创建一个数据库(会在目录下创建一个 .git 的子目录)
    *     log -- 查看版本历史
    *     merge -- 合并分支, 把目标分支合并到当前分支
    *     mv -- 重命名文件或者文件夹
    *     patch -- 打补丁?
    *     pull IP地址:数据库文件夹 -- 从服务器下载数据库, 并跟自己的数据库合并
    *     push [IP:数据库文件夹] [版本] -- 向其他数据库推送自己的数据库（一般是主开发者才能提交）
    *     reset -- 恢复到之前的版本
    *     rm -- 删除文件或者文件夹
    *     show -- 查看版本号对应版本的历史。如果参数是HEAD查看最新版本
    *     status -- 显示当前的状态(比如 所在分支, 文件更改)
    *     update-index -- 内部命令, 如 git add 对应于 git update-index --add
    *     whatchanged [分支1] [分支2] -- 查看两个分支的变化
    * 其他相关工具 -- 想开发一个 nGit(参考 Git 和 Gemit的使用, 如在VS里打开IE View)
    *   Git -- http://git-scm.com/download/win
    *   EGit -- Eclipse 下的 Git Plugin
    *   Gerrit -- 基于Web的代码评审工具和项目管理工具
    *   GitHub -- 可与 Hudson 连接?
    *   TortoiseGit -- 提供 Git 和 Windows 资源管理器的整合(图形化操作界面)
    *   Msysgit -- Window下的Git客户端程序, http://code.google.com/p/msysgit/
    * 
    * Git可以通过SSH连接(ssh-keygen -t rsa -C "xxx" 生成)
    *******************************************************************************************************************************/

	/******************************************************************************************************************************
    * GNU 环境(Windows 下的),
    *   MinGW(Minimalist GNU For Windows) + MSYS(类似linux的命令行环境) , 一套精简的Windows平台编译器, 相比Cygwin体积小很多。
    *     提供了完整的开源编译工具集, 可以在没有第三方动态链接库的情况下使用GCC产生Win32程序
    *     C/C++ 编译环境：binutils/mingw-runtime-dev/mingw-runtime/w32api/gcc-core/gcc-c++/libstdc++ 等
    *     安装：
    *       0.通过 mingw-get-setup.exe 选择需要安装的组件, 在线安装
    *       1.设置 MINGW_HOME 环境变量指向其根目录, 将 %MINGW_HOME%\bin 加入Path
    *       2.将 %MINGW_HOME%\bin\mingw32-make.exe 复制为 make.exe 供eclipse使用
    *     启动及配置(msys\1.0\msys.bat)：
    *       1.运行后通过 mount 可加载本机上的所有磁盘, 可直接访问（但在 / 下看不到), 也可以修改 MinGW\msys\1.0\etc\fstab 文件指定目录
    *       2.可以通过 ln -s 的方式设置 mingw 为 msys 下的mingw 目录(TODO: 实测发现会拷贝目录, 而且会递归？)
    *       3.从GTK+ for Windows下载 pkg-config.exe 和 GLib DLL 到 MinGW/bin
    *         http://ftp.gnome.org/pub/gnome/binaries/win32/dependencies/pkg-config_0.23-3_win32.zip
    *         http://ftp.gnome.org/pub/gnome/binaries/win32/glib/2.28/glib_2.28.1-1_win32.zip
    *         TODO:1.有些dll在 VMWare 中有; 2.可以 copy libintl-8.dll initl.dll
    *       4.介绍了一些MingW的配置和常见软件的编译方式: http://www.gaia-gis.it/gaia-sins/mingw_how_to.html
    *
    *   yasm -- 不管下载的是哪个版本, 必须改名为 yasm.exe,放在 bin 下
    ******************************************************************************************************************************/

    /******************************************************************************************************************************
    * Google Performance Tools(google-perftools)
    * 
    *******************************************************************************************************************************/

    /*******************************************************************************************************************************
    * Google Code(http://code.google.com)
    *  Project Hosting(项目托管)-> Project Hosting on Google Code

    *******************************************************************************************************************************/


    /******************************************************************************************************************************
    * GUI Design Studio -- 软件原型设计工具。其他常见的有 AxureRP-Pro(主要用于Web?),Balsamiq mockup,
    *   UIDesigner(腾讯出的窗体原型设计, 可输出执行文件)
    * 工具
    *   屏幕区域 -- 红色矩形框
    *   主元素(Representative Element) -- 显示的起始元素
    *   故事板(StoryBoard)面板 -- 提供用于构建设计文档中控制流程的元素来实现一个模拟原型
    * 连接类型：
    *   Modal Popup -- 模态窗口
    *   Modal Choice Popup -- 点击窗口区域以外窗口会自动关闭的模态窗口, 适用于嵌套级联菜单或其他弹出式选择窗口
    *   Show Window -- 非模态窗口, 类似于查找替换窗口
    *   Hide Window
    *   Toggle Window -- 切换显示
    *   Toggle Overlay -- 同Toggle Window, 但目标窗口不是别鼠标事件, 适用于响应鼠标经过事件的同时, 按钮, 选项卡或其他元素仍然需要导航切换的情况
    ******************************************************************************************************************************/

    /******************************************************************************************************************************
    * .pn9 目录下有大量文件, 什么生成的?
    *
    * CI的环境配置(C:\hudson\tools\apache-tomcat-5.5.35\bin)
    *   ANT_HOME=C:\hudson\tools\apache-ant-1.8.2
    *   classpath=.;%JAVA_HOME%\lib\tools.jar;%JAVA_HOME%\lib\dt.jar
    *   COVFILE=C:\Users\hudson\Documents\test.cov
    *   GIT_HOME=C:\Program Files (x86)\Git
    *   GTEST_HOME=C:\gtest-1.6.0
    *   HUDSON_HOME=C:\hudson\workspace
    *   JAVA_HOME=C:\Program Files\Java\jdk1.6.0_30
    *   MAVEN_HOME=C:\hudson\tools\apache-maven-2.2.1
    *   Path=C:\Program Files (x86)\BullseyeCoverage\bin;
    *        C:\hudson\util\klocwork\bin;C:\Program Files\Java\jdk1.6.0_30\bin;
    *        %MAVEN%\bin;%ANT%\bin;C:\Program Files (x86)\Cppcheck\;
    *        C:\hudson\util\nsiqcppstyle\nsiqcppstyle;C:\hudson\util\bullshtml;
    *        C:\hudson\tools\apache-ant-1.8.2\bin;
    *        C:\Program Files (x86)\Git\binC:\Program Files (x86)\PHP\;C:\Windows\system32;
    *        C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;
    *        c:\Program Files (x86)\Microsoft SQL Server\100\Tools\Binn\;
	         c:\Program Files\Microsoft SQL Server\100\Tools\Binn\;
    *        c:\Program Files\Microsoft SQL Server\100\DTS\Binn\;C:\Program Files (x86)\Git\cmd;
    *        C:\Program Files\TortoiseSVN\bin;C:\Python27;c:\Program Files (x86)\Microsoft SQL Server\90\Tools\binn\;
    *        C:\Program Files\Microsoft Windows Performance Toolkit\;
    *        C:\Program Files (x86)\Mozilla Firefox;C:\cygwin\bin;
    *   PHPRC=C:\Program Files (x86)\PHP\
    *   PROCESSOR_ARCHITECTURE=AMD64
    *   PROCESSOR_IDENTIFIER=Intel64 Family 6 Model 44 Stepping 2, GenuineIntel
    *   PSModulePath=%SystemRoot%\system32\WindowsPowerShell\v1.0\Modules\
    *   PYTHON_HOME=C:\Python27
    *   VS100COMNTOOLS=C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\Tools\
    *   VS90COMNTOOLS=C:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\Tools\
    *
    *
    * Hudson -- 持续集成(Continuous Integration)的工具,  其他的服务器有：CruiseControl 等
    *   NHN的帮助：http://devcafe.nhncorp.com/QPTalk/529396
    * 执行流程：Svn Update->Build(batch/shell)->PostBuild(生成gtest测试报告等)
    * 
    * 下载安装：
    *   1.http://jdk6.java.net/download.html, 中下载安装JDK(6.0),设置 JAVA_HOME 
    *   2.http://tomcat.apache.org/ <== 60, Binaray Distribution, Core zip, 解压设置 TOMCAT_HOME, 
    *     a. 更改 conf\server.xml 文件, 在每个 "<Connector port=" 部分增加 URIEncoding="UTF-8" 的属性, 可避免Jobs名中包含非ASCII字符时出错。
    *     b. 怎么改?
    *     JAVA_OPTS="$JAVA_OPTS -Xms2048m -Xmx2048m -Dfile.encoding=UTF-8 -server -Dnet.mdns.interface=0.0.0.0"
    *     JAVA_OPTS="$JAVA_OPTS -server -Xms256m -Xmx2048m -XX:PermSize=600m -XX:MaxPermSize=2048m -Dcom.sun.management.jmxremote"
    *     JAVA_OPTS="$JAVA_OPTS -DHUDSON_HOME=C:\hudson\workspace -Xmx2048m"
    *     CATALINA_OPTS="-DHUDSON_HOME=C:\hudson\workspace -Xmx2048m"
    *   3.http://hudson-ci.org/downloads/war/  <== 在 1.395版本以后分为 hudson 和 JeXXXX(http://jenkins-ci.org/) ? 两个分支, 目前最新的是 1.395.1
    *     将 hudson.war 放在 TOMCAT 的 webapps 目录中, 也可解压成 hudson 子目录
    *     设置 HUDSON_HOME 变量到指定的工作目录(放置下载的源码进行编译), 默认为 CSIDL_APPDATA
    *   4.下载解压 apache-maven ? ,  设置 MAVEN_HOME 
    *   5.安装 Python27, 设置 PYTHON_HOME 环境变量
    *   通过 startup.bat 批处理启动Tomcat,然后访问 http://localhost:8080/hudson/,  停止时是 shutdown.bat
    *     启动后(选择Jenkins版本),  一般先安装必要的Plugins, 然后在系统管理中进行配置
    *     注意：需要在Plugin Manager的Advanced中需要将 Update Site改为： http://updates.hudson-labs.org/update-center.json
    *           原来的默认地址是：http://updates.jenkins-ci.org/update-center.json
    *     a.全局属性中, 增加"Environment variables"的键值对
    *       gcovr -- ${PYTHON_HOME}\Scripts\gcovr (需要解压 gcovr-2.3.1.tar.gz, 然后将 scripts\gcovr 更改 python的路径后放到 Python27 下)
    *       GTEST_HOME -- C:\gtest-1.6.0
    *       NSIQCPPSTYLEPATH -- C:\hudson\util\nsiqcppcheckstyle\nsiqcppcheckstyle  <== 似乎路径不对
    *       path -- C:\hudson\util\nsiqcppcheckstyle\nsiqcppcheckstyle;${path}      <== 似乎路径不对
    *
    * CI配置(tomcat5.5.36,安装出来后是5.5.35?)
    *   Build Triggers -- schedule 中依次表示 分钟/小时/天/月/周
    *     Commit Build -- 轮询(如10分钟), 有变动时则编译和单元测试, 保证及时发现编译问题, X/10 * * * * 表示每10分钟触发一次(注意10前面是星号*)
    *     Integration Build -- 定时(如每晚),进行完整编译和全部检查(UT, 静态, CC等), 30 0 * * 1-5 表示周一到周五每天 0:30 分触发 
    *     Publishing Build -- 生成安装文件(注意应该同时备份相关的PDB)
    *   NHN Project Plugin(Assign NHN Project) -- 这样NHN的Project才能用？
    *     项目名的命名规范?
    *   批处理中可用的系统变量
    *     %BUILD_NUMBER% -- 当前编译的序号
    *     %WORKSPACE% -- 当前项目的工作空间, 如 C:\jenkins\workspace\jobs\XXXX_I\workspace
    *
    * 文件路径: ** 表示目录及子目录, 如 JUnit 结果文件应该设置为 xx/test_detail.xml 表示搜索当前目录及子目录中的该文件
    * 
    * 常见Plugin(勾选后在最下面选择 Install, 会自动下载 *.hpi文件并安装) -- http://wiki.hudson-ci.org/display/HUDSON/Plugins
    *   安装以后可以通过 http://localhost:8080/hudson/restart 重启(不过Windows下有问题, 不能重启成功)
    *   SimpleUpdateSite(NHN) -- 定制化的Plugin升级工具,http://devcode.nhncorp.com/projects/updatecenter/downoad,
    *     在 Advanced 中选择 simpleupdatesite.hpi 文件, 上传后安装, 然后进行设置：
    *     New RSS URL为 http://devcafe.nhncorp.com/QPTalk/notice/rss
    *     UpdateSiteURL 为 http://hudson02.nhncorp.com:9080/update/simpleupdatesite.json
    *   Publish JUnit test result report -- 可以查看 JUnit/GTest测试后的 xml(如 gtest默认 的test_detail.xml)
    *   locale <== 本地化(防止部分显示中韩文, 部分显示英文等), 设置为 en_us 且选中"Ignore XXX"
    *   E-mail Notification -- 程序集成有问题时发送邮件通知（需要先配置邮件服务器）,然后其中地址以空格区分(可通如 D0478@XXX 的方式发送邮件组里的)
    *     SMTP server:mexcn01.nhncorp.cn
    *     Default user e-mail suffix: @nhn.com
    *     System Admin E-mail Address: xxxx@nhn.com
    *   Quality Dashboard(NHN) -- 通过plugin从各个Hudson服务器上报指标到统一的QD服务器, 进行统一的展示。
    *     http://nsiq.nhncorp.com/, 每个项目有唯一的API KEY进行区分
    *     选择结果输出时：
    *       Analysis Defect Density 选择 klocwork
    *       Coding Standard Conformence Rate 选择 NSIQ cppstyle
    *       CC 选择 NSIQ Collector for Complexity
    *   JUnit test result report-- 可以查看JUint, Gtest等生成的结果XML(如GTest对应的 xx/test_detail.xml--注:是星号)
    *   CovComplPort(NHN) -- 同时显示比较复杂度和覆盖率的插件,越复杂的越要测试, 目前只支持Clover, 
    *     输出时为 Publish Coverage/Complexity Scatter Plot
    *   analysis-core -- 安完以后显示 Static Analysis Utilities, 静态代码解析的核心(Core)插件, 要进行静态解析(比如 klocwork/CheckStyle 等时必须安装该Plugin)
    *     http://wiki.jenkins-ci.org/x/CwDgAQ ,http://hudson-ci.org/download/plugins/analysis-core/ 
    *   checkstyle-- 安完后显示"Checkstyle Plug-in", 收集CheckStyle的分析结果并进行显示
    *     http://wiki.jenkins-ci.org/x/GYCGAQ
    *   Clover plugin -- integrates Clover code coverage reports to Jenkins.
    *     http://wiki.jenkins-ci.org/display/JENKINS/Clover+Plugin
    *   MSBuild Plugin -- 支持使用 MSBuild 编译Visual Studio的 .proj and .sln, 需要在配置中指定相关信息(然后在项目中怎么使用?)
    *     Name: MSBuild, Path: C:\Windows\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe
    *     Name: MSBuild_64, Path: C:\Windows\Microsoft.NET\Framework64\v4.0.30319\MSBuild.exe
    *     http://wiki.hudson-ci.org/display/HUDSON/MSBuild+Plugin
    *   MSTest plugin -- 把 MSTest TRX测试报告格式转换为JUnit XML格式
    *     http://wiki.hudson-ci.org/display/HUDSON/MSTest+Plugin
    * 代码质量维度及统计插件 -- 单机常用的代码行统计工具是 SourceCounter
    *   Coding Convention(代码规范) -- N'SIQ CppStyle(http://nsiqcppstyle.appspot.com)
    *   Static Analysis(静态分析) -- klocwork
    *      1.通过 kw-user-installer.9.2.2.10679.windows.exe 安装程序先安装客户端软件;
    *      2.通过 SimpleUpdateSite 安装插件, http://devcafe.nhncorp.com/QPTalk/205688
    *      3.Hudson系统配置中设置相关信息
    *        Version:9.0, Path:客户端软件的安装路径
    *        Host:klocwork9.nhncorp.com, Port:27000
    *      4.具体项目中启用klocwork的检查
    *        Linux:设置Config FileName 为编译的命令脚本（并删除编译中的命令, 免得重复编译?）
    *        Windows:设置Config FileName 为 xxx.sln, Build Parameter 中输入 --config Release|Win32 等
    *      注意：实测效果来看, 这个工具非常耗时间(一个普通的工程耗时40分钟左右), 有方法优化吗？
    *   Code Coverage(代码覆盖率,要求语句>50%,分支>40%) -- BullsEye/GCov, 收集工具是 Clover/Cobertura
    *     实现机制有两种：1.插入二进制(GCov); 2.插入源码再进行编译(BullsEye Coverage)
    *     1.GCov(Linux) -- 编译链接选项中加入: -fprofie-arcs -ftest-coverage -lgcov
    *       用Cobertura采集结果, 编译命令行中需要用 gcovr -r src --xml > coverage.xml 生成其需要的文件
    *     2.Bullseye Coverage(Win/Linux), BullseyeCoverage-8.4.2-Windows.exe的安装License : 0z6RNW3dGR0x0lVSwC0JzlmD4dE3Q4116NMw
    *       要设置 COVBUILDZONE=${WORKSPACE}; COVFILE=${WORKSPACE}/test.gov,
    *       VS2008 中可以通过 Tools->Enable/Disable Bullseye Coverage Build 命令打开或关闭其功能
    *       cov01 -1(打开选项); make clean all; cov01 -0(关闭); 执行测试程序; bullshtml target/coverage(在指定目录下生成覆盖率结果);
    *       用Clover采集结果, 其report directory 中填 target/coverage, file name 为 clover.xml
    *       Bullseye 可以通过 COVFILE 环境变量指定全局的覆盖率分析文件(扩展名为 .gov )
    *       注意:VS2008中启用Bullseye以后有可能出现"LNK1000: Internal error during LinkerMain", 
    *         原因：MS的bug(KB948127), http://www.bullseye.com/help/trouble-lnk1000.html ; 
    *         解决：1.安装补丁(似乎无效); 2.
    *   LOC/CC(圈复杂度,要求<30) -- N'SIQ Collector, 注意需要排除第三方代码, Lex/Yacc等自动生成, Windows的消息映射等
    *     http://dev.naver.com/projects/nsiqCollector, 下载后在配置时输入可执行文件(nsiqcollector.exe)的路径, 有单独的Build Step
    *   CQ -- Code Quality
    *   Code Duplication Analysis(代码重复分析) -- CPD
    *   Defect density(缺陷密度,要求 < 4/KLOC)
    ******************************************************************************************************************************/

    /******************************************************************************************************************************
    * Intel C++编译器（9.0 或更高版本） -- 支持 OpenMP* 规范 2.5 版
    *   优化参数：
    *   Linux	Windows	      作用
    *    -O0	  /Od	    禁止优化
    *    -g	      /Zi	    生成标记
    *    -O1	  /O1	  优化二进制代码
    *    -O2	  /O2	  优化速度（默认）
    *    -O3	  /O3	   优化数据缓存
    *   
    * 
    * Intel VTune 性能分析器 7.2 或更高版本
    *   主要功能：
    *     a.取样功能, 调用曲线图功能, 计数器监视器以及经过改进的Intel调优助手;
    *       取样功能 -- 可以帮助开发者分辨程序中最消耗时间的函数和模块, 并给出操作系统和应用程序的详细视图。
    *       调用曲线图 -- 通过分析程序运行时函数的入口点和出口点, 生成一张调用曲线图并且确定调用顺序和显示关键路径。
    *       计数器监控器 -- 在运行时跟踪系统活动, 确定是否会因为可用内存减少或文件输入/输出性能问题而导致应用程序速度变慢。
    *       Intel调优助手(强烈推荐, 好好看看) -- 根据丰富的知识库分辨性能问题, 自动推荐代码改进办法, 帮助提高开发者的工作效率。
    *         它提供了基于性能计数器的视图, 以及关于Windows操作系统和英特尔最新处理器的建议, 以及源代码的改进建议。
    *     b.在Windows下同时提供图形化与命令行界面, Linux 下？
    *     可以识别恶性线程故障, 如数据争用, 错误条件等, 可通过识别源码来识别性能瓶颈, 识别资源代码, 识别低效线程设计等,
    *     《VTune Performance Analyzer Essentials》
    * Intel Thread Checker 线程检查器2.2 或更高版本
    *    可快速查找和修复Win*和OpenMP*线程软件中的bug。
    *    监控程序执行过程中的线程行为, 发现其中存在的竞争现象, 线程阻塞以及潜在的线程死锁问题, 
    *    提示同线程错误相关的源代码位置, 侵权变量以及堆栈跟踪等。
    * 
    * Intel Thread Profiler 线程档案器 2.2 或更高版本
    *    可以帮助调整Win32*和OpenMP*线程化软件的性能。
    *    通过监控程序的运行来检测线程性能的相关问题, 包括线程过载和同步冲突, 能够帮助查找负载平衡, 同步开销等线程性能问题。
    *    可以进行关键路径分析。
    *
    * Intel 数学核心函数库( MKL ) -- 是一套经过高度优化的, 线程安全的数学函数库。功能领域包括：
    *     a. 线性代数 ——BLAS, LAPACK
    *     b. ScaLAPACK
    *     c. PARDISO稀疏矩阵解算器
    *     d. 离散傅立叶变换（Discrete Fourier transforms, DFTs）
    *     e. 矢量数学库（Vector Math Library, VML）
    *     f. 矢量统计库（Vector Statistical Library, VSL）——随机数生成器
    * 
    *******************************************************************************************************************************/

    /*******************************************************************************************************************************
    * Klocwork -- 服务器+客户端, BS架构, 有 Windows/linux/Unix 等多个版本
    *   功能模块
    *     Klocwork for C/C++ And Java
    *     Klocwork Architectural Analysis
    *     Klocwork Metrics and Trending -- 度量和趋势分析
    *     Klocwork Project Central -- 查看分析结果的Web服务
    *   服务(server_name)
    *     lm(license服务器, 端口号27000) -- 
    *     tomcat(Web服务器, 端口号8068) -- 
    *     mysql(数据库服务器, 端口号3311) --
    *     rmimanager(分析引擎调度服务器, 端口号1103) -- 
    *   命令工具
    *     kwservice [check|start|stop] <projects_root> <server_name> -- 查看|启动|停止 服务
    *     KMC -- 
    *   设置分析的缺陷和安全漏洞类型：
    *     1.System configuration -> problems_default.pconf.xml -> Edit in advanced editor -> Klocwork Configuration Editor;
    *     2.<projects_root>\projects\workspace\rules 下的 metrics_default.mconf, usagerules_default.uconf 等
    *   用Klocwork分析C/C++项目(五种方法)
    *     1.命令 kwinforce 或 kwinforce plugin 分析 -- 通常是在开发人员开发过程中分析一个或几个文件
    *     2.用Source Root Directories分析 -- 分析指定目录下所有指定后缀的源文件（不推荐：须手工设置文件类型, 不能确定头文件调用的正确顺序）
    *     3.用Build Specification Files分析 -- 首选方法（真实体现了构建的过程和配置选项）
    *         VS20XX -- kwVcprojParser<vcproj/slnfile> -c <build_config> -o <spec_name>.out
    *         make -- kwinject-o <spec_name>.out <make/build batch cmmand>
    *       然后使用 kwinject 生成的 .out 文件作为输入
    *     4.用Visual Studio Project,Solutionor Workspace分析 -- VS程序首选, 输入为 dsp/dsw/vcproj/sln 等
    *     5.用Tables分析 -- 从中间文件进行分析, 适用于没有更改源码, 仅仅改变了要分析的缺陷和安全漏洞类型的分析, 可节省分析时间
    *   Options
    *     Generate problem filter：创建一个过滤文件用于隐藏不希望看到的缺陷
    *   构建失败 -- 查找信息"parse error","syntax error","can not include"
    *   分析常用的知识库定制(*.kb 文件)
    *     BPS -- 缓冲区属性设置信息描述一个函数如何修改缓冲区属性
    *     NPD -- 声明一个函数在不进行NULL检查的情况下, 会发生空指针引用
    *     DMEM -- 声明自己的内存管理函数（函数如何分配或释放内存）
    *     FREE -- 声明释放内存的函数
    *******************************************************************************************************************************/

    /******************************************************************************************************************************
    * LoadRunner -- HP网站下载, 支持Win和Linux, 试用版只有10天
    *   9.5破解版本的License(未测试)：globa100 -- AEAMAUIKY-AFEKEKJJKEEA-BCJGI
    *                                 web10000 -- AEABEXFR-YTIEKEKJJMFKEKEKWBRAUNQJU-KBYGB
    *   
    *   预测系统行为和性能的负载测试工具, 通过以模拟上千万用户实施并发负载及实时性能监测的方式来确认
    * 和查找问题, LoadRunner 能够对整个企业架构进行测试。主要由三大主要部分组成：
    *   Controller -- 组织起多用户的测试方案, 将测试过程自动化
    *   VuGen(Virtual User Generator) -- 开发 Vuser 脚本的主要工具, 可以录制和运行脚本, 很简便地创立起系统负载
    *   Analysis -- 在整个测试过程中, 记录下所有产生的和所监视的数据, 将其绘成图表
    *
    ******************************************************************************************************************************/

    /******************************************************************************************************************************
    * NuGet -- VS扩展, 能简化在VS项目中添加, 更新和删除库(部署为程序包)的操作。
    *   VS2012中使用: 
    *     1.升级NuGet: Tools -> Extensions and Updates -> Updates -> Visual Studio Gallery
    *     2.新建C++工程,  
    * 
    *   NuGet程序包是打包成一个文件的文件集, 扩展名是 .nupkg, 使用开放打包约定 (OPC) 格式
    *   NuGet程序包, 可以存放在Nuget提供的服务器上, 也可以存放在公司自建的服务器上, 或者直接存放在项目目录中
    * 
    * 制作C++的.nupkg 包, 见:
    *   http://blogs.msdn.com/b/vcblog/archive/2013/04/26/nuget-for-c.aspx 
    *   http://coapp.org/pages/tutorials.html
    *
    * 将NuGet程序包配置在项目目录中
    *   http://beginor.github.io/2013/03/31/nuget-custom-package-repository-location.html
    ******************************************************************************************************************************/
 
	
    /******************************************************************************************************************************
    * PC-Lint(Windows)/FlexeLint(Linux) -- http://www.gimpel.com/ ,  静态代码检测工具,目前最高版本是9
    *   下载地址：http://download.csdn.net/source/2258242  8.x
    *             http://download.csdn.net/download/liuchang5/3005191  9.0e(其中有 pc_lint经验.pdf)
    *   对 C/C++ 源码进行静态分析的工具, 主要针对指针, 任务等进行分析, 但无法发现
    *   运行时错误和逻辑错误。支持 VC, gcc, Intel C/C++ 等, 可以比一般的C/C++编译器进行更深入的语义分析
    *   运行平台是 Windows, Dos, Linux下可以用 FlexeLint, 具体帮助可以参见 gcc-readme.txt。
    *   支持16/32/64的平台环境, 可以检测单个文件和整个工程
    *   使用前需要通过 Config.exe 向导生成配置文件(std.lnt),里面定义了检查的配置信息
    *
    * 常见问题及解决方式:
    *   1."Error -- Unable to open include file 'xxxx' "
    *      需要通过 -i 指定lint检查时需要包含的库文件的路径(系统的可以放在 std.lnt 配置中, 项目相关的可以放在 options.lnt 中)
    *   2.屏蔽各种库(如 MFC/ATL 等)的警告(std.lnt 中设置的会被options.lnt中的同名配置覆盖?)
    *     在 options.lnt 中加入 -wlib(0)
    *   3.默认的输出结果很多, 很难看到真正的问题(默认为 -w3, 输出 Error + Warning + Info + Note)
    *     在 options.lnt 中加入 -w2  //只输出 Error + Warning
    *   4.Lint 不支持 UTF16, 因此源代码最好保存成带签名的UTF8格式
    *   5.先使用 dir 生成要检测的文件列表, 然后 lint-nt [选项] filelist.lnt 的方式进行检查
    *     文件列表文件的生成：dir d:\MyWork\*.cpp /s/b/a:-d > d:\pc-lint\filelist.lnt
    *
    * 文件介绍：
    *   lint-nt.exe [选项] [选项文件(*.lnt)] 分析文件(支持通配符*.cpp)或文件列表文件 
    *     +ffn -- 输出文件全路径名, 确保在IDE环境中可以双击后在不同的文件间切换
    *     -i -- 指定lint检查时需要包含的路径
    *     -u -- 进行单元检查, 抑制许多模块间问题告警
    *        ?? -u xxx.lnt -- 使用指定的xxx.lnt配置文件
    *     -os(结果文件路径)   
    *   
    * 
    *   LIN.bat -- 通过向导生成的批处理文件, 能按照用户指定的配置(一般是 std.lnt, 
    *     可以有多个, 通过 _a 到 _z 的后缀区分)调用pclint, 可以放到系统的Path路径中
    *   LSET.BAT -- 会将PC-lint的目录加入当前%PATH%的批处理, 个人感觉不如将Lint的目录加入PATH更好
    *   std.lnt -- 通过向导生成的配置文件, 其中会调用的 .lnt 文件需要由lnt目录拷贝到同一目录下, 否则会出 xxx 错误
    *   options.lnt -- 包含屏蔽错误信息的配置文件, 可以打开或关闭某些开关, 从而激活或抑制某些错误
    *     (如 if(b = fun()),  符号无符号复制等)
    *
    *   au-xxx.lnt -- C++重大贡献者建议的选项
    *   co-xxx.lnt -- 编译器告警屏蔽选项的配置文件, 如 gnu,mscX0,
    *   env-xxx.lnt --  支持对应的IDE环境整合所需要的配置文件, 并且包含了对应IDE配置的详细说明
    *   lib-xxx.lnt -- 各种库文件告警屏蔽选项的配置文件, 如stl, atl, mfc等
    *   xxx.h/xxx.c(pp) -- 分析时需要的头文件和源文件, 配置声明文件包括一些编译器特有的关键字和特有
    *     用法, 不一定符合c/c++标准, PC-lint为支持这些标准, 通过使用这些头文件和源文件里的特有标识替换
    *     分析文件里对应的代码
    *   xxx.lob -- lint分析处理时的中间文件(Lint Object Module)
    * 用向导生成的一个 std.lnt (适用于VC2008)
    *   au-sm123.lnt au-ds.lnt                              //Effective C++, Dan Saks, MISRA 2004 等
    *   co-msc90.lnt                                        //VC2008
    *   lib-atl.lnt lib-mfc.lnt lib-stl.lnt lib-w32.lnt     //常用的库 ATL,MFC,STL,Win32 
    *   options.lnt  -si4 -sp4 -wlib(1) -w3                 //会使用自定义的options.lnt中的配置
    *   -i"C:\Program Files\Microsoft SDKs\Windows\v6.0A\Include"
    *   -i"D:\Microsoft Visual Studio 9.0\VC\include"
    *   -i"D:\Microsoft Visual Studio 9.0\VC\atlmfc\include"
    *   -i"E:\FJSDK\Windows\FTL"
    * 自定义的options.lnt配置
    *   -wlib(0)                    //屏蔽库中文件的告警
    *   
    *  
    * 在VC的环境中使用, 通过创建外部命令的方式使用, 执行检查后通过快捷键 F8 在各个警告之间切换
    *   检查当前正在编辑的单个文件：
    *     1.标题为: PC-LINT File Check
    *     2.命令为: D:\lint\lint-nt.exe
    *     3.参数为: +v -i"D:\lint"  std.lnt env-vc9.lnt "$(ItemPath)"  -- 似乎可以不要“env-vc9.lnt”?
    *     4.初始目录为: "$(ItemDir)"
    *     5.选中“使用输出窗口”, 会自动选中“退出时关闭”
    *   检查当前正在编辑的工程, 分两步：创建工程相关的.lnt -> 分析.lnt
    *     TODO:实测不行, 最好是写批处理, 生成文件列表来检查
    *     1.标题为：PC-LINT Project Creation
    *     2.命令为: D:\lint\lint-nt.exe
    *     3.参数为: +v -os($(TargetName).lnt) $(ProjectFileName)
    *     4.初始目录为: $(ProjectDir)
    *     5.选中“使用输出窗口”, 会自动选中“退出时关闭”
    *     6.标题为: PC-LINT Check Project, 
    *     7.命令为: D:\lint\lint-nt.exe
    *     8.参数为: +v -i"D:\lint" std.lnt env-vc9.lnt $(TargetName).lnt
    *     9.初始目录为：$(ProjectDir)
    *     10.选中“使用输出窗口”, 会自动选中“退出时关闭”
    *   还有一个所谓的 unit check (在创建完 Project.lnt 后), 具体有什么用？
    *     参数：-i"D:\lint" std.lnt env-vc9.lnt --u $(TargetName).lnt $(ItemPath)
    *     初始化目录：$(ProjectDir)
    *     
    * format 说明(如 format=%f %l %t %n:%m )
    *   %f -- 文件
    *   %l -- 行号
    *
    * 告警配置(部分告警是误报, 不更改时可以屏蔽, 可以在代码中使用特殊的注释格式进行屏蔽), 
    *   尽量采用行屏蔽的方式, 
    *     //lint !e告警号1 -e告警号2 -- 本行禁止输出指定的告警, 一般放在行尾,各选项以空格分开
    *   多行会报告警告的代码, 用 -save 和 -restore 包含起来后, 就不会再报指定的错误(此处为813)了
    *     /×lint -save -e813 ×/ 需要检测的代码 /×lint -restore ×/    -- 注意：这里的 × 实际上应该是 *
    * options.lnt 中的配置
    *   "-" -- 禁止输出相应的错误信息
    *   "+" -- 允许输出相应的错误信息
    *   "#" -- 允许使用通配符 "?" 和 "*"
    *   -e(告警号1,[告警号2]) -- 禁止下一个表达式的告警
    *   --e(告警号1,告警号2) -- 对当前整个表达式禁止输出告警
    *   -e{告警号} -- 表达式整个屏蔽(和上一个的区别？)
    *   -efile(告警号,文件列表) -- 禁止指定的文件对告警
    *   -efunc(告警号,函数名列表) --
    *   -elibsym(告警号,函数名列表) --
    *   -emacro(告警号,宏名) -- 宏展开时禁止告警, 如 -emacro(*,END_MSG_MAP)
    *   -esym(告警号,符号名) -- 可对指定符号名(函数名, 变量名等) 进行告警设置, 如 -esym(534, printf,scanf)
    *   -etemplate(告警号) -- 模版展开时禁止告警
    *   -s符号字节数 -- 设置符号的字节数, 如 -sb8(字节为8比特),  -sc1(char为1字节), -sl4(long为4字节)
    *   -function(比较基础函数,新函数) -- 函数模仿？设置"新函数"采用和"比较基础函数"相同的比较配置进行检查, 如
    *     -function(strcpy,myStrCpy) 后：char buf[4]; myStrCpy(buf,"abcde"); 回报419 的警告(buf越界)
    *   +libdir(第三方库文件目录) -- 将指定目录下的文件设置为lib, 之后可以用 -elib/-wlib 等进行设置
    *   -v -- verbosity 
    *   -wlib(等级) -- 对函数库文件(在-i中包含的?)设置告警输出等级(0不输出信息, 1+错误,2+告警, 3+其他提示, 4所有信息)
    *   -w输出等级 -- 设置告警输出等级
    *
    * 常见错误类型(在结果中搜索 "error xxx" ), <必改>, [建议更改], {可忽略}
    *   [ 19] -- Useless Declaration, 通常是有两个连着的分号, 一般是宏本身定义了分号, 但使用时又在结尾加了分号
    *   { 40} -- Undeclared identifier 'xxx', 
    *   <415> -- access of out-of-bounds pointer, 数组访问越界
    *   <423> -- Creation of memory leak in assignment to variable 'Symbol', 给已有变量的指针赋值, 可能造成内存泄露
    *   [429] -- Custodial pointer 'Symbol' (Location) has not been freed or returned
    *            指针没有释放或返回, 可能出现内存泄露。但也可能是加入了特定容器进行管理。
    *   [438] -- Last value assigned to variable 'Symbol' not used
    *   [529] -- Symbol 'Symbol' (Location) not subsequently referenced, 定义以后就没有再使用
    *            一般可以把变量定义和复制删除(注意：不能简单地把整行代码删除, 否则函数就不会调用了)
    *   <530> -- Symbol 'xxx' not initialized, 变量未初始化
    *   <533> -- 不是所有的路径都返回了结果。function 'Xxx' should return a value
    *   [534] -- Ignoring return value of function 'xxx', 忽视了函数的返回值
    *   {537} -- Repeated include file 'FileName', 重复包含了相同的头文件?
    *   <540> -- Excessive size, 字符串初始化时超过定义的缓冲区大小
    *   <604> -- Returning address of auto variable 'xxx', 返回局部变量的地址
    *   <616> -- control flows into case/default, swtich...case 中没有break, 通常是错误
    *   <644> -- Variable 'xxx' may not have been initialized, 因为执行路径的问题, 变量可能未初始化
    *   <661> -- possible access of out-of-bounds pointer, 定义的数组, 访问时越界
    *   {830} -- "Location cited in prior message"。通常接在一个特定的错误后面, 指定该错误指向的函数原型, 通常只更改调用的地方即可。
    *   <1401>(类似的有1402,1403等) -- 成员变量未在构造函数中初始化, member 'Xxx' not initialized by constructor
    *     BUG? 如果类没有构造函数, 则检查不出来
    *   <1411> -- Member with different signature hides virtual member 'Symbol', 子类有同父类同名, 但函数签名不同的函数
    *   <1509> -- base class destructor for class 'Name' is not virtual, 有子类的父类的析构函数不是虚拟的
    *   <1510> -- base class 'Name' has no destructor, 子类有析构函数, 但父类没有定义析构, 一般需要增加虚析构定义
    *   <1516> -- Member declaration hides inherited member 'Symbol', 子类定义了和父类同名字的成员变量,
    *             注意:通过宏定义的消息映射等会有相同的变量名
    *   <1540> -- pointer member 'Symbol' (Location) neither freed nor zero'ed by destructor. 指针变量在析构中没有释放或赋值为NULL
    *   <1541> -- member 'Symbol' (Location) possibly not initialized by constructor, 构造函数中可能没有初始化指定变量
    *   [1551] -- function 'Symbol' may throw an exception in destructor 'Symbol', 
    *      在析构函数中调用可能抛出异常的代码, 需要通过 try...catch 捕获异常
    *   [1579] -- Pointer member ’Symbol’ (Location) might have been freed by a separate function, 类中指针类型的变量没有在析构函数中明确释放(可能通过内部函数释放了),
    *             可以设置 /x -sem( CMyClass::myCleanMethod, cleanup ) x/ 的选项来过滤。
    *   TODO: 没有被适当检验的数组下标; 未被初始化的变量; 使用空指针; 冗余代码
    *
    * 其他的工具
    *   ALOA(A Lint Output Analyzer ) -- 可对结果统计并排序
    *   lintProject -- 开源的工具, 可以将 sln/vcproj 等工程文件转换成 文件列表文件(lnt)
    *   RuleChecker -- 倾向于代码编码规范的检查, 比如代码缩进格式, case语句书写规范, 函数声明和布尔表达式的编写规则
    ******************************************************************************************************************************/

    /******************************************************************************************************************************
    * Purify
    ******************************************************************************************************************************/

    /******************************************************************************************************************************
    * ReviewBoard -- Web Code Review Tool( http://www.reviewboard.org/screenshots )
    *   插件: http://code.google.com/p/reviewboardvsx/
    ******************************************************************************************************************************/

	/******************************************************************************************************************************
    * scons(http://www.scons.org/) -- 需要先安装Python,安装好Scons后, 在PATH中加入 scons.bat 所在路径
    *   Python写的跨平台(Windows/Linux/Mac OS等)的下一代自动化构建工具(类似 GNU make, 但更高效和可靠), 可以用来编译 NSIS/jsoncpp 等的源码
    *   安装:
    *     Linux: python setup.py install -- 需要管理员权限, 似乎有 --install-lib|--install-dir 参数, 但测试未成功
    *   SConstruct -- python 格式的编译说明文件,scons可以根据该文件自动完成依赖关系的推导及编译链接等过程
    *   可以使用多层次的 SConscript(['子目录的SConscript脚本']) 脚本文件形成多层目录构建
    *     Library|StaticLibrary('foo',['f1.c','f2.c','f3.c']) -- 将文件f1.c,f2.c和f3.c编译成静态库libfoo.a
    *     Java(xxx) -- 
    *     Object -- 只编译成目标文件(.o 或 .obj)
    *     Program('hello', ['hello.c'], LIBS='m', LIBPATH=['/usr/lib','/usr/local/lib'],CCFLAGS='-DHELLO'); 
    *       --  将hello.c(.cpp?) 编译成可执行文件hello, 其中使用到了 libm.so|.a 库(即 -lm),
    *       语法为:Program( target='program',source=src_files )
    *     SharedLibrary('foo',['f1.c','f2.c','f3.c']) -- 编译成静态库libfoo.so
    *   参数:
    *       LIBS=[依赖的静态, 动态库]
    *       LIBPATH='../lib'  -- 指定搜索lib的路径
    *       CCFLAGS='-D_DEBUG' -- 编译参数, 如定义 _DEBUG 宏
    *       CPPPATH=['include', '/home/project/inc'] -- 头文件包含, 编译时使用 -I
    *       CPPDEFINES -- 宏定义?
    *       LINKFLAGS -- 链接参数?
    *   语法(可以使用 Python 标准的 import 等语法)：
    *     原始文件列表:
    *       1.使用数组的方式列出所有需要编译的源文件 -- 如 ['f1.c','f2.c','f3.c'] 或 Split('f1.c f2.c f3.c')
    *       2.使用 Glob 函数的正则表达式 -- 如 Glob('*.c')
    *     节点对象(nodes)--SCons把所有知道的文件和目录表示为节点,builder方法的返回值都是节点对象List,可以相加(+)
    *       File(['f1.c']) -- 创建文件节点
    *       Dir('classes') -- 创建目录节点
    *     内置函数|对象?
    *       Decider('MD5|timestamp-newer') -- 确定文件是否被修改的方式, 默认为 MD5
    *       Entry(xxx) -- 统一的节点对象方式(文件, 目录等)
    *       Environment -- 环境对象, 需要 import os?
    *         Dictionary() -- 获取到环境对象中的键值对, 然后可通过 for key in [xxx] 等方式显示
    *         Install('目的地','文件')
    *       SetOption('参数名',参数值) -- 
    *     
    *     调试命令:
    *        print "信息1", "信息2" -- 多个信息用逗号分隔?
    *     示例:
    *       1.判断文件是否存在：import os.path<CR> if not os.path.exists(program_name):<CR> print program_name, "does not exist!"
    *   scons 命令参数
    *     -c|--clean -- 执行清理任务
    *     --debug=TYPE -- 打印调试信息, 可选的有 includes,objects,pdb 等
    *     -h|--help -- 打印帮助信息
    *     -j N -- 同时执行N个Job
    *     -Q -- 屏蔽"Reading/Building"等的进度消息
    ******************************************************************************************************************************/

	/******************************************************************************************************************************
    * 版本控制工具 SVN（CVS的替代, 对于二进制文件只保存和上一版本不同之处）, SVN一般有如下目录：branches, tgs, trunk
    *   服务器(Subversion/VisualSVN-Server 等)  -- http://www.visualsvn.com/downloads/( http://subversion.tigris.org/)
    *     http://www.collab.net/downloads/subversion
    *     自带命令行的 svn.exe 作为客户端
    *   客户端(TortoiseSVN) -- http://tortoisesvn.net/downloads
    *   VS 插件(AnkhSvn)    -- http://ankhsvn.open.collab.net/
    * 
    * 全局配置文件： ~/.subversion/config
    *   global-ignores -- 设置全局过滤列表(目录或扩展名等)
    * 
    * 环境变量
    *   SVN_EDITOR <==
    *   VISUAL, EDITOR
    *
    * svnadmin.exe 
    *   create 空的目录名 -- 创建版本库, 等价于TortoiseSVN中 右键->TortoiseSVN->Create Repository here
    * svnserve.exe <== 启动服务并在端口3690等待请求
    *   --daemon : 以守护进程方式运行, 手动终止之前不会退出
    *   --root 本地目录名: 设置根位置来限制服务器的访问目录
    *   批处理方式启动svn：
    *     set CUR_PATH=%~dp0； svnserve --daemon --root %CUR_PATH% 
    *   创建服务(命令行中, 注意每一个等号后面都要有一个空格, 否则会报错)：
    *     sc create SVN binpath= "E:\Subversion\bin\svnserve.exe --service --root E:\fishjam\Code_SVN" displayname= "SVN Service" depend= Tcpip start= auto
    *
    * 配置文件(版本库目录的conf子目录中)
    *   svnserve.conf
    *     password-db=passwd -- 
    *   passwd
    *     [users] -- 其后每一行都是一个用户, 采用 用户名=密码 的方式
    *
    * SVN的命令行( svn.exe )
    *   add 本地文件或目录 <== 增加
    *   blame 文件 <== 查看文件的修订合作者等信息（每行的最后修改任何版本）, 可通过 | sort 查看最后的修改
    *   checkout https://xxxxx 本地路径 --username 用户名  <== 检出库
    *   cleanup <== 解决“工作副本已锁定”的错误, 问题是怎么发生的？是否正常？
    *   copy SRC DST <== 库<-->本地 或 本地之间拷贝（注：不支持库之间）
    *   export SRC DST <== 可从库, 本地修改中导出不带版本控制信息的结构
    *   import PATH URL <== 将无版本的文件或树到如到项目存储库中
    *   info <== 查看库路径信息
    *   list <== 列出库中的内容(当前目录下的文件和目录)
    *   log <== 更改历史
    *   merge <== 以库中的最新版本德文件合并到工作副本中
    *   resolved 文件 <== 已解决冲突
    *   status(st) <== 查看本地的文件修改情况, 通常可用 svn st | grep ^[^?] 的方式查看更改
    *   switch <== 更新副本的URL
    *   proplist 目录 -R <== 列出指定目录下所有的属性(如 svn:executable)
    *   propedit 属性名(如 propedit) 版本路径 [ --editor-cmd notepad ]  
    *     <== 使用 notepad 设置属性(如果设置了SVN_EDITOR 环境变量的话, 可以用指定的编辑器进行编辑设置 )
    *   设置属性( propset )
    *       svn:externals "[-r版本] 服务器URL地址 本地名"  <== 实现文件, 目录共享。
    *         注意, URL中的空格必须用%20代替, 本地名的空格必须用双引号。"^/"代表根URL, 示例:
    *         绝对路径方式: swanfalconapp https://....    (TODO: 需要确认)
    *         相对路径方式: ^/trunk/Temp/FJDriverDemo/InlineHook.h Temp/nComic/ComicHelper/InlineHook.h
    *       svn:executable <== 设置可执行属性(用于linux的so等？)
    *       svn:ignore  "*.obj *.exe *.bak" 要设置的目录(如.) <== 设置SVN忽略的文件(可以通过 * 指定特殊的扩展名)
    *    update <== 更新代码, 可能会发生冲突
    *    del --keep-local MyConfig.xml  <== 保留本地副本, 每人有不同的副本（尚未测试是否真行）
    * 
    * 通过SVN设置外接, 来配置本地代码目录--使用本地的 Local Repository 作为代理, 中转到真正的外链接
    *   1.svnadmin create 本地仓库目录 <== 
    *   2.svn co file:///本地仓库目录 . <== 将本机仓库目录checkout到临时目录下, 之后会进一步进行配置
    *   3.创建需要的目录结构, 加入需要的文件, 然后使用 svn add 加入;
    *   4.$SVN_EDITOR=gedit svn pe svn:externals 链接名 <== 设置 svn 外链接属性
    *     在弹出的 gedit 中输入外部链接的路径：外部链接名 SVN地址, 如:
    *   5.svn commit -m "注释" <== 将已经配置好的本地目录结构 commit 到 本地的 Local Repository 中
    *   6.Eclipse 中添加 Resposity location, 并使得 URL 指向本地的 Local Repository, Checkout后
    *     就可以直接在Eclipse中管理代码了
    *
    * 冲突解决
    *   p(ostpone) <== 推迟, 合并代码并由用户解决, 冲突的地方采用 <=== 等分割开[Windows下的默认解决方式]
    *   mc(我的版本)
    *   tc(他人的版本)
    *   df(diff-full)显示全部差异
    *   edit <== 编辑, 但需要定义 SVN_EDITOR 等环境变量
    *   r(esolved) <== 已解决
    *   dc()
    *   mf <== 全用我的文件
    *   tf <== 全用他们的文件(和tc的区别？)
    ******************************************************************************************************************************/
    
    /******************************************************************************************************************************
    * UltraEdit(查找替换时的正则表达式), 有三种：P(erl), U(nix), (Ultra)E(dit),  L(ex,通常同U)
    *   找string              L<== 直接输入string
    *   找"a+b"串(字面)：   U<== "a+b"
    *   转义字符：          U<== \              E<== ^
    *   替换表达式(分组)：  U<== (KEYWORD)      E<== ^(KEYWORD^)
    *   替换标签(1-9)：     U<== \n             E<== ^n
    *   逻辑或(查找A或B)：  U<== (A|B)          E<== ^{A^}^{B^} 
    *   ab的1次或多次：     U<== (ab)+
    *   行首：              U<== ^              E<== %
    *   行尾(r$等价于r/\n)：U<== $              E<== $
    *   任意数量字符：                          E<== *
    *   前字符0或1次：      U<== ?
    *   前字符0或多次：     U<== *              E<== ++
    *   前字符1或多次：     U<== +              E<== +
    *   前字符N到M次：      U<== \{N, M\}
    *   出现次数A出现N到M)：  L<== A{N,M}   <==说明：Lex的语法, 如 [a-z]{5,} 表示长度大于5由 a-z 组成的字符
    *   除\n外任何单字符：  U<== .              E<== ?
    *   换页符：            U<== \f             E<== ^b
    *   0D0A(DOS)：         U<== \p             E<== ^p
    *   0D(MAC)：           U<== \r             E<== ^r
    *   换行符OA(UNIX)：    U<== \n             E<== ^n
    *   空格制表：          U<== \s
    *   非空字符：          U<== \S
    *   制表(TAB)：         U<== \t             E<== ^t
    *   垂直制表：          U<== \v
    *   下划线或字符：      U<== \w
    *   非字符：            U<== \W
    *   范围(如小写字母)    U<== [a-z]          E<== [a-z]
    *   排除(如0-9)：       U<== [^0-9]         E<== [~0-9]
    *     除ab外的任意字符   <== [^ab]
    *   向前匹配(尾部相关)：   L<== r/s 匹配后面接着s的r。如 ABC/D 匹配 ABCD 而不匹配 ABCE, 但找到的模式为 ABC
    * 注意：
    *   *和+ 只匹配之前最近的元素, 可以用小括号将多个元素括起来, 则通配符就可以匹配整个括号的内容了
    *   "^" 放在方括号的首部表示"除了"的意思, 在其他地方没有特别意义
    *   "|"不在方括号中表示“或者”, 在方括号中只表示"|" 符号
    * 例子：
    *   1.查找 create poa ok 或 create orb ok, 然后倒序（即为 ok poa create）
    *     Unix<== (create) (orb|poa) (ok), 替换字符串： \3 \2 \1  -- 注意：有BUG
    *     UltraEdit<== ^(create^) ^(^{orb^}^{poa^}^) ^(ok^),  替换字符串：^3 ^2 ^1
    ******************************************************************************************************************************/

    /******************************************************************************************************************************
    * 单元测试(Unit Testing) --
    *   异常测试--确认代码的结构可靠性, 能处理所有可行的输入以及输入组合, 不会产生预料之外的异常。
    *   功能测试--验证所建立模块是否符合需求和功能是否正常工作。
    *   回归测试--验证现有代码行为不会随着代码库改进而更改,在代码更改之后运行, 以捕获更改代码行为中的偏差
    *
    ******************************************************************************************************************************/

    /******************************************************************************************************************************
    * Visual Unit -- 国产的单元测试工具
    *   
    ******************************************************************************************************************************/

    /******************************************************************************************************************************
    * Visual Studio
    *   编辑 UTF-8格式的文档（Linux同步开发）：
    *     Options->Text Editor->General->Auto-detect UTF-8 encoding without signature
    * 
    * 查找中输入 ":a+" 且选中"正则表达式", 可以搜索 文档内硬编码的字符串
    * 利用正则表达式去除 .ini 文件中 = 前后的空格和Tab： 查找： ^{[^ \t=]*}{[ \t]*}={[ \t]*}{.*}$ , 替换成：\1=\4 
    * 利用正则对VS2010中的.vcxproj.filters文件设置过滤目录(EmEditor中):
    *   查找: <(\w+) Include=\"(((\w*\\)*).*)\"\sx/>$           <== 注意: 组后的 "sx/>$" 其中的 x 应该是 *
    *   替换: <\1 Include=\"\2">\n        <Filter>\3</Filter>\n    </\1> 
    *   EditPlus中的语法(支持命名): <(?<tag>\w+) Include=\"(?<wholename>(?<path>(\w*\\)*).*)\"\sx/>$
    *                                       <$+{tag} Include=\"$+{wholename}\">\n        <Filter>$+{path}</Filter>\n    </$+{tag}>
    *   TODO:目前的替换方法会多一个 "\" 符号
    *
    * Visual Studio Team System(VSTS)
    *   内置工具和过程管理框架
    * 
    * Visual Studio Team Explorer(下载, 管理 CodePlex 上代码的工具)
    * 
    * Profiler(性能分析工具 -- 企业版中才有): 
    *   Tools->Performance Tools->Performance Wizard
    *  
    * 代码静态检查
    *   Analyze -> Run Code Analysis On Only
    *
    * 常见编译, 链接警告和错误
    *   C1859 -- unexpected precompiled header error, 微软的BUG, http://code.msdn.microsoft.com/KB976656, TODO:似乎工程配置出错也会报这个错
    *   C4005 -- 宏重定义, macro redefinition
    *   C4101 -- 未引用的本地变量 unreferenced local variable
    *   C4390 -- 空控制语句(可能是if后直接跟了分号),empty controlled statement found; is this the intent
    *   C4715 -- 不是所有的路径都有返回值, not all control paths return a value
    *   C4930 -- 将定义变量的语法写成了函数声明的语法。prototyped function not called (was a variable definition intended?)
    *   C4065 -- switch 语句里面有default但是没有case。switch statement contains 'default' but no 'case' labels
    *   D9038 -- /ZI is not supported on this platform; enabling /Zi instead
    *     解决: 仅 x86 支持 /ZI, 如果在x64下启用就会报这个错。更改: C/C++ => General =>Debug Information Format
    *   LNK2026:module unsafe for SAFESEH image -- VS2012编译汇编文件时, 报告的错误, /SAFESEH
    *     解决：(推荐)使用 ml(64).exe 编译时, 可以指定 /safeseh 参数(set the Use Safe Exception Handler MASM property to Yes)
    *            或    整个程序链接选项Command中输入 /SAFESEH:NO
    *   LNK4222: exported symbol 'DllCanUnloadNow' should not be assigned an ordinal
    *     解决: DllCanUnloadNow 等函数不能通过序号导出, 删除 .def 中对应的序号即可
    * 运行错误:
    *   64位机器上运行32位的程序时,报告0xc000007b(STATUS_INVALID_IMAGE_FORMAT) -- 
    * 
    * 函数断点：方式为 ???  -- 
    *   {,,USER32.DLL}_MessageBeep@4 对应 WinDbg中的 bp USER32!MessageBeep
    *   TODO:为什么有的函数设置不起来？而且规则是什么？@4 对应什么 -- 可以通过 dumpbin 查看导出的函数, 来确认是否能设置断点
    ******************************************************************************************************************************/

    /******************************************************************************************************************************
    * VC++默认情况下, 调试版本中处理异常, 发布版本中并不处理。即 try {*NULL = 100;} catch(...){处理只在 Debug 中有效} 
    * 同步异常模型(/Gx 的编译设置), 如采用异步异常模型, 任何错误指令都会产生异常(/Eha)
    * C++异常只能由 throw 语句抛出, 结构化异常(可用 __try ... __except 捕获) 
    * 
    * 
    * C++ 异常和结构化异常的比较 -- P139
    * VC++ 不支持异常规范(C4290) -- 即不支持用 throw 声明函数可能抛出的异常类型
    *
    * 编译器设置：
    *   1.保证所有版本(包括发布版本)中都带有调试符号PDB文件。
    *     优化后的发布版本并不始终能够匹配源代码的执行流, 不易进行单步跟踪；
    *     对堆栈寄存器进行了优化, 无法看到完整的调用堆栈信息；由于会在文件中添加标识PDB文件的调试区
    *       (section)字符串, 会稍微增加文件的大小。
    *       a..NET(C#/VB) 中：   Build -> Generate Debugging Infomation => True
    *       b.本机代码(C/C++)中：C/C++ -> General -> Debug Information Format => Program Database(/Zi)
    *         Linker ->General -> Enable Incremental Linking => No(/INCREMENTAL:NO), 将增量连接开关设为No, 
    *         Linker -> Debugging -> Generate Debug Info => Yes(/DEBUG),加入调试信息, 但使得连接器自动连
    *           接所有函数, 不管他们是否被引用（需要 /OPT:REF 删除）
    *         Linker -> Debugging -> Generate Program Database File => $(OutDir)/$(ProjectName).pdb, 
    *         Linker -> Debugging -> Strip Private Symbols => $(OutDir)/$(ProjectName)_Stripped.pdb, 
    *         Linker -> Optimization -> References => Eliminate Unreferenced Data(/OPT:REF), 只连接那些被程序直接调用的函数
    *         Linker -> Optimization -> Enable COMDAT Folding => Remove Redundant COMDATs(OPT:ICF), 必要的时候
    *           合并相同的数据COMDAT记录, 使得所有引用某常量值的地方只能使用唯一的常量数据变量。
    *   2.把托管代码中的编译警告视为编译错误（/WARASERROR+）, 将大部分本机代码的编译警告视为编译错误
    *
    *******************************************************************************************************************************/

    /******************************************************************************************************************************
    * Visual Assist -- VC助手(类似的还有 DPack / Resharper 等)
    * 1.更改缓存的默认位置( %APPDATA%\Visual Assist )
    *   HKCU\Software\Whole Tomato 下增加名为 "UserDataDir" 的字符串键, 其值为目录, 如"F:\Visual Assist X\Cache"
    * 1.AutoText 中的宏 和 环境变量（在系统中定义）
    *   %FILE%              Full filename with path 
    *   %FILE_PATH%         Path of file
    *   %FILE_BASE%         Filename without path or extension
    *   %FILE_EXT%          Filename extension
    *   %DATE%              Year/month/day formatted as %04d/%02d/%02d
    *   %YEAR%              Year formatted as %d
    *   %MONTH%             Month formatted as %d
    *   %MONTH_02%          Month formatted as %02d
    *   %MONTHNAME%         Three-character abbreviation of month
    *   %DAY%               Day of month formatted as %d
    *   %DAY_02%            Day of month formatted as %02d
    *   %DAYNAME%           Three-character abbreviation of day
    *   %HOUR%              Hour formatted as %d
    *   %HOUR_02%           Hour formatted as %02d
    *   %MINUTE%            Minute formatted as %02d
    *   %SECOND%            Second formatted as %02d
    *   %%                  %
    *   %USER_NAME%         USERNAME
    *   %0                  Current selection
    *   %1 through %8       User input field
    ******************************************************************************************************************************/

}

#endif //FTL_IDE_TOOLS_H

//#ifndef USE_EXPORT
//#  include "ftlIDETools.hpp"
//#endif
