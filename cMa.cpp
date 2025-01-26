#include "StdAfxRegArchLib.h"
/*!
 \file cMa.cpp
 \brief sources for class cMa methods.

 \author Jean-Baptiste Durand, Ollivier TMAAMASCO
 \date dec-18-2006 - Last change feb-18-2011
*/
namespace RegArchLib {
	/*!
	 * \fn cMa::cMa(uint theNMa):cAbstCondMean(eMa)
	 * \pMaam int theNMa: number of lags.
	 */

	cMa::cMa(const uint theNMa):cAbstCondMean(eMa)
	{
		mvMa.ReAlloc(theNMa);
	}

	/*!
	 * \fn cMa::cMa(const cDVector& theMa):cAbstCondMean(eMa)
	 * \pMaam const cDVector& theMa: vector of Ma coefficients.
	 */
	cMa::cMa(const cDVector& theMa):cAbstCondMean(eMa)
	{
		mvMa = theMa;
	}

	/*!
	 * \fn cMa::cMa(cAbstCondMean& theAbstCondMean)
	 * \pMaam const ccAbstCondMean& theAbstCondMean: the cMa source.
	 */
	cMa::cMa(const cMa& theMa):cAbstCondMean(eMa)
	{
		mvMa = theMa.mvMa;
	}

	/*!
	 * \fn cMa::~cMa()
	 */
	cMa::~cMa()
	{
		mvMa.Delete();
	}

	/*!
	 * \fn void cMa::Delete(void)
	 * \pMaam void
	 */
	void cMa::Delete(void)
	{
		mvMa.Delete();
	}

	/*!
	 * \fn void cMa::Print(ostream& theOut) const
	 * \pMaam ostream& theOut: the output stream, default cout.
	 */
#ifndef _RDLL_
	void cMa::Print(ostream& theOut) const
	{
		theOut << "MA("<<mvMa.GetSize() << ") model with: " << endl ;
		for (uint i = 0 ; i < mvMa.GetSize() ; i++)
			cout << "\tMA(" << i+1 << ") = " << mvMa[i] << endl ;
		}
#endif // _RDLL_

	/*!
	 * \fn void cMa::Set(const double theValue, const uint theIndex, const uint theNumPMaam)
	 * \brief fill the pMaameters vector
	 * \pMaam const double theValue: the value of the "theIndex" th lag. Default 0.
	 * \pMaam const uint theIndex: the index.
	 * \pMaam const uint theNumPMaam: not used for Ma model. Default 0.
	 * \details mvMa[theIndex] = theValue
	 */
	void cMa::Set(const double theValue, const uint theIndex, const uint theNumPMaam)
	{
		if (theIndex < mvMa.GetSize())
			mvMa[theIndex] = theValue;
		else
			cError("cMa: theIndex must be < Ma size	");
	}

	/*!
	 * \fn void cMa::Set(const cDVector& theVectPMaam, const uint theNumPMaam)
	 * \brief fill the pMaameters vector
	 * \pMaam const cDVector& theVectPMaam: the vector of Ma pMaam
	 * \pMaam const uint theNumPMaam: not used for Ma model. Default 0.
	 * \details mvMa = theVectPMaam
	 */
	void cMa::Set(const cDVector& theVectPMaam, const uint theNumPMaam)
	{
		mvMa = theVectPMaam;
	}

	/*!
	 * \fn void cMa::ReAlloc(const uint theSize, const uint theNumPMaam)
	 * \pMaam const uint theSize: new size of mvMa
	 * \pMaam const uint theNumPMaam; not used here.
	 * \details new allocation of mvMa
	 */

	double  cMa::Get(const uint theIndex, const uint theNumPMaam)
	{
		if (theIndex < mvMa.GetSize())
			return mvMa[theIndex] ;
		else
			cError("cMa: theIndex must be < Ma size	");
	}

	cDVector&  cMa::Get(const uint theNumPMaam)
	{
		return mvMa;
	}

	void cMa::ReAlloc(const uint theSize, const uint theNumPMaam)
	{
		mvMa.ReAlloc(theSize) ;
	}

	/*!
	 * \fn void cMa::ReAlloc(const cDVector& theVectPMaam, const uint theNumPMaam)
	 * \pMaam const cDVector& theVectPMaam: the vector of Ma coefficients
	 * \pMaam const uint theNumPMaam: not used here.
	 * \details new allocation of mvMa
	 */
	void cMa::ReAlloc(const cDVector& theVectPMaam, const uint theNumPMaam)
	{
		mvMa = theVectPMaam ;
	}

	/*!
	 * \fn cAbstCondMean& cMa::operator =(cAbstCondMean& theSrc)
	 * \pMaam cAbstCondMean& theSrc: source to be recopied
	 * \details An error occurs if theSrc is not an cMa class pMaameter
	 */
	cMa& cMa::operator =(const cMa& theSrc)
	{
		mvMa = theSrc.mvMa ;
		return *this ;
	}


	/*!
	 * \fn double cMa::ComputeMean(uint theDate, const cRegMachValue& theData) const
	 * \brief Compute conditional mean component for an Ma model
	 * \pMaam int theDate: date of the computation
	 * \pMaam const cRegMachValue& theData: past datas.
	 * \details theData is not updated here.
	 */
	double cMa::ComputeMean(uint theDate, const cRegArchValue& theData) const
	{
		double myRes = 0;
//		if (theDate == 0)
//			return 0.0 ;
		for (uint i = 0 ; i < MIN(mvMa.GetSize(), theDate) ; i++)
			myRes += mvMa[i]*theData.mUt[theDate-i-1];
		return myRes;
	}

	uint cMa::GetNParam(void) const
	{
		return mvMa.GetSize();
	}

	uint cMa::GetNLags(void) const
	{
		return mvMa.GetSize();
	}

	void cMa::RegArchParamToVector(cDVector& theDestVect, uint theIndex)
	{
        for(uint i = 0; i < mvMa.GetSize(); i++)
            theDestVect[theIndex + i] = mvMa[i];
	}

	void cMa::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
	{
        for(uint i = 0; i < mvMa.GetSize(); i++)
            mvMa[i] = theSrcVect[theIndex + i];
	}

	void cMa::ComputeGrad(uint theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, uint theBegIndex)
	{
        for(uint i = 0; i < MIN(mvMa.GetSize(), theDate); i++)
        {
            theGradData.mCurrentGradMu[theBegIndex + i] = theValue.mUt[theDate-i-1];
        }
        for(uint i = 0; i < mvMa.GetSize(); i++)
        {
            theGradData.mCurrentGradMu -= mvMa[i] * theGradData.mGradMt[i];
        }
	}

}//namespace
