
///////////////////////////////////////
// DRVMCU_V VERSION: V01
////////////////////////////////////////

#ifndef ENABLE_UART1
#define ENABLE_UART1       0
#endif
#define _SMOD       1
#define S0REL       (1024-((_SMOD*CRYSTAL_CLOCK+CRYSTAL_CLOCK)/SERIAL_BAUD_RATE)/64)
#define S1REL       (1024-(                      CRYSTAL_CLOCK/SERIAL_BAUD_RATE)/32)

#define    CLOCK_216MHZ    216000000ul
#define    CLOCK_MPLL_MHZ  172000000ul
#define    CLOCK_144MHZ    144000000ul
#define    CLOCK_108MHZ    108000000ul
#define    CLOCK_86MHZ      86000000ul
#define    CLOCK_54MHZ      54000000ul
#define    CLOCK_43MHZ      43000000ul
#define    CLOCK_36MHZ      36000000ul
#define    CLOCK_27MHZ      27000000ul
#define    CLOCK_48MHZ      48000000ul//20130427
#define    CLOCK_12MHZ      12000000ul
#define    CLOCK_XTAL    CRYSTAL_CLOCK
#define    CLOCK_4MHZ        4000000ul
#define    CLOCK_0MHZ              0ul

//mapping to g_mcuPLLFreqTable[]
#define    IDX_MCU_CLK_4MHZ      0
#define    IDX_MCU_CLK_12MHZ     1
#define    IDX_MCU_CLK_216MHZ    2
#define    IDX_MCU_CLK_MPLL_DIV  3
#define    IDX_MCU_CLK_108MHZ    4
#define    IDX_MCU_CLK_86MHZ     5
#define    IDX_MCU_CLK_54MHZ     6
#define    IDX_MCU_CLK_48MHZ     7//20130427
#define    IDX_MCU_CLK_XTAL      8//20130427

//not used
#define    IDX_MCU_CLK_144MHZ    9//20130427



#ifndef MCU_SPEED_INDEX
#error "Please define MCU_SPEED_INDEX!!!"
#endif
//Jison, used for decide the cpu clock in compile time
//#if MCU_SPEED_INDEX==IDX_MCU_CLK_RESERVED0
//#error "Wrong MCU_SPEED_INDEX define!!!"
//#endif

#if CHIP_ID==CHIP_TSUMD//20130427
#if MCU_SPEED_INDEX==IDX_MCU_CLK_144MHZ
#error "Wrong MCU_SPEED_INDEX define!!!"
#endif
#endif


// SPI Clock Selection item define
#define    IDX_SPI_CLK_4MHZ     0
#define    IDX_SPI_CLK_27MHZ    1
#define    IDX_SPI_CLK_36MHZ    2
#define    IDX_SPI_CLK_43MHZ    3
#define    IDX_SPI_CLK_54MHZ    4
#define    IDX_SPI_CLK_86MHZ    5
#define    IDX_SPI_CLK_SSC      6
#define    IDX_SPI_CLK_12MHZ    7
#define    IDX_SPI_CLK_XTAL     8


typedef enum
{
	SPI_MODE_NORMAL,
	SPI_MODE_FR,
	SPI_MODE_SADD,
	SPI_MODE_DADD,
	SPI_MODE_SAQD,
	SPI_MODE_QAQD
} SPI_ModeType;

typedef enum
{
	SPEED_4MHZ_MODE,
	#if (CHIP_ID == CHIP_TSUMC)||(CHIP_ID == CHIP_TSUMD)
	SPEED_12MHZ_MODE,
	#endif
	SPEED_XTAL_MODE,
	SPEED_NORMAL_MODE
} SystemSpeedMode;

extern void Init_WDT( BYTE bEnable );
#if ENABLE_DEBUG
extern void mcuSetUartMux( BYTE ucMuxUart0, BYTE ucMuxUart1 );
#endif
extern void mcuSetSpiSpeed( BYTE ucIndex );
extern void mcuSetSpiMode( BYTE ucMode );
extern void mcuSetMcuSpeed( BYTE ucSpeedIdx );
extern void mcuSetSystemSpeed(BYTE u8Mode);


#if (0)
#define MCU_ON_DRAM_START_ADDR          (0UL)
#define HK_CODE_ON_SPI_START_ADDR       (0UL)
#define HK_CODE_SIZE                    (1024UL*64*7)//20130427


#define R2_CODE_2DTO3D_SIZE             (0UL)


#define R2_CODE_USB_SIZE                (0UL)


#define R2_CODE_2DTO3D_ON_SPI_START_ADDR    (HK_CODE_ON_SPI_START_ADDR+HK_CODE_SIZE) // 5th bank
#define R2_CODE_USB_ON_SPI_START_ADDR       (R2_CODE_2DTO3D_ON_SPI_START_ADDR+R2_CODE_2DTO3D_SIZE) // 6th bank


#define MCU_ON_DRAM_END_ADDR            (0UL)

#define MCU_ON_SPI_START_ADDR           (MCU_ON_DRAM_END_ADDR)
#define MCU_ON_SPI_END_ADDR             (MCU_ON_SPI_START_ADDR+(1024ul*64)*16)

#define DMA_TO_DRAM_DESTIN_ADDR         MCU_ON_DRAM_START_ADDR
#define DMA_TO_DRAM_BYTE_COUNT          (MCU_ON_DRAM_END_ADDR-MCU_ON_DRAM_START_ADDR+1)
#endif

typedef enum
{
	_SPI,
	_DRAM,
} _CodeType;
extern void mcuDMADownloadCode(DWORD dwSourceAddr, DWORD dwDestinAddr, DWORD dwByteCount);
#if (ENABLE_HK_CODE_ON_DRAM)//20130427
extern void mcuArrangeCodeAddr(BYTE ucType, DWORD dwAddrStart, DWORD dwAddrEnd);
#endif
#define WIN0_ADDR_START         (0x5400>>10)  // map to xdata 0x5400~0xEFFF
#define WIN0_ADDR_END           (0xF000>>10)
#define WIN1_ADDR_START         WIN0_ADDR_END // map to xdata 0xF000~0xFFFF
#define WIN1_ADDR_END           (0x10000>>10)
extern void mcuInitXdataMapToDRAM(void);
extern void mcuXdataMapToDRAM(DWORD dwADDR);
extern void mcu40kXdataMapToDRAM(WORD w64k);
extern void mcu4kXdataMapToDRAM(DWORD dw4k);
