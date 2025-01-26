#include "StdAfxRegArchLib.h"

/*!
 \file cNormResiduals.cpp
 \brief implementation of the class for N(0, 1) conditional distribution.

 \author Jean-Baptiste DURAND, Ollivier TARAMASCO
 \date dec-18-2006 - Last change feb-18-2011
*/
namespace RegArchLib {
	/*!
	 * \fn cNormResiduals::cNormResiduals(const cDVector* theDistrParameter, bool theSimulFlag):cAbstResiduals(eNormal, NULL, theSimulFlag)
	 * \param bool theSimulFlag: true if created for simulation
	 * \details: mvBool is initialised by cAbstResiduals constructor and theDistrParameter is never used.
	 */
	cNormResiduals::cNormResiduals(const cDVector* theDistrParameter, bool theSimulFlag):cAbstResiduals(eNormal, NULL, theSimulFlag)
	{

        if(theDistrParameter != NULL)
            mDistrParameter = new cDVector(*theDistrParameter);
        else
            mDistrParameter = NULL;
	}

	cNormResiduals::cNormResiduals(const cNormResiduals& theSrc) : cAbstResiduals(eNormal, NULL, (theSrc.mtR != NULL))
	{
        if(theSrc.mDistrParameter != NULL)
            mDistrParameter = new cDVector(*theSrc.mDistrParameter);
        else
            mDistrParameter = NULL;
	}
	/*!
	 * \fn cNormResiduals::~cNormResiduals
	 * \details: nothing to do here
	 */
	cNormResiduals::~cNormResiduals()
	{
	}

	/*!
	 * \fn void cNormResiduals::Print(ostream& theOut) const
	 * \param ostream& theOut: the output stream, default cout.
	 */
#ifndef _RDLL_
	void cNormResiduals::Print(ostream& theOut) const
	{
        theOut << "Conditional Normal distribution N(0,1)" << endl ;

	}
#endif // _RDLL_

	/*!
	 * \fn void cNormResiduals::Generate(const uint theNSample, cDVector& theYt) const 
	 * \brief Draw a sample of N(0, 1) residuals.
	 * \param const uint theNSample: the sample size.
	 * \param cDVector& theYt: output parameter
	 * \details: theYt is reallocated to size theNSample here.
	 */
	void cNormResiduals::Generate(const uint theNSample, cDVector& theYt) const 
	{
        theYt.ReAlloc(theNSample);
        for(uint i = 0 ; i < theNSample ; i++)
            theYt[i] = gsl_ran_ugaussian(mtR);
	}

	/*!
	 * \fn double cNormResiduals::LogDensity(double theX) const
	 * \param double theX: the point where density is computed.
	 * \brief Compute the log density of N(0, 1)
	 */
	double cNormResiduals::LogDensity(double theX) const
	{
        return -0.5 * (theX * theX) - LOG_SQRT_2_PI ;
	}

	/*!
	 * \fn double cNormResiduals::GetNParam(void)
	 * \param void.
	 * \brief return 0: no parameter for N(0,1) residuals.
	 */
	uint cNormResiduals::GetNParam(void) const
	{
		return 0 ;
	}

	/*!
	 * \fn static void GradLogDensity(double theX, cDVector& theGrad)
	 * \brief Compute the derivative of log density of a Gaussian distribution with respect to the random variable (theGrad[0])
	 * \e and the gradient of log density with respect to the model parameters (other components in theGrad)
	 * \param theX double: value of the random variable
	 * \param theGrad cDVector&: concatenation of derivatives with respect to the random variable and the model parameters
	 */
	static void GradLogDensity(double theX, cDVector& theGrad)
	{
		theGrad[0] = -theX ;
	}

	/*!
	* \fn cNormResiduals::DiffLogDensity(double theX) const
	* \brief Compute the derivative of log density of a Gaussian distribution with respect to the random variable 
	* \param theX double: value of the random variable
	*/

}//namespace
