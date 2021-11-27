#include "swoshook.h"

  uintptr_t SWOSHook::m_BaseAddress = 0;
  uintptr_t SWOSHook::m_CompetitionTablePtr = 0;

  void SWOSHook::Init()
  {
    GetBaseAddress();
  }

  uintptr_t SWOSHook::GetBaseAddress()
  {
    if (m_BaseAddress == 0)
      m_BaseAddress = (uintptr_t)GetModuleHandle(NULL);
    return m_BaseAddress;
  }

  uintptr_t SWOSHook::GetCompetitionTablePtr()
  {
    if (m_CompetitionTablePtr == 0)
    {
      const uint8_t data[] = {0xAA, 0xAA, 0x02, 0x00, 0xee, 0xee, 0x02, 0x00};
      uintptr_t cta = 0;
      cta = FindInMemory((void*)(&data), 8);
      //char finded[128];
      //sprintf(finded, "SWSHOOK finded data address: 0x%08x", cta+8);
      //MessageBoxA(NULL, finded, "SWSHOOK", MB_OK);
      m_CompetitionTablePtr = cta+8;
    }
    return m_CompetitionTablePtr;
  }

  uintptr_t SWOSHook::FindInMemory(void* data, size_t sizeofdata)
  {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    MEMORY_BASIC_INFORMATION info;
    uintptr_t p = (uintptr_t)si.lpMinimumApplicationAddress;
    uint8_t *buffer;
    SIZE_T bytesRead;
    while (p < (uintptr_t)si.lpMaximumApplicationAddress)
    {
      if (VirtualQueryEx(GetCurrentProcess(),(LPVOID)p, &info, sizeof(info)) == sizeof(info))
      {
        if (info.State == MEM_COMMIT && info.Protect != PAGE_NOACCESS)
        {
          buffer = new uint8_t[info.RegionSize];
          DWORD oldprotect;
          if (VirtualProtectEx(GetCurrentProcess(), info.BaseAddress, info.RegionSize, PAGE_EXECUTE_READWRITE, &oldprotect))
          {
            ReadProcessMemory(GetCurrentProcess(), info.BaseAddress, buffer, info.RegionSize, &bytesRead);
            VirtualProtectEx(GetCurrentProcess(), info.BaseAddress, info.RegionSize, oldprotect, &oldprotect);
            uint8_t* end = &buffer[bytesRead];
            for (uint8_t* start = buffer; start < end; start++)
              if (memcmp(start, data, sizeofdata) == 0)
              {
                uintptr_t res = ((uintptr_t)start - (uintptr_t)buffer) + (uintptr_t)info.BaseAddress;
                delete[] buffer;
                if (res != (uintptr_t)data)
                  return res;
              }
          }
        }
      }
      p+= (uintptr_t)info.RegionSize;
    }
    return 0;
  }

  bool SWOSHook::WriteMemory(uintptr_t address, void* value, size_t size)
  {
    DWORD dwOrginalProtect;
		DWORD dwNewProtect = PAGE_EXECUTE_READWRITE;
    MEMORY_BASIC_INFORMATION info;
    if (VirtualQuery((LPVOID)address, &info, sizeof(info))!= 0)
    {
      VirtualProtect((LPVOID)address, size, dwNewProtect, &dwOrginalProtect);
      memcpy((void*)address, value, size);
      VirtualProtect((LPVOID)address, size, dwOrginalProtect, &dwNewProtect);
      return true;
    }
    else
    {
      return false;
    }
  }

  bool SWOSHook::ReadMemory(uintptr_t address, void* value, size_t size)
  {
    MEMORY_BASIC_INFORMATION info;
    if (VirtualQuery((LPVOID)address, &info, sizeof(info))!= 0)
    {
      memcpy(value, (void*)address, size);
      return true;
    }
    else
    {
      return false;
    }
  }

  bool SWOSHook::SetMemory(uintptr_t address, uint8_t value, size_t size)
  {
    DWORD dwOrginalProtect;
		DWORD dwNewProtect = PAGE_EXECUTE_READWRITE;
    MEMORY_BASIC_INFORMATION info;
    if (VirtualQuery((LPVOID)address, &info, sizeof(info))!= 0)
    {
		  VirtualProtect((LPVOID)address, size, dwNewProtect, &dwOrginalProtect);
		  memset((void*)address, value, size);
		  VirtualProtect((LPVOID)address, size, dwOrginalProtect, &dwNewProtect);  
      return true;
    }
    else
    {
      return false;
    }
  }

  bool SWOSHook::MakeCall(uintptr_t relative, void* func)
	{
		uint32_t funct = ((reinterpret_cast<uint32_t>(func)) - (relative + 5));
    bool ret = false;
		ret = SetMemory(relative, 0xe8, 1);
		ret = WriteMemory(relative + 1, &funct, 4);
    return ret;
	}
