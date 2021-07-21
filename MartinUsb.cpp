// MartinUSB.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"

#include "USBDMXFunc.cpp"// подключаем USB-DMX функции

int DasHardCommand(int command,int param, unsigned char *bloc)
{
	//******************************************************************************************
	//***** Begin Original MartinUsb intrface **************************************************
	//******************************************************************************************
	if (command<DHC_SIUDI9)// Begin Original MartinUsb intrface	
	{

		if (fnDasHardCommand!=NULL)
		{
			return ((*fnDasHardCommand)(command,param,bloc));
		}
		return DHE_ERROR_COMMAND;
	}
	//******************************************************************************************
	//******************************************************************************************

	switch (command)
	{
		//******************************************************************************************
		//***** Begin Vcore MartinUsb intrface *****************************************************
		//******************************************************************************************


		//******************************************************************************************
		//******************************************************************************************
		case DHC_SIUDI9 + DHC_OPEN:// OPEN LightJockey USB/DMX interface II DMX Out
			if(param==254)// еще 255
			{
				if (DMXHandle)
				{
					DMX_Close();
				}
				DMX_Open();
				if (DMXHandle)
				{
					return param;// Ok
				}
			}
			return DHE_ERROR_NOTOPEN;//not open

		break;
		//******************************************************************************************
		//******************************************************************************************
		case DHC_SIUDI9 + DHC_CLOSE:// Close LightJockey USB/DMX interface II DMX Out
			if (DMXHandle)
			{
				DMX_Close();
				return DHE_OK;// Ok
			}
			return DHE_ERROR_NOTOPEN;//not open
		break;

		//******************************************************************************************
		//******************************************************************************************
		case DHC_SIUDI9 + DHC_DMXOUTOFF:// DMX_OUTOFF Function LightJockey USB/DMX interface II DMX Out
			if (DMXHandle)
			{
				memset(DMXBuffer,0,512);
				DMXnBytes = DMX_Send(ChannelCount, FromChannel, DMXBuffer);
				if(DMXnBytes < 0)
				{
					DMXnBytes = NULL;
					return DHE_DMXOUT_PACKWRITE;//DHE_DMXOUT_PACKWRITE error
				}
				return DHE_OK;// Ok
			}
			return DHE_ERROR_NOTOPEN;//not open
		break;
		//******************************************************************************************
		//******************************************************************************************
		case DHC_SIUDI9 + DHC_DMXOUT:// DMX_OUT Function LightJockey USB/DMX interface II DMX Out
			if (DMXHandle)
			{
				//******************************************************************************************
				//******************************************************************************************
				memset((char *)(((unsigned char *)bloc)-4),0x0,4);//clear counter in LightJockey
				DMXnBytes = DMX_Send(ChannelCount, FromChannel, (char*)bloc);
				if(DMXnBytes < 0)
				{
					DMXnBytes = NULL;
					return DHE_DMXOUT_PACKWRITE;//DHE_DMXOUT_PACKWRITE error
				}
				return DHE_OK;// Ok
				//******************************************************************************************
				//******************************************************************************************
			}
			return DHE_ERROR_NOTOPEN;//not open
		break;
		//******************************************************************************************
		//******************************************************************************************
		case DHC_SIUDI9 + DHC_VERSION://version LightJockey USB/DMX interface II DMX Out
			if (DMXHandle)
			{
				return MARTIN_USB_VERSION;
			}
			return DHE_ERROR_NOTOPEN;//not open
		break;
		//******************************************************************************************
		//******************************************************************************************
		case DHC_SIUDI9 + DHC_TRANSPORT://TRANSPORT of LightJockey USB/DMX interface II DMX Out
			if (DMXHandle)// параметр 1 и 3
			{
				return DHP_TRANSPORT_MODEALW;// какаято хрень
			}
			return DHE_ERROR_NOTOPEN;//not open
		break;
		//******************************************************************************************

		//***** end   Vcore MartinUsb intrface *****************************************************
		//******************************************************************************************
	}// End   Vcore MartinUsb intrface
		return DHE_OK;
}
//******************************************************************************************
//******************************************************************************************
