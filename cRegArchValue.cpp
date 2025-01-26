/*!
 * \file cRegArchValue.cpp
 * \brief declaration of the cRegArchValue class methods.
 * \par Details.
 * 
 * This class is used for computing the conditional mean, variance and
 * residuals for a regression ARCH model.
 *
 * \author Jean-Baptiste DURAND, Ollivier TARAMASCO
 * \date dec-18-2006 - Last change feb-18-2011
*/

#include "StdAfxRegArchLib.h"
namespace RegArchLib {
    /*!
     * \fn cRegArchValue::cRegArchValue(uint theSampleSize, cDMatrix* theXt)
     * \param uint theSampleSize: size of the sample.
     * \param cDMatrix* theXt: the regressors matrix if any
    */
    cRegArchValue::cRegArchValue(uint theSampleSize, cDMatrix* theXt, cDMatrix* theXvt)
    {
		mYt.ReAlloc(theSampleSize) ;
    	mMt.ReAlloc(theSampleSize) ;
    	mHt.ReAlloc(theSampleSize) ;
    	mUt.ReAlloc(theSampleSize) ;
    	mEpst.ReAlloc(theSampleSize) ;
    	if (theXt != NULL)
    		mXt=*theXt;
    	else
    		mXt.Delete();
    	if (theXvt != NULL)
    		mXvt=*theXvt;
    	else
    		mXvt.Delete();
    }

    /*!
     * \fn cRegArchValue::cRegArchValue(uint theSampleSize, cDMatrix* theXt)
     * \param cDVector* theYt: vector of Y(t)
     * \param cDMatrix* theXt: the regressors matrix if any
    */
    cRegArchValue::cRegArchValue(cDVector* theYt, cDMatrix* theXt, cDMatrix* theXvt)
    {
    	if (theYt != NULL)
    	{
    		mYt=*theYt;
    		uint mySize = mYt.GetSize();
    		mMt.ReAlloc(mySize);
    		mHt.ReAlloc(mySize);
    		mUt.ReAlloc(mySize);
    		mEpst.ReAlloc(mySize);
    		if (theXt != NULL)
    			mXt=*theXt;
    		else
    			mXt.Delete();
    		if (theXvt != NULL)
    			mXvt=*theXvt;
    		else
    			mXvt.Delete();
    	}
    	else
    	{
    		mYt.Delete();
    		mMt.Delete();
    		mHt.Delete();
    		mUt.Delete();
    		mEpst.Delete();
    		mXt.Delete();
    		mXvt.Delete();
    	}
    }

    /*!
     * \fn cRegArchValue::~cRegArchValue()
    */
    cRegArchValue::~cRegArchValue()
    {
    	mYt.Delete();
    	mMt.Delete();
    	mHt.Delete();
    	mUt.Delete();
    	mEpst.Delete();
    	mXt.Delete();
    	mXvt.Delete();
    }

    void cRegArchValue::Delete(void)
    {
    	mYt.Delete();
    	mMt.Delete();
    	mHt.Delete();
    	mUt.Delete();
    	mEpst.Delete();
    	mXt.Delete();
    	mXvt.Delete();
    }
    /*!
     * \fn void cRegArchValue::ReAlloc(uint theSize)
     * \param uint theSize: new size of datas
    */
    void cRegArchValue::ReAlloc(uint theSize)
    {
    	mYt.ReAlloc(theSize) ;
    	mMt.ReAlloc(theSize) ;
    	mHt.ReAlloc(theSize) ;
    	mUt.ReAlloc(theSize) ;
    	mEpst.ReAlloc(theSize) ;
      }

    /*!
     * \fn void cRegArchValue::ReAlloc(cDVector& theYt)
     * \param cDVector& theYt: vector of new datas
    */
    void cRegArchValue::ReAlloc(cDVector& theYt)
    {
    	mYt=theYt;
    	uint mySize = mYt.GetSize();
    	mMt.ReAlloc(mySize);
    	mHt.ReAlloc(mySize);
    	mUt.ReAlloc(mySize);
    	mEpst.ReAlloc(mySize);
    }

    void cRegArchValue::ReAllocXt(uint theNRow, uint theNCol)
    {
    	mXt.ReAlloc(theNRow, theNCol) ;
    }

	void cRegArchValue::ReAllocXt(cDMatrix& theXt)
	{
    	mXt=theXt;
	}

	void cRegArchValue::ReAllocXvt(uint theNRow, uint theNCol)
	{
   		mXvt.ReAlloc(theNRow, theNCol) ;
	}

	void cRegArchValue::ReAllocXvt(cDMatrix& theXtv)
	{
   		mXvt=theXtv;
	}

#ifndef _RDLL_
    /*!
     * \fn void cRegArchValue::PrintValue(ostream& theOut, bool theHeader, char* theSep)
     * \param ostream& theOut: output stream (screen or file). Default, cout.
     * \param bool theHeader: true if an header line is printed. Default, true
     * \param char* theSep: separator character. Default, "\t".
    */
    void cRegArchValue::PrintValue(ostream& theOut, bool theHeader, const char* theSep)
    {
    	if (theHeader)
    	{
    		theOut << "Y(t)" << theSep << "M(t)" << "H(t)" << theSep << "U(t)" << theSep << "Eps(t)" << endl ;
    	}
    	for (uint t = 0 ; t < mYt.GetSize(); t++)
    		theOut << mYt[t] << theSep << mMt[t] << theSep << mHt[t] << theSep << mUt[t] << theSep << mEpst[t] << endl;
    }

    /*!
     * \fn ostream& operator <<(ostream& theOut, cRegArchValue& theData)
     * \param ostream& theOut: output stream (screen or file). Default, cout.
     * \param cRegArchValue& theData: datas to be printed.
     * \details Uses cRegArchValue::PrintValue with default values.
    */
    ostream& operator <<(ostream& theOut, cRegArchValue& theData)
    {
		theData.PrintValue(theOut, true, "\t");
		return theOut;
    }

#endif //_RDLL_

} //Namespace
