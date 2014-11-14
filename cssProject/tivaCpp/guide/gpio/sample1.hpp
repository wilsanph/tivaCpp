// GPIO pointer configuration tutorial

#include "tivaCppLibrary/include/Gpio.hpp"
#include "tivaCppLibrary/include/clock.hpp"
#include "tivaCppLibrary/delays.hpp"


// Lets create a pointer that will point (sorry for redunding xD) to ...
// ... our GPIO regs
u32* regPointer;


void toogleLed()
{

}

int main()
{
	// clock configuration ( 80 Mhz - using main oscilator )
	// LETS JUST USE THE CLOCK API AS WE ARE ONLY CONCERNED WITH THE GPIO CONFIGURATION
	// FEEL FREE TO CHECK THE CLOCK API, THE WAY IS CONFIGURED ( THE IDEA :D ) IS VERY ...
	// ... SIMILAR TO THE GPIO CONFIGURATION WE SAW FOR THE GPIO.
	clock::clock::config( clock::configOptions::clockSource::mainOscilator,
						  clock::configOptions::clockRate::clock_80Mhz );


	// ENABLE THE APPROPIATE GPIO CLOCK PERIPHERAL
	// Change the register our pointer is pointing to to the ...
	// ... RCCGPIO register, located in the system control module
	regPointer = (u32*)(0x400FE000 + 0x608);// RCCGPIO register address
	// Enable the clock for the port F peripheral
	*regPointer |= (1<<5);
	// The similar API step for this would be ...
	// Gpio::enableClock( Gpio::peripheral::GPIOF );

	// SET THE GPIO PIN MODE (gpio or alternate)
	// Change the register our pointer is pointing to to the ...
	// ... GPIOAFSEL register, located in the GPIO module
	regPointer = (u32*)(0x40025000 + 0x420);
	// Set the mode of the PF2 pin to GPIO (not alternate)
	*regPointer |= (1<<2);
	// The similar API step for this would be ...
	// PF2::setMode(Gpio::options::mode::alternate);

	// SET THE GPIO DIR MODE (input or output)
	// Change the register our pointer is pointing to to the ...
	// ... GPIODIR register, located in the GPIO module
	regPointer = (u32*)(0x40025000 + 0x400);
	// Set the output mode of the PF2 pin to output
	*regPointer |= (1<<2);
	// The similar API st	ep for this would be ...
	//PF2::setIOmode(Gpio::options::IOmode::output);

	// Change the register our pointer is pointing to to the ...
	// ... GPIODATA register, located at offset 0x000 in the GPIO module.
	// Also, a mask is applied as an offset, as explained in the datasheet :D.
	regPointer = (u32*)(0x40025000 + 0x000 + (0x04 << 2));

	while(1)
	{
		// Toogle bit2.
		// Just bit2 is being toogled, as our pointer is configured to only ...
		// ... change the contents in this bit.
		*regPointer = (0xffffffff - *regPointer);
		//PF2::toogle();
		delays::delay_ms(250);
	}
}

