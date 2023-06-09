/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR:
*
*  STUDENT#:
*
*  EMAIL:
*
*  DATE: 24/10/2009
*
*******************************************************************/

#include "modeladm.h"
#include "mainsimu.h"
#include "hospital.h"        	// class Hospital
#include "laundryShipping.h"    // class LaundryShipping
#include "laundryCleaning.h"    // class LaundryCleaning

void MainSimulator::registerNewAtomics()
{

	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Hospital>(), "Hospital" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<LaundryShipping>(), "LaundryShipping" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<LaundryCleaning>(), "LaundryCleaning" ) ;  }

