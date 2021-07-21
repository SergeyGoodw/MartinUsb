// dllmain.cpp: определяет точку входа для приложения DLL.
#include "stdafx.h"



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
			hMartinUsb=LoadLibraryA(MARTIN_USB_NAME);//Rename original MartinUsb.dll to Vcore.dat
			if (hMartinUsb!=NULL)
			{
				fnDasHardCommand=(FNDASHARDCOMMAND)GetProcAddress(hMartinUsb,MARTIN_USB_FUNC);
			}
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
			if (hMartinUsb!=NULL)
			{
				FreeLibrary(hMartinUsb);
			}
		break;
	}
	return TRUE;
}

