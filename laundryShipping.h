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

#ifndef __LAUNDRYSHIPPING_H
#define __LAUNDRYSHIPPING_H

//#include <list>
#include "atomic.h"     // class Atomic

class LaundryShipping : public Atomic
{
public:
	LaundryShipping( const string &name = "LaundryShipping" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &clean;
	Port &shipped;
	Port &shortAmount;	
	Time shippingTime;
	int shippingAmount;
	int amountClean;

};	// class LaundryShipping

// ** inline ** // 
inline
string LaundryShipping::className() const
{
	return "LaundryShipping" ;
}

#endif   //__LAUNDRYSHIPPING_H
