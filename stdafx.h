// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include "targetver.h"
//#include <stdlib.h>


#define WIN32_LEAN_AND_MEAN             // ��������� ����� ������������ ���������� �� ���������� Windows
// ����� ���������� Windows:
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������
#include "../uDMX_cmds.h"				// ���������� ����� �������
#include "../libusb/include/lusb0_usb.h" // ���������� usb ����
#include "_DasHard.h"						// ���������� ��������� DasHard

extern "C" __declspec(dllexport) int DasHardCommand(int command,int param, unsigned char *bloc); // �������������� �������


typedef int (__cdecl *FNDASHARDCOMMAND)(int,int,unsigned char * ); // ������������� ������� MartinUSB
static FNDASHARDCOMMAND						fnDasHardCommand;
static HINSTANCE							hMartinUsb;

#define MARTIN_USB_NAME						"Vcore.dat"		/* ����� ��� �������������� ���������� MartinUSB.dll  */
#define MARTIN_USB_FUNC						"DasHardCommand"/* ��� ������� ���������� MartinUSB.dll  */
#define MARTIN_USB_VERSION					11				/* ������ USB-DMX ��� ������� */

#define USBDEV_SHARED_VENDOR				0x16C0			/* ������������� ������������� - VOTI */
#define USBDEV_SHARED_PRODUCT				0x05DC			/* ������������� ��������, ����� PID ��� ���� Obdev ��������� */
#define USBDEV_SHARED_MANUFACTURER_STRING	"www.anyma.ch"	/* ������������� "www.anyma.ch" */
#define USBDEV_SHARED_PRODUCT_STRING		"uDMX"			/* ������ �������� "uDMX" */
#define USB_DEBUG							FALSE			/* ������� ��� ��� */





static usb_dev_handle						*DMXHandle		=	NULL;			/* ���������� usb ���������� */	
static int									DMXnBytes;					/* ���������� �������� �� usb ������ */
static const int							FromChannel		=	1;			/* ����� ������� ������ � ������� */
static const int							ChannelCount	=	512;			/* ����� ���������� ������� � ������� */
static char									DMXBuffer[ChannelCount];	/* ����� ������� */

