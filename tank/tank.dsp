# Microsoft Developer Studio Project File - Name="tank" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=tank - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tank.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tank.mak" CFG="tank - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tank - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "tank - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tank - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "regexx" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "USE_AUDIERE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 audiere.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "tank - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "regexx" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "USE_AUDIERE" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 audiere.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "tank - Win32 Release"
# Name "tank - Win32 Debug"
# Begin Group "files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AudiereAudioSystem.cxx
# End Source File
# Begin Source File

SOURCE=.\AudioSystemFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\BmpImporter.cxx
# End Source File
# Begin Source File

SOURCE=.\ColorRGBA.cxx
# End Source File
# Begin Source File

SOURCE=.\CppImageExporter.cxx
# End Source File
# Begin Source File

SOURCE=.\Entity.cxx
# End Source File
# Begin Source File

SOURCE=.\FileHandler.cxx
# End Source File
# Begin Source File

SOURCE=.\Geode.cxx
# End Source File
# Begin Source File

SOURCE=.\glRenderLight.cxx
# End Source File
# Begin Source File

SOURCE=.\Image.cxx
# End Source File
# Begin Source File

SOURCE=.\imageIoReg.cxx
# End Source File
# Begin Source File

SOURCE=.\ImageManager.cxx
# End Source File
# Begin Source File

SOURCE=.\iniFile.cxx
# End Source File
# Begin Source File

SOURCE=.\Light.cxx
# End Source File
# Begin Source File

SOURCE=.\Material.cxx
# End Source File
# Begin Source File

SOURCE=.\Matrix4f.cxx
# End Source File
# Begin Source File

SOURCE=.\NullAudioSystem.cxx
# End Source File
# Begin Source File

SOURCE=.\Player.cxx
# End Source File
# Begin Source File

SOURCE=.\sys_glut.cxx
# End Source File
# Begin Source File

SOURCE=.\TankGame.cxx
# End Source File
# Begin Source File

SOURCE=.\Texture.cxx
# End Source File
# Begin Source File

SOURCE=.\TgaImporter.cxx
# End Source File
# Begin Source File

SOURCE=.\World.cxx
# End Source File
# End Group
# Begin Group "regexx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\regexx\chartables.c
# End Source File
# Begin Source File

SOURCE=.\regexx\config.h
# End Source File
# Begin Source File

SOURCE=.\regexx\get.c
# End Source File
# Begin Source File

SOURCE=.\regexx\internal.h
# End Source File
# Begin Source File

SOURCE=.\regexx\maketables.c
# End Source File
# Begin Source File

SOURCE=.\regexx\pcre.c
# End Source File
# Begin Source File

SOURCE=.\regexx\pcre.h
# End Source File
# Begin Source File

SOURCE=.\regexx\regexx.cpp
# End Source File
# Begin Source File

SOURCE=.\regexx\split.cpp
# End Source File
# Begin Source File

SOURCE=.\regexx\study.c
# End Source File
# End Group
# End Target
# End Project
