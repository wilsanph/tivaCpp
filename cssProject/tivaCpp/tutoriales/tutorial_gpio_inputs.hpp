#include "tivaCppLibrary/include/Gpio.hpp"
#include "tivaCppLibrary/include/clock.hpp"
#include "tivaCppLibrary/delays.hpp"



int main()
{
	// clock configuration ( 80 Mhz - using main oscilator )
	clock::clock::config( clock::configOptions::clockSource::mainOscilator,
						  clock::configOptions::clockRate::clock_80Mhz );

	// Enable clock for the desired peripheral
	Gpio::enableClock( Gpio::peripheral::GPIOF );

	PF2::enableAsDigital();
	PF2::setMode( Gpio::options::mode::gpio );
	PF2::setIOmode( Gpio::options::IOmode::output );

	PF3::enableAsDigital();
	PF3::setMode( Gpio::options::mode::gpio );
	PF3::setIOmode( Gpio::options::IOmode::output );

	PF4::enableAsDigital();
	PF4::setMode( Gpio::options::mode::gpio );
	PF4::setIOmode( Gpio::options::IOmode::input );
	PF4::setPullUp();



	while(1)
	{
		PF2::toogle();
		if ( PF4::isHigh() )
		{
			PF3::setHigh();
		}
		else{
			PF3::setLow();
		}
		delays::delay_ms( 500 );
	}
}
