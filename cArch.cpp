0#include "StdAfxRegArchLib.h"

/*!
	\file cArch.cpp
	\brief sources for class cArch methods.

	\author Jean-Baptiste DURAND, Ollivier TARAMASCO 
	\date dec-18-2006 - Last change feb-18-2011
*/

namespace RegArchLib {
	/*!
	 * \fn cArch::cArch(uint theNArch):cAbstCondVar(eArch)
	 * \param uint theNArch: number of lags
	 */
	cArch::cArch(uint theNArch)
	:cAbstCondVar(eArch)   // call constructor of cAbstCondVar with type eArch
	{
		mvArch.ReAlloc(theNArch);
	}

	/*!
	* \fn cArch::cArch(const cAbstCondVar& theArch):cAbstCondVar(eArch)
	* \param const cAbstCondVar& theArch: the recopy parameter
	*/
	cArch::cArch(const cArch& theArch)
		:cAbstCondVar(eArch)   // call constructor of cAbstCondVar with type eArch
	{
		mvConst = theArch.mvConst;
		mvArch = theArch.mvArch;
	}

	/*!
	 * \fn cArch::~cArch()
	 */
	cArch::~cArch()
	{
		mvArch.Delete();
	}

	/*!
	 * \fn void cArch::Delete(void)
	 * \param void
	 * \details Delete mvVar
	 */
	void cArch::Delete(void)
	{	mvArch.Delete() ;
	}


#ifndef _RDLL_
	/*!
	* \fn void cArch::Print(ostream& theOut) const
	* \param ostream& theOut: output stream (file or screen). Default cout.
	*/
	void cArch::Print(ostream& theOut) const
	{
		cout << "ARCH(" << mvArch.GetSize() <<") model with:" <<endl;
		cout << "\tConst = " << mvConst << endl;
		for (uint i = 0 ; i < mvArch.GetSize() ; i++)
			cout << "\tARCH(" << i + 1 <<") = " << mvArch[i] << endl;
	}

#endif // _RDLL_
	cArch& cArch::operator =(const cArch& theSrc)
	{	mvConst = theSrc.mvConst;
		mvArch = theSrc.mvArch;
		return *this;
	}

	/*!
	 * \fn void cArch::ReAlloc(const uint theSize, const uint theNumParam)
	 * \param const uint theSize: new size of mvAr
	 * \param const uint theNumParam: not used here.
	 * \details new allocation of mvArch
	 */
	void cArch::ReAlloc(const uint theSize, const uint theNumParam)
	{
		if (theNumParam == 1)
			mvArch.ReAlloc(theSize);
	}

	/*!
	 * \fn void cArch::ReAlloc(const cDVector& theVectParam, const uint theNumParam)
	 * \param const cDVector& theVectParam: the vector of Const or ARCH coefficients
	 * \param const uint theNumParam: =0, the constant part; =1 the ARCH coefficients
	 * \details new allocation of mvArch or mvConst
	 */
	void cArch::ReAlloc(const cDVector& theVectParam, const uint theNumParam)
	{
		if (theNumParam == 0)
		{
			if (theVectParam.GetSize() > 0)
				mvConst = theVectParam[0];
			else
				cError("cArch.ReAlloc: the VectParam size must be > 0");
		}
		else
		{
			if (theNumParam == 1)
				mvArch = theVectParam;
			else
				cError("cArch.ReAlloc: theNumParam must be 0 or 1");
		}
	}

	/*!
	 * \fn void cArch::Set(const double theValue, const uint theIndex, const uint theNumParam)
	 * \brief fill the parameters vector
	 * \param const double theValue: the value of the "theIndex" th lag. Default 0.
	 * \param const uint theIndex: the index.
	 * \param const uint theNumParam: =0, mvConst, =1, ARCH parameters
	 * \details mvArch[theIndex] = theValue or mvConst = theValue
	 */
	void cArch::Set(const double theValue, const uint theIndex, const uint theNumParam)
	{
		if (theNumParam == 0)
			mvConst = theValue;
		else
			if (theNumParam == 1) {
				if (mvArch.GetSize() > theIndex)
					mvArch[theIndex] = theValue ;
				else
					cError("cAr.Set: theIndex must be < AR size");

			}
			else
				cError("cArch.Set: theNumParam must be 0 or 1");
	}

	double  cArch::Get(const uint theIndex, const uint theNumParam)
	{
		if (theNumParam == 0)
			return mvConst;
		else
			if (theNumParam == 1) {
				if (mvArch.GetSize() > theIndex)
					return mvArch[theIndex];
				else
					cError("cArch.Get: theIndex must be < AR size");
			}
	}

	cDVector& cArch::Get(const uint theNumParam)
	{
		if (theNumParam == 0)
			return *new cDVector(1, mvConst);
		else
			if (theNumParam == 1)
				return mvArch;
			else
				cError("cArch.Get: theNumParam must be 0 or 1");
	}

	/*!
	 * \fn void cArch::Set(const cDVector& theVectParam, const uint theNumParam)
	 * \brief fill the parameters vector
	 * \param const cDVector& theVectParam: the vector of values
	 * \param const uint theNumParam: =0, mvConst; =1, mvArch
	 * \details mvArch = theVectParam or mvConst = theVectParam[0]
	 */
	void cArch::Set(const cDVector& theVectParam, const uint theNumParam)
	{
		if (theNumParam == 0)
		{
			if (theVectParam.GetSize() > 0)
				mvConst = theVectParam[0];
		}
		else
			if (theNumParam == 1) {
				mvArch = theVectParam;
			}
			else
				cError("cArch.Set: theNumParam must be 0 or 1");
	}

	/*!
	 * \fn double cArch::ComputeVar(uint theDate, const cRegArchValue& theData) const
	 * \param int theDate: date of computation
	 * \param const cRegArchValue& theData: past datas
	 * \details theData is not updated here.
	*/
	double cArch::ComputeVar(uint theDate, const cRegArchValue& theData) const
	{
		double myRes = mvConst ;
		for (uint i = 1 ; i <= MIN(theDate, mvArch.GetSize()) ; i++)
			myRes += mvArch[i-1]*theData.mUt[theDate-i]*theData.mUt[theDate-i];
		return myRes;
	}

	uint cArch::GetNParam(void) const
	{
		return mvArch.GetSize() + 1 ;
	}

	uint cArch::GetNLags(void) const
	{
		return mvArch.GetSize() ;
	}

	void cArch::RegArchParamToVector(cDVector& theDestVect, uint theIndex)
	{
        theDestVect[theIndex] = mvConst ;
        uint myIndex = theIndex + 1 ;
        for (uint i = 0 ; i < mvArch.GetSize() ; i++)
        {
            theDestVect[myIndex + i] = mvArch[i] ;
        }

	}

	void cArch::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
	{
        mvConst = theSrcVect[theIndex] ;
        uint myIndex = theIndex + 1 ;
        for (uint i = 0 ; i < mvArch.GetSize() ; i++)
        {
            mvArch[i] = theSrcVect[myIndex + i] ;
        }
	}

	void cArch::ComputeGrad(uint theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, cAbstResiduals* theResiduals)
	{
        uint myIndex = theGradData.GetNMeanParam() ;
        theGradData.mCurrentGradVar[myIndex++] = 1.0 ;

        for(uint i = 0 ; i < MIN(theDate, mvArch.GetSize()) ; i++)
        {
            theGradData.mCurrentGradVar[myIndex + i] = theValue.mUt[theDate - i - 1] * theValue.mUt[theDate - i - 1] ;
        }
        for(uint i = 0 ; i < MIN(theDate, mvArch.GetSize()); i++)
        {
            theGradData.mCurrentGradVar -= 2.0 * mvArch[i] * theValue.mUt[theDate - i - 1] * theGradData.mGradMt[i - 1] ;
        }


	}


}//namespace
