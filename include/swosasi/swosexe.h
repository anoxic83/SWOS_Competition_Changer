/*
Copyright <2020> <AnoXic>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once
#include <windows.h>
#include <cstdint>
#include <string>
#include <sstream>
#include <functional>


//FUNCTIONS
// 1.4.3c

const uintptr_t SWOSPTR_FUNC_SWOSMAIN = 0x181E0;

const uintptr_t SWOSPTR_CALL_MENUMAIN = 0x1839E;
const uintptr_t SWOSPTR_FUNC_MENUMAIN = 0x19280;

//DATA AND STRUCTS
const uintptr_t SWOSPTR_DATA_REGISTER = 0x4B90DA7 - 0x400000;//0x75ADA7;
const uintptr_t SWOSPTR_ADDR_REGISTER = 0x4B90DC7 - 0x400000;//0x75ADC7;

const uintptr_t SWOSPTR_SDL_WINDOW = 0x7DCD94 - 0x400000;
const uintptr_t SWOSPTR_SDL_GLCONTEXT = 0x7DCDF0 - 0x400000;
const uintptr_t SWOSPTR_SDL_RENDERER = 0x4B60638 - 0x400000;

namespace SWOS
{
  inline uintptr_t GetBaseAddress()
  {
    static uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);   
    return base;
  }

  inline std::string HexToStr(uint64_t val)
	{
		std::stringstream stream;
		stream << std::hex << val;
		std::string result(stream.str());
		return result;
	}

  void LogSWOS(int logtype, const char* logtext);

  typedef struct
  {
    uint32_t Val[8];
  } Register;

  template <typename Ret, typename... Args>
	Ret aCallSWOS(uint32_t absolute, Args... args) {
		return reinterpret_cast<Ret(__cdecl*)(Args...)>(absolute)(args...);
	}

  template <typename Ret, typename... Args>
	Ret rCallSWOS(uint32_t relative, Args... args) {
    uint32_t addr = GetBaseAddress() + relative;
    return reinterpret_cast<Ret(__cdecl*)(Args...)>(addr)(args...);
	}

/*
  __declspec(naked) inline void CallSWOS_Abs(uintptr_t addr) 
  {
    _asm {
      push ebp
      call [addr]
      pop ebp
    }
  }

  inline void CallSWOS(uintptr_t addr)
  {
    uintptr_t taddr = GetBaseAddress() + addr;
    CallSWOS_Abs(taddr);
  }

*/
  template <typename Typ>
  Typ &rValueSWOS(uint32_t relative)
  {
    return *reinterpret_cast<Typ*>(GetBaseAddress()+relative);
  }
/*
  inline void LogSWOS(int logtype, const char* logtext)
  {
    reinterpret_cast<void(__cdecl*)(int,const char*)>(GetBaseAddress()+SWOSPTR_FUNC_LOG)(logtype, logtext);
  }
*/

  inline Register &DataRegisters()
  {
    return *reinterpret_cast<Register*>(GetBaseAddress()+SWOSPTR_DATA_REGISTER);
  }

  inline Register &AddressRegisters()
  {
    return *reinterpret_cast<Register*>(GetBaseAddress()+SWOSPTR_ADDR_REGISTER);
  }

  inline void ReadMemory(uintptr_t address, void* value, size_t size)
	{
		memcpy(value, (void*)address, size);
	}

  inline void SetMemory(uintptr_t address, uint8_t val, size_t size, bool execute = true)
	{
    DWORD dwOrginalProtect;
		DWORD dwNewProtect = PAGE_EXECUTE_READWRITE;
    if (execute)
    {
		  VirtualProtect((LPVOID)address, size, dwNewProtect, &dwOrginalProtect);
    }
		memset((void*)address, val, size);
    if (execute)
		  VirtualProtect((LPVOID)address, size, dwOrginalProtect, &dwNewProtect);
	}

  inline void WriteMemory(uintptr_t address, void* value, size_t size, bool execute = true)
	{
    DWORD dwOrginalProtect;
		DWORD dwNewProtect = PAGE_EXECUTE_READWRITE;
    if (execute)
    {
		  VirtualProtect((LPVOID)address, size, dwNewProtect, &dwOrginalProtect);
    }
		memcpy((void*)address, value, size);
    if (execute)
		  VirtualProtect((LPVOID)address, size, dwOrginalProtect, &dwNewProtect);
	}

  inline void WriteMemoryDirect(uintptr_t relative, void* value, size_t size)
  {
    WriteMemory(relative, value, size, false);
  }

  inline void MakeCall(uintptr_t relative, void* func)
	{
		uint32_t funct = ((reinterpret_cast<uint32_t>(func)) - (relative + 5));
		SetMemory(relative, 0xe8, 1);
		WriteMemory(relative + 1, &funct, 4);
	}

  inline void SetNOP(uintptr_t relative, size_t length)
	{
		SetMemory(relative, 0x90, length);
	}

	inline void MakeRet(uintptr_t relative)
	{
		SetMemory(relative, 0xc3, 1);
	}

/*

  inline void ShowMenu(uintptr_t menuaddr)
	{
		AddressRegisters().Val[6] = menuaddr;
		rCallSWOS<void>(SWOSPTR_FUNC_SHOWMENU);
	}

*/
}