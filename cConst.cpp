#include "StdAfxRegArchLib.h"
/*!
	\file cAbstCondMean.cpp
	\brief sources for abstract class cConst methods.

	\author Jean-Baptiste Durand, Ollivier TARAMASCO
	\date dec-18-2006 - Last change feb-18-2011
*/
namespace RegArchLib {
	/*!
	 * \fn cConst::cConst(double theVal):cAbstCondMean(eConst)
	 * \param double theVal: constant value, default 0.0L.
	 */
	cConst::cConst(double theVal):cAbstCondMean(eConst)
    {
        mvConst = theVal;
	}

	/*!
	 * \fn cConst::cConst(cAbstCondMean& theAbstCondMean)
	 * \param const cAbstCondMean& theAbstCondMean: the cConst source.
	 */
	cConst::cConst(const cConst& theConst):cAbstCondMean(eConst)
	{
        *this = theConst;
	}

	/*!
	 * \fn cConst::~cConst()
	 * \details Nothing to do.
	 */
	cConst::~cConst()
	{
	}

	/*!
	 * \fn void cConst::Delete(void)
	 * \\details Delete. Nothing to do.
	 */
	void cConst::Delete(void)
	{
	}

	/*!
	 * \fn void cConst::Print(ostream& theOut) const
	 * \param ostream& theOut: output stream (screen or file). Default cout.
	 */

#ifndef _RDLL_
	void cConst::Print(ostream& theOut) const
	{
        theOut << "Constant mean model with:" << endl;
        theOut << "\tConstant=" << mvConst << endl;
	}
#endif // _RDLL_

	/*!
	 * \fn void cConst::Set(const double theValue, const uint theIndex, const uint theNumParam)
	 * \brief fill the parameters vector
	 * \param const double theValue: the constant value.
	 * \param const uint theIndex: not used here. Default 0.
	 * \param const uint theNumParam: not used for cConst model. Default 0.
	 * \details mvConst = theValue
	 */
	void cConst::Set(const double theValue, const uint theIndex, const uint theNumParam)
	{
        mvConst = theValue;
	}

	/*!
	 * \fn void cConst::Set(const cDVector& theVectParam, const uint theNumParam)
	 * \brief fill the parameters vector
	 * \param const cDVector& theVectParam: the constant value is in theVectParam[0].
	 * \param const uint theIndex: not used here. Default 0.
	 * \param const uint theNumParam: not used for cConst model. Default 0.
	 * \details mvConst = theVectParam[0]
	 */
	void cConst::Set(const cDVector& theVectParam, const uint theNumParam)
    {
        if(theVectParam.GetSize() > 0) {
            mvConst = theVectParam[0];
        }
        else {
            cError("theVectParam lenght must be > 0");
        }
	}

	double  cConst::Get(const uint theIndex, const uint theNumParam)
	{
        return mvConst;
	}

	cDVector& cConst::Get(const uint theNumParam)
	{
        cDVector* myVect;
            myVect = new cDVector(1, mvConst);
        return *myVect;
	}

	/*!
	 * \fn void cConst::ReAlloc(const uint theSize, const uint theNumParam=0)
	 * \param const uint theSize: not used. Not used for cConstClass
	 * \param const uint theNumParam: not used for cConst class
	 * \details Nothing to do for cConst Class.
	 */
	void cConst::ReAlloc(const uint theSize, const uint theNumParam)
	{
	}

	/*!
	 * \fn void cConst::ReAlloc(const cDVector& theVectParam, const uint theNumParam)
	 * \param const cDVector& theVectParam: the constant value is in theVectParam[0]
	 * \param const uint theNumParam: not used for cConst class
	 * \details Here, mvConst = theVectParam[0]
	 */
	void cConst::ReAlloc(const cDVector& theVectParam, const uint theNumParam)
	{
        mvConst = theVectParam[0];
	}

	/*!
	 * \fn cAbstCondMean& cConst::operator =(cAbstCondMean &theSrc)
	 * \param cAbstCondMean &theSrc
	 * \details theSrc must be a cConst parameter
	 */
	cConst& cConst::operator =(const cConst& theSrc)
	{
        mvConst = theSrc.mvConst;
        return *this;
	}

	/*!
	 * \param int theDate: date of the computation
	 * \param cRegArchValue& theData: past datas.
	 * \details theData must not be updated here.
	 */
	double cConst::ComputeMean(uint theDate, const cRegArchValue& theData) const
	{
        return mvConst;
	}

	uint cConst::GetNParam(void) const
	{
        return 1;
	}

	uint cConst::GetNLags(void) const
	{
        return 0;
	}

}//namespace
