#include "StdAfxRegArchLib.h"

/*!
	\file cAbstCondVar.cpp
	\brief sources for abstract class cAbstCondVar methods.

	\author Jean-Baptiste DURAND, Ollivier TARAMASCO 
	\date dec-18-2006 - Last change feb-18-2011
*/

namespace RegArchLib {

	/*!
	 * \fn cAbstCondVar::cAbstCondVar(eCondVarEnum theType)
	 * \param eCondVarEnum theType: Conditional variance type code. Default eNotKnown.
	 */
	cAbstCondVar::cAbstCondVar(eCondVarEnum theType)
	{
		mvCondVar = theType;
	}

	/*!
	 * \fn cAbstCondVar::~cAbstCondVar()
	 * \details Nothing to do here
	 */
	cAbstCondVar::~cAbstCondVar()
	{
		mvCondVar = eNotKnown;
	}

	/*!
	 * \fn inline eCondVarEnum cAbstCondVar::GetCondVarType(void) const
	 * \param void
	 * \brief return the real conditional variance type code.
	*/
	eCondVarEnum cAbstCondVar::GetCondVarType(void) const
	{
		return mvCondVar;
	}

	void cAbstCondVar::SetCondVarType(eCondVarEnum theType)
	{
		mvCondVar = theType;
	}

#ifndef _RDLL_
	/*!
	 * \fn ostream& operator <<(ostream& theOut, const cAbstCondVar& theAbstCondVar)
	 * \param ostream& theOut: output stream (file or screen). Default cout.
	 * \param const cAbstCondVar& theAbstCondVar: the variance model.
	 * \details Uses cAbstCondVar::Print
	 */
	ostream& operator <<(ostream& theOut, const cAbstCondVar& theAbstCondVar)
	{
	}
#endif // _RDLL_


	/*!
	* \fn template<class T> static T* TemplateCreateOneRealCondVar(cAbstCondVar& theAbstCondVar)
	* \param cAbstCondVar& theAbstCondVar
	*/
	template<class T>
	T* TemplateCreateOneRealCondVar(cAbstCondVar* theAbstCondVar)
	{
	T*	mySrc = static_cast<T *>(theAbstCondVar);
		if (mySrc)
		{
			return new T(*mySrc);
		}
		else
		{
			throw cError("Wrong Conditional Variance in TemplateCreateOneRealCondVar");
		}
	}

	/*!
	* \fn template<class T> static T* TemplateCreateOneRealCondVar(void)
	* \param void
	*/
	template<class T>
	T* TemplateCreateOneRealCondVar(void)
	{
		return new T();
	}

	/*!
	* \fn CreateOneRealCondVar* CreateOneRealCondVar(eCondVarEnum theType)
	* \param theType: type of conditional variance.
	* \par Details This function has to be changed when adding a new conditional variance type.
	*/
	cAbstCondVar* CreateOneRealCondVar(eCondVarEnum theType)
	{
		switch (theType)
		{
		case eCste:
			return TemplateCreateOneRealCondVar<cConstCondVar>();
			break;
		case eArch:
			return TemplateCreateOneRealCondVar<cArch>();
			break;
		case eGarch:
			return TemplateCreateOneRealCondVar<cGarch>();
			break;

		case eNotKnown:
		default:
			throw cError("unknown conditional variance type");
			break;
		}
	}

	cAbstCondVar* CreateOneRealCondVar(cAbstCondVar& theAbstCondVar) 
	{
		switch (theAbstCondVar.GetCondVarType())
		{
		case eCste:
			return TemplateCreateOneRealCondVar<cConstCondVar>(&theAbstCondVar);
			break;
		case eArch:
			return TemplateCreateOneRealCondVar<cArch>(&theAbstCondVar);
			break;
		case eGarch:
			return TemplateCreateOneRealCondVar<cGarch>(&theAbstCondVar);
			break;
		case eNotKnown:
		default:
			throw cError("unknown conditional variance type");
			break;
		}
	}
}
