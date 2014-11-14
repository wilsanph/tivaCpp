//*****************************************************************************
//
// startup_ccs.c - Startup code for use with TI's Code Composer Studio.
//
// Copyright (c) 2012 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 9453 of the EK-LM4F120XL Firmware Package.
//
//*****************************************************************************
#include "tivaCppLibrary/interrupts.hpp"


//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
void ResetISR(void);
static void NmiSR(void);
static void FaultISR(void);
static void IntDefaultHandler(void);

//*****************************************************************************
//
// External declaration for the reset handler that is to be called when the
// processor is started
//
//*****************************************************************************
extern void _c_int00(void);

//*****************************************************************************
//
// Linker variable that marks the top of the stack.
//
//*****************************************************************************
extern unsigned long __STACK_TOP;

//*****************************************************************************
//
// External declarations for the interrupt handlers used by the application.
//
//*****************************************************************************
extern void IntGPIOa(void);
extern void IntGPIOb(void);
extern void IntGPIOc(void);

#pragma WEAK;
void interruptFuncs::reset_isr(){
    //
    // Jump to the CCS C initialization routine.  This will enable the
    // floating-point unit as well, so that does not need to be done here.
    //
    __asm("    .global _c_int00\n"
          "    b.w     _c_int00");
}

void interruptFuncs::mpuFault_isr(){

}


//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000 or at the start of
// the program if located at a start address other than 0.
//
//*****************************************************************************



#pragma DATA_ALIGN(1024)
#pragma DATA_SECTION(".vtable")
void (*g_pfnRAMVectors[155])(void);


namespace interruptFuncs{

#pragma DATA_SECTION(".intvecs")
extern "C" void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))((unsigned long)&__STACK_TOP),// The initial stack pointer
	#ifdef mpuLib
    (void (*)(void))reset_isr,
	#else
    (void (*)(void))ResetISR,                               // The reset handler
	#endif
    (void (*)(void))NmiSR,                                  // The NMI handler
    (void (*)(void))FaultISR,                               // The hard fault handler
	#ifdef mpuLib
    (void (*)(void))mpuFault_isr,                      // The MPU fault handler
	#else
    (void (*)(void))IntDefaultHandler,
	#endif
    (void (*)(void))busFault_isr,                      // The bus fault handler
    (void (*)(void))usageFault_isr,                      // The usage fault handler
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))svCall_isr,                      // SVCall handler
    (void (*)(void))debugMonitor_isr,                      // Debug monitor handler
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))pendSV_isr,                      // The PendSV handler
    (void (*)(void))sysTick_isr,                      // The SysTick handler
	#ifdef gpioInts
    (void (*)(void))gpioA_isr,            // GPIO Port A
	#else
    (void (*)(void))IntDefaultHandler,                      // GPIO Port A
	#endif
    (void (*)(void))gpioB_isr,                      // GPIO Port B
    (void (*)(void))gpioC_isr,                      // GPIO Port C
    (void (*)(void))gpioD_isr,                      // GPIO Port D
    (void (*)(void))gpioE_isr,                      // GPIO Port E
    (void (*)(void))uart0rxtx_isr,                      // UART0 Rx and Tx
    (void (*)(void))uart1rxtx_isr,                      // UART1 Rx and Tx
    (void (*)(void))ssi0rxtx_isr,                      // SSI0 Rx and Tx
    (void (*)(void))i2c0masterSlave_isr,                      // I2C0 Master and Slave
    (void (*)(void))pwmFault_isr,                      // PWM Fault
    (void (*)(void))pwm0_isr,                      // PWM Generator 0
    (void (*)(void))pwm1_isr,                      // PWM Generator 1
    (void (*)(void))pwm2_isr,                      // PWM Generator 2
    (void (*)(void))quadEnc0_isr,                      // Quadrature Encoder 0
    (void (*)(void))adcSeq0_isr,                      // ADC Sequence 0
    (void (*)(void))adcSeq1_isr,                      // ADC Sequence 1
    (void (*)(void))adcSeq2_isr,                      // ADC Sequence 2
    (void (*)(void))adcSeq3_isr,                      // ADC Sequence 3
    (void (*)(void))watchdogTimer_isr,                      // Watchdog timer
    (void (*)(void))timer0SubA_isr,                      // Timer 0 subtimer A
    (void (*)(void))timer0SubB_isr,                      // Timer 0 subtimer B
    (void (*)(void))timer1SubA_isr,                      // Timer 1 subtimer A
    (void (*)(void))timer1SubB_isr,                      // Timer 1 subtimer B
    (void (*)(void))timer2SubA_isr,                      // Timer 2 subtimer A
    (void (*)(void))timer2SubB_isr,                      // Timer 2 subtimer B
    (void (*)(void))analogComparator0_isr,                      // Analog Comparator 0
    (void (*)(void))analogComparator1_isr,                      // Analog Comparator 1
    (void (*)(void))analogComparator2_isr,                      // Analog Comparator 2
    (void (*)(void))sysCtrl_isr,                      // System Control (PLL, OSC, BO)
    (void (*)(void))flashCtrl_isr,                      // FLASH Control
    (void (*)(void))gpioF_isr,                      // GPIO Port F
    (void (*)(void))gpioG_isr,                      // GPIO Port G
    (void (*)(void))gpioH_isr,                      // GPIO Port H
    (void (*)(void))uart2rxtx_isr,                           // UART2 Rx and Tx
    (void (*)(void))ssi1rxtx_isr,                           // SSI1 Rx and Tx
    (void (*)(void))timer3SubA_isr,                           // Timer 3 subtimer A
    (void (*)(void))timer3SubB_isr,                           // Timer 3 subtimer B
    (void (*)(void))i2c1masterSlave_isr,                           // I2C1 Master and Slave
    (void (*)(void))quadEnc1_isr,                           // Quadrature Encoder 1
    (void (*)(void))can0_isr,                           // CAN0
    (void (*)(void))can1_isr,                           // CAN1
    (void (*)(void))can2_isr,                           // CAN2
    (void (*)(void))ethernet_isr,                           // Ethernet
    (void (*)(void))hibernate_isr,                           // Hibernate
    (void (*)(void))usb0_isr,                           // USB0
    (void (*)(void))pwm3_isr,                           // PWM Generator 3
    (void (*)(void))uDMAsofTransfer_isr,                           // uDMA Software Transfer
    (void (*)(void))uDMAerror_isr,                           // uDMA Error
    (void (*)(void))adc_1_Seq0_isr,                           // ADC1 Sequence 0
    (void (*)(void))adc_1_Seq1_isr,                           // ADC1 Sequence 1
    (void (*)(void))adc_1_Seq2_isr,                           // ADC1 Sequence 2
    (void (*)(void))adc_1_Seq3_isr,                           // ADC1 Sequence 3
    (void (*)(void))i2s0_isr,                           // I2S0
    (void (*)(void))extBusInterface_isr,                           // External Bus Interface 0
    (void (*)(void))gpioJ_isr,                           // GPIO Port J
    (void (*)(void))gpioK_isr,                           // GPIO Port K
    (void (*)(void))gpioL_isr,                           // GPIO Port L
    (void (*)(void))ssi2rxtx_isr,                           // SSI2 Rx and Tx
    (void (*)(void))ssi3rxtx_isr,                           // SSI3 Rx and Tx
    (void (*)(void))uart3rxtx_isr,                           // UART3 Rx and Tx
    (void (*)(void))uart4rxtx_isr,                           // UART4 Rx and Tx
    (void (*)(void))uart5rxtx_isr,                           // UART5 Rx and Tx
    (void (*)(void))uart6rxtx_isr,                           // UART6 Rx and Tx
    (void (*)(void))uart7rxtx_isr,                           // UART7 Rx and Tx
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))i2c2masterSlave_isr,                           // I2C2 Master and Slave
    (void (*)(void))i2c3masterSlave_isr,                           // I2C3 Master and Slave
    (void (*)(void))timer4SubA_isr,                           // Timer 4 subtimer A
    (void (*)(void))timer4SubB_isr,                           // Timer 4 subtimer B
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))timer5SubA_isr,                           // Timer 5 subtimer A
    (void (*)(void))timer5SubB_isr,                           // Timer 5 subtimer B
    (void (*)(void))timer0WideA_isr,                           // Wide Timer 0 subtimer A
    (void (*)(void))timer0WideB_isr,                           // Wide Timer 0 subtimer B
    (void (*)(void))timer1WideA_isr,                           // Wide Timer 1 subtimer A
    (void (*)(void))timer1WideB_isr,                           // Wide Timer 1 subtimer B
    (void (*)(void))timer2WideA_isr,                           // Wide Timer 2 subtimer A
    (void (*)(void))timer2WideB_isr,                           // Wide Timer 2 subtimer B
    (void (*)(void))timer3WideA_isr,                           // Wide Timer 3 subtimer A
    (void (*)(void))timer3WideB_isr,                           // Wide Timer 3 subtimer B
    (void (*)(void))timer4WideA_isr,                           // Wide Timer 4 subtimer A
    (void (*)(void))timer4WideB_isr,                           // Wide Timer 4 subtimer B
    (void (*)(void))timer5WideA_isr,                           // Wide Timer 5 subtimer A
    (void (*)(void))timer5WideB_isr,                           // Wide Timer 5 subtimer B
    (void (*)(void))fpu_isr,                           // FPU
    (void (*)(void))peci0_isr,                           // PECI 0
    (void (*)(void))lpc0_isr,                           // LPC 0
    (void (*)(void))i2c4masterSlave_isr,                           // I2C4 Master and Slave
    (void (*)(void))i2c5masterSlave_isr,                           // I2C5 Master and Slave
    (void (*)(void))gpioM_isr,                           // GPIO Port M
    (void (*)(void))gpioN_isr,                           // GPIO Port N
    (void (*)(void))quadEnc2_isr,                           // Quadrature Encoder 2
    (void (*)(void))fan0_isr,                           // Fan 0
    (void (*)(void))0,                                      // Reserved
    (void (*)(void))gpioP_isr,                           // GPIO Port P (Summary or P0)
    (void (*)(void))gpioP1_isr,                           // GPIO Port P1
    (void (*)(void))gpioP2_isr,                           // GPIO Port P2
    (void (*)(void))gpioP3_isr,                           // GPIO Port P3
    (void (*)(void))gpioP4_isr,                           // GPIO Port P4
    (void (*)(void))gpioP5_isr,                           // GPIO Port P5
    (void (*)(void))gpioP6_isr,                           // GPIO Port P6
    (void (*)(void))gpioP7_isr,                           // GPIO Port P7
    (void (*)(void))gpioQ_isr,                           // GPIO Port Q (Summary or Q0)
    (void (*)(void))gpioQ1_isr,                           // GPIO Port Q1
    (void (*)(void))gpioQ2_isr,                           // GPIO Port Q2
    (void (*)(void))gpioQ3_isr,                           // GPIO Port Q3
    (void (*)(void))gpioQ4_isr,                           // GPIO Port Q4
    (void (*)(void))gpioQ5_isr,                           // GPIO Port Q5
    (void (*)(void))gpioQ6_isr,                           // GPIO Port Q6
    (void (*)(void))gpioQ7_isr,                           // GPIO Port Q7
    (void (*)(void))gpioR_isr,                           // GPIO Port R
    (void (*)(void))gpioS_isr,                           // GPIO Port S
    (void (*)(void))pwm_1_0_isr,                           // PWM 1 Generator 0
    (void (*)(void))pwm_1_1_isr,                           // PWM 1 Generator 1
    (void (*)(void))pwm_1_2_isr,                           // PWM 1 Generator 2
    (void (*)(void))pwm_1_3_isr,                           // PWM 1 Generator 3
    (void (*)(void))pwm_1_Fault_isr         // PWM 1 Fault
};
}
//#pragma SET_DATA_SECTION()
//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************


#pragma WEAK;
void interruptFuncs::busFault_isr(){}
#pragma WEAK;
void interruptFuncs::usageFault_isr(){}
#pragma WEAK;
void interruptFuncs::svCall_isr(){}
#pragma WEAK;
void interruptFuncs::debugMonitor_isr(){}
#pragma WEAK;
void interruptFuncs::pendSV_isr(){}
#pragma WEAK;
void interruptFuncs::sysTick_isr(){}
#pragma WEAK;
void interruptFuncs::gpioB_isr(){}
#pragma WEAK;
void interruptFuncs::gpioC_isr(){}
#pragma WEAK;
void interruptFuncs::gpioD_isr(){}
#pragma WEAK;
void interruptFuncs::gpioE_isr(){}
#pragma WEAK;
void interruptFuncs::uart0rxtx_isr(){}
#pragma WEAK;
void interruptFuncs::uart1rxtx_isr(){}
#pragma WEAK;
void interruptFuncs::ssi0rxtx_isr(){}
#pragma WEAK;
void interruptFuncs::i2c0masterSlave_isr(){}
#pragma WEAK;
void interruptFuncs::pwmFault_isr(){}
#pragma WEAK;
void interruptFuncs::pwm0_isr(){}
#pragma WEAK;
void interruptFuncs::pwm1_isr(){}
#pragma WEAK;
void interruptFuncs::pwm2_isr(){}
#pragma WEAK;
void interruptFuncs::quadEnc0_isr(){}
#pragma WEAK;
void interruptFuncs::adcSeq0_isr(){}
#pragma WEAK;
void interruptFuncs::adcSeq1_isr(){}
#pragma WEAK;
void interruptFuncs::adcSeq2_isr(){}
#pragma WEAK;
void interruptFuncs::adcSeq3_isr(){}
#pragma WEAK;
void interruptFuncs::watchdogTimer_isr(){}
#pragma WEAK;
void interruptFuncs::timer0SubA_isr(){}
#pragma WEAK;
void interruptFuncs::timer0SubB_isr(){}
#pragma WEAK;
void interruptFuncs::timer1SubA_isr(){}
#pragma WEAK;
void interruptFuncs::timer1SubB_isr(){}
#pragma WEAK;
void interruptFuncs::timer2SubA_isr(){}
#pragma WEAK;
void interruptFuncs::timer2SubB_isr(){}
#pragma WEAK;
void interruptFuncs::analogComparator0_isr(){}
#pragma WEAK;
void interruptFuncs::analogComparator1_isr(){}
#pragma WEAK;
void interruptFuncs::analogComparator2_isr(){}
#pragma WEAK;
void interruptFuncs::sysCtrl_isr(){}
#pragma WEAK;
void interruptFuncs::flashCtrl_isr(){}
#pragma WEAK;
void interruptFuncs::gpioF_isr(){}
#pragma WEAK;
void interruptFuncs::gpioG_isr(){}
#pragma WEAK;
void interruptFuncs::gpioH_isr(){}
#pragma WEAK;
void interruptFuncs::uart2rxtx_isr(){}
#pragma WEAK;
void interruptFuncs::ssi1rxtx_isr(){}
#pragma WEAK;
void interruptFuncs::timer3SubA_isr(){}
#pragma WEAK;
void interruptFuncs::timer3SubB_isr(){}
#pragma WEAK;
void interruptFuncs::i2c1masterSlave_isr(){}
#pragma WEAK;
void interruptFuncs::quadEnc1_isr(){}
#pragma WEAK;
void interruptFuncs::can0_isr(){}
#pragma WEAK;
void interruptFuncs::can1_isr(){}
#pragma WEAK;
void interruptFuncs::can2_isr(){}
#pragma WEAK;
void interruptFuncs::ethernet_isr(){}
#pragma WEAK;
void interruptFuncs::hibernate_isr(){}
#pragma WEAK;
void interruptFuncs::usb0_isr(){}
#pragma WEAK;
void interruptFuncs::pwm3_isr(){}
#pragma WEAK;
void interruptFuncs::uDMAsofTransfer_isr(){}
#pragma WEAK;
void interruptFuncs::uDMAerror_isr(){}
#pragma WEAK;
void interruptFuncs::adc_1_Seq0_isr(){}
#pragma WEAK;
void interruptFuncs::adc_1_Seq1_isr(){}
#pragma WEAK;
void interruptFuncs::adc_1_Seq2_isr(){}
#pragma WEAK;
void interruptFuncs::adc_1_Seq3_isr(){}
#pragma WEAK;
void interruptFuncs::i2s0_isr(){}
#pragma WEAK;
void interruptFuncs::extBusInterface_isr(){}
#pragma WEAK;
void interruptFuncs::gpioJ_isr(){}
#pragma WEAK;
void interruptFuncs::gpioK_isr(){}
#pragma WEAK;
void interruptFuncs::gpioL_isr(){}
#pragma WEAK;
void interruptFuncs::ssi2rxtx_isr(){}
#pragma WEAK;
void interruptFuncs::ssi3rxtx_isr(){}
#pragma WEAK;
void interruptFuncs::uart3rxtx_isr(){}
#pragma WEAK;
void interruptFuncs::uart4rxtx_isr(){}
#pragma WEAK;
void interruptFuncs::uart5rxtx_isr(){}
#pragma WEAK;
void interruptFuncs::uart6rxtx_isr(){}
#pragma WEAK;
void interruptFuncs::uart7rxtx_isr(){}
#pragma WEAK;
void interruptFuncs::i2c2masterSlave_isr(){}
#pragma WEAK;
void interruptFuncs::i2c3masterSlave_isr(){}
#pragma WEAK;
void interruptFuncs::timer4SubA_isr(){}
#pragma WEAK;
void interruptFuncs::timer4SubB_isr(){}
#pragma WEAK;
void interruptFuncs::timer5SubA_isr(){}
#pragma WEAK;
void interruptFuncs::timer5SubB_isr(){}
#pragma WEAK;
void interruptFuncs::timer0WideA_isr(){}
#pragma WEAK;
void interruptFuncs::timer0WideB_isr(){}
#pragma WEAK;
void interruptFuncs::timer1WideA_isr(){}
#pragma WEAK;
void interruptFuncs::timer1WideB_isr(){}
#pragma WEAK;
void interruptFuncs::timer2WideA_isr(){}
#pragma WEAK;
void interruptFuncs::timer2WideB_isr(){}
#pragma WEAK;
void interruptFuncs::timer3WideA_isr(){}
#pragma WEAK;
void interruptFuncs::timer3WideB_isr(){}
#pragma WEAK;
void interruptFuncs::timer4WideA_isr(){}
#pragma WEAK;
void interruptFuncs::timer4WideB_isr(){}
#pragma WEAK;
void interruptFuncs::timer5WideA_isr(){}
#pragma WEAK;
void interruptFuncs::timer5WideB_isr(){}
#pragma WEAK;
void interruptFuncs::fpu_isr(){}
#pragma WEAK;
void interruptFuncs::peci0_isr(){}
#pragma WEAK;
void interruptFuncs::lpc0_isr(){}
#pragma WEAK;
void interruptFuncs::i2c4masterSlave_isr(){}
#pragma WEAK;
void interruptFuncs::i2c5masterSlave_isr(){}
#pragma WEAK;
void interruptFuncs::gpioM_isr(){}
#pragma WEAK;
void interruptFuncs::gpioN_isr(){}
#pragma WEAK;
void interruptFuncs::quadEnc2_isr(){}
#pragma WEAK;
void interruptFuncs::fan0_isr(){}
#pragma WEAK;
void interruptFuncs::gpioP_isr(){}
#pragma WEAK;
void interruptFuncs::gpioP1_isr(){}
#pragma WEAK;
void interruptFuncs::gpioP2_isr(){}
#pragma WEAK;
void interruptFuncs::gpioP3_isr(){}
#pragma WEAK;
void interruptFuncs::gpioP4_isr(){}
#pragma WEAK;
void interruptFuncs::gpioP5_isr(){}
#pragma WEAK;
void interruptFuncs::gpioP6_isr(){}
#pragma WEAK;
void interruptFuncs::gpioP7_isr(){}
#pragma WEAK;
void interruptFuncs::gpioQ_isr(){}
#pragma WEAK;
void interruptFuncs::gpioQ1_isr(){}
#pragma WEAK;
void interruptFuncs::gpioQ2_isr(){}
#pragma WEAK;
void interruptFuncs::gpioQ3_isr(){}
#pragma WEAK;
void interruptFuncs::gpioQ4_isr(){}
#pragma WEAK;
void interruptFuncs::gpioQ5_isr(){}
#pragma WEAK;
void interruptFuncs::gpioQ6_isr(){}
#pragma WEAK;
void interruptFuncs::gpioQ7_isr(){}
#pragma WEAK;
void interruptFuncs::gpioR_isr(){}
#pragma WEAK;
void interruptFuncs::gpioS_isr(){}
#pragma WEAK;
void interruptFuncs::pwm_1_0_isr(){}
#pragma WEAK;
void interruptFuncs::pwm_1_1_isr(){}
#pragma WEAK;
void interruptFuncs::pwm_1_2_isr(){}
#pragma WEAK;
void interruptFuncs::pwm_1_3_isr(){}
#pragma WEAK;
void interruptFuncs::pwm_1_Fault_isr(){}






void interruptFuncs::gpioA_isr(){

}




void
ResetISR(void)
{
    //
    // Jump to the CCS C initialization routine.  This will enable the
    // floating-point unit as well, so that does not need to be done here.
    //
    __asm("    .global _c_int00\n"
          "    b.w     _c_int00");
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
static void
NmiSR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void
FaultISR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void
IntDefaultHandler(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}
