/*******************************************************************
*
*  DESCRIPTION: Atomic Model Hospital
*
*  AUTHOR: Mike Lepard
*
*  EMAIL:
*
*  DATE: 24/10/2009
*
*******************************************************************/

/** include files **/
#include "hospital.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "distri.h"

/** public functions **/

/*******************************************************************
* Function Name: Hospital
* Description:
********************************************************************/
Hospital::Hospital( const string &name )
: Atomic( name )
, clean( addInputPort( "clean" ) )
, dirty( addOutputPort( "dirty" ) )
, shippingTime(16, 0, 0, 0)
, cleanTime(8, 0, 0, 0)
, amountDirty( 0 )
, amountClean( 0 )
{
	//What time (oclock) does the dirty laundry leave the hospital?
	string time( MainSimulator::Instance().getParameter( description(), "shippingTime" ) ) ;

	if( time != "" )
		shippingTime = time;

	//What time (oclock) does the clean laundry get distributed across the hospital?
	time = MainSimulator::Instance().getParameter( description(), "cleanTime" );

	if( time != "" )
		cleanTime = time;

	if( MainSimulator::Instance().existsParameter( description(), "amountClean" ) )
	{
		amountClean = str2Int( MainSimulator::Instance().getParameter( description(), "amountClean" ) );
	}

	if( MainSimulator::Instance().existsParameter( description(), "amountDirty" ) )
	{
		amountDirty = str2Int( MainSimulator::Instance().getParameter( description(), "amountDirty" ) );
	}

	try
	{
		dist = Distribution::create( MainSimulator::Instance().getParameter( description(), "distribution" ) );
		MASSERT( dist );

		for ( register int i = 0 ; i < dist->varCount() ; i++ )
		{
			string parameter( MainSimulator::Instance().getParameter( description(), dist->getVar(i) ) ) ;
			dist->setVar( i, str2float( parameter ) ) ;
		}
	}
	catch( InvalidDistribution &e )
	{
		e.addText( "The model " + description() + " has distribution problems!" ) ;
		e.print(cerr);
		MTHROW( e ) ;
	}
	catch( MException &e )
	{
		MTHROW( e ) ;
	}
}

/*******************************************************************
* Function Name: initFunction
* Description:
* Precondition:
********************************************************************/
Model &Hospital::initFunction()
{
	if( amountClean == 0  && amountDirty == 0 )
	{
		//we have no laundry to start with, passivate
		this-> passivate();
	}
	else
	{
		if( cleanTime < shippingTime )
		{
			holdIn( active, cleanTime );
		}
		else
		{
			holdIn( active, shippingTime );
		}
	}
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &Hospital::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == clean )
	{
		amountClean += static_cast<int>(msg.value());
		if( state() == passive )
		{
			//We were in passive state with no clean laundry
			//determine the time till our next clean laundry distribution time.
			Time currentClock = msg.time();
			currentClock.hours( currentClock.hours()%24 );
			if( currentClock.hours() > cleanTime.hours() )
			{
				//We have to wait till the next day to send out clean laundry
				Time oneDay( 24, 0, 0, 0);
				holdIn( active, oneDay - (currentClock - cleanTime) );
			}
			else
			{
				holdIn( active, cleanTime - currentClock );
			}
		}
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &Hospital::internalFunction( const InternalMessage &msg )
{
	Time currentClock = msg.time();
	currentClock.hours( currentClock.hours()%24 );
	if( currentClock == cleanTime )
	{
		int newDirtyAmount = static_cast<int>(distribution().get());
		if( amountClean < newDirtyAmount)
		{
			amountDirty += amountClean;
			amountClean = 0;
		}
		else
		{
			amountDirty += newDirtyAmount;
			amountClean -= newDirtyAmount;
		}
		if( currentClock.hours() > shippingTime.hours() )
		{
			//We have to wait till the next day to send out clean laundry
			Time oneDay( 24, 0, 0, 0);
			holdIn( active, oneDay - (currentClock - shippingTime) );
		}
		else
		{
			holdIn( active, shippingTime - currentClock );
		}
	}
	else if( currentClock == shippingTime )
	{
		//its shipping time, empty the dirty laundry
		amountDirty = 0;
		if( amountClean == 0 )
		{
			//if we have no clean laundry, go to passivate
			passivate();
		}
		else
		{
			//else we have clean laundry, schedule the next distribution of clean
			//laundry.
			if( currentClock.hours() > cleanTime.hours() )
			{
				//We have to wait till the next day to send out clean laundry
				Time oneDay( 24, 0, 0, 0);
				holdIn( active, oneDay - (currentClock - cleanTime) );
			}
			else
			{
				holdIn( active, cleanTime - currentClock );
			}
		}
	}
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &Hospital::outputFunction( const InternalMessage &msg )
{
	Time currentClock = msg.time();
	currentClock.hours( currentClock.hours()%24 );
	if( currentClock == shippingTime )
	{
		sendOutput( msg.time(), dirty, amountDirty) ;
	}
	return *this ;
}
