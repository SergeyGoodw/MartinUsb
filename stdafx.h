// stdafx.h: включаемый файл для стандартных системных включаемых файлов
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
//

#pragma once

#include "targetver.h"
//#include <stdlib.h>


#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows:
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Установите здесь ссылки на дополнительные заголовки, требующиеся для программы
#include "../uDMX_cmds.h"				// подключаем общие команды
#include "../libusb/include/lusb0_usb.h" // подключаем usb либу
#include "_DasHard.h"						// подключаем константы DasHard

extern "C" __declspec(dllexport) int DasHardCommand(int command,int param, unsigned char *bloc); // Экспортируемая функция


typedef int (__cdecl *FNDASHARDCOMMAND)(int,int,unsigned char * ); // Импортируемая функция MartinUSB
static FNDASHARDCOMMAND						fnDasHardCommand;
static HINSTANCE							hMartinUsb;

#define MARTIN_USB_NAME						"Vcore.dat"		/* Новое имя переименованой библиотеки MartinUSB.dll  */
#define MARTIN_USB_FUNC						"DasHardCommand"/* Имя функции библиотеки MartinUSB.dll  */
#define MARTIN_USB_VERSION					11				/* Версия USB-DMX для мартина */

#define USBDEV_SHARED_VENDOR				0x16C0			/* Идентификатор производителя - VOTI */
#define USBDEV_SHARED_PRODUCT				0x05DC			/* Идентификатор продукта, общие PID для всех Obdev устройств */
#define USBDEV_SHARED_MANUFACTURER_STRING	"www.anyma.ch"	/* Производитель "www.anyma.ch" */
#define USBDEV_SHARED_PRODUCT_STRING		"uDMX"			/* Строка продукта "uDMX" */
#define USB_DEBUG							FALSE			/* Отладка или нет */





static usb_dev_handle						*DMXHandle		=	NULL;			/* Дискриптор usb устройства */	
static int									DMXnBytes;					/* Количество принятых от usb байтов */
static const int							FromChannel		=	1;			/* Номер первого канала в посылке */
static const int							ChannelCount	=	512;			/* Общее количество каналов в посылке */
static char									DMXBuffer[ChannelCount];	/* Буфер каналов */

