#include "pch.h"
#include "MiscHelpers.h"
#include <Rpc.h>

unsigned __int64 GetCurTime()
{
	__int64 iTime = 0;
	_time64(&iTime);
	return (unsigned)iTime;
}

unsigned __int64 GetCurTick()
{
	return ::GetTickCount64();
}

unsigned __int64 GetCurTimeStamp()
{
	FILETIME ftNow;
	LARGE_INTEGER liNow;
	__int64 now;

	GetSystemTimeAsFileTime(&ftNow);
	liNow.LowPart = ftNow.dwLowDateTime;
	liNow.HighPart = ftNow.dwHighDateTime;
	now = liNow.QuadPart;

	return (unsigned __int64)now;
}

std::wstring MkGuid()
{
	std::wstring Guid;
	GUID myGuid;
	RPC_STATUS status = UuidCreate(&myGuid);
	if (status == RPC_S_OK || status == RPC_S_UUID_LOCAL_ONLY) {
		RPC_WSTR guidString = NULL;
		status = UuidToStringW(&myGuid, &guidString);
		if (status == RPC_S_OK) {
			Guid = std::wstring((wchar_t*)guidString, wcslen((wchar_t*)guidString));
			RpcStringFreeW(&guidString);
		}
	}
	return Guid;
}