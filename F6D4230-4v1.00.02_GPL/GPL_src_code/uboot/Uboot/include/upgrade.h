#ifndef _UPGRADE_H_
#define _UPGRADE_H_

#include <config.h>

#define BULKIN_ASSIGN_RULE

/* sercomm define for sercomm download */
#define FLASH_ADDR_BASE	(CFG_FLASH_BASE)
#define BOOT_ADDR_BASE	(CFG_FLASH_BASE)

#if 0
#define FLASH_SIZE	(0x400000)
#else
extern unsigned long flash_size;
#define FLASH_SIZE	(flash_size)
#endif

#define BOOT_SIZE	(0x30000)
#define NVRAM_SIZE	(0x10000)
#define RF_SIZE	(0x200)	//RF parameters (calibration data)

#define PID_OFFSET	(BOOT_SIZE - 0x56)
#define NODE_ADDRESS	(BOOT_SIZE - 0x60)
#define SN_ADDRESS	(NODE_ADDRESS - 0x10)
#define DOMAIN_ADDRESS	(SN_ADDRESS - 0x10)
#define COUNTRY_ADDRESS	(DOMAIN_ADDRESS + 1)	
#define WPS_PIN_ADDRESS	(DOMAIN_ADDRESS - 0x10)
#define RF_ADDRESS	(WPS_PIN_ADDRESS - RF_SIZE)

#define PRODUCT_ID_OFFSET	(FLASH_SIZE - 0x10)
#define PROTOCOL_ID_OFFSET	(PRODUCT_ID_OFFSET + 0x02)
#define FW_VERSION_OFFSET	(PRODUCT_ID_OFFSET + 0x04)
#define SIGN_OFFSET	(PRODUCT_ID_OFFSET + 0x08)   /* eRcOmM */

#define UPGRADE_START_OFFSET	(BOOT_SIZE + NVRAM_SIZE)
#define UPGRADE_END_OFFSET	(FLASH_SIZE)

/* protect area */
#define SC_PROTECT_START	(CFG_ENV_ADDR)	//for tftp upgrade uboot, include env
#define SC_PROTECT_END	(CFG_FLASH_BASE + BOOT_SIZE)
#define SC_DL_PROTECT_START	(CFG_FLASH_BASE + RF_ADDRESS)	//for sercomm download, do not include env
#define SC_DL_PROTECT_END	(CFG_FLASH_BASE + PID_OFFSET)	// do not include pid

/* for debug */
#define ASSIGN_TEST 0

/* gpio define */
#define HIGH	1
#define LOW	0

#define LED_ACTIVE	LOW
#define BUTTON_ACTIVE	LOW

#define WPS_BUTTON              5
#define RESET_BUTTON            7
#define INTERNET_LED            1       /* blue  */
#define INTERNET_PROBLEM_LED    2       /* amber */
#define POWER_LED               10      /* blue  */
#define MODEM_LED               8       /* blue  */
#define MODEM_PROBLEM_LED       12      /* amber */
#define WIRED_LED               14      /* blue  */
#define WIRED_PROBLEM_LED       11      /* amber */
#define WIRELESS_LED            6       /* blue  */
#define WIRELESS_PROBLEM_LED    3       /* amber */
#define WPS_PROBLEM_LED         9       /* amber */
#define SECURITY_LED            13      /* blue  */

/* move from .c file, some macros needed by some other files */
typedef struct {
	unsigned char      DestAddress[6];
	unsigned char      SrcAddress[6];
	unsigned short     sap;
	unsigned short     wcmd;
	unsigned short     wsequence;
	unsigned short     woffset;
	unsigned short     wsegment;
	unsigned short     wLen;
	unsigned char      bData[600];
} __attribute__((packed)) DLC;
/* sap */
#define UPGRADE_HW_ETHER 0x8888
#define ASSIGN_HW_ETHER 0x15
/* wcmd */
#define  GET_VERSION_INFO 0x0000
#define  DOWN_REQUEST     0x0001
#define  DOWN_DATA        0x0002
#define  DOWN_RESET       0x0003
#define  DOWN_VERIFY      0x0004   
#define  DOWN_EALL        0x0005   

#define DLC_LEN      10

typedef struct  VCI  {
	unsigned char     Prifix[7];
	unsigned short    VerControl;
	unsigned short    DownControl;
	unsigned char     Hid[32];
	unsigned short    Hver;
	unsigned short    ProdID;
	unsigned short    ProdIDmask;
	unsigned short    ProtID;
	unsigned short    ProtIDmask;
	unsigned short    FuncID;
	unsigned short    FuncIDmask;
	unsigned short    Fver;
	unsigned short    Cseg;
	unsigned short    Csize;
	unsigned char     Postfix[7];
}  __attribute__((packed)) VCI_TABLE;

#define  VCI_LEN         56 //sizeof(VCI_TABLE)-14

typedef  struct  DCB_TYPE {
	unsigned short   sequn;
	unsigned short   dest_seg;
	unsigned short   dest_off;
	unsigned short   src_seg;
	unsigned short   src_off;
	unsigned short   count;
	unsigned         erase;
	unsigned         no;
	unsigned short   tme_of_day;
	unsigned long    state;
}   DCB_BUF;
#define  IDLE            0x00
#define  PROG            0x01
#define  PROGERR         0x02
#define  COM_SEQ_ERR     0x05
#define  SEQ_NUM_ERR     0x06
#define  PROG_ERR        0x07
#define  VERIFY_ERR      0x09

typedef struct belkin_aspack {
	unsigned char	mac[6];
	unsigned int	unused;		/* unused 4 bytes */
	unsigned char	password[6];	/* PMTIAZ for wireless. PMTI for non-wireless */
	unsigned short	padd;		/* unused 2 bytes */
	unsigned char	domain;
	unsigned char	country_code;
	unsigned char	padding[6];	/* unused */
	unsigned char	serial[16];
	unsigned int	pad[4];		/* unused 16 bytes */
	unsigned char	wps_pin[8];
} __attribute__((packed)) belkin_assign;

#define ENET_MAX_PKT 1514

#define REG_WRITE(addr,data) (*((volatile unsigned long *)addr)) = data
#define REG_READ(addr)  (*((volatile unsigned long *) addr))


void AssignStart(void);
void DownloadStart(void);
void AssignHandler (uchar * pkt, unsigned dest, unsigned src, unsigned len);
void DownloadHandler (uchar * pkt, unsigned dest, unsigned src, unsigned len);
void do_boot(void);
void AssignHWAddress(unsigned char *psBuffer);
#ifdef BULKIN_ASSIGN_RULE
void Assign_domain(unsigned char *psBuffer);
#endif

unsigned long flash_get_sector_addr(unsigned long addr);
unsigned long flash_get_sector_size(unsigned long addr);

#endif
