# Microsoft Developer Studio Project File - Name="gk" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=gk - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gk.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gk.mak" CFG="gk - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gk - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "gk - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gk - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GK_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I "../.." /I "../../external/xdl" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GK_EXPORTS" /D "XDL_BUILD_DLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../../dist/opt/gk.dll"
# Begin Special Build Tool
TargetDir=\home\kevn\src\lib\gamekernel\dist\opt
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Release\gk.lib $(TargetDir)\gk.lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "gk - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GK_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I "../.." /I "../../external/xdl" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GK_EXPORTS" /D "XDL_BUILD_DLL" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../dist/dbg/gk.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=copy ..\..\test\input\config.xml .
PostBuild_Cmds=copy ..\..\test\input\config.xml .
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "gk - Win32 Release"
# Name "gk - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\gk\GameInput.cpp
# End Source File
# Begin Source File

SOURCE=..\..\gk\GameKernel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\gk\gk.cpp
# End Source File
# Begin Source File

SOURCE=..\..\gk\SystemDriverFactory.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\gk\AbstractGameApp.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\AnalogDevice.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\AnalogInput.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\AnalogInterface.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\ContextData.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\DigitalDevice.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\DigitalInput.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\DigitalInterface.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\DLLInterface.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\EventInput.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\GameInput.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\GameInputConfigure.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\GameKernel.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\gk.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\gkCommon.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\IDevice.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\IGameApp.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\IGameInput.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\IGameKernel.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\Input.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\InputInterface.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\ISystemDriver.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\Joystick.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\Keyboard.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\Mouse.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\Singleton.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\SystemDriverFactory.h
# End Source File
# Begin Source File

SOURCE=..\..\gk\TypedDevice.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "xmlpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\xmlpp\shared_ptr.h
# End Source File
# Begin Source File

SOURCE=..\..\xmlpp\xmlconfig.h
# End Source File
# Begin Source File

SOURCE=..\..\xmlpp\xmlparser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\xmlpp\xmlparser.h
# End Source File
# Begin Source File

SOURCE=..\..\xmlpp\xmlpp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\xmlpp\xmlpp.h
# End Source File
# Begin Source File

SOURCE=..\..\xmlpp\xmltokenizer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\xmlpp\xmltokenizer.h
# End Source File
# End Group
# End Target
# End Project
