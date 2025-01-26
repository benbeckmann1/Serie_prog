#include "StdAfxRegArchLib.h"

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
        mvArch.ReAlloc(theNArch) ;
	}

	/*!
	* \fn cArch::cArch(const cAbstCondVar& theArch):cAbstCondVar(eArch)
	* \param const cAbstCondVar& theArch: the recopy parameter
	*/
	cArch::cArch(const cArch& theArch)
		:cAbstCondVar(eArch)   // call constructor of cAbstCondVar with type eArch
	{
        mvArch = theArch.mvArch ;
	}

	/*!
	 * \fn cArch::~cArch()
	 */
	cArch::~cArch()
	{
        mvArch.Delete() ;
	}

	/*!
	 * \fn void cArch::Delete(void)
	 * \param void
	 * \details Delete mvVar
	 */
	void cArch::Delete(void)
	{
        mvArch.Delete() ;
	}


#ifndef _RDLL_
	/*!
	* \fn void cArch::Print(ostream& theOut) const
	* \param ostream& theOut: output stream (file or screen). Default cout.
	*/
	void cArch::Print(ostream& theOut) const
	{
        theOut << "ARCH(" << mvArch.GetSize() << ") model with:" << endl ;
        theOut << "\tConstant=" << mvConst << endl ;
        for (uint i = 0 ; i < mvArch.GetSize() ; i++)
            theOut << "\tARCH[" << i+1 << "]=" << mvArch[i] << endl ;
	}

#endif // _RDLL_
	cArch& cArch::operator =(const cArch& theSrc)
	{
        mvConst = theSrc.mvConst ;
        mvArch = theSrc.mvArch ;
        return *this ;
	}

	/*!
	 * \fn void cArch::ReAlloc(const uint theSize, const uint theNumParam)
	 * \param const uint theSize: new size of mvAr
	 * \param const uint theNumParam: not used here.
	 * \details new allocation of mvArch
	 */
	void cArch::ReAlloc(const uint theSize, const uint theNumParam)
	{
        mvArch.ReAlloc(theSize) ;
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
            mvConst = theVectParam[0] ;
        else if(theNumParam == 1)
            mvArch = theVectParam ;
        else
            cError("cArch::ReAlloc - theNumParam must be in 0, 1") ;
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
            mvConst = theValue ;
        else if(theNumParam == 1)
            mvArch[theIndex] = theValue ;
        else
            cError("cArch::Set - theNumParam must be in 0, 1") ;
	}

	double  cArch::Get(const uint theIndex, const uint theNumParam)
	{
        if(theNumParam == 0)
            return mvConst ;
        else if(theNumParam == 1)
            return mvArch[theIndex] ;
        else
            cError("cArch::Set - theNumParam must be in 0, 1") ;
	}

	cDVector& cArch::Get(const uint theNumParam)
	{
        if(theNumParam == 0) {
            cDVector *myVect;
            myVect = new cDVector(1, mvConst);
            return *myVect;
        }
        else if(theNumParam == 1)
            return mvArch ;
        else
            cError("cArch::Set - theNumParam must be in 0, 1") ;
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
            mvConst = theVectParam[0] ;
        else if(theNumParam == 1)
            mvArch = theVectParam ;
        else
            cError("cArch::Set - theNumParam must be in 0, 1") ;
	}

	/*!
	 * \fn double cArch::ComputeVar(uint theDate, const cRegArchValue& theData) const
	 * \param int theDate: date of computation
	 * \param const cRegArchValue& theData: past datas
	 * \details theData is not updated here.
	*/
	double cArch::ComputeVar(uint theDate, const cRegArchValue& theDatas) const
	{
        uint myp = mvArch.GetSize() ;
        double myRes = mvConst ;
        for (uint i = 0 ; i < MIN(myp, theDate) ; i++)
            myRes += mvArch[i] * theDatas.mUt[theDate-i-1] * theDatas.mUt[theDate-i-1] ;
        return myRes ;
	}

	uint cArch::GetNParam(void) const
	{
        return mvArch.GetSize() + 1 ;
	}

	uint cArch::GetNLags(void) const
	{
        return mvArch.GetSize() ;
	}

}//namespace
