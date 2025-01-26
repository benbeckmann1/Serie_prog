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
		cout << "GARCH(" << mvArch.GetSize() <<", " << mvGarch.GetSize() << ") model with:" <<endl;
		cout << "\tConst = " << mvConst << endl;
		for (uint i = 0 ; i < mvArch.GetSize() ; i++)
			cout << "\tARCH(" << i + 1 <<") = " << mvArch[i] << endl;
		for (uint j = 0 ; j < mvGarch.GetSize() ; j++)
			cout << "\tGARCH(" << j + 1 <<") = " << mvGarch[j] << endl;
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
		if (theNumParam == 1) // ARCH
			mvArch.ReAlloc(theSize);
		else
			if (theNumParam == 2) // GARCH
				mvGarch.ReAlloc(theSize);
			else
				cError("cGarch::ReAlloc theNumParam must be 1 or 2");
	}

	/*!
	 * \fn void cGarch::ReAlloc(const cDVector& theVectParam, const uint theNumParam)
	 * \param const cDVector& theVectParam: the vector of Const, ARCH or GARCH coefficients
	 * \param const uint theNumParam: =0, the constant part; =1 the ARCH coefficients; =2 theGARCH Coefficients
	 * \details new allocation of mvArch or mvConst
	 */
	void cGarch::ReAlloc(const cDVector& theVectParam, const uint theNumParam)
	{
			if (theNumParam == 0)
		{
			if (theVectParam.GetSize() > 0)
				mvConst = theVectParam[0] ;
		}
		else
			if (theNumParam == 1) // ARCH
				mvArch=theVectParam;
			else
			if (theNumParam == 2) // GARCH
				mvGarch =  theVectParam;
			else
				cError("cGarch::ReAlloc theNumParam must be 0, 1 or 2");
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
        switch (theNumParam) {
        case 0:
            mvConst = theValue;
            break;
        case 1:
            if (theIndex < mvArch.GetSize())
                mvArch[theIndex] = theValue;
            break;
        case 2:
            if (theIndex < mvGarch.GetSize())
                mvGarch[theIndex] = theValue;
            break;
        }
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
        switch (theNumParam) {
        case 0:
            if (theVectParam.GetSize() > 0)
                mvConst = theVectParam[0];
            else
                cError("cGarch.Set: size of theVectParam must be > 0");
            break;
        case 1:
            mvArch = theVectParam;
            break;
        case 2:
            mvGarch = theVectParam;
            break;
        default:
            cError("cGarch.Set: theNumParam must be 0, 1 or 2");
            break;
        }
	}

	double  cGarch::Get(const uint theIndex, const uint theNumParam)
	{
        switch (theNumParam) {
        case 0:
            return mvConst;
            break;
        case 1:
            if (theIndex < mvArch.GetSize())
                return mvArch[theIndex];
            else
                cError("cGarch.Get: theIndex out of range");
            break;
        case 2:
            if (theIndex < mvGarch.GetSize())
                return mvGarch[theIndex];
            else
                cError("cGarch.Get: theIndex out of range");
            break;

        }
	}

	cDVector& cGarch::Get(const uint theNumParam)
	{
        switch (theNumParam) {
        case 0:
            return *new cDVector(1, mvConst);
            break;
        case 1:
            return mvArch;
            break;
        case 2:
            return mvGarch;
            break;
        default:
            cError("cGarch.Get: theNumParam must be 0, 1 or 2");
            break;
        }
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
		double myRes = mvConst ;
		for (uint i = 1 ; i <= MIN(theDate, mvArch.GetSize()); i++)
			myRes += mvArch[i-1]*theData.mUt[theDate-i]*theData.mUt[theDate-i] ;
		for (uint j = 1 ; j <= MIN(theDate, mvGarch.GetSize()); j++)
			myRes += mvGarch[j-1] + theData.mHt[theDate-j] ;
		return myRes ;
	}

	uint cGarch::GetNParam(void) const
	{
		return 1 + mvArch.GetSize() + mvGarch.GetSize() ;
	}

	uint cGarch::GetNLags(void) const
	{
		return MAX(mvArch.GetSize(), mvGarch.GetSize()) ;
	}

	void cGarch::RegArchParamToVector(cDVector& theDestVect, uint theIndex)
	{
        theDestVect[theIndex] = mvConst ;
        uint myIndex = theIndex + 1 ;
        for(uint i = 0 ; i < mvArch.GetSize() ; i++)
            theDestVect[myIndex + i] = mvArch[i] ;
        myIndex += mvArch.GetSize() ;
        for(uint i = 0 ; i < mvGarch.GetSize() ; i++)
            theDestVect[myIndex + i] = mvGarch[i] ;
	}

	void cGarch::VectorToRegArchParam(const cDVector& theSrcVect, uint theIndex)
	{
        mvConst = theSrcVect[theIndex] ;
        uint myIndex = theIndex + 1 ;
        for(uint i = 0 ; i < mvArch.GetSize() ; i++)
            mvArch[i] = theSrcVect[myIndex + i] ;
        myIndex += mvArch.GetSize() ;
        for(uint i = 0 ; i < mvGarch.GetSize() ; i++)
            mvGarch[i] = theSrcVect[myIndex + i] ;
	}

	void cGarch::ComputeGrad(uint theDate, const cRegArchValue& theValue, cRegArchGradient& theGradData, cAbstResiduals* theResiduals)
	{
        uint myIndex = theGradData.GetNMeanParam() ;
        uint myp = mvArch.GetSize() ;
        theGradData.mCurrentGradVar[myIndex++] = 1.0 ;

        //Partie ARCH
        for(uint i = 0 ; i < MIN(theDate, mvArch.GetSize()) ; i++)
        {
            theGradData.mCurrentGradVar[myIndex + i] = theValue.mUt[theDate - i - 1] * theValue.mUt[theDate - i - 1] ;
        }

        //Partie GARCH
        for(uint i = 0; i < MIN(theDate, mvGarch.GetSize()); i++)
        {
            theGradData.mCurrentGradVar[myIndex + i + myp] = theValue.mHt[theDate - i - 1] ;
        }

        //Partie ARCH
        for(uint i = 0 ; i < MIN(theDate, mvArch.GetSize()); i++)
        {
            theGradData.mCurrentGradVar -= 2.0 * mvArch[i] * theValue.mUt[theDate - i - 1] * theGradData.mGradMt[i] ;
        }

        //Partie GARCH
        for(uint i = 0; i < MIN(theDate, mvGarch.GetSize()); i++)
        {
            theGradData.mCurrentGradVar += mvGarch[i] * theGradData.mGradHt[i + myp] ;
        }


	}

}//namespace
