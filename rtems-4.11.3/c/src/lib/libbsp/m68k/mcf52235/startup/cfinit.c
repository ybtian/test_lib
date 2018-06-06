/*********************************************************************
* Initialisation Code for ColdFire MCF52235 Processor                *
**********************************************************************
 Generated by ColdFire Initialisation Utility 2.10.8
 Fri May 23 14:39:00 2008

 MicroAPL Ltd makes no warranties in respect of the suitability
 of this code for any particular purpose, and accepts
 no liability for any loss arising out of its use. The person or
 persons making use of this file must make the final evaluation
 as to its suitability and correctness for a particular application.

*/

/* Processor/internal bus clocked at 60.00 MHz */

#include <bsp.h>

/* Additional register read/write macros (missing in headers) */
#define MCF_CIM_CCON                   (*(vuint16*)(void*)(&__IPSBAR[0x00110004]))

/* Bit definitions and macros for MCF_CIM_CCON */
#define MCF_CIM_CCON_SZEN              (0x00000040)
#define MCF_CIM_CCON_PSTEN             (0x00000020)
#define MCF_CIM_CCON_BME               (0x00000008)
#define MCF_CIM_CCON_BMT(x)            (((x)&0x00000007)<<0)

/* Function prototypes */
void init_main(void);
static void disable_interrupts(void);
static void disable_watchdog_timer(void);
static void init_ipsbar(void);
static void init_clock_config(void);
static void init_sram(void);
static void init_flash_controller(void);
static void init_eport(void);
static void init_flexcan(void);
static void init_bus_config(void);
static void init_power_management(void);
static void init_dma_timers(void);
static void init_gp_timer(void);
static void init_interrupt_timers(void);
static void init_real_time_clock(void);
static void init_watchdog_timer(void);
static void init_pin_assignments(void);
static void init_interrupt_controller(void);

/*********************************************************************
* init_main - Main entry point for initialisation code               *
**********************************************************************/
void init_main(void)
{
  /* Mask all interrupts */
  __asm__ ("move.w   #0x2700,%sr");

  /* Initialise base address of peripherals, VBR, etc */
  init_ipsbar();
  init_clock_config();

  /* Disable interrupts and watchdog timer */
  disable_interrupts();
  disable_watchdog_timer();

  /* Initialise individual modules */
  init_sram();
  init_flash_controller();
  init_eport();
  init_flexcan();
  init_bus_config();
  init_power_management();
  init_dma_timers();
  init_gp_timer();
  init_interrupt_timers();
  init_real_time_clock();
  init_watchdog_timer();
  init_pin_assignments();

  /* Initialise interrupt controller */
  init_interrupt_controller();
}

/*********************************************************************
* disable_interrupts - Disable all interrupt sources                 *
**********************************************************************/
static void disable_interrupts(void)
{
  vuint8 *p;
  int i;

  /* Set ICR008-ICR063 to 0x0 */
  p = (vuint8 *) & MCF_INTC0_ICR8;
  for (i = 8; i <= 63; i++)
    *p++ = 0x0;

  /* Set ICR108-ICR139 to 0x0 */
  p = (vuint8 *) & MCF_INTC1_ICR8;
  for (i = 108; i <= 139; i++)
    *p++ = 0x0;
}

/*********************************************************************
* disable_watchdog_timer - Disable system watchdog timer             *
**********************************************************************/
static void disable_watchdog_timer(void)
{
  /* Disable Core Watchdog Timer */
  MCF_SCM_CWCR = 0;
}

/*********************************************************************
* init_clock_config - Clock Module                                   *
**********************************************************************/
static void init_clock_config(void)
{
  /* Clock source is 25.0000 MHz external crystal
     Clock mode: Normal PLL mode
     Processor/Bus clock frequency = 60.00 MHz
     Loss of clock detection disabled
     Reset on loss of lock disabled
   */

  /* Divide 25.0000 MHz clock to get 5.00 MHz PLL input clock */
  MCF_CLOCK_CCHR = MCF_CLOCK_CCHR_PFD(0x4);

  /* Set RFD+1 to avoid frequency overshoot and wait for PLL to lock */
  MCF_CLOCK_SYNCR = 0x4103;
  while ((MCF_CLOCK_SYNSR & 0x08) == 0) ;

  /* Set desired RFD=0 and MFD=4 and wait for PLL to lock */
  MCF_CLOCK_SYNCR = 0x4003;
  while ((MCF_CLOCK_SYNSR & 0x08) == 0) ;
  MCF_CLOCK_SYNCR = 0x4007;                       /* Switch to using PLL */
}

/*********************************************************************
* init_ipsbar - Internal Peripheral System Base Address (IPSBAR)     *
**********************************************************************/
static void init_ipsbar(void)
{
  /* Base address of internal peripherals (IPSBAR) = 0x40000000

     Note: Processor powers up with IPS base address = 0x40000000
     Write to IPS base + 0x00000000 to set new value
   */
  *(vuint32 *) 0x40000000 = (vuint32) __IPSBAR + 1;     /* +1 for Enable */
}

/*********************************************************************
* init_flash_controller - Flash Module                               *
**********************************************************************/
static void init_flash_controller(void)
{
  /* Internal Flash module enabled, address = $00000000
     Flash state machine clock = 197.37 kHz
     All access types except CPU space/interrupt acknowledge cycle allowed
     Flash is Write-Protected
     All interrupts disabled
   */
  MCF_CFM_CFMCLKD = MCF_CFM_CFMCLKD_PRDIV8 | MCF_CFM_CFMCLKD_DIV(0x12);
  MCF_CFM_CFMMCR = 0;

  /* WARNING: Setting FLASHBAR[6]=1 in order to turn off address speculation
     This is a workaround for a hardware problem whereby a speculative
     access to the Flash occuring at the same time as an SRAM access
     can return corrupt data.

     This workaround can result in a 4% - 9% performance penalty. Other workarounds
     are possible for certain applications.

     For example, if you know that you will not be using the top 32 KB of the Flash
     you can place the SRAM base address at 0x20038000

     See Device Errata for further details
   */
  __asm__ ("move.l   #0x00000161,%d0");
  __asm__ ("movec    %d0,%FLASHBAR");
}

/*********************************************************************
* init_eport - Edge Port Module (EPORT)                              *
**********************************************************************/
static void init_eport(void)
{
  /* Pins 1-15 configured as GPIO inputs */
  MCF_EPORT_EPDDR0 = 0;
  MCF_EPORT_EPDDR1 = 0;
  MCF_EPORT_EPPAR0 = 0;
  MCF_EPORT_EPPAR1 = 0;
  MCF_EPORT_EPIER0 = 0;
  MCF_EPORT_EPIER1 = 0;
}

/*********************************************************************
* init_flexcan - FlexCAN Module                                      *
**********************************************************************/
static void init_flexcan(void)
{
  /* FlexCAN controller disabled (CANMCR0[MDIS]=1) */
  MCF_CAN_IMASK = 0;
  MCF_CAN_RXGMASK = MCF_CAN_RXGMASK_MI(0x1fffffff);
  MCF_CAN_RX14MASK = MCF_CAN_RX14MASK_MI(0x1fffffff);
  MCF_CAN_RX15MASK = MCF_CAN_RX15MASK_MI(0x1fffffff);
  MCF_CAN_CANCTRL = 0;
  MCF_CAN_CANMCR = MCF_CAN_CANMCR_MDIS |
    MCF_CAN_CANMCR_FRZ |
    MCF_CAN_CANMCR_HALT | MCF_CAN_CANMCR_SUPV | MCF_CAN_CANMCR_MAXMB(0xf);
}

/*********************************************************************
* init_bus_config - Internal Bus Arbitration                         *
**********************************************************************/
static void init_bus_config(void)
{
  /* Use round robin arbitration scheme
     Assigned priorities (highest first):
     Ethernet
     DMA Controller
     ColdFire Core
     DMA bandwidth control disabled
     Park on last active bus master
   */
  MCF_SCM_MPARK = MCF_SCM_MPARK_M3PRTY(0x3) |
    MCF_SCM_MPARK_M2PRTY(0x2) | (0x1 << 16);
}

/*********************************************************************
* init_sram - On-chip SRAM                                           *
**********************************************************************/
static void init_sram(void)
{
  /* Internal SRAM module enabled, address = $20000000
     DMA access to SRAM block disabled
     All access types (supervisor and user) allowed
   */
  __asm__ ("move.l   #0x20000001,%d0");
  __asm__ ("movec    %d0,%RAMBAR");
}

/*********************************************************************
* init_power_management - Power Management                           *
**********************************************************************/
static void init_power_management(void)
{
  /* On executing STOP instruction, processor enters RUN mode
     Mode is exited when an interrupt of level 1 or higher is received
   */
  MCF_PMM_LPICR = MCF_PMM_LPICR_ENBSTOP;
  MCF_PMM_LPCR = MCF_PMM_LPCR_LPMD_RUN;
}

/*********************************************************************
* init_dma_timers - DMA Timer Modules                                *
**********************************************************************/
static void init_dma_timers(void)
{
  /* DMA Timer 0 disabled (DTMR0[RST] = 0) */
  MCF_DTIM0_DTMR = MCF_DTIM_DTMR_CLK(0x1);
  MCF_DTIM0_DTXMR = 0;
  MCF_DTIM0_DTRR = MCF_DTIM_DTRR_REF(0xffffffff);

  /* DMA Timer 1 disabled (DTMR1[RST] = 0) */
  MCF_DTIM1_DTMR = 0;
  MCF_DTIM1_DTXMR = 0;
  MCF_DTIM1_DTRR = MCF_DTIM_DTRR_REF(0xffffffff);

  /* DMA Timer 2 disabled (DTMR2[RST] = 0) */
  MCF_DTIM2_DTMR = 0;
  MCF_DTIM2_DTXMR = 0;
  MCF_DTIM2_DTRR = MCF_DTIM_DTRR_REF(0xffffffff);

  /* DMA Timer 3 disabled (DTMR3[RST] = 0) */
  MCF_DTIM3_DTMR = MCF_DTIM_DTMR_CLK(0x1);
  MCF_DTIM3_DTXMR = 0;
  MCF_DTIM3_DTRR = MCF_DTIM_DTRR_REF(0xffffffff);
}

/*********************************************************************
* init_gp_timer - General Purpose Timer (GPT) Module                 *
**********************************************************************/
static void init_gp_timer(void)
{
  /*
     GPT disabled (GPTASCR1[GPTEN] = 0)
     Channel 0 configured as GPIO input
     Channel 1 configured as GPIO input
     Channel 2 configured as GPIO input
     Channel 3 configured as GPIO input
   */
  MCF_GPT_GPTSCR1 = 0;
  MCF_GPT_GPTDDR = 0;
}

/**********************************************************************
* init_interrupt_timers - Programmable Interrupt Timer (PIT) Modules  *
***********************************************************************/
static void init_interrupt_timers(void)
{
  /* PIT0 disabled (PCSR0[EN]=0) */
  MCF_PIT0_PCSR = 0;

  /* PIT1 disabled (PCSR1[EN]=0) */
  MCF_PIT1_PCSR = 0;
}

/*********************************************************************
* init_real_time_clock - Real-Time Clock (RTC)                       *
**********************************************************************/
static void init_real_time_clock(void)
{
  /* Disable the RTC */
  MCF_RTC_CR = 0;
}

/*********************************************************************
* init_watchdog_timer - Watchdog Timer                               *
**********************************************************************/
static void init_watchdog_timer(void)
{
  /* Core Watchdog Timer disabled (CWCR[CWE]=0) */
  MCF_SCM_CWCR = 0;
}

/*********************************************************************
* init_interrupt_controller - Interrupt Controller                   *
**********************************************************************/
static void init_interrupt_controller(void)
{
  /* Configured interrupt sources in order of priority...
     Level 7:  External interrupt /IRQ7, (initially masked)
     Level 6:  External interrupt /IRQ6, (initially masked)
     Level 5:  External interrupt /IRQ5, (initially masked)
     Level 4:  External interrupt /IRQ4, (initially masked)
     Level 3:  External interrupt /IRQ3, (initially masked)
     Level 2:  External interrupt /IRQ2, (initially masked)
     Level 1:  External interrupt /IRQ1, (initially masked)
   */
  MCF_INTC0_ICR1 = 0;
  MCF_INTC0_ICR2 = 0;
  MCF_INTC0_ICR3 = 0;
  MCF_INTC0_ICR4 = 0;
  MCF_INTC0_ICR5 = 0;
  MCF_INTC0_ICR6 = 0;
  MCF_INTC0_ICR7 = 0;
  MCF_INTC0_ICR8 = 0;
  MCF_INTC0_ICR9 = 0;
  MCF_INTC0_ICR10 = 0;
  MCF_INTC0_ICR11 = 0;
  MCF_INTC0_ICR12 = 0;
  MCF_INTC0_ICR13 = 0;
  MCF_INTC0_ICR14 = 0;
  MCF_INTC0_ICR15 = 0;
  MCF_INTC0_ICR17 = 0;
  MCF_INTC0_ICR18 = 0;
  MCF_INTC0_ICR19 = 0;
  MCF_INTC0_ICR20 = 0;
  MCF_INTC0_ICR21 = 0;
  MCF_INTC0_ICR22 = 0;
  MCF_INTC0_ICR23 = 0;
  MCF_INTC0_ICR24 = 0;
  MCF_INTC0_ICR25 = 0;
  MCF_INTC0_ICR26 = 0;
  MCF_INTC0_ICR27 = 0;
  MCF_INTC0_ICR28 = 0;
  MCF_INTC0_ICR29 = 0;
  MCF_INTC0_ICR30 = 0;
  MCF_INTC0_ICR31 = 0;
  MCF_INTC0_ICR32 = 0;
  MCF_INTC0_ICR33 = 0;
  MCF_INTC0_ICR34 = 0;
  MCF_INTC0_ICR35 = 0;
  MCF_INTC0_ICR36 = 0;
  MCF_INTC0_ICR41 = 0;
  MCF_INTC0_ICR42 = 0;
  MCF_INTC0_ICR43 = 0;
  MCF_INTC0_ICR44 = 0;
  MCF_INTC0_ICR45 = 0;
  MCF_INTC0_ICR46 = 0;
  MCF_INTC0_ICR47 = 0;
  MCF_INTC0_ICR48 = 0;
  MCF_INTC0_ICR49 = 0;
  MCF_INTC0_ICR50 = 0;
  MCF_INTC0_ICR51 = 0;
  MCF_INTC0_ICR52 = 0;
  MCF_INTC0_ICR53 = 0;
  MCF_INTC0_ICR55 = 0;
  MCF_INTC0_ICR56 = 0;
  MCF_INTC0_ICR59 = 0;
  MCF_INTC0_ICR60 = 0;
  MCF_INTC0_ICR61 = 0;
  MCF_INTC0_ICR62 = 0;
  MCF_INTC0_ICR63 = 0;
  MCF_INTC1_ICR8 = 0;
  MCF_INTC1_ICR9 = 0;
  MCF_INTC1_ICR10 = 0;
  MCF_INTC1_ICR11 = 0;
  MCF_INTC1_ICR12 = 0;
  MCF_INTC1_ICR13 = 0;
  MCF_INTC1_ICR14 = 0;
  MCF_INTC1_ICR15 = 0;
  MCF_INTC1_ICR16 = 0;
  MCF_INTC1_ICR17 = 0;
  MCF_INTC1_ICR18 = 0;
  MCF_INTC1_ICR19 = 0;
  MCF_INTC1_ICR20 = 0;
  MCF_INTC1_ICR21 = 0;
  MCF_INTC1_ICR22 = 0;
  MCF_INTC1_ICR23 = 0;
  MCF_INTC1_ICR24 = 0;
  MCF_INTC1_ICR25 = 0;
  MCF_INTC1_ICR32 = 0;
  MCF_INTC1_ICR33 = 0;
  MCF_INTC1_ICR34 = 0;
  MCF_INTC1_ICR35 = 0;
  MCF_INTC1_ICR36 = 0;
  MCF_INTC1_ICR37 = 0;
  MCF_INTC1_ICR38 = 0;
  MCF_INTC1_ICR39 = 0;
  MCF_INTC0_IMRH = 0xffffffff;
  MCF_INTC0_IMRL = 0xfffffffe;
  MCF_INTC1_IMRH = 0xffffffff;
  MCF_INTC1_IMRL = 0xfffffffe;
}

/*********************************************************************
* init_pin_assignments - Pin Assignment and General Purpose I/O      *
**********************************************************************/
static void init_pin_assignments(void)
{
  /* Pin assignments for port NQ
     Pins NQ7-NQ1 : EdgePort GPIO/IRQ
   */
  MCF_GPIO_DDRNQ = 0;
  MCF_GPIO_PNQPAR = MCF_GPIO_PNQPAR_PNQPAR7(0x1) |
    MCF_GPIO_PNQPAR_PNQPAR6(0x1) |
    MCF_GPIO_PNQPAR_PNQPAR5(0x1) |
    MCF_GPIO_PNQPAR_PNQPAR4(0x1) |
    MCF_GPIO_PNQPAR_PNQPAR3(0x1) |
    MCF_GPIO_PNQPAR_PNQPAR2(0x1) | MCF_GPIO_PNQPAR_PNQPAR1(0x1);

  /* Pin assignments for port GP
     Pins PG7-PG0 : EdgePort GPIO/IRQ
   */
  MCF_GPIO_DDRGP = 0;
  MCF_GPIO_PGPPAR = MCF_GPIO_PGPPAR_PGPPAR7 |
    MCF_GPIO_PGPPAR_PGPPAR6 |
    MCF_GPIO_PGPPAR_PGPPAR5 |
    MCF_GPIO_PGPPAR_PGPPAR4 |
    MCF_GPIO_PGPPAR_PGPPAR3 |
    MCF_GPIO_PGPPAR_PGPPAR2 |
    MCF_GPIO_PGPPAR_PGPPAR1 | MCF_GPIO_PGPPAR_PGPPAR0;

  /* Pin assignments for port DD
     Pin DD7 : DDATA[3]
     Pin DD6 : DDATA[2]
     Pin DD5 : DDATA[1]
     Pin DD4 : DDATA[0]
     Pin DD3 : PST[3]
     Pin DD2 : PST[2]
     Pin DD1 : PST[1]
     Pin DD0 : PST[0]
     CCON[PSTEN] = 1 to enable PST/DDATA function
   */
  MCF_GPIO_DDRDD = 0;
  MCF_GPIO_PDDPAR = MCF_GPIO_PDDPAR_PDDPAR7 |
    MCF_GPIO_PDDPAR_PDDPAR6 |
    MCF_GPIO_PDDPAR_PDDPAR5 |
    MCF_GPIO_PDDPAR_PDDPAR4 |
    MCF_GPIO_PDDPAR_PDDPAR3 |
    MCF_GPIO_PDDPAR_PDDPAR2 |
    MCF_GPIO_PDDPAR_PDDPAR1 | MCF_GPIO_PDDPAR_PDDPAR0;
  MCF_CIM_CCON = 0x0021;

  /* Pin assignments for port AN
     Pins are all GPIO inputs
   */
  MCF_GPIO_DDRAN = 0;
  MCF_GPIO_PANPAR = 0;

  /* Pin assignments for port AS
     Pins are all GPIO inputs
   */
  MCF_GPIO_DDRAS = 0;
  MCF_GPIO_PASPAR = 0;

  /* Pin assignments for port LD
     Pins are all GPIO inputs
   */
  MCF_GPIO_DDRLD = 0;
  MCF_GPIO_PLDPAR = 0;

  /* Pin assignments for port QS
     Pins are all GPIO inputs
   */
  MCF_GPIO_DDRQS = 0;
  MCF_GPIO_PQSPAR = 0;

  /* Pin assignments for port TA
     Pins are all GPIO inputs
   */
  MCF_GPIO_DDRTA = 0;
  MCF_GPIO_PTAPAR = 0;

  /* Pin assignments for port TC
     Pins are all GPIO inputs
   */
  MCF_GPIO_DDRTC = 0;
  MCF_GPIO_PTCPAR = 0;

  /* Pin assignments for port TD
     Pins are all GPIO inputs
   */
  MCF_GPIO_DDRTD = 0;
  MCF_GPIO_PTDPAR = 0;

  /* Pin assignments for port UA
     Pin UA3 : UART 0 clear-to-send, UCTS0
     Pin UA2 : UART 0 request-to-send, URTS0
     Pin UA1 : UART 0 receive data, URXD0
     Pin UA0 : UART 0 transmit data, UTXD0
   */
  MCF_GPIO_DDRUA = 0;
  MCF_GPIO_PUAPAR = MCF_GPIO_PUAPAR_PUAPAR3(0x1) |
    MCF_GPIO_PUAPAR_PUAPAR2(0x1) |
    MCF_GPIO_PUAPAR_PUAPAR1(0x1) | MCF_GPIO_PUAPAR_PUAPAR0(0x1);

  /* Pin assignments for port UB
     Pin UB3 : UART 1 clear-to-send, UCTS1
     Pin UB2 : UART 1 request-to-send, URTS1
     Pin UB1 : UART 1 receive data, URXD1
     Pin UB0 : UART 1 transmit data, UTXD1
   */
  MCF_GPIO_DDRUB = 0;
  MCF_GPIO_PUBPAR = MCF_GPIO_PUBPAR_PUBPAR3(0x1) |
    MCF_GPIO_PUBPAR_PUBPAR2(0x1) |
    MCF_GPIO_PUBPAR_PUBPAR1(0x1) | MCF_GPIO_PUBPAR_PUBPAR0(0x1);

  /* Pin assignments for port UC
     Pin UC3 : UART 2 clear-to-send, UCTS2
     Pin UC2 : UART 2 request-to-send, URTS2
     Pin UC1 : UART 2 receive data, URXD2
     Pin UC0 : UART 2 transmit data, UTXD2
   */
  MCF_GPIO_DDRUC = 0;
  MCF_GPIO_PUCPAR = MCF_GPIO_PUCPAR_PUCPAR3 |
    MCF_GPIO_PUCPAR_PUCPAR2 |
    MCF_GPIO_PUCPAR_PUCPAR1 | MCF_GPIO_PUCPAR_PUCPAR0;

  /* Configure drive strengths */
  MCF_GPIO_PDSRH = 0;
  MCF_GPIO_PDSRL = 0;

  /* Configure Wired-OR register */
  MCF_GPIO_PWOR = 0;
}