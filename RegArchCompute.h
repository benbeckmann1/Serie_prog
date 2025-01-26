#pragma once 
#ifndef _REGARCHCOMPUTE_H_
#define _REGARCHCOMPUTE_H_

#include "StdAfxRegArchLib.h"

/*!
 \file RegArchCompute.h
 \brief Header for simulation / estimation of general RegArch models.

 \author Jean-Baptiste DURAND, Ollivier TARAMASCO
 \date dec-18-2006 - Last change feb-18-2011
*/
namespace RegArchLib {
	extern void RegArchSimul(const uint theNSample, const cRegArchModel& theModel, cDVector& theYt, cDMatrix* theXt=NULL, cDMatrix* theXvt=NULL) ; ///< Simulation of a general RegArch Model
	extern void RegArchSimul(const uint theNSample, const cRegArchModel& theModel, cRegArchValue& theData) ; ///< Simulation of a general RegArch Model
	extern void FillValue(uint theDate, const cRegArchModel& theModel, cRegArchValue& theValue);
	extern double RegArchLLH(const cRegArchModel& theModel, cDVector* theYt, cDMatrix* theXt=NULL) ; ///< Log-Likelihood of a general RegArch Model
	extern double RegArchLLH(const cRegArchModel& theModel, cRegArchValue& theData) ; ///< Log-Likelihood of a general RegArch Model
	extern void RegArchGradLt(int theDate, cRegArchModel& theModel, cRegArchValue& theData, cRegArchGradient& theGradData, cDVector& theGradlt);
	extern void RegArchGradLLH(cRegArchModel& theModel, cRegArchValue& theData, cDVector& theGradLLH);
}

#endif //_REGARCHCOMPUTE_H_
