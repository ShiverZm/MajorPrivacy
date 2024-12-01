#pragma once
#include "../Types.h"
#include "../lib_global.h"

LIBRARY_EXPORT unsigned __int64 GetCurTime();

LIBRARY_EXPORT unsigned __int64 GetCurTick();

LIBRARY_EXPORT unsigned __int64 GetCurTimeStamp();

LIBRARY_EXPORT std::wstring MkGuid();