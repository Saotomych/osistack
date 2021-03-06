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
	Q_PROPERTY(CBerIdentifier IdInteger READ getIdInteger)
	Q_PROPERTY(IBerBaseType* Integer READ getInteger)

	bool is_copy;

protected:
	QByteArray m_Code;

	CBerInteger* m_pInteger;

	const CBerIdentifier c_Identifier;

	inline IBerBaseType* create_object_by_id(const CBerIdentifier& id)
	{
		qDebug() << "INFO: CAeQualifier create member by id = " << id.getCode()->toHex();

		if ( getIdInteger() == id )
			{ m_pInteger = new CBerInteger(); is_copy = true; return m_pInteger; }

		return nullptr;
	}

public:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdentifier() { return c_Identifier; }

	CBerIdentifier getIdInteger() { return CBerInteger::getBerIdentifier(); }

	IBerBaseType* getInteger() { return m_pInteger; }

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	static CBerIdentifier getBerIdentifier()
	{
		return CBerIdentifier();
	}

	CAeQualifier():
		is_copy(false),
		m_pInteger(nullptr),
		c_Identifier(getBerIdentifier())
	{ }

	CAeQualifier(CBerInteger* pInteger):
		is_copy(false),
		m_pInteger(pInteger),
		c_Identifier(getBerIdentifier())
	{ }

	CAeQualifier(const CAeQualifier& rhs): QObject(),
		c_Identifier(getBerIdentifier())
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
