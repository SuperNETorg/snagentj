vcvars32.bat && cl.exe /D_USRDLL /D_WINDLL .\\native\\win\\procutils.c crypt32.lib advapi32.lib /link /DLL /OUT:.\\lib\\win32-x86\\procutils.dll && del procutils.obj