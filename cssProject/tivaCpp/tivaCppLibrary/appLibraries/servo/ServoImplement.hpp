/*
 * Servo.cpp
 *
 *  Created on: Aug 9, 2014
 *      Author: wilsan
 */

#include "Servo.hpp"

namespace Servo {

	template<Gpio::Port::_Port pwmPort,
			 Gpio::Pin::_Pin pwmPin,
			 gpTimer::gpTimerModule pwmTimer,
			 gpTimer::subTimers::subtimer pwmSubtimer>
	void Servo<pwmPort,pwmPin,pwmTimer,pwmSubtimer>::initPins()
	{
		Gpio::gpio<pwmPort,pwmPin>::enableAsDigital();
		Gpio::gpio<pwmPort,pwmPin>::setMode(Gpio::options::mode::alternate);
		// All pwmPins have (so far) alternate function 7
		Gpio::gpio<pwmPort,pwmPin>::setAlternateMode(Gpio::options::altModes::alt7);
	}


	template<Gpio::Port::_Port pwmPort,
			 Gpio::Pin::_Pin pwmPin,
			 gpTimer::gpTimerModule pwmTimer,
			 gpTimer::subTimers::subtimer pwmSubtimer>
	void Servo<pwmPort,pwmPin,pwmTimer,pwmSubtimer>::config(u32 period_us,
														    u32 minStep_us,
														    u32 maxStep_us,
														    float minAngle,
														    float maxAngle)
	{

		gpTimer::pwm<pwmTimer,pwmSubtimer>::enableClock();
		this->m_period_us = period_us;
		gpTimer::pwm<pwmTimer,pwmSubtimer>::config(period_us,
												   0,
												   gpTimer::options::pwmOptions::outputLevel::normal);
		this->m_duty = 0;
		this->m_minStep_us = minStep_us;
		this->m_maxStep_us = maxStep_us;
		this->m_deltaStep_us = maxStep_us - minStep_us;
		this->minAngle = minAngle;
		this->maxAngle = maxAngle;
		this->deltaAngle = maxAngle - minAngle;
	}

	template<Gpio::Port::_Port pwmPort,
			 Gpio::Pin::_Pin pwmPin,
			 gpTimer::gpTimerModule pwmTimer,
			 gpTimer::subTimers::subtimer pwmSubtimer>
	void Servo<pwmPort,pwmPin,pwmTimer,pwmSubtimer>::setAngle(float angle)
	{
		angle = (angle < this->minAngle) ? this->minAngle : angle;
		angle = (angle > this->maxAngle) ? this->maxAngle : angle;
		this->angle = angle;

		float percent = (angle - this->minAngle)/(this->deltaAngle);
		u32 ticks_us = this->m_minStep_us + this->m_deltaStep_us * percent;
		this->m_duty = ((float)ticks_us)/(this->m_period_us);
		gpTimer::pwm<pwmTimer,pwmSubtimer>::setDuty(this->m_duty);
	}


} /* namespace Servo */
