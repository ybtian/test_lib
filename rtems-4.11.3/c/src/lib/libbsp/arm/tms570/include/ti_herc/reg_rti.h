/* The header file is generated by make_header.py from RTI.json */
/* Current script's version can be found at: */
/* https://github.com/AoLaD/rtems-tms570-utils/tree/headers/headers/python */

/*
 * Copyright (c) 2014-2015, Premysl Houdek <kom541000@gmail.com>
 *
 * Czech Technical University in Prague
 * Zikova 1903/4
 * 166 36 Praha 6
 * Czech Republic
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the FreeBSD Project.
*/
#ifndef LIBBSP_ARM_TMS570_RTI
#define LIBBSP_ARM_TMS570_RTI

#include <bsp/utility.h>

typedef struct{
  uint32_t COMPx;             /*RTI Compare x Register*/
  uint32_t UDCPx;             /*RTI Update Compare x Register*/
} tms570_rti_compare_t;

typedef struct{
  uint32_t FRCx;              /*RTI Free Running Counter x Register*/
  uint32_t UCx;               /*RTI Up Counter x Register*/
  uint32_t CPUCx;             /*RTI Compare Up Counter x Register*/
  uint8_t reserved1 [4];
  uint32_t CAFRCx;            /*RTI Capture Free Running Counter x Register*/
  uint32_t CAUCx;             /*RTI Capture Up Counter x Register*/
  uint32_t rsvd[2];           /*Reserved*/
} tms570_rti_counter_t;

typedef struct{
  uint32_t GCTRL;             /*RTI Global Control Register*/
  uint32_t TBCTRL;            /*RTI Timebase Control Register*/
  uint32_t CAPCTRL;           /*RTI Capture Control Register*/
  uint32_t COMPCTRL;          /*RTI Compare Control Register*/
  tms570_rti_counter_t CNT[2];/*Counters*/
  tms570_rti_compare_t CMP[4];/*Compares*/
  uint32_t TBLCOMP;           /*RTI Timebase Low Compare Register*/
  uint32_t TBHCOMP;           /*RTI Timebase High Compare Register*/
  uint8_t reserved2 [8];
  uint32_t SETINTENA;         /*RTI Set Interrupt Enable Register*/
  uint32_t CLEARINTENA;       /*RTI Clear Interrupt Enable Register*/
  uint32_t INTFLAG;           /*RTI Interrupt Flag Register*/
  uint8_t reserved3 [4];
  uint32_t DWDCTRL;           /*Digital Watchdog Control Register*/
  uint32_t DWDPRLD;           /*Digital Watchdog Preload Register*/
  uint32_t WDSTATUS;          /*Watchdog Status Register*/
  uint32_t WDKEY;             /*RTI Watchdog Key Register*/
  uint32_t DWDCNTR;           /*RTI Digital Watchdog Down Counter Register*/
  uint32_t WWDRXNCTRL;        /*Digital Windowed Watchdog Reaction Control Register*/
  uint32_t WWDSIZECTRL;       /*Digital Windowed Watchdog Window Size Control Register*/
  uint32_t INTCLRENABLE;      /*RTI Compare Interrupt Clear Enable Register*/
  uint32_t COMP0CLR;          /*RTI Compare 0 Clear Register*/
  uint32_t COMP1CLR;          /*RTI Compare 1 Clear Register*/
  uint32_t COMP2CLR;          /*RTI Compare 2 Clear Register*/
  uint32_t COMP3CLR;          /*RTI Compare 3 Clear Register*/
} tms570_rti_t;


/*----------------------TMS570_RTI_COMPx----------------------*/
/* field: COMPx - Compare x. */
/* Whole 32 bits */

/*----------------------TMS570_RTI_UDCPx----------------------*/
/* field: UDCPx - Update compare x. */
/* Whole 32 bits */

/*----------------------TMS570_RTI_FRCx----------------------*/
/* field: FRC0 - FRC0 */
/* Whole 32 bits */

/*-----------------------TMS570_RTI_UCx-----------------------*/
/* field: UC0 - Up counter 0. */
/* Whole 32 bits */

/*----------------------TMS570_RTI_CPUCx----------------------*/
/* field: CPUC0 - Compare up counter 0. This register holds the value that is compared with the up counter 0. */
/* Whole 32 bits */

/*---------------------TMS570_RTI_CAFRCx---------------------*/
/* field: CAFRC0 - Capture free running counter 0. */
/* Whole 32 bits */

/*----------------------TMS570_RTI_CAUCx----------------------*/
/* field: CAUC0 - Capture up counter 0. */
/* Whole 32 bits */

/*----------------------TMS570_RTI_rsvd----------------------*/
/* field: CAUC0 - Capture up counter 0. */
/* Whole 32 bits */

/*----------------------TMS570_RTI_GCTRL----------------------*/
/* field: NTUSEL - Select NTU signal. */
#define TMS570_RTI_GCTRL_NTUSEL(val) BSP_FLD32(val,16, 19)
#define TMS570_RTI_GCTRL_NTUSEL_GET(reg) BSP_FLD32GET(reg,16, 19)
#define TMS570_RTI_GCTRL_NTUSEL_SET(reg,val) BSP_FLD32SET(reg, val,16, 19)

/* field: COS - Continue on suspend. */
#define TMS570_RTI_GCTRL_COS BSP_BIT32(15)

/* field: CNT1EN - Counter 1 enable. This bit starts and stops counter block 1 (RTIUC1 and RTIFRC1). */
#define TMS570_RTI_GCTRL_CNT1EN BSP_BIT32(1)

/* field: CNT0EN - Counter 0 enable. This bit starts and stops counter block 0 (RTIUC0 and RTIFRC0). */
#define TMS570_RTI_GCTRL_CNT0EN BSP_BIT32(0)


/*---------------------TMS570_RTI_TBCTRL---------------------*/
/* field: INC - Increment free running counter 0. */
#define TMS570_RTI_TBCTRL_INC BSP_BIT32(1)

/* field: TBEXT - Timebase external. */
#define TMS570_RTI_TBCTRL_TBEXT BSP_BIT32(0)


/*---------------------TMS570_RTI_CAPCTRL---------------------*/
/* field: CAPCNTR1 - Capture counter 1. */
#define TMS570_RTI_CAPCTRL_CAPCNTR1 BSP_BIT32(1)

/* field: CAPCNTR0 - Capture counter 0. */
#define TMS570_RTI_CAPCTRL_CAPCNTR0 BSP_BIT32(0)


/*--------------------TMS570_RTI_COMPCTRL--------------------*/
/* field: COMPSEL3 - Compare select 3. */
#define TMS570_RTI_COMPCTRL_COMPSEL3 BSP_BIT32(12)

/* field: COMPSEL2 - Compare select 2. */
#define TMS570_RTI_COMPCTRL_COMPSEL2 BSP_BIT32(8)

/* field: COMPSEL1 - Compare select 1. */
#define TMS570_RTI_COMPCTRL_COMPSEL1 BSP_BIT32(4)

/* field: COMPSEL0 - Compare select 0. */
#define TMS570_RTI_COMPCTRL_COMPSEL0 BSP_BIT32(0)


/*---------------------TMS570_RTI_TBLCOMP---------------------*/
/* field: TBLCOMP - Timebase low compare value. */
/* Whole 32 bits */

/*---------------------TMS570_RTI_TBHCOMP---------------------*/
/* field: TBHCOMP - Timebase high compare value. */
/* Whole 32 bits */

/*--------------------TMS570_RTI_SETINTENA--------------------*/
/* field: SETOVL1INT - Set free running counter 1 overflow interrupt. */
#define TMS570_RTI_SETINTENA_SETOVL1INT BSP_BIT32(18)

/* field: SETOVL0INT - Set free running counter 0 overflow interrupt. */
#define TMS570_RTI_SETINTENA_SETOVL0INT BSP_BIT32(17)

/* field: SETTBINT - Set timebase interrupt. */
#define TMS570_RTI_SETINTENA_SETTBINT BSP_BIT32(16)

/* field: SETDMA3 - Set compare DMA request 3. */
#define TMS570_RTI_SETINTENA_SETDMA3 BSP_BIT32(11)

/* field: SETDMA2 - Set compare DMA request 2. */
#define TMS570_RTI_SETINTENA_SETDMA2 BSP_BIT32(10)

/* field: SETDMA1 - Set compare DMA request 1. */
#define TMS570_RTI_SETINTENA_SETDMA1 BSP_BIT32(9)

/* field: SETDMA0 - Set compare DMA request 0. */
#define TMS570_RTI_SETINTENA_SETDMA0 BSP_BIT32(8)

/* field: SETINT3 - Set compare interrupt 3. */
#define TMS570_RTI_SETINTENA_SETINT3 BSP_BIT32(3)

/* field: SETINT2 - Set compare interrupt 2. */
#define TMS570_RTI_SETINTENA_SETINT2 BSP_BIT32(2)

/* field: SETINT1 - Set compare interrupt 1. */
#define TMS570_RTI_SETINTENA_SETINT1 BSP_BIT32(1)

/* field: SETINT0 - Set compare interrupt 0. */
#define TMS570_RTI_SETINTENA_SETINT0 BSP_BIT32(0)


/*-------------------TMS570_RTI_CLEARINTENA-------------------*/
/* field: CLEAROVL1INT - Clear free running counter 1 overflow interrupt. */
#define TMS570_RTI_CLEARINTENA_CLEAROVL1INT BSP_BIT32(18)

/* field: CLEAROVL0INT - Clear free running counter 0 overflow interrupt. */
#define TMS570_RTI_CLEARINTENA_CLEAROVL0INT BSP_BIT32(17)

/* field: CLEARTBINT - Clear timebase interrupt. */
#define TMS570_RTI_CLEARINTENA_CLEARTBINT BSP_BIT32(16)

/* field: CLEARDMA3 - Clear compare DMA request 3. */
#define TMS570_RTI_CLEARINTENA_CLEARDMA3 BSP_BIT32(11)

/* field: CLEARDMA2 - Clear compare DMA request 2. */
#define TMS570_RTI_CLEARINTENA_CLEARDMA2 BSP_BIT32(10)

/* field: CLEARDMA1 - Clear compare DMA request 1. */
#define TMS570_RTI_CLEARINTENA_CLEARDMA1 BSP_BIT32(9)

/* field: CLEARDMA0 - Clear compare DMA request 0. */
#define TMS570_RTI_CLEARINTENA_CLEARDMA0 BSP_BIT32(8)

/* field: CLEARINT3 - Clear compare interrupt 3. */
#define TMS570_RTI_CLEARINTENA_CLEARINT3 BSP_BIT32(3)

/* field: CLEARINT2 - Clear compare interrupt 2. */
#define TMS570_RTI_CLEARINTENA_CLEARINT2 BSP_BIT32(2)

/* field: CLEARINT1 - Clear compare interrupt 1. */
#define TMS570_RTI_CLEARINTENA_CLEARINT1 BSP_BIT32(1)

/* field: CLEARINT0 - Clear compare interrupt 0. */
#define TMS570_RTI_CLEARINTENA_CLEARINT0 BSP_BIT32(0)


/*---------------------TMS570_RTI_INTFLAG---------------------*/
/* field: OVL1INT - Free running counter 1 overflow interrupt flag. This bit determines if an interrupt is pending. */
#define TMS570_RTI_INTFLAG_OVL1INT BSP_BIT32(18)

/* field: OVL0INT - Free running counter 0 overflow interrupt flag. This bit determines if an interrupt is pending. */
#define TMS570_RTI_INTFLAG_OVL0INT BSP_BIT32(17)

/* field: TBINT - Timebase interrupt flag. */
#define TMS570_RTI_INTFLAG_TBINT BSP_BIT32(16)

/* field: INT3 - Interrupt flag 3. These bits determine if an interrupt due to a Compare 3 match is pending. */
#define TMS570_RTI_INTFLAG_INT3 BSP_BIT32(3)

/* field: INT2 - Interrupt flag 2. These bits determine if an interrupt due to a Compare 2 match is pending. */
#define TMS570_RTI_INTFLAG_INT2 BSP_BIT32(2)

/* field: INT1 - Interrupt flag 1. These bits determine if an interrupt due to a Compare 1 match is pending. */
#define TMS570_RTI_INTFLAG_INT1 BSP_BIT32(1)

/* field: INT0 - Interrupt flag 0. These bits determine if an interrupt due to a Compare 0 match is pending. */
#define TMS570_RTI_INTFLAG_INT0 BSP_BIT32(0)


/*---------------------TMS570_RTI_DWDCTRL---------------------*/
/* field: DWDCTRL - DWDCTRL Digital Watchdog Control. */
/* Whole 32 bits */

/*---------------------TMS570_RTI_DWDPRLD---------------------*/
/* field: DWDPRLD - Digital Watchdog Preload Value. */
#define TMS570_RTI_DWDPRLD_DWDPRLD(val) BSP_FLD32(val,0, 15)
#define TMS570_RTI_DWDPRLD_DWDPRLD_GET(reg) BSP_FLD32GET(reg,0, 15)
#define TMS570_RTI_DWDPRLD_DWDPRLD_SET(reg,val) BSP_FLD32SET(reg, val,0, 15)


/*--------------------TMS570_RTI_WDSTATUS--------------------*/
/* field: DWWD_ST - Windowed Watchdog Status */
#define TMS570_RTI_WDSTATUS_DWWD_ST BSP_BIT32(5)

/* field: END_TIME_VIOL - Windowed Watchdog End Time Violation Status. */
#define TMS570_RTI_WDSTATUS_END_TIME_VIOL BSP_BIT32(4)

/* field: START_TIME_VIOL - Windowed Watchdog Start Time Violation Status. */
#define TMS570_RTI_WDSTATUS_START_TIME_VIOL BSP_BIT32(3)

/* field: KEY_ST - Watchdog key status. */
#define TMS570_RTI_WDSTATUS_KEY_ST BSP_BIT32(2)

/* field: DWD_ST - DWD status. */
#define TMS570_RTI_WDSTATUS_DWD_ST BSP_BIT32(1)


/*----------------------TMS570_RTI_WDKEY----------------------*/
/* field: WDKEY - Watchdog key. These bits provide the key sequence location. */
#define TMS570_RTI_WDKEY_WDKEY(val) BSP_FLD32(val,0, 15)
#define TMS570_RTI_WDKEY_WDKEY_GET(reg) BSP_FLD32GET(reg,0, 15)
#define TMS570_RTI_WDKEY_WDKEY_SET(reg,val) BSP_FLD32SET(reg, val,0, 15)


/*---------------------TMS570_RTI_DWDCNTR---------------------*/
/* field: DWDCNTR - DWD down counter. */
#define TMS570_RTI_DWDCNTR_DWDCNTR(val) BSP_FLD32(val,0, 24)
#define TMS570_RTI_DWDCNTR_DWDCNTR_GET(reg) BSP_FLD32GET(reg,0, 24)
#define TMS570_RTI_DWDCNTR_DWDCNTR_SET(reg,val) BSP_FLD32SET(reg, val,0, 24)


/*-------------------TMS570_RTI_WWDRXNCTRL-------------------*/
/* field: WWDRXN - The DWWD reaction */
#define TMS570_RTI_WWDRXNCTRL_WWDRXN(val) BSP_FLD32(val,0, 3)
#define TMS570_RTI_WWDRXNCTRL_WWDRXN_GET(reg) BSP_FLD32GET(reg,0, 3)
#define TMS570_RTI_WWDRXNCTRL_WWDRXN_SET(reg,val) BSP_FLD32SET(reg, val,0, 3)


/*-------------------TMS570_RTI_WWDSIZECTRL-------------------*/
/* field: WWDSIZE - The DWWD window size */
/* Whole 32 bits */

/*------------------TMS570_RTI_INTCLRENABLE------------------*/
/* field: INTCLRENABLE3 - Enables the auto-clear functionality on the compare 3 interrupt. */
#define TMS570_RTI_INTCLRENABLE_INTCLRENABLE3(val) BSP_FLD32(val,24, 27)
#define TMS570_RTI_INTCLRENABLE_INTCLRENABLE3_GET(reg) BSP_FLD32GET(reg,24, 27)
#define TMS570_RTI_INTCLRENABLE_INTCLRENABLE3_SET(reg,val) BSP_FLD32SET(reg, val,24, 27)

/* field: INTCLRENABLE2 - Enables the auto-clear functionality on the compare 2 interrupt. */
#define TMS570_RTI_INTCLRENABLE_INTCLRENABLE2(val) BSP_FLD32(val,16, 19)
#define TMS570_RTI_INTCLRENABLE_INTCLRENABLE2_GET(reg) BSP_FLD32GET(reg,16, 19)
#define TMS570_RTI_INTCLRENABLE_INTCLRENABLE2_SET(reg,val) BSP_FLD32SET(reg, val,16, 19)

/* field: INTCLRENABLE1 - Enables the auto-clear functionality on the compare 1 interrupt. */
#define TMS570_RTI_INTCLRENABLE_INTCLRENABLE1(val) BSP_FLD32(val,8, 11)
#define TMS570_RTI_INTCLRENABLE_INTCLRENABLE1_GET(reg) BSP_FLD32GET(reg,8, 11)
#define TMS570_RTI_INTCLRENABLE_INTCLRENABLE1_SET(reg,val) BSP_FLD32SET(reg, val,8, 11)

/* field: INTCLRENABLE0 - Enables the auto-clear functionality on the compare 0 interrupt. */
#define TMS570_RTI_INTCLRENABLE_INTCLRENABLE0(val) BSP_FLD32(val,0, 3)
#define TMS570_RTI_INTCLRENABLE_INTCLRENABLE0_GET(reg) BSP_FLD32GET(reg,0, 3)
#define TMS570_RTI_INTCLRENABLE_INTCLRENABLE0_SET(reg,val) BSP_FLD32SET(reg, val,0, 3)


/*--------------------TMS570_RTI_COMP0CLR--------------------*/
/* field: CMP0CLR - Compare 0 clear. */
/* Whole 32 bits */

/*--------------------TMS570_RTI_COMP1CLR--------------------*/
/* field: CMP0CLR - Compare 1 clear. */
/* Whole 32 bits */

/*--------------------TMS570_RTI_COMP2CLR--------------------*/
/* field: CMP2CLR - Compare 2 clear. */
/* Whole 32 bits */

/*--------------------TMS570_RTI_COMP3CLR--------------------*/
/* field: CMP3CLR - Compare 3 clear. */
/* Whole 32 bits */


#endif /* LIBBSP_ARM_TMS570_RTI */
