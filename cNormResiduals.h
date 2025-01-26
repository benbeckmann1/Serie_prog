#pragma once
#ifndef _CNORMRESIDUALS_H_
#define _CNORMRESIDUALS_H_
#include "cAbstResiduals.h"
#include "cRegArchValue.h"

/*!
 \file cNormResiduals.h
 \brief Definition of the class for N(0, 1) conditional distribution.

 \author Jean-Baptiste DURAND, Ollivier TARAMASCO
 \date dec-18-2006 - Last change feb-18-2011
*/

namespace RegArchLib {

	/*! 
	 * \class cNormResiduals
	 * \brief  Class to implement the N(0, 1) residuals
	 */

	class cNormResiduals: public cAbstResiduals
	{
	public :
		cNormResiduals(const cDVector* theDistrParameter=NULL, bool theSimulFlag=true) ; ///< a simple constructor
		cNormResiduals(const cNormResiduals& theSrc);
		virtual ~cNormResiduals() ; ///< a simple destructor
       // cAbstResiduals* PtrCopy() const ; /// < Return a copy of *this
	#ifndef _RDLL_
		void Print(ostream& theOut = cout) const; ///< print the parameters
	#else
		void Print(void);
	#endif //_RDLL_
		void Generate(const uint theNSample, cDVector& theYt) const ; ///< Draw a sample from residual distribution 
		double LogDensity(double theX) const ;
		uint GetNParam(void) const ;
	};

}

#endif //_CNORMRESIDUALS_H_

