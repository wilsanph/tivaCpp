#include "tivaCppLibrary/delays.hpp"

#include "tivaCpp/include/Clock.hpp"
#include "tivaCpp/include/Gpio.hpp"
#include "tivaCpp/include/Timer.hpp"

#include "tivaCppLibrary/interrupts.hpp"
#include "tivaCppLibrary/include/Core.hpp"
#include "tivaCpp/GProjectCore/GObjectContainer.hpp"
//#include <memory>

//std::auto_ptr<>

clock::Clock systemClock;

Gpio::Pin led( Gpio::port::GPIOPortF_APB, Gpio::pin::pin2 );

Gpio::Pin pwmOut( Gpio::port::GPIOPortC_APB, Gpio::pin::pin6 );

//GpTimer::Pwm sPwm( GpTimer::timerModule::TIMER1_WIDE,
//					GpTimer::subtimer::SUBTIMER_A );

float duty = 0.1;

gObject::GObjectContainer servo2;

int main()
{
	systemClock.config( clock::config::clockSource::mainOscilator,
						clock::config::clockRate::clock_80Mhz );

	systemClock.enableGpioClock( clock::peripheral::gpio::GPIOF,
								 clock::config::gpioBusType::APBbus );
	systemClock.enableGpioClock( clock::peripheral::gpio::GPIOC,
								 clock::config::gpioBusType::APBbus );

	systemClock.enableWideTimerClock( clock::peripheral::timer::wideTimer::WTIMER1 );

	led.enableDigitalFunc();
	led.setMode( Gpio::config::mode::gpio );
	led.setIOMode( Gpio::config::ioMode::output );

	pwmOut.enableDigitalFunc();
	pwmOut.setMode( Gpio::config::mode::alternate );
	pwmOut.setAlternateMode( Gpio::config::altModes::alt7 );

	gObject::GObjectContainer servo1( new GpTimer::Pwm( GpTimer::timerModule::TIMER1_WIDE,
						  	  	  	  	  	 	 	    GpTimer::subtimer::SUBTIMER_A ) );

	servo2.reset( new GpTimer::Pwm( GpTimer::timerModule::TIMER0_WIDE,
									GpTimer::subtimer::SUBTIMER_A ) );

	reinterpret_cast< GpTimer::Pwm* >(servo1.get())->configPWM( 20000,
														  duty,
														  GpTimer::config::pwmConfig::outputLevel::normal );

//	servo1->configPWM( 20000,
//					duty,
//					GpTimer::config::pwmConfig::outputLevel::normal );

//	sPwm.configPWM( 20000,
//					duty,
//					GpTimer::config::pwmConfig::outputLevel::normal );

	led.setLow();
//	GpTimer::Pwm* pt = new GpTimer::Pwm( GpTimer::timerModule::TIMER1_WIDE,
//					  	  	  	  	  	 GpTimer::subtimer::SUBTIMER_A );

//	std::auto_ptr<gObject::GObject> pt( new GpTimer::Pwm( GpTimer::timerModule::TIMER1_WIDE,
//						  	  	  	  	  	 	 	  GpTimer::subtimer::SUBTIMER_A ) );

//	gObject::GObjectContainer servo1( new GpTimer::Pwm( GpTimer::timerModule::TIMER1_WIDE,
//						  	  	  	  	  	 	 	  GpTimer::subtimer::SUBTIMER_A ) );

	while(1)
	{
		led.toggle();
//		sPwm.setDuty( duty );
//		reinterpret_cast< GpTimer::Pwm* >(servo1.get())->setDuty( duty );
		GCast( GpTimer::Pwm*, servo1 )->setDuty( duty );
		delays::delay_ms( 250 );
	}
}
