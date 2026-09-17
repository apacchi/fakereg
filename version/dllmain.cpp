// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

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
