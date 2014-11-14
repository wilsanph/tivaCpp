/*
 * Servo.h
 *
 *  Created on: Aug 9, 2014
 *      Author: wilsan
 */

#ifndef SERVO_HPP_
#define SERVO_HPP_

#pragma once

#include "../../include/Gptimer.hpp"
#include "../../include/Gpio.hpp"


namespace Servo {

	template<Gpio::Port::_Port pwmPort,
			 Gpio::Pin::_Pin pwmPin,
			 gpTimer::gpTimerModule pwmTimer,
			 gpTimer::subTimers::subtimer pwmSubtimer>
	class Servo {

		private:

			float m_duty;
			u32 m_period_us;
			u32 m_minStep_us;
			u32 m_maxStep_us;
			u32 m_deltaStep_us;

		public:

			float angle;
			float minAngle;
			float maxAngle;
			float deltaAngle;

			void initPins();
			void config( u32 period_us,
						 u32 minStep_us, u32 maxStep_us,
						 float minAngle, float maxAngle);
			void setAngle(float angle);

	};

} /* namespace Servo */

#include "ServoImplement.hpp"

#endif /* SERVO_HPP_ */
