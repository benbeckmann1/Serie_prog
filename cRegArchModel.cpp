#include "StdAfxRegArchLib.h"

namespace RegArchLib {

	/*!
	 * \fn cRegArchModel::cRegArchModel()
	 * \param None
	 * \details A simple constructor
	 */
	cRegArchModel::cRegArchModel()
	{
		mMean = NULL ;
		mVar = NULL ;
		mResids = NULL ;
	}

	/*!
	 * \fn cRegArchModel::cRegArchModel(cCondMean* theMean, cAbstCondVar* theVar, cAbstResiduals* theResiduals)
	 * \param cCondMean* theMean: pointer to conditional mean model
	 * \param cAbstCondVar* theVar: pointer to conditional variance model
	 * \param cAbstResiduals* theResiduals: pointer to conditional residuals distribution model
	 * \details A simple constructor
	 */
	cRegArchModel::cRegArchModel(cCondMean& theMean, cAbstCondVar& theVar, cAbstResiduals& theResiduals)
	{
		if (mMean != NULL)
			delete mMean;
		mMean = new cCondMean(theMean);
		if (mVar != NULL)
			delete mVar;
		mVar = CreateOneRealCondVar(theVar);
		if (mResids != NULL)
			delete mResids;
		mResids = CreateRealCondResiduals(theResiduals);
	}

	/*!
	 * \fn cRegArchModel::cRegArchModel(cRegArchModel& theModel)
	 * \param cRegArchModel& theModel: the source
	 * \details recopy constructor
	 */
	cRegArchModel::cRegArchModel(const cRegArchModel& theModel)
	{	
		if (mMean != NULL)
			delete mMean;
		mMean = new cCondMean(*(theModel.mMean));
		if (mVar != NULL)
			delete mVar;
		mVar = CreateOneRealCondVar(*(theModel.mVar));
		if (mResids != NULL)
			delete mResids;
		mResids = CreateRealCondResiduals(*(theModel.mResids));
	}

	/*!
	 * \fn cRegArchModel::~cRegArchModel()
	 */
	cRegArchModel::~cRegArchModel()
	{
		if (mMean != NULL)
		{
			mMean->Delete();
			mMean = NULL;
		}
		if (mVar != NULL)
		{
			mVar->Delete();

		}
		if (mResids != NULL)
		{
			mResids->Delete();
			mResids = NULL;
		}
	}

	/*!
	 * \fn cRegArchModel& cRegArchModel::operator=(cRegArchModel& theRegArchModel)
	 * \param cRegArchModel& theRegArchModel: the source
	 * \details = operator for cRegArchModel
	 */
	cRegArchModel& cRegArchModel::operator=(cRegArchModel& theRegArchModel)
	{
		if (mMean != NULL)
		{
			mMean->Delete();
			mMean = NULL;
		}
		if (theRegArchModel.mMean != NULL)
		{
			mMean = new cCondMean(*(theRegArchModel.mMean));
		}
		if (mVar != NULL)
		{
			mVar->Delete();
			mVar = NULL;
		}
		if (theRegArchModel.mVar != NULL)
		{
			mVar = CreateOneRealCondVar(*(theRegArchModel.mVar));
		}
		if (mResids != NULL)
		{
			mResids->Delete();
			mResids = NULL;
		}
		if (theRegArchModel.mResids != NULL)
		{
			mResids = CreateRealCondResiduals(*(theRegArchModel.mResids));
		}

	}

	void cRegArchModel::Delete(void)
	{
		if (mMean != NULL)
		{
			mMean->Delete();
			mMean = NULL;
		}
		if (mVar != NULL)
		{
			mVar->Delete();
			mVar = NULL;
		}
		if (mResids != NULL)
		{
			mResids->Delete();
			mResids = NULL;
		}
	}

	/*!
	 * \fn void cRegArchModel::SetMean(cCondMean& theCondMean)
	 * \param cCondMean& theCondMean: the conditinew conal mean model
	 */
	void cRegArchModel::SetMean(cCondMean& theCondMean)
	{
		if (mMean != NULL)
			mMean->Delete();
		mMean = new cCondMean(theCondMean);
	}

	/*!
	 * \fn void cRegArchModel::GetNMean(void)
	 * \param void
	 * \details return the number of mean components
	 */
	int cRegArchModel::GetNMean(void)
	{
		if (mMean != NULL)
			return mMean->GetNMean();
		else
			return 0 ;
	}

	/*!
	 * \fn void cRegArchModel::AddOneMean(cAbstCondMean& theOneMean)
	 * \param cAbstCondMean& theOneMean: the conditional mean component model
	 * \details Add a new mean component
	 */
	void cRegArchModel::AddOneMean(cAbstCondMean& theOneMean)
	{
		if (mMean != NULL)
			mMean->AddOneMean(theOneMean);
		else
			cError("cRegArchModel::AddOneMean: mMean is NULL");
	}

	/*!
	 * \fn void cRegArchModel::GetOneMean(int theNumMean)
	 * \param int theNumMean: the index of the mean component
	 * \details Return theNumMean th mean component
	 */
	cAbstCondMean* cRegArchModel::GetOneMean(int theNumMean)
	{
		if (mMean != NULL)
			if (theNumMean < MAX_COND_MEAN)
				return mMean->GetOneMean(theNumMean);
	}

	bool cRegArchModel::IsGoodMeanType(eCondMeanEnum theMeanEnum, int theIndex)
	{	
	}

#ifndef _RDLL_
	
	/*!
	* \fn void cRegArchModel::PrintMean(ostream& theOut) const
	* \param ostream& theOut: output stream (screen or file). Default: cout
	*/
	void cRegArchModel::PrintMean(ostream& theOut) const
    {
		if (mMean != NULL)
			mMean->Print(theOut);
	}

	/*!
	* \fn void cRegArchModel::PrintVar(ostream& theOut) const
	* \param ostream& theOut: output stream (screen or file). Default: cout
	*/
	void cRegArchModel::PrintVar(ostream& theOut) const
	{
		if (mVar != NULL)
			mVar->Print(theOut);
	}
	/*!
	* \fn void cRegArchModel::PrintResiduals(ostream& theOut) const
	* \param ostream& theOut: output stream (screen or file). Default: cout
	*/
	void cRegArchModel::PrintResiduals(ostream& theOut) const
	{
		if (mResids != NULL)
			mResids->Print(theOut);
	}

	/*!
	* \fn void cRegArchModel::Print(ostream& theOut) const
	* \param ostream& theOut: output stream (screen or file). Default: cout
	*/
	void cRegArchModel::Print(ostream& theOut) const
	{
		theOut << "Regression with ARCH type residuals" << endl ;
		theOut << "-----------------------------------" << endl;
		PrintMean(theOut) ;
		PrintVar(theOut) ;
		PrintResiduals(theOut) ;
	}
#endif //_RDLL_
	/*!
	 * \fn void cRegArchModel::SetVar(cAbstCondVar& theCondVar)
	 * \param cCondVar& theCondVar: the conditional variance model
	 */
	void cRegArchModel::SetVar(cAbstCondVar& theCondVar)
	{
		if (mVar != NULL)
			mVar->Delete();
		mVar = CreateOneRealCondVar(theCondVar);
	}

	cAbstCondVar* cRegArchModel::GetVar(void)
	{
		return mVar;
	}

	/*!
	 * \fn void cRegArchModel::SetResid(cAbstResiduals& theCondResiduals)
	 * \param cAbstResiduals& theCondResiduals: the conditional residuals model
	 */
	void cRegArchModel::SetResid(cAbstResiduals& theCondResiduals)
	{
		mResids = CreateRealCondResiduals(theCondResiduals);
	}

	cAbstResiduals*  cRegArchModel::GetResid(void)
	{
		return mResids;
	}

	uint cRegArchModel::GetNParam(void) const
    {
		return mMean->GetNParam() + mVar->GetNParam()+ mResids->GetNParam();
    }

	uint cRegArchModel::GetNLags(void) const
    {
		return MAX(mMean->GetNLags(), mVar->GetNLags());
    }

	void cRegArchModel::ComputeGrad(uint theDate, cRegArchValue& theValue, cRegArchGradient& theGradData)
	{
        FillValue(theDate, *this ,theValue);
        if (mMean != NULL)
        {
            mMean->ComputeGrad(theDate, theValue, theGradData) ;
        }
        if (mVar != NULL)
        {
            mVar->ComputeGrad(theDate, theValue, theGradData) ;
        }
        if (mResids != NULL)
        {
            mResids->ComputeGrad(theDate, theValue, theGradData) ;
        }
        double mySigmat = sqrt(theValue.mHt[theDate]);
        theGradData.mCurrentGradSigma = theGradData.mCurrentGradVar / (2.0 * mySigmat);

        theGradData.mCurrentGradEps = (-1.0) * (theGradData.mCurrentGradMu + theGradData.mCurrentGradSigma * theValue.mEpst[theDate])/mySigmat;
	}

	void cRegArchModel::RegArchParamToVector(cDVector& theDestVect) const
	{
        uint myIndex = 0 ;
        theDestVect.ReAlloc(GetNParam()) ;
        if(mMean != NULL)
        {
            mMean->RegArchParamToVector(theDestVect, myIndex) ;
            myIndex += mMean->GetNParam() ;
        }
        if(mVar != NULL)
        {
            mVar->RegArchParamToVector(theDestVect, myIndex) ;
            myIndex += mVar->GetNParam() ;
        }
        if(mResids != NULL)
        {
            mResids->RegArchParamToVector(theDestVect, myIndex) ;
        }
    }

	void cRegArchModel::VectorToRegArchParam(const cDVector& theSrcParam)
	{
        uint myIndex = 0 ;
        if(mMean != NULL)
        {
            mMean->VectorToRegArchParam(theSrcParam, myIndex) ;
            myIndex += mMean->GetNParam() ;
        }
        if(mVar != NULL)
        {
            mVar->VectorToRegArchParam(theSrcParam, myIndex) ;
            myIndex += mVar->GetNParam() ;
        }
        if(mResids != NULL)
        {
            mResids->VectorToRegArchParam(theSrcParam, myIndex) ;
        }
	}


	
}//namespace

