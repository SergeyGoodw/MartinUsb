
#ifndef DASHARD_H
#define DASHARD_H

#define DHC_SIUDI0				0		// COMMAND
#define DHC_SIUDI1				100		// COMMAND
#define DHC_SIUDI2				200		// COMMAND
#define DHC_SIUDI3				300		// COMMAND
#define DHC_SIUDI4				400		// COMMAND
#define DHC_SIUDI5				500		// COMMAND
#define DHC_SIUDI6				600		// COMMAND
#define DHC_SIUDI7				700		// COMMAND
#define DHC_SIUDI8				800		// COMMAND
#define DHC_SIUDI9				900		// COMMAND

#define DHC_OPEN				0		// COMMAND
#define DHC_CLOSE				2		// COMMAND
#define DHC_DMXOUTOFF			3		// COMMAND
#define DHC_DMXOUT				4		// COMMAND
#define DHC_PORTREAD			5		// COMMAND
#define DHC_PORTCONFIG			6		// COMMAND
#define DHC_VERSION				7		// COMMAND
#define DHC_DMXIN				8		// COMMAND

#define DHC_RESET				11		// COMMAND
#define DHC_DEBUG_OPEN			12		// COMMAND
#define DHC_DEBUG_CLOSE			13		// COMMAND

#define DHC_WRITEMEMORY			21		// COMMAND
#define DHC_READMEMORY			22		// COMMAND
#define DHC_SIZEMEMORY			23		// COMMAND

#define DHC_3DWRITE				25		// COMMAND
#define DHC_3DREAD				26		// COMMAND
#define DHC_MMWRITE				27		// COMMAND
#define DHC_MMREAD				28		// COMMAND

#define DHC_TRANSPORT			30		// COMMAND
#define DHP_TRANSPORT_MODEALW	1		// PARAM
#define DHP_TRANSPORT_MODEALW32	2		// PARAM
#define DHP_TRANSPORT_MODEOPT	3		// PARAM		DEFAULT 
#define DHP_TRANSPORT_MODEOPT32	4		// PARAM

#define DHC_SERIALNREAD			47		// COMMAND
#define DHC_SERIALNWRITE		48		// COMMAND

#define DHE_OK					1		// RETURN NO ERROR
#define DHE_NOTHINGTODO			2		// RETURN NO ERROR

#define DHE_ERROR_COMMAND		-1		// RETURN ERROR
#define DHE_ERROR_NOTOPEN		-2		// RETURN ERROR

#define DHE_DMXOUT_PACKWRITE	-1000	// RETURN ERROR   -1005 = ERROR_ACCESS_DENIED  -1023 = ERROR_CRC
#define ERROR_ACCESS_DENIED		-5		// RETURN ERROR   -1005 = ERROR_ACCESS_DENIED  -1023 = ERROR_CRC
#define ERROR_CRC				-23		// RETURN ERROR   -1005 = ERROR_ACCESS_DENIED  -1023 = ERROR_CRC

#define DHE_DMXOUT_PACKREAD		-1100	// RETURN ERROR

#endif