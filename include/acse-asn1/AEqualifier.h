/*
 * AEqualifier.h
 *
 *  Created on: 16 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_ACSE_ASN1_AEQUALIFIER_H_
#define INCLUDE_ACSE_ASN1_AEQUALIFIER_H_

#include "osistack_global.h"
#include "berInteger.h"

class OSISTACK_SHAREDEXPORT CAeQualifier: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(IBerBaseType* Integer READ getInteger)

	bool is_copy;

protected:
	QByteArray m_Code;

	CBerInteger* m_pInteger;

	const CBerIdentifier c_Identifier;

public:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdentifier() { return c_Identifier; }
	IBerBaseType* getInteger() { return m_pInteger; }

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	CAeQualifier(CBerInteger* pInteger):
		is_copy(false),
		m_pInteger(pInteger),
		c_Identifier()
	{ }

	CAeQualifier(const CAeQualifier& rhs): QObject(),
		c_Identifier()
	{
			m_Code = rhs.m_Code;

			if (rhs.m_pInteger != nullptr)
					m_pInteger = new CBerInteger(*rhs.m_pInteger);

			is_copy = true;
	}

	CAeQualifier& operator=(const CAeQualifier& rhs)
	{
			if (this == &rhs) return *this;

			m_Code = rhs.m_Code;

			if (is_copy)
				delete m_pInteger;

			if (rhs.m_pInteger != nullptr)
					m_pInteger = new CBerInteger(*rhs.m_pInteger);

			is_copy = true;

			return *this;
	}

	bool operator!=(const CAeQualifier& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerInteger>(m_pInteger, rhs.m_pInteger) ) return true;

		return false;
	}

	virtual ~CAeQualifier()
	{
		if (is_copy)
			delete m_pInteger;
	}

};

Q_DECLARE_METATYPE(CAeQualifier*)

#endif /* INCLUDE_ACSE_ASN1_AEQUALIFIER_H_ */
