/*
 * PdvList.h
 *
 *  Created on: 24 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_PRESENTATION_ASN1_PDVLIST_H_
#define INCLUDE_PRESENTATION_ASN1_PDVLIST_H_

#include "osistack_global.h"
#include "externalLinkV1.h"

typedef CExternalLinkV1 SubchoicePresentationDataValues;

class OSISTACK_SHAREDEXPORT CPdvList: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier* Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(IBerBaseType* Integer READ getInteger)

	bool is_copy;

protected:

	CBerIdentifier m_Identifier;
	QByteArray m_Code;

	SubchoicePresentationDataValues* m_pSPDV;

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier* getIdentifier() { return &m_Identifier; }
	IBerBaseType* getInteger() { return m_pSPDV; }

public:

	ASN1_CODEC(CBerBaseStorage)

	static CBerIdentifier s_Identifier;
	static quint32 s_metaTypeIdentifier;

	CPdvList(SubchoicePresentationDataValues* pSPDV):
		is_copy(false),
		m_Identifier(s_Identifier),
		m_pSPDV(pSPDV)
	{ }

	CPdvList(const CPdvList& rhs): QObject()
	{
		m_Identifier = s_Identifier;
		m_Code = rhs.m_Code;

		if (rhs.m_pSPDV != nullptr)
				m_pSPDV = new SubchoicePresentationDataValues(*rhs.m_pSPDV);

		is_copy = true;
	}

	CPdvList& operator=(const CPdvList& rhs)
	{
		if (this == &rhs) return *this;

		m_Code = rhs.m_Code;

		if (is_copy)
			delete m_pSPDV;

		if (rhs.m_pSPDV != nullptr)
				m_pSPDV = new SubchoicePresentationDataValues(*rhs.m_pSPDV);

		is_copy = true;

		return *this;
	}

	bool operator!=(const CPdvList& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<SubchoicePresentationDataValues>(m_pSPDV, rhs.m_pSPDV) ) return true;

		return false;
	}

	bool operator==(const CPdvList& rhs)
	{
		if (this == &rhs) return true;

		if ( *this != rhs ) return false;
		else return true;
	}

	virtual ~CPdvList()
	{
		if (is_copy)
			delete m_pSPDV;
	}

};

Q_DECLARE_METATYPE(CPdvList*)


#endif /* INCLUDE_PRESENTATION_ASN1_PDVLIST_H_ */
