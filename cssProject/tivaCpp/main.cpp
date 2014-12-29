#include "tivaCppLibrary/include/clock.hpp"
#include "tivaCppLibrary/delays.hpp"

#include "tivaCpp/include/Gpio.hpp"

Gpio::Pin led( Gpio::port::GPIOPortF_APB, Gpio::pin::pin3 );

int main()
{
	clock::clock::config(clock::configOptions::clockSource::mainOscilator,
						 clock::configOptions::clockRate::clock_80Mhz);

	PORTF::enableClock( Gpio::peripheral::GPIOF );

	led.enableDigitalFunc();
	led.setMode( Gpio::config::mode::gpio );
	led.setIOMode( Gpio::config::ioMode::output );

	while(1)
	{

		led.toggle();
		delays::delay_ms(250);
	}

}
