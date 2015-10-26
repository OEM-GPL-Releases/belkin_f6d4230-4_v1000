/**************************************************************************
 *
 *  BRIEF MODULE DESCRIPTION
 *     serial port definition for Ralink RT2880 solution
 *
 *  Copyright 2007 Ralink Inc. (steven_liu@ralinktech.com.tw)
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License along
 *  with this program; if not, write  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *
 **************************************************************************
 */

#ifndef __RALINK_MMAP__
#define __RALINK_MMAP__

#if defined (CONFIG_RALINK_RT2880_SHUTTLE)

#define RALINK_SYSCTL_BASE 		0xA0300000
#define RALINK_TIMER_BASE		0xA0300100
#define RALINK_INTCL_BASE		0xA0300200
#define RALINK_MEMCTRL_BASE		0xA0300300
#define RALINK_UART_BASE		0xA0300500
#define RALINK_PIO_BASE			0xA0300600
#define RALINK_I2C_BASE			0xA0300900
#define RALINK_SPI_BASE			0xA0300B00
#define RALINK_UART_LITE_BASE		0xA0300C00
#define RALINK_FRAME_ENGINE_BASE	0xA0310000
#define RALINK_EMBEDD_ROM_BASE		0xA0400000
#define RALINK_PCI_BASE			0xA0500000
#define RALINK_11N_MAC_BASE		0xA0600000

//Interrupt Controller
#define RALINK_INTCTL_TIMER0		(1<<0)
#define RALINK_INTCTL_WDTIMER		(1<<1)
#define RALINK_INTCTL_UART		(1<<2)
#define RALINK_INTCTL_PIO		(1<<3)
#define RALINK_INTCTL_PCM		(1<<4)
#define RALINK_INTCTL_UARTLITE		(1<<8)
#define RALINK_INTCTL_ILL_ACCESS	(1<<23)

//Reset Control Register
#define RALINK_TIMER_RST		(1<<1)
#define RALINK_INTC_RST			(1<<2)
#define RALINK_MC_RST			(1<<3)
#define RALINK_CPU_RST			(1<<4)
#define RALINK_UART_RST			(1<<5)
#define RALINK_PIO_RST			(1<<6)
#define RALINK_I2C_RST			(1<<9)
#define RALINK_SPI_RST			(1<<11)
#define RALINK_UART2_RST		(1<<12)
#define RALINK_PCI_RST			(1<<16)
#define RALINK_2860_RST			(1<<17)
#define RALINK_FE_RST			(1<<18)
#define RALINK_PCM_RST			(1<<19)


#elif defined (CONFIG_RALINK_RT2880_MP)

#define RALINK_SYSCTL_BASE 		0xA0300000
#define RALINK_TIMER_BASE		0xA0300100
#define RALINK_INTCL_BASE		0xA0300200
#define RALINK_MEMCTRL_BASE		0xA0300300
#define RALINK_UART_BASE		0xA0300500
#define RALINK_PIO_BASE			0xA0300600
#define RALINK_I2C_BASE			0xA0300900
#define RALINK_SPI_BASE			0xA0300B00
#define RALINK_UART_LITE_BASE		0x00300C00
#define RALINK_FRAME_ENGINE_BASE	0xA0400000
#define RALINK_EMBEDD_ROM_BASE		0xA0410000
#define RALINK_PCI_BASE			0xA0440000
#define RALINK_11N_MAC_BASE		0xA0480000

//Interrupt Controller
#define RALINK_INTCTL_TIMER0		(1<<0)
#define RALINK_INTCTL_WDTIMER		(1<<1)
#define RALINK_INTCTL_UART		(1<<2)
#define RALINK_INTCTL_PIO		(1<<3)
#define RALINK_INTCTL_PCM		(1<<4)
#define RALINK_INTCTL_UARTLITE		(1<<8)
#define RALINK_INTCTL_ILL_ACCESS	(1<<23)

//Reset Control Register
#define RALINK_TIMER_RST		(1<<1)
#define RALINK_INTC_RST			(1<<2)
#define RALINK_MC_RST			(1<<3)
#define RALINK_CPU_RST			(1<<4)
#define RALINK_UART_RST			(1<<5)
#define RALINK_PIO_RST			(1<<6)
#define RALINK_I2C_RST			(1<<9)
#define RALINK_SPI_RST			(1<<11)
#define RALINK_UART2_RST		(1<<12)
#define RALINK_PCI_RST			(1<<16)
#define RALINK_2860_RST			(1<<17)
#define RALINK_FE_RST			(1<<18)
#define RALINK_PCM_RST			(1<<19)

#elif defined (CONFIG_RALINK_RT3052) || defined (CONFIG_RALINK_RT2883)

#define RALINK_SYSCTL_BASE		0xB0000000
#define RALINK_TIMER_BASE		0xB0000100
#define RALINK_INTCL_BASE		0xB0000200
#define RALINK_MEMCTRL_BASE		0xB0000300
#define RALINK_PCM_BASE			0xB0000400
#define RALINK_UART_BASE		0x10000500
#define RALINK_PIO_BASE			0xB0000600
#define RALINK_GDMA_BASE		0xB0000700
#define RALINK_NAND_CTRL_BASE		0xB0000800
#define RALINK_I2C_BASE			0xB0000900
#define RALINK_I2S_BASE			0xB0000A00
#define RALINK_SPI_BASE			0xB0000B00
#define RALINK_UART_LITE_BASE		0x10000C00
#define RALINK_FRAME_ENGINE_BASE	0xB0100000
#define RALINK_ETH_SW_BASE		0xB0110000
#define RALINK_11N_MAC_BASE		0xB0180000
#define RALINK_USB_OTG_BASE		0x101C0000

//Interrupt Controller
#define RALINK_INTCTL_SYSCTL		(1<<0)
#define RALINK_INTCTL_TIMER0		(1<<1)
#define RALINK_INTCTL_WDTIMER		(1<<2)
#define RALINK_INTCTL_ILL_ACCESS	(1<<3)
#define RALINK_INTCTL_PCM		(1<<4)
#define RALINK_INTCTL_UART		(1<<5)
#define RALINK_INTCTL_PIO		(1<<6)
#define RALINK_INTCTL_DMA		(1<<7)
#define RALINK_INTCTL_NAND		(1<<8)
#define RALINK_INTCTL_PC		(1<<9)
#define RALINK_INTCTL_I2S		(1<<10)
#define RALINK_INTCTL_UARTLITE		(1<<12)
#define RALINK_INTCTL_ESW		(1<<17)
#define RALINK_INTCTL_OTG		(1<<18)
#define RALINK_INTCTL_OTG_IRQN		18
#define RALINK_INTCTL_GLOBAL		(1<<31)

//Reset Control Register
#define RALINK_SYS_RST			(1<<0)
#define RALINK_CPU_RST			(1<<1)
#define RALINK_TIMER_RST		(1<<8)
#define RALINK_INTC_RST			(1<<9)
#define RALINK_MC_RST			(1<<10)
#define RALINK_PCM_RST			(1<<11)
#define RALINK_UART_RST			(1<<12)
#define RALINK_PIO_RST			(1<<13)
#define RALINK_DMA_RST			(1<<14)
#define RALINK_I2C_RST			(1<<16)
#define RALINK_I2S_RST			(1<<17)
#define RALINK_SPI_RST			(1<<18)
#define RALINK_UARTL_RST		(1<<19)
#define RALINK_RT2872_RST		(1<<20)
#define RALINK_FE_RST			(1<<21)
#define RALINK_OTG_RST			(1<<22)
#define RALINK_SW_RST			(1<<23)
#define RALINK_EPHY_RST			(1<<24)

#endif
#endif
