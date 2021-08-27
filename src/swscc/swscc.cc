#include <Windows.h>
#include "swscomp.h"

SWSCompetitionChanger* cc;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID /*lpReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
    //MessageBoxA(nullptr, "Loaded CC", "SWSCC", MB_OK | MB_ICONEXCLAMATION);
    cc = new SWSCompetitionChanger("plugins//swscc.xml");
	}
  if (reason == DLL_PROCESS_DETACH)
  {
    delete cc;
  }
	return TRUE;
}