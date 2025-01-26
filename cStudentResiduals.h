#pragma once 
#ifndef _CSTUDENTRESIDUALS_H_
#define _CSTUDENTRESIDUALS_H_

#include <gsl/gsl_sf_gamma.h>
#include <gsl/gsl_sf_psi.h>
#include "cAbstResiduals.h"
#include "cRegArchValue.h"

/*!
 \file cStudentResiduals.h
 \brief Definition of the class for Student conditional distribution.

 \author Jean-Baptiste DURAND, Ollivier TARAMASCO
 \date dec-18-2006 - Last change feb-18-2011
*/


namespace RegArchLib {

	/*! 
	 * \class cStudentResiduals
	 * \brief  Class to implement a Student distribution with unitary variance for residuals
	 */
	class cStudentResiduals: public cAbstResiduals
	{
	public :
		cStudentResiduals(double theDof, bool theSimulFlag=true) ; ///< A constructor
		cStudentResiduals(cDVector* theDistrParameter=NULL, bool theSimulFlag=true) ;	///< A constructor
		cStudentResiduals(const cStudentResiduals& theSrc);
		virtual ~cStudentResiduals() ; ///< A simple destructor
		//cAbstResiduals* PtrCopy() const ; /// < Return a copy of *this
	#ifdef _RDLL_
		void Print(void);
	#else
		void Print(ostream& theOut) const; ///< Print the distribution type
	#endif // _RDLL_
		void SetDefaultInitPoint(void) ;
		void Generate(const uint theNSample, cDVector& theYt) const; ///< Draw a sample from residual distribution 
		double LogDensity(double theX) const ;
		uint GetNParam(void) const ;
	};
}
#endif //_CSTUDENTRESIDUALS_H_

