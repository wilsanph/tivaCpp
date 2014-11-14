/*
 * test1.hpp
 *
 *  Created on: 18/05/2014
 *      Author: Wilbert
 */
#include "tivaCppLibrary/include/Gpio.hpp"
#include "tivaCppLibrary/include/clock.hpp"
#include "tivaCppLibrary/include/Gptimer.hpp"
#include "tivaCppLibrary/delays.hpp"
#include "tivaCppLibrary/interrupts.hpp"
#include "tivaCppLibrary/include/Core.hpp"

#include "tivaCppLibrary/appLibraries/servo/Servo.hpp"

Servo::Servo<Gpio::Port::GPIOPortC_APB,
			 Gpio::Pin::pin4,
			 gpTimer::timer0_wide,
			 gpTimer::subTimers::subTimerA> servo1;


float angle;


int main()
{
	clock::clock::config(clock::configOptions::clockSource::mainOscilator,
						 clock::configOptions::clockRate::clock_80Mhz);


	Gpio::enableClock(Gpio::peripheral::GPIOF);
	Gpio::enableClock(Gpio::peripheral::GPIOC);


	PF2::enableAsDigital();
	PF2::setMode(Gpio::options::mode::gpio);
	PF2::setIOmode(Gpio::options::IOmode::output);

	servo1.initPins();
	servo1.config(20000,900,2100,0.0,180.0);

	while(1)
	{
		PF2::toogle();
		servo1.setAngle(angle);
		angle += 1;
		angle = (angle > 180) ? 0 : angle;
		delays::delay_ms(100);
	}
}

