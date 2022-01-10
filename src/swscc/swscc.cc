#include <Windows.h>
#include "swoshook.h"
#include "swscomp.h"

SWSCompetitionChanger* cc;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID /*lpReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
    //MessageBoxA(nullptr, "Loaded CC", "SWSCC", MB_OK | MB_ICONEXCLAMATION);
    printf("[SWSCC.ASI]:: Init Hook...\n");
    SWOSHook::Init();
    printf("[SWSCC.ASI]:: Creating Changer...\n");
    cc = new SWSCompetitionChanger("plugins/swscc.xml");
	}
  if (reason == DLL_PROCESS_DETACH)
  {
    delete cc;
  }
	return TRUE;
}