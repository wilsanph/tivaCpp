#include "tivaCppLibrary/include/Gpio.hpp"
#include "tivaCppLibrary/include/clock.hpp"
#include "tivaCppLibrary/delays.hpp"

#include "tivaCppLibrary/include/Gptimer.hpp"

#include "tivaCppLibrary/include/Uart.h"
#include "tivaCppLibrary/interrupts.hpp"
#include "tivaCppLibrary/include/Core.hpp"

#include "tivaCppLibrary/devLibraries/QEI.hpp"


float duty = 0.2;
float rpm = 0;

#define BUFF_RX_SIZE 6
#define BUFF_TX_SIZE 11
u8 buffRx[BUFF_RX_SIZE] = {0,0,0,0,0,0};
u8 buffTx[BUFF_TX_SIZE] = {0,0,0,0,0,0,0,0,0,0,0};
u8 rxCount = 0;
u8 errorMsg[BUFF_TX_SIZE] = {'s','e',0,0,0,0,0,0,0,0,0};
u8 acknowledgMsg[BUFF_TX_SIZE] = {'s','o',0,0,0,0,0,0,0,0,0};

#define CODE_START 's'
#define CODE_ERROR 'e'

#define CODE_READ_ENCODER 'q'
#define CODE_READ_SPEED 'r'
#define CODE_READ_ALL 'a'

#define CODE_SET_SPEED 'w'
#define CODE_SET_DIRECTION 'd'

union qeiReg
{
	u32 value;
	u8 bytes[4];
};

struct qeiData{
	qeiReg speedReg;
	qeiReg countReg;
};

qeiData encData;

u8 direction = 0;

enum State
{
	ST_IDLE = 0,
	ST_RECEIVING = 1,
	ST_TRANSMITTING = 2
};

State controllerState = ST_IDLE;

void reset();
void gotoState( State state );
bool processRxData();
void sendPacket( u8* buff, u8 len );

namespace responseFunctions
{
	void readEncoder();
	void readSpeed();
	void readAll();

	void setSpeed( u8 value );
	void setDirection( u8 dir );
}

int main()
{
	clock::clock::config( clock::configOptions::clockSource::mainOscilator,
						  clock::configOptions::clockRate::clock_80Mhz );

	Gpio::enableClock( Gpio::peripheral::GPIOF );
	Gpio::enableClock( Gpio::peripheral::GPIOC );
	Gpio::enableClock( Gpio::peripheral::GPIOA );
	Gpio::enableClock( Gpio::peripheral::GPIOE );

	PF2::setMode(Gpio::options::mode::gpio);
	PF2::setIOmode(Gpio::options::IOmode::output);

	// ENABLE THE DIRECTION PIN ***************************************************
	PE3::setMode( Gpio::options::mode::gpio );
	PE3::setIOmode( Gpio::options::IOmode::output );
	// ****************************************************************************
	// ENABLE THE QEI MODULE 1 TO TAKE SPEED MEASUREMENT EVERY 100ms **************
	PC5::setMode( Gpio::options::mode::alternate );
	PC5::setAlternateMode( Gpio::options::altModes::alt6 );

	PC6::setMode( Gpio::options::mode::alternate );
	PC6::setAlternateMode( Gpio::options::altModes::alt6 );

	qei1::enableClock();
	qei1::config( qei::options::stallOnDebugger::dontStall,
				  qei::options::velocityPredivider::div_1,
				  qei::options::capVelocity::captureVel,
				  qei::options::captureMode::mode1 );
	qei1::setTimer( 8000000 );
	qei1::enableQEI();
	// ****************************************************************************
	// ENABLE THE PWM MODULE ******************************************************

	PC4::setMode( Gpio::options::mode::alternate );
	PC4::setAlternateMode( Gpio::options::altModes::alt7 );

	pwmW_0A::enableClock();
	pwmW_0A::config( 50, duty );

	// ****************************************************************************
	// ENABLE THE UART MODULE AND ITS INTERRUPTS **********************************

	PA0::setMode( Gpio::options::mode::alternate );
	PA0::setAlternateMode( Gpio::options::altModes::alt1 );

	PA1::setMode( Gpio::options::mode::alternate );
	PA1::setAlternateMode( Gpio::options::altModes::alt1 );

	UART0::enableClock();
	UART0::configUart( uart::configOptions::baudrate::baud_1000000 );

	core::IntEnableMaster();
	core::enableInterrupt( core::interrupts::uart0 );

	// ****************************************************************************

	while(1)
	{
		PF2::toogle();
		delays::delay_ms(250);
	}
}



void interruptFuncs::uart0rxtx_isr()
{
	gotoState( ST_RECEIVING );
	UART0::clearInterrupts( uart::configOptions::interrupts::receiveInt );
	buffRx[rxCount] = UART0::receiveByte();
	rxCount++;
	if ( rxCount >= BUFF_RX_SIZE )
	{
		// Has received an entire packet, then, process it
		rxCount = 0;
		processRxData();
		gotoState( ST_IDLE );
	}


}

bool processRxData()
{
	bool success = true;
	if ( buffRx[0] != CODE_START )
	{
		// An error occurred, send an error message
		success = false;
	}
	else
	{
		switch ( buffRx[1] )
		{

			case CODE_READ_ENCODER:
				responseFunctions::readEncoder();
			break;

			case CODE_READ_SPEED:
				responseFunctions::readSpeed();
			break;

			case CODE_READ_ALL:
				responseFunctions::readAll();
			break;

			case CODE_SET_DIRECTION:
				responseFunctions::setDirection( buffRx[2] );
			break;

			case CODE_SET_SPEED:
				responseFunctions::setSpeed( buffRx[2] );
			break;

			default:
				// An error occurred, send an error message
				success = false;
			break;
		}

		success = true;
	}
	if ( !success )
	{
		sendPacket( errorMsg, BUFF_TX_SIZE );
	}
	return success;
}

void sendPacket( u8 *bytes, u8 len )
{
	for (int i = 0; i < len; ++i)
	{
		UART0::sendByte( *bytes );
		bytes++;
	}
}

void responseFunctions::readEncoder()
{
	encData.countReg.value = qei1::getCount();
	buffTx[0] = CODE_START;
	buffTx[1] = CODE_READ_ENCODER;
	buffTx[2] = direction;
	for (int i = 0; i < 4; ++i)
	{
		buffTx[i+3] = encData.countReg.bytes[i];
	}
	for (int k = 0; k < 4; ++k)
	{
		buffTx[k+7] = 0;
	}
	sendPacket( buffTx, BUFF_TX_SIZE );
}

void responseFunctions::readSpeed()
{
	encData.speedReg.value = qei1::getSpeedReg();
	buffTx[0] = CODE_START;
	buffTx[1] = CODE_READ_SPEED;
	buffTx[2] = direction;
	for (int i = 0; i < 4; ++i)
	{
		buffTx[i+3] = encData.speedReg.bytes[i];
	}
	for (int k = 0; k < 4; ++k)
	{
		buffTx[k+7] = 0;
	}
	sendPacket( buffTx, BUFF_TX_SIZE );
}

void responseFunctions::readAll()
{
	encData.countReg.value = qei1::getCount();
	encData.speedReg.value = qei1::getSpeedReg();
	buffTx[0] = CODE_START;
	buffTx[1] = CODE_READ_ALL;
	buffTx[2] = direction;
	for (int i = 0; i < 4; ++i)
	{
		buffTx[i+3] = encData.countReg.bytes[i];
	}
	for (int k = 0; k < 4; ++k)
	{
		buffTx[k+7] = encData.speedReg.bytes[k];
	}
	sendPacket( buffTx, BUFF_TX_SIZE );
}

void responseFunctions::setSpeed( u8 value )
{
	duty = ( value / 255.0 );
	duty = ( value > 0.99 ) ? 0.99 : duty;
	pwmW_0A::setDuty( duty );
	sendPacket( acknowledgMsg, BUFF_TX_SIZE );
}

void responseFunctions::setDirection( u8 dir )
{
	if ( dir == '1' )
	{
		PE3::setLow();
	}
	else if ( dir == '2' )
	{
		PE3::setHigh();
	}
	sendPacket( acknowledgMsg, BUFF_TX_SIZE );
}

void gotoState( State state )
{
	if ( controllerState == state )
	{
		return;
	}
	controllerState = state;
	switch ( controllerState )
	{
		case ST_RECEIVING:

		break;

		case ST_TRANSMITTING:

		break;
	}
}



void reset()
{


}

/*
int main()
{

	GApplication app;

	GPWMmodule pwmModule;
	GUARTinterface comInterface;
	app.addEntity( pwmModule );
	app.addEntity( comInterface );

	app.init();

	app.run();


}





class GMotorModule : public GEntity
{

	void init()
	{
		this->addComponent();
	}
	void update( dt );

	void onInterrupt();
};



class GComModule : public GEntity
{
	void init();
	void update( dt );

	void onInterrupt();
};

for {interrupt} in {interrupts}
void interruptFuncs::{interrupt}() {
	app.onInterrupt({interrupt.id});
}


*/



