#include "tivaCppLibrary/delays.hpp"

#include "tivaCpp/include/Clock.hpp"
#include "tivaCpp/include/Gpio.hpp"
#include "tivaCpp/include/Timer.hpp"

#include "tivaCppLibrary/interrupts.hpp"
#include "tivaCppLibrary/include/Core.hpp"

clock::Clock systemClock;

Gpio::Pin led( Gpio::port::GPIOPortF_APB, Gpio::pin::pin2 );
Gpio::Pin led2( Gpio::port::GPIOPortF_APB, Gpio::pin::pin3 );

GpTimer::Timer sTimer0( GpTimer::timerModule::TIMER0_WIDE,
						GpTimer::subtimer::SUBTIMER_A );

int main()
{

	systemClock.config( clock::config::clockSource::mainOscilator,
						clock::config::clockRate::clock_80Mhz );

	systemClock.enableGpioClock( clock::peripheral::gpio::GPIOF,
								 clock::config::gpioBusType::APBbus );

//	systemClock.enableSimpleTimerClock( clock::peripheral::timer::simpleTimer::TIMER0 );
	systemClock.enableWideTimerClock( clock::peripheral::timer::wideTimer::WTIMER0 );

	led.enableDigitalFunc();
	led.setMode( Gpio::config::mode::gpio );
	led.setIOMode( Gpio::config::ioMode::output );

	led2.enableDigitalFunc();
	led2.setMode( Gpio::config::mode::gpio );
	led2.setIOMode( Gpio::config::ioMode::output );

	sTimer0.disableTimer();
	sTimer0.config( 200000, 3 );
	sTimer0.enableTimer();

	core::IntEnableMaster();
	core::enableInterrupt( core::interrupts::timer0a_wide );

	led.setLow();

	while(1)
	{
//		led.toggle();
		//PF2_AHB::toggle();
		delays::delay_ms(250);
	}

}

void interruptFuncs::timer0WideA_isr()
{
	sTimer0.clearInterrupt( GpTimer::config::timerConfig::interruptFlag::timeoutSubA );

	led2.toggle();
}
