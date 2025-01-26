#include "StdAfxRegArchLib.h"
/*!
 \file cAbstCondVar.cpp
 \brief sources for abstract class cAbstCondVar methods.

 \author Jean-Baptiste DURAND, Ollivier TARAMASCO 
 \date dec-18-2006 - Last change feb-18-2011
*/

namespace RegArchLib {
	/*!
	 * \fn cCondMean::cCondMean(uint theNCondMean)
	 * \param uint theNCondMean: number of conditional means
	 * \details mvCondMean = theNCondMean
	 */
	cCondMean::cCondMean()
	{
        for(uint i = 0 ; i < MAX_COND_MEAN ; i++)
            mvCondMean[i] = NULL;
	}

	/*!
	 * \fn cCondMean::cCondMean(const cCondMean& theCondMean)
	 * \param cCondMean& theCondMean: conditional mean
	 * \details Recopy constructor
	 */
	cCondMean::cCondMean(const cCondMean& theCondMean)
	{
        for(uint i = 0 ; i < MAX_COND_MEAN ; i++) {
            if (theCondMean.mvCondMean[i] != NULL)
                mvCondMean[i] = CreateOneRealCondMean(*theCondMean.mvCondMean[i]);
            else
                mvCondMean[i] = NULL;
        }
	}

	/*!
	 * \fn cCondMean::~cCondMean()
	 * \param None
	 * \details simple destructor
	 */
	cCondMean::~cCondMean()
	{
	}

	/*!
	 * \fn void cCondMean::Delete(void)
	 * \param void
	 * \details free memory used par the cCondMean class
	 */
	void cCondMean::Delete(void)
	{
        for(uint i = 0 ; i < MAX_COND_MEAN ; i++)
        {
            if(mvCondMean[i] != NULL)
            {
                delete mvCondMean[i];
                mvCondMean[i] = NULL;
            }
        }
	}

	/*!
	 * \fn inline uint cCondMean::GetNMean(void) const
	 * \param void
	 * \brief return mvNCondMean
	 */
	uint cCondMean::GetNMean(void) const
	{
        uint myNMean = 0;
        for(uint i = 0 ; i < MAX_COND_MEAN ; i++)
            if (mvCondMean[i] != NULL)
                myNMean++;
        return myNMean;
	}

	/*!
	* \fn  void cCondMean::AddOneMean(cAbstCondMean* theAbstCondMean)
	* \param cAbstCondMean* theAbstCondMean: conditional mean component to be copied in the mCondMean array.
	* \brief *mvCondMean[theWhatMean] = *theAbstCondMean
	*/
	void cCondMean::AddOneMean(cAbstCondMean& theAbstCondMean)
	{
        uint myPlace = (uint) theAbstCondMean.GetCondMeanType();
        if (mvCondMean[myPlace] != NULL)
            mvCondMean[myPlace]->Delete();
        mvCondMean[myPlace] = CreateOneRealCondMean(theAbstCondMean);
	}

	/*!
	 * \fn cAbstCondMean** cCondMean::GetCondMean(void)
	 * \\details return mvCondMean
	 */
	cAbstCondMean** cCondMean::GetCondMean(void) const
	{
        return (cAbstCondMean**) mvCondMean;
	}

	/*!
	 * \fn cAbstCondMean* cCondMean::GetOneMean(uint theIndex) const
	 * \param uint theIndex: index of component to be returned
	 * \\details return mvCondMean[theWhateMean] 
	 */
	cAbstCondMean* cCondMean::GetOneMean(uint theIndex) const
	{
        if(theIndex < MAX_COND_MEAN)
            return mvCondMean[theIndex];
        else
            cerr << "Error: cCondMean::GetOneMean: index is out of range" << endl;
        return NULL;
    }

	/*!
	 * \fn void cCondMean::GetCondMeanType(eCondMeanEnum* theCodeType) const
	 * \param eCondMeanEnum* theCodeType: array of all conditional mean component codes
	 * \details fill theCodeType array
	 */
	void cCondMean::GetCondMeanType(eCondMeanEnum* theCodeType) const
	{
        for(uint i = 0 ; i < MAX_COND_MEAN ; i++)
            if (mvCondMean[i] != NULL)
                theCodeType[i] = mvCondMean[i]->GetCondMeanType();
	}

	/*!
	 * \fn void cCondMean::Print(ostream& theOut) const
	 * \param ostream& theOut: output stream (file or screen). Default cout.
	 */
#ifndef _RDLL_
	void cCondMean::Print(ostream& theOut) const
	{
        theOut << "Conditional Mean with " << GetNMean() << " components:" << endl;
        for(uint i = 0 ; i < MAX_COND_MEAN ; i++)
            if (mvCondMean[i] != NULL)
                mvCondMean[i]->Print(theOut);
	}
#endif // _RDLL_

	/*!
	 * \fn double cCondMean::Get(uint theNumMean, uint theIndex, uint theNumParam)
	 * \param uint theNumMean: index of conditional mean
	 * \param uint theNumParam: index of parameter
	 */
	double cCondMean::Get(uint theNumMean, uint theIndex, uint theNumParam)
	{
        if (theNumMean < MAX_COND_MEAN)
            if(mvCondMean[theNumMean] != NULL)
                return mvCondMean[theNumMean]->Get(theIndex, theNumParam);
            else
                cerr << "Error: cCondMean::Get: no mean component" << endl;
        else
            cerr << "Error: cCondMean::Get: index is out of range" << endl;
        return 0.0;
	}


	/*!
	 * \fn ostream& operator <<(ostream& theOut, const cCondMean& theCondMean)
	 * \param ostream& theOut: output (file or screen).
	 * \param const cCondMean& theCondMean: the conditional mean class to be printed.
	 */
#ifndef _RDLL_
	ostream& operator <<(ostream& theOut, const cCondMean& theCondMean)
	{
        theCondMean.Print(theOut);
        return theOut;
    }
#endif //_RDLL_

	/*!
	 * \fn cCondMean& cCondMean::operator =(cCondMean& theSrc)
	 * \param cCondMean& theSrc: source class
	 */
	cCondMean& cCondMean::operator =(cCondMean& theSrc)
    {
        for(uint i = 0 ; i < MAX_COND_MEAN ; i++)
        {
            if (theSrc.mvCondMean[i] != NULL)
            {
                if (mvCondMean[i] != NULL)
                    mvCondMean[i]->Delete();
                mvCondMean[i] = CreateOneRealCondMean(*theSrc.mvCondMean[i]);
            }
            else
            {
                if (mvCondMean[i] != NULL)
                {
                    mvCondMean[i]->Delete();
                    mvCondMean[i] = NULL;
                }
            }
        }
        return *this;
    }


	/*!
	 * \fn double cCondMean::ComputeMean(uint theDate, const cRegArchValue& theData) const
	 * \param int theDate: date of computation
	 * \param const cRegArchValue& theData: past datas.
	 * \details Compute the value of the conditional mean at date theDate. 
	 * theData is not updated here.
	 */
	double cCondMean::ComputeMean(uint theDate, const cRegArchValue& theData) const
	{
        double myRes = 0.0;
        for(uint i = 0 ; i < MAX_COND_MEAN ; i++)
            if (mvCondMean[i] != NULL)
                myRes += mvCondMean[i]->ComputeMean(theDate, theData);
        return myRes;
	}

	uint cCondMean::GetNParam(void) const
	{
        uint myNParam = 0;
        for(uint i = 0 ; i < MAX_COND_MEAN ; i++)
            if (mvCondMean[i] != NULL)
                myNParam += mvCondMean[i]->GetNParam();
        return myNParam;
	}

	uint cCondMean::GetNLags(void) const
	{
        uint myNLags = 0;
        for(uint i = 0 ; i < MAX_COND_MEAN ; i++)
            if (mvCondMean[i] != NULL)
                myNLags = MAX(myNLags, mvCondMean[i]->GetNLags());
        return myNLags;
	}

}//namespace
