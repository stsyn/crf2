# Microsoft Developer Studio Project File - Name="lesson1" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=lesson1 - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "lesson1.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "lesson1.mak" CFG="lesson1 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "lesson1 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
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
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# SUBTRACT MTL /Oicf
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 Winmm.lib opengl32.lib glu32.lib glaux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib SDL2.lib SDL2main.lib SDL2test.lib /nologo /subsystem:windows /machine:I386 /out:"Release/CRFly.exe"
# Begin Target

# Name "lesson1 - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CRF\Modules\Base.cpp
# End Source File
# Begin Source File

SOURCE=.\CRF\Core.cpp
# End Source File
# Begin Source File

SOURCE=.\demoscene.cpp
# End Source File
# Begin Source File

SOURCE=.\CRF\Modules\Binaries\Main.cpp
# End Source File
# Begin Source File

SOURCE=.\CRF\Modules\ExDrawing\Mask.cpp
# End Source File
# Begin Source File

SOURCE=.\CRF\Platform.cpp
# End Source File
# Begin Source File

SOURCE=.\CRF\Modules\Text.cpp
# End Source File
# Begin Source File

SOURCE=.\CRF\Modules\ExDrawing\Zoom.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CRF\Modules\Base.h
# End Source File
# Begin Source File

SOURCE=.\CRF\Core.h
# End Source File
# Begin Source File

SOURCE=.\CRF.h
# End Source File
# Begin Source File

SOURCE=.\CRF\Modules\Particles\LParticles.h
# End Source File
# Begin Source File

SOURCE=.\CRF\Modules\Particles\LPController.h
# End Source File
# Begin Source File

SOURCE=.\CRF\Modules\Particles\LPObjects.h
# End Source File
# Begin Source File

SOURCE=.\CRF\Modules\Sprites\LSprite.h
# End Source File
# Begin Source File

SOURCE=.\CRF\Modules\Binaries\Main.h
# End Source File
# Begin Source File

SOURCE=.\CRF\Modules\ExDrawing\Mask.h
# End Source File
# Begin Source File

SOURCE=.\CRF\Platform.h
# End Source File
# Begin Source File

SOURCE=.\CRF\Modules\Text.h
# End Source File
# Begin Source File

SOURCE=.\CRF\Modules\ExDrawing\Zoom.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
