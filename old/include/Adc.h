/*
 * Adc.h
 *
 *  Created on: 29/07/2013
 *      Author: wilbert
 */

#pragma once

#include "../memorymap/MapADC.h"


namespace adc
{

	namespace converter
	{
		enum _converter
		{
			adc0 = 0x40038000,
			adc1 = 0x40039000
		};
	}
	namespace sequencer
	{
		enum _sequencer
		{
			sequencer0 = 1,
			sequencer1 = 2,
			sequencer2 = 4,
			sequencer3 = 8
		};

	}
	namespace configOptions
	{
		namespace trigger
		{
			enum _trigger
			{
				software 	= 0x00,
				analogComp0 = 0x01,
				analogComp1 = 0x02,
				extGpio     = 0x04,
				timer	    = 0x05,
				continuous  = 0x0f
			};
		}

		namespace sample
		{
			enum _sample
			{
				sample_1st = 0,
				sample_2nd = 4,
				sample_3rd = 8,
				sample_4th = 12,
				sample_5th = 16,
				sample_6th = 20,
				sample_7th = 24,
				sample_8th = 28
			};
		}


		namespace inputpin
		{
			enum _inputpin
			{
				ain0  = 0,
				ain1  = 1,
				ain2  = 2,
				ain3  = 3,
				ain4  = 4,
				ain5  = 5,
				ain6  = 6,
				ain7  = 7,
				ain8  = 8,
				ain9  = 9,
				ain10 = 10,
				ain11 = 11
			};
		}
		namespace tempsensor
		{
			enum _tempsensor
			{
				selectTempSensor  = 8,
				ommitTempSensor   = 0
			};
		}
		namespace interruptEnable
		{
			enum _interruptEnable
			{
				sampleIntEnable   = 4,
				sampleIntDisabled = 0
			};
		}
		namespace endOfSequence
		{
			enum _endOfSequence
			{
				isEndOfSample   = 2,
				isntEndOfSample = 0
			};
		}
		namespace differentialMode
		{
			enum _differentialMode
			{
				selectDiffMode = 1,
				ommitDiffMode  = 0
			};
		}

		namespace sampleRate
		{
			enum _sampleRate{
				sample_125ksps  = 0x1,
				sample_250ksps  = 0x3,
				sample_500ksps  = 0x5,
				sample_1msps	= 0x7
			};
		}
	}


	inline void setSampleRate(converter::_converter converter_,configOptions::sampleRate::_sampleRate sampleRate_);
	inline void enableClock(converter::_converter converter_);

	template<adc::converter::_converter converter_,adc::sequencer::_sequencer sequencer_>
	class adcMod
	{

		public:

			static inline void disableSequencer();
			static inline void enableSequencer();
			static inline void selectTrigger(configOptions::trigger::_trigger trigger_);
			static inline void sampleConfigure(configOptions::sample::_sample sample_,
											   configOptions::inputpin::_inputpin inputpin_,
											   configOptions::tempsensor::_tempsensor tempsensor_,
											   configOptions::interruptEnable::_interruptEnable intEnable_,
											   configOptions::endOfSequence::_endOfSequence endOfSequence_,
											   configOptions::differentialMode::_differentialMode diffMode_);
			static inline void softBeginSampling();
			static inline bool finishedSampling();
			static inline void clearInterrupt();
			static inline void takeData(unsigned short *buff);
	};


}

typedef adc::adcMod<adc::converter::adc0,adc::sequencer::sequencer0> adc0seq0;
typedef adc::adcMod<adc::converter::adc0,adc::sequencer::sequencer1> adc0seq1;
typedef adc::adcMod<adc::converter::adc0,adc::sequencer::sequencer2> adc0seq2;
typedef adc::adcMod<adc::converter::adc0,adc::sequencer::sequencer3> adc0seq3;

typedef adc::adcMod<adc::converter::adc1,adc::sequencer::sequencer0> adc1seq0;
typedef adc::adcMod<adc::converter::adc1,adc::sequencer::sequencer1> adc1seq1;
typedef adc::adcMod<adc::converter::adc1,adc::sequencer::sequencer2> adc1seq2;
typedef adc::adcMod<adc::converter::adc1,adc::sequencer::sequencer3> adc1seq3;

#include "../src/ADCimplement.hpp"
