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
        if(theSampleSize > 0) {
            mYt.ReAlloc(theSampleSize);
            mMt.ReAlloc(theSampleSize);
            mHt.ReAlloc(theSampleSize);
            mUt.ReAlloc(theSampleSize);
            mEpst.ReAlloc(theSampleSize);
            if(theXt != NULL) {
                mXt = *theXt;
            }
            else {
                mXt.Delete();
            }
            if(theXvt != NULL) {
                mXvt = *theXvt;
            }
            else {
                mXvt.Delete();
            }
        }
    }

    /*!
     * \fn cRegArchValue::cRegArchValue(uint theSampleSize, cDMatrix* theXt)
     * \param cDVector* theYt: vector of Y(t)
     * \param cDMatrix* theXt: the regressors matrix if any
    */
    cRegArchValue::cRegArchValue(cDVector* theYt, cDMatrix* theXt, cDMatrix* theXvt)
    {
        if(theYt != NULL) {
            mYt = *theYt;
            mMt.ReAlloc(mYt.GetSize());
            mHt.ReAlloc(mYt.GetSize());
            mUt.ReAlloc(mYt.GetSize());
            mEpst.ReAlloc(mYt.GetSize());
            if(theXt != NULL) {
                mXt = *theXt;
            }
            else {
                mXt.Delete();
            }
            if(theXvt != NULL) {
                mXvt = *theXvt;
            }
            else {
                mXvt.Delete();
            }
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
        mYt.ReAlloc(theSize);
        mMt.ReAlloc(theSize);
        mHt.ReAlloc(theSize);
        mUt.ReAlloc(theSize);
        mEpst.ReAlloc(theSize);
    }

    /*!
     * \fn void cRegArchValue::ReAlloc(cDVector& theYt)
     * \param cDVector& theYt: vector of new datas
    */
    void cRegArchValue::ReAlloc(cDVector& theYt)
    {
        mYt = theYt;
        mMt.ReAlloc(mYt.GetSize());
        mHt.ReAlloc(mYt.GetSize());
        mUt.ReAlloc(mYt.GetSize());
        mEpst.ReAlloc(mYt.GetSize());
    }

    void cRegArchValue::ReAllocXt(uint theNRow, uint theNCol)
    {
        mXt.ReAlloc(theNRow, theNCol);
    }

	void cRegArchValue::ReAllocXt(cDMatrix& theXt)
	{
        mXt = theXt;
	}

	void cRegArchValue::ReAllocXvt(uint theNRow, uint theNCol)
	{
        mXvt.ReAlloc(theNRow, theNCol);
	}

	void cRegArchValue::ReAllocXvt(cDMatrix& theXt)
	{
        mXvt = theXt;
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
        if(theHeader) {
            theOut << "Yt" << theSep << "Mt" << theSep << "Ht" << theSep << "Ut" << theSep << "Epst" << endl;
        }
        for(uint i = 0 ; i < mYt.GetSize() ; i++) {
            theOut << mYt[i] << theSep << mMt[i] << theSep << mHt[i] << theSep << mUt[i] << theSep << mEpst[i] << endl;
        }
    }

    /*!
     * \fn ostream& operator <<(ostream& theOut, cRegArchValue& theData)
     * \param ostream& theOut: output stream (screen or file). Default, cout.
     * \param cRegArchValue& theData: datas to be printed.
     * \details Uses cRegArchValue::PrintValue with default values.
    */
    ostream& operator <<(ostream& theOut, cRegArchValue& theData)
    {
        theData.PrintValue(theOut);
        return theOut;
    }
#endif //_RDLL_

} //Namespace
