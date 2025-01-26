#include "StdAfxRegArchLib.h"
/*!
	\file cGarch.cpp
	\brief sources for class cGarch methods.

	\author Jean-Baptiste DURAND, Ollivier TARAMASCO 
	\date dec-18-2006 - Last change feb-18-2011
*/
namespace RegArchLib {
	/*!
	 * \fn cGarch::cGarch(uint theNArch, uint theNGarch):cAbstCondVar(eGarch)
	 * \param uint theNArch: number of ARCH lags
	 * \param uint theNGarch: number of GARCH lags
	*/
	cGarch::cGarch(uint theNArch, uint theNGarch)
		:cAbstCondVar(eGarch)  // call constructor of cAbstCondVar with type eGarch
	{
        mvArch.ReAlloc(theNArch);
        mvGarch.ReAlloc(theNGarch);
	}

	/*!
	 * \fn cGarch::cGarch(double theConst, cDVector& theArch, cDVector& theGarch):cAbstCondVar(eGarch)
	 * \param double theConst: constant part of the GARCH(p, q) model
	 * \param cDVector& theGarch theArch: ARCH parameters
	 * \param cDVector& theGarch theGarch: GARCH parameters
	*/
	cGarch::cGarch(double theConst, cDVector& theArch, cDVector& theGarch)
		:cAbstCondVar(eGarch)
	{
        mvConst = theConst;
        mvArch = theArch;
        mvGarch = theGarch;
	}

	/*!
	* \fn cGarch::cGarch(const cAbsCondVar& theGarch):cAbstCondVar(eGarch)
	* \param cAbsCondVar& theEgarch: theGarch class
	*/
	cGarch::cGarch(const cGarch& theGarch)
		:cAbstCondVar(eGarch)
	{
        mvConst = theGarch.mvConst;
        mvArch = theGarch.mvArch;
        mvGarch = theGarch.mvGarch;
	}

	/*!
	 * \fn cGarch::~cGarch()
	*/
	cGarch::~cGarch()
	{
        mvArch.Delete();
        mvGarch.Delete();
	}

	/*!
	 * \fn void cGarch::Delete(void)
	 * \param void
	 * \details Free memory
	 */
	void cGarch::Delete(void)
	{
        mvArch.Delete();
        mvGarch.Delete();
	}

	/*!
	 * \fn void cGarch::Print(ostream& theOut) const
	 * \param ostream& theOut: the output stream, default cout.
	 */
#ifndef _RDLL_
	void cGarch::Print(ostream& theOut) const
	{
        theOut << "GARCH(" << mvArch.GetSize() << ", " << mvGarch.GetSize() << ") model with:" << endl ;
        theOut << "\tConstant=" << mvConst << endl ;
        for (uint i = 0 ; i < mvArch.GetSize() ; i++)
            theOut << "\tARCH[" << i+1 << "]=" << mvArch[i] << endl ;
        for (uint i = 0 ; i < mvGarch.GetSize() ; i++)
            theOut << "\tGARCH[" << i+1 << "]=" << mvGarch[i] << endl ;
	}
#endif //_RDLL_

	/*!
	 * \fn void cGarch::ReAlloc(const uint theSize, const uint theNumParam)
	 * \param const uint theSize: new size of mvArch or mvGarch
	 * \param const uint theNumParam: 0 for mvArch, 1 for mvGarch.
	 * \details new allocation of mvArch or mvGarch
	 */
	void cGarch::ReAlloc(const uint theSize, const uint theNumParam)
	{
        if(theNumParam == 0)
            mvArch.ReAlloc(theSize) ;
        else if(theNumParam == 1)
            mvGarch.ReAlloc(theSize) ;
        else
            cError("cGarch::ReAlloc - theNumParam must be in 0, 1") ;
	}

	/*!
	 * \fn void cGarch::ReAlloc(const cDVector& theVectParam, const uint theNumParam)
	 * \param const cDVector& theVectParam: the vector of Const, ARCH or GARCH coefficients
	 * \param const uint theNumParam: =0, the constant part; =1 the ARCH coefficients; =2 theGARCH Coefficients
	 * \details new allocation of mvArch or mvConst
	 */
	void cGarch::ReAlloc(const cDVector& theVectParam, const uint theNumParam)
	{
        if(theNumParam == 0)
            mvConst = theVectParam[0] ;
        else if(theNumParam == 1)
            mvArch = theVectParam ;
        else if(theNumParam == 2)
            mvGarch = theVectParam ;
        else
            cError("cGarch::ReAlloc - theNumParam must be in 0, 1, 2") ;
	}

	/*!
	 * \fn void cGarch::Set(const double theValue, const uint theIndex, const uint theNumParam)
	 * \brief fill the parameters vector
	 * \param const double theValue: the value of the "theIndex" th lag. Default 0.
	 * \param const uint theIndex: the index.
	 * \param const uint theNumParam: =0, mvConst, =1, ARCH parameters; =2, GARCH parameters
	 * \details mvArch[theIndex] = theValue or mvGarch[theIndex]= theValue or mvConst = theValue
	 */
	void cGarch::Set(const double theValue, const uint theIndex, const uint theNumParam)
	{
        if(theNumParam == 0)
            mvConst = theValue ;
        else if(theNumParam == 1)
            mvArch[theIndex] = theValue ;
        else if(theNumParam == 2)
            mvGarch[theIndex] = theValue ;
        else
            cError("cGarch::Set - theNumParam must be in 0, 1, 2") ;
	}

	/*!
	 * \fn void cGarch::Set(const cDVector& theVectParam, const uint theNumParam)
	 * \brief fill the parameters vector
	 * \param const cDVector& theVectParam: the vector of values
	 * \param const uint theNumParam: =0, mvConst, =1, ARCH parameters; =2, GARCH parameters
	 * \details mvAr = theValue
	 */
	void cGarch::Set(const cDVector& theVectParam, const uint theNumParam)
	{
        if(theNumParam == 0)
            mvConst = theVectParam[0] ;
        else if(theNumParam == 1)
            mvArch = theVectParam ;
        else if(theNumParam == 2)
            mvGarch = theVectParam ;
        else
            cError("cGarch::Set - theNumParam must be in 0, 1, 2") ;
	}

	double  cGarch::Get(const uint theIndex, const uint theNumParam)
	{
        if(theNumParam == 0)
            return mvConst ;
        else if(theNumParam == 1)
            return mvArch[theIndex] ;
        else if(theNumParam == 2)
            return mvGarch[theIndex] ;
        else
            cError("cGarch::Set - theNumParam must be in 0, 1, 2") ;
	}

	cDVector& cGarch::Get(const uint theNumParam)
	{
        if(theNumParam == 0) {
            cDVector *myVect;
            myVect = new cDVector(1, mvConst);
            return *myVect;
        }
        else if(theNumParam == 1)
            return mvArch ;
        else if(theNumParam == 2)
            return mvGarch ;
        else
            cError("cGarch::Set - theNumParam must be in 0, 1, 2") ;
	}

	cGarch& cGarch::operator =(const cGarch& theSrc)
	{
        mvConst = theSrc.mvConst;
        mvArch = theSrc.mvArch;
        mvGarch = theSrc.mvGarch;
        return *this;
	}

	/*!
	 * \fn double cGarch::ComputeVar(uint theDate, const cRegArchValue& theData) const
	 * \param int theDate: date of computation
	 * \param const cRegArchValue& theData: past datas
	 * \details theData is not updated here.
	*/
	double cGarch::ComputeVar(uint theDate, const cRegArchValue& theData) const 
	{
        uint myp = mvArch.GetSize() ;
        uint myq = mvGarch.GetSize() ;
        double myRes = mvConst ;
        for (uint i = 0 ; i < MIN(myp, theDate) ; i++)
            myRes += mvArch[i] * theData.mUt[theDate-i-1] * theData.mUt[theDate-i-1] ;
        for (uint i = 0 ; i < MIN(myq, theDate) ; i++)
            myRes += mvGarch[i] * theData.mHt[theDate-i-1] ;
        return myRes ;
	}

	uint cGarch::GetNParam(void) const
	{
        return mvArch.GetSize() + mvGarch.GetSize() + 1;
	}

	uint cGarch::GetNLags(void) const
	{
        return MAX(mvArch.GetSize(), mvGarch.GetSize()) ;
	}

}//namespace
