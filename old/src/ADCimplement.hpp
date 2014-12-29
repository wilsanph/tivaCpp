/*
 * ADCimplement.hpp
 *
 *  Created on: Aug 24, 2013
 *      Author: wilbert
 */

#pragma once

#include "../include/Adc.h"
#include "../memorymap/MapADC.h"
#include "../memorymap/mapClock.hpp"


namespace adc
{
	void setSampleRate(adc::converter::_converter converter_,configOptions::sampleRate::_sampleRate sampleRate_)
	{
		reinterpret_cast<mapAdc::AdcRegs *>
			(converter_)->ADCPC = sampleRate_;
	}
	void enableClock(adc::converter::_converter converter_)
	{
		switch(converter_) {
			case adc::converter::adc0:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCADC |= (1<<0);
			break;
			case converter::adc1:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCADC |= (1<<1);
			break;
		}
	}

	template<adc::converter::_converter converter_,adc::sequencer::_sequencer sequencer_>
	void adc::adcMod<converter_,sequencer_>::disableSequencer()
	{
		reinterpret_cast<mapAdc::AdcRegs *>
			(converter_)->ADCACTSS &= (0x000f - sequencer_);
	}
	template<adc::converter::_converter converter_,adc::sequencer::_sequencer sequencer_>
	void adc::adcMod<converter_,sequencer_>::enableSequencer()
	{
		reinterpret_cast<mapAdc::AdcRegs *>
			(converter_)->ADCACTSS |= sequencer_;
	}
	template<adc::converter::_converter converter_,adc::sequencer::_sequencer sequencer_>
	void adc::adcMod<converter_,sequencer_>::selectTrigger(adc::configOptions::trigger::_trigger trigger_)
	{
		reinterpret_cast<mapAdc::AdcRegs *>
			(converter_)->ADCEMUX = trigger_;
	}
	template<adc::converter::_converter converter_,adc::sequencer::_sequencer sequencer_>
	void adc::adcMod<converter_,sequencer_>::sampleConfigure(configOptions::sample::_sample sample_,
														     configOptions::inputpin::_inputpin inputpin_,
														     configOptions::tempsensor::_tempsensor tempsensor_,
														     configOptions::interruptEnable::_interruptEnable intEnable_,
														     configOptions::endOfSequence::_endOfSequence endOfSequence_,
														     configOptions::differentialMode::_differentialMode diffMode_)
	{
		switch (sequencer_)
		{
			case sequencer::sequencer0 :
				reinterpret_cast<mapAdc::AdcRegs *>
					(converter_)->ADCSSMUX0 |= (inputpin_ << sample_);
				reinterpret_cast<mapAdc::AdcRegs *>
					(converter_)->ADCSSCTL0 |= ((tempsensor_|intEnable_|endOfSequence_|diffMode_) << sample_);
				break;
			case sequencer::sequencer1 :
				reinterpret_cast<mapAdc::AdcRegs *>
					(converter_)->ADCSSMUX1 |= (inputpin_ << sample_);
				reinterpret_cast<mapAdc::AdcRegs *>
					(converter_)->ADCSSCTL1 |= ((tempsensor_|intEnable_|endOfSequence_|diffMode_) << sample_);
				break;
			case sequencer::sequencer2 :
				reinterpret_cast<mapAdc::AdcRegs *>
					(converter_)->ADCSSMUX2 |= (inputpin_ << sample_);
				reinterpret_cast<mapAdc::AdcRegs *>
					(converter_)->ADCSSCTL2 |= ((tempsensor_|intEnable_|endOfSequence_|diffMode_) << sample_);
				break;
			case sequencer::sequencer3 :
				reinterpret_cast<mapAdc::AdcRegs *>
					(converter_)->ADCSSMUX3 |= (inputpin_ << sample_);
				reinterpret_cast<mapAdc::AdcRegs *>
					(converter_)->ADCSSCTL3 |= ((tempsensor_|intEnable_|endOfSequence_|diffMode_) << sample_);
				break;
			default:
				break;
		}
	}
	template<adc::converter::_converter converter_,adc::sequencer::_sequencer sequencer_>
	void adc::adcMod<converter_,sequencer_>::softBeginSampling()
	{
		reinterpret_cast<mapAdc::AdcRegs *>
			(converter_)->ADCPSSI |=sequencer_;
	}
	template<adc::converter::_converter converter_,adc::sequencer::_sequencer sequencer_>
	bool adc::adcMod<converter_,sequencer_>::finishedSampling()
	{
		if(((reinterpret_cast<mapAdc::AdcRegs *>(converter_)->ADCRIS)&(sequencer_))== sequencer_ )
		{
			return true;
		}
		return false;
	}
	template<adc::converter::_converter converter_,adc::sequencer::_sequencer sequencer_>
	void adc::adcMod<converter_,sequencer_>::clearInterrupt()
	{
		reinterpret_cast<mapAdc::AdcRegs *>
			(converter_)->ADCISC |=sequencer_;
	}
	template<adc::converter::_converter converter_,adc::sequencer::_sequencer sequencer_>
	void adc::adcMod<converter_,sequencer_>::takeData(unsigned short *buff)
	{
		switch(sequencer_)
		{
		case adc::sequencer::sequencer0 :
			while(!(((reinterpret_cast<mapAdc::AdcRegs *>(converter_)->ADCSSFSTAT0)&(0x0100))==(0x0100)))
			{
				*buff = reinterpret_cast<mapAdc::AdcRegs *>(converter_)->ADCSSFIFO0;
				buff++;
			}
			break;
		case adc::sequencer::sequencer1 :
			while(!(((reinterpret_cast<mapAdc::AdcRegs *>(converter_)->ADCSSFSTAT1)&(0x0100))==(0x0100)))
			{
				*buff = reinterpret_cast<mapAdc::AdcRegs *>(converter_)->ADCSSFIFO1;
				buff++;
			}
			break;
		case adc::sequencer::sequencer2 :
			while(!(((reinterpret_cast<mapAdc::AdcRegs *>(converter_)->ADCSSFSTAT2)&(0x0100))==(0x0100)))
			{
				*buff = reinterpret_cast<mapAdc::AdcRegs *>(converter_)->ADCSSFIFO2;
				buff++;
			}
			break;
		case adc::sequencer::sequencer3 :
			while(!(((reinterpret_cast<mapAdc::AdcRegs *>(converter_)->ADCSSFSTAT3)&(0x0100))==(0x0100)))
			{
				*buff = reinterpret_cast<mapAdc::AdcRegs *>(converter_)->ADCSSFIFO3;
				buff++;
			}
			break;
		default:
			break;
		}
	}


}
