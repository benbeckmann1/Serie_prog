#pragma once 
#ifndef _CABSTRESIDUALS_H_
#define _CABSTRESIDUALS_H_
/*!
	\file cAbstResiduals.h
	\brief Definition of the abstract class to implement a distribution for residuals
	
	\author Jean-Baptiste DURAND, Ollivier TARAMASCO 
	\date dec-18-2006 - last change feb-18-2011
*/

#include "RegArchDef.h"
#include <gsl/gsl_randist.h>
#include <ctime>
#include <cmath>
#include "cRegArchValue.h"
#include "cRegArchGradient.h"

namespace RegArchLib {

	/*! 
	 * \class cAbstResiduals
	 * \brief Abstract class to implement a conditional distribution model
	 */
	class cAbstResiduals
	{
	private :
		eDistrTypeEnum	mvDistr	; ///< Code for distribution type
	protected :
		gsl_rng* mtR ; ///< random generator
	public :
		cDVector *mDistrParameter ; ///< Parameters of the distribution (if any)
	public :
	
		cAbstResiduals(eDistrTypeEnum theDistr, cDVector* theDistrParam=NULL, bool theSimulFlag=false) ; ///< A simple constructor
		virtual ~cAbstResiduals() ; ///< A simple destructor
		void Delete(void) ; ///< Delete
		eDistrTypeEnum GetDistrType(void) const ; ///< Return the distribution type
		void SetSimul(void) ; ///< Change for simulation
		bool IsForSimul(void) { return (mtR != NULL); };
		double Get(const uint theIndex=0) ;
		void ReAlloc(uint theSize);
		void Set(double theValue, const uint theIndex=0) ;
	#ifndef _RDLL_
		virtual void Print(ostream& theOut = cout) const=0; ///< print the parameters
		friend ostream& operator <<(ostream& theOut, const cAbstResiduals& theAbstResisuals); ///< Print the distribution type
	#else
		virtual void Print(void)=0;
	#endif //_RDLL_
		virtual void Generate(const uint theNSample, cDVector& theYt) const=0; ///< Draw a sample from residual distribution 
		virtual double LogDensity(double theX) const=0 ; ///< log density function
		virtual uint GetNParam(void) const = 0 ;
		virtual double DiffLogDensity(double theX) const = 0;
		virtual void RegArchParamToVector(cDVector & theDestVect, uint theIndex) const = 0;
		virtual void VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex = 0) = 0;
		virtual void ComputeGrad(uint theDate, const cRegArchValue& theData, cRegArchGradient& theGradData) const = 0;

	};
	cAbstResiduals* CreateRealCondResiduals(const eDistrTypeEnum theType, cDVector* theDistrParam=NULL, bool theSimulFlag=true);
	cAbstResiduals* CreateRealCondResiduals(cAbstResiduals& theAbstCondResiduals);
}
#endif //_CABSTRESIDUALS_H_

