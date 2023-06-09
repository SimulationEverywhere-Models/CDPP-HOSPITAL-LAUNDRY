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

#ifndef __HOSPITAL_H
#define __HOSPITAL_H

//#include <list>
#include "atomic.h"     // class Atomic

class Distribution;

class Hospital : public Atomic
{
public:
	Hospital( const string &name = "Hospital" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &clean;
	Port &dirty;
	Time shippingTime;
	Time cleanTime;
	int amountClean;
	int amountDirty;
	Distribution *dist;

	Distribution &distribution()
		{return *dist;}

};	// class Hospital

// ** inline ** //
inline
string Hospital::className() const
{
	return "Hospital" ;
}

#endif   //__HOSPITAL_H
