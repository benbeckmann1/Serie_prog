#include "StdAfxRegArchLib.h"
//#include <gsl/gsl_cdf.h>
/*!
	\file RegArchCompute.cpp
	\brief implementation of the Simulation / Estimation procedures for general RegArchModel
	
	\author Jean-Baptiste DURAND, Ollivier TARAMASCO 
	\date dec-18-2006 - last change feb-18-2011
*/


namespace RegArchLib {
	using namespace VectorAndMatrixNameSpace;


	/*!
	 * \fn void RegArchSimul(const uint theNSample, const cRegArchModel& theModel, cRegArchValue& theData)
	 * \param const uint theNSample: size of the sample
	 * \param const cRegArchModel& theModel: the RegArch model
	 * \param cRegArchValue& theData: output parameter. The Y(t) values are stored in theData.mYt
	 */
	void RegArchSimul(const uint theNSample, const cRegArchModel& theModel, cRegArchValue& theData)
	{
        theData.ReAlloc(theNSample);
        if(!theModel.mResids->IsForSimul())
        {
            theModel.mResids->SetSimul();
        }
        theModel.mResids->Generate(theNSample, theData.mEpst);

        for(uint t = 0; t < theNSample; t++)
        {
            theData.mHt[t] = theModel.mVar->ComputeVar(t, theData);
            theData.mMt[t] = theModel.mMean->ComputeMean(t, theData);
            theData.mUt[t] = sqrt(theData.mHt[t]) * theData.mEpst[t];
            theData.mYt[t] = theData.mMt[t] + theData.mUt[t];
        }

    }

   /*!
	 * \fn void RegArchSimul(const uint theNSample, const cRegArchModel& theModel, cDVector& theYt)
	 * \param const uint theNSample: size of the sample
	 * \param const cRegArchModel& theModel: the RegArch model
	 * \param cDVector& theYt: output parameter. 
	 */
	void RegArchSimul(const uint theNSample, const cRegArchModel& theModel, cDVector& theYt, cDMatrix* theXt, cDMatrix* theXvt)
	{
        cRegArchValue myValue = cRegArchValue(theNSample, theXt, theXvt);
        RegArchSimul(theNSample, theModel, myValue);
        theYt = myValue.mYt;
	}

	void FillValue(uint theDate, const cRegArchModel& theModel, cRegArchValue& theValue)
	{
        theValue.mHt[theDate] = theModel.mVar->ComputeVar(theDate, theValue);
        if(theModel.mMean->GetNMean() > 0)
        {
            theValue.mMt[theDate] = theModel.mMean->ComputeMean(theDate, theValue);
        }
        theValue.mUt[theDate] = theValue.mYt[theDate] - theValue.mMt[theDate];
        theValue.mEpst[theDate] = theValue.mUt[theDate] / sqrt(theValue.mHt[theDate]);
	}

    /*
     * ComputeLt
     */
    double ComputeLt(const cRegArchModel& theModel, uint theDate, cRegArchValue& theValue)
    {
        FillValue(theDate, theModel, theValue);
        return -0.5 * log(theValue.mHt[theDate]) - theModel.mResids->LogDensity(theValue.mEpst[theDate]);
    }
  	/*!
	 * \fn double RegArchLLH(const cRegArchModel& theModel, cDVector* theYt, cDMatrix* theXt)
	 * \param const cRegArchModel& theModel: the model
	 * \param cDVector* theYt: the observations
	 * \param cDMatrix* theXt: the regressors matrix. Default NULL
	 * \brief return the log-likelihood value
	 */
	double RegArchLLH(const cRegArchModel& theModel, cDVector* theYt, cDMatrix* theXt)
	{
        double myRes = 0;
        cRegArchValue myValue = cRegArchValue(theYt, theXt);
        for(uint t = theModel.GetNLags(); t < myValue.mYt.GetSize(); t++)
        {
            myRes += ComputeLt(theModel, t, myValue);
        }

        return myRes;
	}

	/*!
	 * \fn double RegArchLLH(const cRegArchModel& theModel,cRegArchValue& theData)
	 * \param const cRegArchModel& theModel: the model
	 * \param cRegArchValue& theData: theData.mYt contains the observations.
	 * \brief return the log-likelihood value
	 */
	double RegArchLLH(const cRegArchModel& theModel, cRegArchValue& theData)
	{
        double myRes = 0;
        for(uint t = theModel.GetNLags(); t < theData.mYt.GetSize(); t++)
        {
            myRes += ComputeLt(theModel, t, theData);
        }

        return myRes;
	}

}
