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

#ifndef __LAUNDRYCLEANING_H
#define __LAUNDRYCLEANING_H

//#include <list>
#include "atomic.h"     // class Atomic

class LaundryCleaning : public Atomic
{
public:
	LaundryCleaning( const string &name = "LaundryCleaning" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &dirty;
	Port &clean;
	Time cleaningTime;
	int cleaningLoad;
	int amountDirty;
	int currentCleaning;


};	// class LaundryCleaning

// ** inline ** //
inline
string LaundryCleaning::className() const
{
	return "LaundryCleaning" ;
}

#endif   //__LAUNDRYCLEANING_H
