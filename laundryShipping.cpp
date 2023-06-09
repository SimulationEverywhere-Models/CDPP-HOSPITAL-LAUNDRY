/*******************************************************************
*
*  DESCRIPTION: Atomic Model LaundryShipping
*
*  AUTHOR: Mike Lepard
*
*  EMAIL:
*
*  DATE: 24/10/2009
*
*******************************************************************/

/** include files **/
#include "laundryShipping.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: LaundryShipping
* Description:
********************************************************************/
LaundryShipping::LaundryShipping( const string &name )
: Atomic( name )
, clean( addInputPort( "clean" ) )
, shipped( addOutputPort( "shipped" ) )
, shortAmount( addOutputPort( "shortAmount" ) )
, shippingTime( 8, 0, 0, 0 )
, shippingAmount( 500 )
, amountClean( 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "shippingTime" ) ) ;

	if( time != "" )
		shippingTime = time ;

	if( MainSimulator::Instance().existsParameter( description(), "shippingAmount" ) )
	{
		shippingAmount = str2Int( MainSimulator::Instance().getParameter( description(), "shippingAmount" ) );
	}

	if( MainSimulator::Instance().existsParameter( description(), "amountClean" ) )
	{
		amountClean = str2Int( MainSimulator::Instance().getParameter( description(), "amountClean" ) );
	}
}

/*******************************************************************
* Function Name: initFunction
* Description:
* Precondition:
********************************************************************/
Model &LaundryShipping::initFunction()
{
	//we always need to be shipping laundry to the hospital
	holdIn( active, shippingTime );
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &LaundryShipping::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == clean )
	{
		amountClean += static_cast<int>(msg.value());
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &LaundryShipping::internalFunction( const InternalMessage &msg )
{
	if( amountClean > shippingAmount )
	{
		amountClean -= shippingAmount;
	}
	else
	{
		amountClean = 0;
	}

	Time oneDay( 24, 0, 0, 0 );
	holdIn( active, oneDay );
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &LaundryShipping::outputFunction( const InternalMessage &msg )
{
	if( amountClean < shippingAmount )
	{
		sendOutput( msg.time(), shipped, amountClean );
		sendOutput( msg.time(), shortAmount, shippingAmount - amountClean );
	}
	else
	{
		sendOutput( msg.time(), shipped, shippingAmount) ;
	}
	return *this ;
}
