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
	cStudentResiduals::cStudentResiduals(double theDof, bool theSimulFlag)
	:cAbstResiduals(eStudent, NULL, theSimulFlag)
	{
		mDistrParameter=new cDVector(1, theDof);
	}
	/*!
	 * \fn cStudentResiduals::cStudentResiduals(const cDVector* theDistrParameter, bool theSimulFlag): cAbstResiduals(eStudent, theDistrParameter, theSimulFlag)
	 * \param const cDVector* theDistrParameter: theDistrParameter[0] = d.o.f.
	 * \param bool theSimulFlag: true if created for simulation
	 * \details: mvBool is initialised by ce cAbstResiduals constructor
	 */
	cStudentResiduals::cStudentResiduals(cDVector* theDistrParameter, bool theSimulFlag)
	:cAbstResiduals(eStudent, theDistrParameter, theSimulFlag)
	{
	}

	cStudentResiduals::cStudentResiduals(const cStudentResiduals& theSrc)
	:cAbstResiduals(eStudent, theSrc.mDistrParameter, (theSrc.mtR != NULL))
	{
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
		double myDof = (*mDistrParameter)[0];
		if (myDof <= 2)
			cError("cStudent: d.o.f must be > 2\n");
		double myStd = sqrt(myDof/(myDof-2)) ;
		theYt.ReAlloc(theNSample);
		for (uint t = 0 ; t < theNSample ; t++)
			theYt[t] = gsl_ran_tdist(mtR, myDof)/myStd;
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

    static double StudentLogDensity(double theX, double theDof)
    {
        return log(gsl_ran_tdist_pdf(theX, theDof));
    }

    static void StudentGradLogDensity(double theX, double theDof, cDVector& theGrad)
    {
        double myt2 = theX * theX;
        double myAux1 = myt2 + theDof;
        theGrad[0] = -(theDof + 1)*theX / myAux1;
        double myAux2 = log(myAux1) - gsl_sf_psi((theDof + 1) / 2.0) - log(theDof) + gsl_sf_psi(theDof / 2.0);
        theGrad[1] = -0.5*(myAux2 + (1 - myt2) / myAux1);
    }


	double cStudentResiduals::LogDensity(double theX) const
	{
		double myStd = sqrt((*mDistrParameter)[0] / ((*mDistrParameter)[0] - 2.0));
		return StudentLogDensity(theX * myStd, (*mDistrParameter)[0]) + log(myStd);
	}

	/*!
	 * \fn double cStudentResiduals::GetNParam(void) const
	 * \param void.
	 * \brief return 1: One parameter for St(n) residuals.
	 */
	uint cStudentResiduals::GetNParam(void) const
	{
        return 1;
	}

	double cStudentResiduals::DiffLogDensity(double theX) const
	{
		double myDof = (*mDistrParameter)[0];
		return -(myDof + 1) * theX / (theX * theX + myDof - 2.0);
	}

	/*!
	 * \fn static void GradLogDensity(double theX, cDVector& theGrad, cDVector& theDistrParam)
	 * \brief Compute the derivative of log density with respect to the random variable (theGrad[0]) \e and the gradient
	 * of log density with respect to the model parameters (other components in theGrad)
	 * \param theX double: value of the random variable
	 * \param theGrad cDVector&: concatenation of derivatives with respect to the random variable and the model parameters
	 * \param theDistrParam cDVector&: value of the distribution parameters
	 */
	static void GradLogDensity(double theX, cDVector& theGrad, const cDVector& theDistrParam, uint theBegIndex)
	{
		double	myDof = theDistrParam[0];
		double myt2 = theX * theX;
		double myAux1 = myt2 + myDof - 2;
		double myRes = -log(myAux1 / (myDof - 2)) / 2;
		myRes += (gsl_sf_psi((myDof + 1) / 2) - gsl_sf_psi(myDof / 2)) / 2;
		myRes += (myDof * myt2 - myDof + 2) / ((myDof - 2) * (myt2 + myDof - 2)) / 2;
		theGrad[theBegIndex] = myRes;
	}


	/*!
	 * \fn void cStudentResiduals::ComputeGrad(uint theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData)
	 * \brief Compute the derivative of log density with respect to the random variable (theGradData[0]) \e and the gradient
	 * of log density with respect to the model parameters (other components in theGradData)
	 * \param theDate uint: time at which gradient is computed
	 * \param theValue const cRegArchValue&: value of the random variable
	 * \param theGradData cRegArchGradient&: concatenation of derivatives with respect to the random variable and the model parameters
	 */
	void cStudentResiduals::ComputeGrad(uint theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData) const
	{
	}

	void cStudentResiduals::RegArchParamToVector(cDVector& theDestVect, uint theIndex) const
	{
        theDestVect[theIndex] = (*mDistrParameter)[0];
	}

	void cStudentResiduals::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
	{
        (*mDistrParameter)[0] = theSrcVect[theIndex];
	}



}//namespace
