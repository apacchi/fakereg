// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

#pragma region Forward functions to system version.dll (via /EXPORT, not .def forwarder)
#pragma comment(linker, "/EXPORT:GetFileVersionInfoA=version_o.GetFileVersionInfoA")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoByHandle=version_o.GetFileVersionInfoByHandle")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExA=version_o.GetFileVersionInfoExA")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExW=version_o.GetFileVersionInfoExW")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeA=version_o.GetFileVersionInfoSizeA")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExA=version_o.GetFileVersionInfoSizeExA")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExW=version_o.GetFileVersionInfoSizeExW")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeW=version_o.GetFileVersionInfoSizeW")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoW=version_o.GetFileVersionInfoW")
#pragma comment(linker, "/EXPORT:VerFindFileA=version_o.VerFindFileA")
#pragma comment(linker, "/EXPORT:VerFindFileW=version_o.VerFindFileW")
#pragma comment(linker, "/EXPORT:VerInstallFileA=version_o.VerInstallFileA")
#pragma comment(linker, "/EXPORT:VerInstallFileW=version_o.VerInstallFileW")
#pragma comment(linker, "/EXPORT:VerLanguageNameA=version_o.VerLanguageNameA")
#pragma comment(linker, "/EXPORT:VerLanguageNameW=version_o.VerLanguageNameW")
#pragma comment(linker, "/EXPORT:VerQueryValueA=version_o.VerQueryValueA")
#pragma comment(linker, "/EXPORT:VerQueryValueW=version_o.VerQueryValueW")
#pragma endregion

bool FileExists(LPCTSTR filename) {
	HANDLE hFile = CreateFile(
		filename,                // File name
		GENERIC_READ,            // Desired access: read
		FILE_SHARE_READ,         // Share mode: allow others to read
		NULL,                    // Security attributes
		OPEN_EXISTING,           // Creation disposition: open only if it exists
		FILE_ATTRIBUTE_NORMAL,   // Flags and attributes
		NULL);                   // Template file handle (not used)

	if (hFile == INVALID_HANDLE_VALUE) {
		return false; // File does not exist
	}
	else {
		CloseHandle(hFile);
		return true;  // File exists
	}
}

BOOL APIENTRY DllMain(CONST HMODULE hModule, CONST DWORD fdwReason, CONST LPVOID lpvReserved)
{
	if (fdwReason != DLL_PROCESS_ATTACH)
		return TRUE;

	if (!FileExists(L"fakereg.dll"))
	{
		MessageBoxA(NULL, "fakereg.dll not found", "version", MB_ICONERROR);
		return FALSE;
	}

	if (!LoadLibraryA("fakereg.dll"))
	{
		MessageBoxA(NULL, "fakereg.dll", "version - Failed to load library", MB_ICONERROR);
	}

	return TRUE;
}
