/*
 * modeSelector.h
 *
 *  Created on: 24 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_PRESENTATION_ASN1_MODESELECTOR_H_
#define INCLUDE_PRESENTATION_ASN1_MODESELECTOR_H_


#include "osistack_global.h"
#include "berInteger.h"

class OSISTACK_SHAREDEXPORT CModeSelector: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier Identifier READ getIdModeValue)
	Q_PROPERTY(IBerBaseType* OI READ getModeValue)

	bool is_copy;

protected:

	QByteArray m_Code;

	CBerInteger* m_pModeValue;

	const CBerIdentifier c_Identifier;
	const CBerIdentifier c_IdModValue;

	CBerIdentifier getIdentifier() { return c_Identifier; }
	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdModeValue() { return c_IdModValue; }
	IBerBaseType* getModeValue() { return m_pModeValue; }

public:

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	static CBerIdentifier getBerIdentifier()
	{
		return CBerIdentifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 17);
	}

	CModeSelector(CBerInteger* pModeValue):
		is_copy(false),
		m_pModeValue(pModeValue),
		c_Identifier(getBerIdentifier()),
		c_IdModValue(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 0)
	{
	}

	CModeSelector(QByteArray& code):
		is_copy(false),
		m_pModeValue(nullptr),
		c_Identifier(getBerIdentifier()),
		c_IdModValue(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 0)
	{
		m_Code = code;
	}

	CModeSelector(const CModeSelector& rhs): QObject(),
		c_Identifier(getBerIdentifier()),
		c_IdModValue(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 0)
	{
		m_Code = rhs.m_Code;

		if (rhs.m_pModeValue != nullptr)
		{
			m_pModeValue = new CBerInteger(*rhs.m_pModeValue);
		}

		is_copy = true;
	}

	CModeSelector& operator=(const CModeSelector& rhs)
	{
		if (this == &rhs) return *this;

		m_Code = rhs.m_Code;

		if (is_copy)
			delete m_pModeValue;

		if (rhs.m_pModeValue != nullptr)
		{
			m_pModeValue = new CBerInteger(*rhs.m_pModeValue);
		}

		is_copy = true;

		return *this;
	}

	bool operator!=(const CModeSelector& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerInteger>(m_pModeValue, rhs.m_pModeValue) ) return true;

		return false;
	}

	virtual ~CModeSelector()
	{
		if (is_copy)
			delete m_pModeValue;
	}
};

Q_DECLARE_METATYPE(CModeSelector*)

#endif /* INCLUDE_PRESENTATION_ASN1_MODESELECTOR_H_ */
