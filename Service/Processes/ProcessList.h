#pragma once
#include "../Library/Status.h"
#include "Process.h"
#include "Programs/ProgramID.h"
#include "ExecLogEntry.h"

#define NT_OS_KERNEL_PID	4

class CProcessList
{
	TRACK_OBJECT(CProcessList)
public:
	CProcessList();
	~CProcessList();

	STATUS Init();

	void Update();

	void Reconfigure();

	STATUS EnumProcesses();

	std::map<uint64, CProcessPtr> List() { 
		std::unique_lock Lock(m_Mutex);
		return m_List; 
	}
	CProcessPtr GetProcess(uint64 Pid, bool bCanAdd = false);

	std::map<uint64, CProcessPtr> FindProcesses(const CProgramID& ID);

	class CServiceList* Services() { return m_Services; }

protected:

	void AddProcessUnsafe(const CProcessPtr& pProcess);
	void RemoveProcessUnsafe(const CProcessPtr& pProcess);

	std::wstring GetPathFromCmd(const std::wstring& CommandLine, const std::wstring& FileName, uint64 ParentID);

	NTSTATUS OnProcessDrvEvent(const struct SProcessEvent* pEvent);
	void OnProcessEtwEvent(const struct SEtwProcessEvent* pEvent);

	//void TerminateProcess(uint64 Pid, const std::wstring& FileName);

	bool OnProcessStarted(uint64 Pid, uint64 ParentPid, uint64 ActorPid, const std::wstring& ActorServiceTag, const std::wstring& FileName, const std::wstring& Command, uint64 CreateTime, EEventStatus Status, bool bETW = false);
	void OnProcessStopped(uint64 Pid, uint32 ExitCode);

	void OnProcessAccessed(uint64 Pid, uint64 ActorPid, const std::wstring& ActorServiceTag, bool bThread, uint32 AccessMask, uint64 AccessTime, EEventStatus Status);
	void OnImageEvent(const struct SProcessImageEvent* pImageEvent);
	
	void OnResourceAccessed(const std::wstring& Path, uint64 ActorPid, const std::wstring& ActorServiceTag, uint32 AccessMask, uint64 AccessTime, EEventStatus Status, NTSTATUS NtStatus, bool IsDirectory);

	void AddExecLogEntry(const std::shared_ptr<CProgramFile>& pProgram, const CExecLogEntryPtr& pLogEntry);

	mutable std::recursive_mutex m_Mutex;

	bool m_bLogNotFound = false;
	bool m_bLogInvalid = false;

	class CServiceList* m_Services;

	std::map<uint64, CProcessPtr> m_List;
	std::multimap<std::wstring, CProcessPtr> m_Apps;
	std::multimap<std::wstring, CProcessPtr> m_ByPath;
};