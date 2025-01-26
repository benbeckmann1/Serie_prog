#include "StdAfxRegArchLib.h"
/*!
 \file cStudentResiduals.cpp
 \brief implementation of the class for Student conditional distribution.

 \author Jean-Baptiste DURAND, Ollivier TARAMASCO
 \date dec-18-2006 - Last change apr-7-2019
*/
namespace RegArchLib {
	/*!
	 * \fn cStudentResiduals::cStudentResiduals(double theDof, bool theSimulFlag)
	 * \param double theDof: number of degrees of freedom 
	 * \param bool theSimulFlag: true if created for simulation
	 * \details: mvBool is initialised by ce cAbstResiduals constructor
	 */
	cStudentResiduals::cStudentResiduals(double theDof, bool theSimulFlag): cAbstResiduals(eStudent, NULL, theSimulFlag)
	{
        mDistrParameter = new cDVector(1) ;
        (*mDistrParameter)[0] = theDof ;
        if(theSimulFlag)
        {
            gsl_rng_env_setup() ;
            mtR = gsl_rng_alloc(gsl_rng_default) ;
        }
        else
            mtR = NULL;
	}

	/*!
	 * \fn cStudentResiduals::cStudentResiduals(const cDVector* theDistrParameter, bool theSimulFlag): cAbstResiduals(eStudent, theDistrParameter, theSimulFlag)
	 * \param const cDVector* theDistrParameter: theDistrParameter[0] = d.o.f.
	 * \param bool theSimulFlag: true if created for simulation
	 * \details: mvBool is initialised by ce cAbstResiduals constructor
	 */
	cStudentResiduals::cStudentResiduals(cDVector* theDistrParameter, bool theSimulFlag): cAbstResiduals(eStudent, theDistrParameter, theSimulFlag)
	{
        if(theSimulFlag)
        {
            gsl_rng_env_setup() ;
            mtR = gsl_rng_alloc(gsl_rng_default) ;
        }
        else
            mtR = NULL;

        if(theDistrParameter != NULL)
            mDistrParameter = new cDVector(*theDistrParameter);
        else
            mDistrParameter = NULL;
	}

	cStudentResiduals::cStudentResiduals(const cStudentResiduals& theSrc) : cAbstResiduals(eStudent, theSrc.mDistrParameter, (theSrc.mtR != NULL))
	{
        if(theSrc.mDistrParameter != NULL)
            mDistrParameter = new cDVector(*theSrc.mDistrParameter);
        else
            mDistrParameter = NULL;
	}

	/*!
	 * \fn cStudentResiduals::~cStudentResiduals()
	 */
	cStudentResiduals::~cStudentResiduals()
	{
	}

	/*!
	 * \fn void cStudentResiduals::Generate(const uint theNSample, cDVector& theYt) const
	 * \param const uint theNSample: the sample size
	 * \param cDVector& theYt: the output vector
	 */
	void cStudentResiduals::Generate(const uint theNSample, cDVector& theYt) const
    {
        if(mDistrParameter == NULL)
            throw cError("cStudentResiduals::Generate: parameter not set") ;

        theYt.ReAlloc(theNSample);
        double k = (*mDistrParameter)[0];
        if(k > 2) {
            for (uint t = 0; t < theNSample; t++)
                theYt[t] = gsl_ran_tdist(mtR, k) / (k / (k - 2));
        }
	}

	/*!
	 * \fn void cStudentResiduals::Print(ostream& theOut) const
	 * \param ostream& theOut: the output stream, default cout.
	 */
#ifndef _RDLL_
	void cStudentResiduals::Print(ostream& theOut) const
	{
		theOut << "Conditional Student Distribution with " << (*mDistrParameter)[0] << " d. o. f." << endl ;
	}
#endif // _RDLL_

	double cStudentResiduals::LogDensity(double theX) const
	{
        if (mDistrParameter == NULL)
            throw cError("No parameter for Student residuals") ;
        double k = (*mDistrParameter)[0];
        return - (log(k * M_PI)) / 2.0 + gsl_sf_lngamma((k + 1) / 2.0) - gsl_sf_lngamma(k/2.0) - (k + 1) / 2.0 * log(1 + theX * theX / k);
	}

	/*!
	 * \fn double cStudentResiduals::GetNParam(void) const
	 * \param void.
	 * \brief return 1: One parameter for St(n) residuals.
	 */
	uint cStudentResiduals::GetNParam(void) const
	{
        return 1 ;
	}


}//namespace
