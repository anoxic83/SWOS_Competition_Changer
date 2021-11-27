#pragma once
/*

MIT License

Copyright (c) 2021 Anoxic

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#include <windows.h>
#include <cstdint>
#include <string>
#include <sstream>
#include <functional>

class SWOSHook
{
private:
  static uintptr_t m_BaseAddress;
  static uintptr_t m_CompetitionTablePtr;
public:
  static void Init();
  static uintptr_t GetBaseAddress();
  static uintptr_t GetCompetitionTablePtr();
  static uintptr_t FindInMemory(void* data, size_t sizeofdata);
  static bool WriteMemory(uintptr_t address, void* value, size_t size);
  static bool ReadMemory(uintptr_t address, void* value, size_t size);
  static bool SetMemory(uintptr_t address, uint8_t value, size_t size);
  static bool MakeCall(uintptr_t relative, void* func);
};