/*******************************************************************
*
*  DESCRIPTION: Atomic Model LaundryCleaning
*
*  AUTHOR: Mike Lepard
*
*  EMAIL:
*
*  DATE: 24/10/2009
*
*******************************************************************/

/** include files **/
#include "laundryCleaning.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: LaundryCleaning
* Description:
********************************************************************/
LaundryCleaning::LaundryCleaning( const string &name )
: Atomic( name )
, dirty( addInputPort( "dirty" ) )
, clean( addOutputPort( "clean" ) )
, cleaningTime( 0, 1, 0, 0 )
, amountDirty( 0 )
, cleaningLoad( 500 )
, currentCleaning( 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "cleaningTime" ) ) ;

	if( time != "" )
		cleaningTime = time ;

	if( MainSimulator::Instance().existsParameter( description(), "amountDirty" ) )
	{
		amountDirty = str2Int( MainSimulator::Instance().getParameter( description(), "amountDirty" ) );
	}

	if( MainSimulator::Instance().existsParameter( description(), "cleaningLoad" ) )
	{
		cleaningLoad = str2Int( MainSimulator::Instance().getParameter( description(), "cleaningLoad" ) );
	}
}

/*******************************************************************
* Function Name: initFunction
* Description:
* Precondition:
********************************************************************/
Model &LaundryCleaning::initFunction()
{
	if( amountDirty == 0 )
	{
		//we have no dirty laundry, passivate
		this-> passivate();
	}
	else
	{
		if( amountDirty < cleaningLoad )
		{
			currentCleaning = amountDirty;
			amountDirty = 0;
		}
		else
		{
			currentCleaning = cleaningLoad;
			amountDirty -= cleaningLoad;
		}
		holdIn( active, cleaningTime );
	}
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &LaundryCleaning::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == dirty )
	{
		amountDirty += static_cast<int>(msg.value());
		if( state() == passive )
		{
			//we had no laundry and were in passive phase, activate!
			if( amountDirty < cleaningLoad )
			{
				currentCleaning = amountDirty;
				amountDirty = 0;
			}
			else
			{
				currentCleaning = cleaningLoad;
				amountDirty -= currentCleaning;
			}
			holdIn( active, cleaningTime );
		}
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &LaundryCleaning::internalFunction( const InternalMessage & )
{
	if( amountDirty == 0 )
	{
		passivate();
	}
	else if( amountDirty > cleaningLoad )
	{
		amountDirty -= cleaningLoad;
		currentCleaning = cleaningLoad;
		holdIn( active, cleaningTime );
	}
	else
	{
		currentCleaning = amountDirty;
		amountDirty = 0;
		holdIn( active, cleaningTime );
	}
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &LaundryCleaning::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), clean, currentCleaning );
	return *this ;
}
