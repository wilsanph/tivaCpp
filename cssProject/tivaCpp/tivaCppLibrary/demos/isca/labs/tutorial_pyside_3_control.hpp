#include "tivaCppLibrary/include/Gpio.hpp"
#include "tivaCppLibrary/include/clock.hpp"
#include "tivaCppLibrary/delays.hpp"

#include "tivaCppLibrary/include/Gptimer.hpp"
#include "tivaCppLibrary/devLibraries/QEI.hpp"

#include "tivaCppLibrary/include/Uart.h"// funcionalidad para los m�dulos UARTx
#include "tivaCppLibrary/include/Core.hpp"// funciones para habilitar las interrupciones
#include "tivaCppLibrary/interrupts.hpp"// prototipos de interrupci�n ya mapeados

// Array para guardar los bytes a transmitir
u8 buffTx[2] = {0,0};

// Variables globales ( antes del main )
u32 countReg = 0;
u32 speedReg = 0;

float duty = 0.2;

float kp = 0.002272;
float ki = 0.000473;
float u = 0;

float x = 0;
float ref = 100;
float e_t 	= 0;
float e_t_1 = 0;

float ep = 0;
float ei = 0;

#define DELTA_STEP 0.05

int main()
{
	clock::clock::config(clock::configOptions::clockSource::mainOscilator,
						 clock::configOptions::clockRate::clock_80Mhz);

	Gpio::enableClock(Gpio::peripheral::GPIOF);
	Gpio::enableClock(Gpio::peripheral::GPIOC);
	Gpio::enableClock(Gpio::peripheral::GPIOA);

	PA0::enableAsDigital();
	PA0::setMode(Gpio::options::mode::alternate);
	PA0::setAlternateMode(Gpio::options::altModes::alt1);

	PA1::enableAsDigital();
	PA1::setMode(Gpio::options::mode::alternate);
	PA1::setAlternateMode(Gpio::options::altModes::alt1);

	PF2::enableAsDigital();
	PF2::setMode(Gpio::options::mode::gpio);
	PF2::setIOmode(Gpio::options::IOmode::output);

	PC4::enableAsDigital();
	PC4::setMode(Gpio::options::mode::alternate);
	PC4::setAlternateMode(Gpio::options::altModes::alt7);

	PC5::enableAsDigital();
	PC5::setMode(Gpio::options::mode::alternate);
	PC5::setAlternateMode(Gpio::options::altModes::alt6);

	PC6::enableAsDigital();
	PC6::setMode(Gpio::options::mode::alternate);
	PC6::setAlternateMode(Gpio::options::altModes::alt6);

	qei1::enableClock();
	qei1::config(qei::options::stallOnDebugger::stall,
				 qei::options::velocityPredivider::div_1,
				 qei::options::capVelocity::captureVel,
				 qei::options::captureMode::mode2);
	qei1::setTimer(4000000);// set the timer to 50 ms
	qei1::enableQEI();

	pwmW_0A::enableClock();
	pwmW_0A::config(50,0.1);

	// Configurando el UART0
	UART0::enableClock();
	UART0::configUart(uart::configOptions::baudrate::baud_1000000);

	core::IntEnableMaster();
	core::enableInterrupt(core::interrupts::uart0);

	while(1)
	{
//		countReg = qei1::getCount();
//		speedReg = qei1::getSpeedReg();

//		pwmW_0A::setDuty(duty);

		PF2::toogle();
		delays::delay_ms(250);
	}

}


void interruptFuncs::uart0rxtx_isr()
{
	UART0::clearInterrupts(uart::configOptions::interrupts::receiveInt);

	u8 foo = UART0::receiveByte();
	if ( foo == 's' )
	{

		u16 x1_u16 = qei1::getSpeedReg();

		// PID Controller *****************
		x = (float)x1_u16;
		e_t = ref - x;

		ep = e_t;
		ei += (e_t_1 + e_t) * 0.5 * DELTA_STEP;

		u = kp * ep + ki * ei;

		e_t_1 = e_t;
		// ********************************

		duty = u;

		duty = ( duty > 0.99 ) ? 0.99 : duty;
		duty = ( duty < 0.01 ) ? 0.01 : duty;

		pwmW_0A::setDuty(duty);

		// Extrayendo el MSB del x1_u16
		buffTx[0] = ( x1_u16 & 0xff00 ) >> 8;
		// Extrayendo el LSB del x1_u16
		buffTx[1] = ( x1_u16 & 0x00ff ) >> 0;


		int i = 0;
		for (i = 0; i < 2; i++) {
			UART0::sendByte( buffTx[i] );
		}
	}
}
