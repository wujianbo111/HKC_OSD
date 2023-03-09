#include "board.h"
#include "types.h"
#include "debugDef.h"
#include "global.h"
#include "ms_reg.h"
#include "ms_rwreg.h"
#include "misc.h"


// 121026 coding modified to prevent debug message abnormally when mcu clock change
void putSIOChar(unsigned char sendData)
{
	#if 1
	if( ES == 0 )
		return;
	SBUF = sendData;
	while( 1 )
	{
		if( EA && ES )
		{
			if( TI0_FLAG )
			{
				TI0_FLAG = 0;
				break;
			}
		}
		else
		{
			if( TI )
			{
				TI = 0;
				break;
			}
		}
	}
	#else
	if(!ES)
		return;
	//while(!TI0_FLAG);
	//TI0_FLAG = 0;
	//SBUF = sendData;
	SBUF = sendData;
	while(1)
	{
		if(TI0_FLAG)
		{
			TI0_FLAG = 0;
			break;
		}
	}
	#endif
}



#if DEBUG_MSG
void printMsg(char *str)
{
	char sendData;
	sendData = Send_Msg;
	while (sendData)
		//!='\0')
	{
		putSIOChar((unsigned char)sendData);
		sendData = *(str++);
	}
	putSIOChar(0xd);
	putSIOChar((char)'\n');
}

#endif

#if DEBUG_PRINTDATA
void printData(char *str, WORD value)
{
	char sendData = Send_MsgValue;
	#if 0
	putSIOChar(Send_MsgValue);
	putSIOChar(value >> 8);
	putSIOChar(value & 0xFF);
	#endif
	while (sendData = *(str++))
	{
		if (sendData == (char)'%')
			// %
		{
			sendData = *(str++);
			if (sendData == (char)'d' || sendData == (char)'x')
				// d
			{
				if (value)
				{
					Bool noneZero = FALSE;
					WORD divider = 10000;
					char dispValue;
					if (sendData == (char)'x')
					{
						divider = 0x1000;
					}
					while (divider)
					{
						dispValue = value / divider;
						value -= dispValue * divider;
						if (dispValue)
						{
							noneZero = TRUE;
						}
						if (noneZero)
						{
							if (dispValue > 9)
							{
								dispValue += 55;
							}
							else
							{
								dispValue += 0x30;
							}
							putSIOChar(dispValue);
						}
						if (sendData == (char)'d')
						{
							divider /= 10;
						}
						else
						{
							divider /= 0x10;
						}
					}
				}
				else
				{
					putSIOChar('0');
				}
			}
		}
		else
		{
			putSIOChar(sendData);
		}
	}
	putSIOChar(0xd);
	putSIOChar((char)'\n');
}

#endif


