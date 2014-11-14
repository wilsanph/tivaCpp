#include "tivaCppLibrary/include/Gpio.hpp"
#include "tivaCppLibrary/include/clock.hpp"
#include "tivaCppLibrary/delays.hpp"

#include "tivaCppLibrary/include/Uart.h"// funcionalidad para los módulos UARTx
#include "tivaCppLibrary/include/Core.hpp"// funciones para habilitar las interrupciones
#include "tivaCppLibrary/interrupts.hpp"// prototipos de interrupción ya mapeados

#include "math.h"

// Array para guardar los bytes a transmitir
u8 buffTx[6] = {0,0,0,0,0,0};

float simTime = 0;

#define HOST_DT 0.025

double x1 = 0;
double x2 = 0;
double x3 = 0;

int main()
{
	clock::clock::config(clock::configOptions::clockSource::mainOscilator,
						 clock::configOptions::clockRate::clock_80Mhz);

	Gpio::enableClock(Gpio::peripheral::GPIOF);
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

	// Configurando el UART0
	UART0::enableClock();
	UART0::configUart(uart::configOptions::baudrate::baud_1000000);

	core::IntEnableMaster();
	core::enableInterrupt(core::interrupts::uart0);

	while(1)
	{
		// Blink blue led
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
		simTime += HOST_DT;

		x1 = 0.5 + 0.5 * std::cos(simTime);
		x2 = 0.5 + 0.5 * std::sin(simTime);
		x3 = 0.5 + 0.5 * std::cos(simTime/2.0);

		x1 = (x1 > 0.99) ? 0.99 : x1;
		x1 = (x1 < 0.01) ? 0.01 : x1;

		x2 = (x2 > 0.99) ? 0.99 : x2;
		x2 = (x2 < 0.01) ? 0.01 : x2;

		x3 = (x3 > 0.99) ? 0.99 : x3;
		x3 = (x3 < 0.01) ? 0.01 : x3;

		u16 x1_u16 = (u16)( x1 * 4095.0 );
		u16 x2_u16 = (u16)( x2 * 4095.0 );
		u16 x3_u16 = (u16)( x3 * 4095.0 );

		// Extrayendo el MSB del x1_u16
		buffTx[0] = ( x1_u16 & 0xff00 ) >> 8;
		// Extrayendo el LSB del x1_u16
		buffTx[1] = ( x1_u16 & 0x00ff ) >> 0;

		// Extrayendo el MSB del x2_u16
		buffTx[2] = ( x2_u16 & 0xff00 ) >> 8;
		// Extrayendo el LSB del x2_u16
		buffTx[3] = ( x2_u16 & 0x00ff ) >> 0;

		// Extrayendo el MSB del x3_u16
		buffTx[4] = ( x3_u16 & 0xff00 ) >> 8;
		// Extrayendo el LSB del x3_u16
		buffTx[5] = ( x3_u16 & 0x00ff ) >> 0;

		int i = 0;
		for (i = 0; i < 6; i++) {
			UART0::sendByte( buffTx[i] );
		}
	}
}
