# Microsoft Developer Studio Project File - Name="gk" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

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
!MESSAGE "gk - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "gk - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
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
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GR /GX /O2 /I "." /I "external/xdl" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /D "USE_WIN32" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

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
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /I "." /I "external/xdl" /D "_DEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /D "USE_WIN32" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "gk - Win32 Release"
# Name "gk - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\gk\GameKernel.cpp
# End Source File
# Begin Source File

SOURCE=.\gk\gk.cpp
# End Source File
# Begin Source File

SOURCE=.\gk\SystemDriverFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\gk\Version.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\gk\AbstractGameApp.h
# End Source File
# Begin Source File

SOURCE=.\gk\AnalogDevice.h
# End Source File
# Begin Source File

SOURCE=.\gk\AnalogInput.h
# End Source File
# Begin Source File

SOURCE=.\gk\AnalogInterface.h
# End Source File
# Begin Source File

SOURCE=.\gk\ContextData.h
# End Source File
# Begin Source File

SOURCE=.\gk\Device.h
# End Source File
# Begin Source File

SOURCE=.\gk\DigitalDevice.h
# End Source File
# Begin Source File

SOURCE=.\gk\DigitalInput.h
# End Source File
# Begin Source File

SOURCE=.\gk\DigitalInterface.h
# End Source File
# Begin Source File

SOURCE=.\gk\DLLInterface.h
# End Source File
# Begin Source File

SOURCE=.\gk\EventInput.h
# End Source File
# Begin Source File

SOURCE=.\gk\GameInput.h
# End Source File
# Begin Source File

SOURCE=.\gk\GameInputConfigure.h
# End Source File
# Begin Source File

SOURCE=.\gk\GameKernel.h
# End Source File
# Begin Source File

SOURCE=.\gk\gk.h
# End Source File
# Begin Source File

SOURCE=.\gk\gkCommon.h
# End Source File
# Begin Source File

SOURCE=.\gk\IGameApp.h
# End Source File
# Begin Source File

SOURCE=.\gk\IGameKernel.h
# End Source File
# Begin Source File

SOURCE=.\gk\Input.h
# End Source File
# Begin Source File

SOURCE=.\gk\InputInterface.h
# End Source File
# Begin Source File

SOURCE=.\gk\Joystick.h
# End Source File
# Begin Source File

SOURCE=.\gk\Keyboard.h
# End Source File
# Begin Source File

SOURCE=.\gk\Mouse.h
# End Source File
# Begin Source File

SOURCE=.\gk\Singleton.h
# End Source File
# Begin Source File

SOURCE=.\gk\SystemDriver.h
# End Source File
# Begin Source File

SOURCE=.\gk\SystemDriverFactory.h
# End Source File
# Begin Source File

SOURCE=.\gk\Version.h
# End Source File
# End Group
# End Target
# End Project
