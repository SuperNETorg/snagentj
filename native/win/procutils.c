//#include <inttypes.h>
#include <stdint.h>
#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>
#include <process.h>
#include <tlhelp32.h>

__declspec(dllexport) int32_t OS_getpid() { return(GetCurrentProcessId()); }

__declspec(dllexport) int32_t OS_getppid()
{
    int pid, ppid = -1;
    HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe = { 0 };
    pe.dwSize = sizeof(PROCESSENTRY32);
    pid = GetCurrentProcessId();
    if( Process32First(h, &pe)) {
    	do {
    		if (pe.th32ProcessID == pid) {
    			ppid = pe.th32ParentProcessID;
                break;
    		}
    	} while( Process32Next(h, &pe));
    }

    CloseHandle(h);
    return ppid;
}

__declspec(dllexport) int32_t OS_pingpid(int32_t pid) {
    HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, pid);
    DWORD dwExitCode = 0;
    if(!GetExitCodeProcess(process, &dwExitCode)) return 0;
    if(dwExitCode == 259) return 0;
    return 1;
}

__declspec(dllexport) int32_t OS_waitpid(int32_t pid, int32_t *statusp, int32_t flags) {
    _cwait (statusp, pid, WAIT_CHILD);
    return 0;
}

__declspec(dllexport) int32_t  OS_launch_process(char *args[])
{
    int32_t pid;
    pid = _spawnl( _P_NOWAIT, args[0], args[0],  NULL, NULL );
    return pid;
}

// from tweetnacl
__declspec(dllexport) void randombytes(unsigned char *x,int xlen)
{
    HCRYPTPROV prov = 0;
    CryptAcquireContextW(&prov, NULL, NULL,PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
    CryptGenRandom(prov, xlen, x);
    CryptReleaseContext(prov, 0);
}