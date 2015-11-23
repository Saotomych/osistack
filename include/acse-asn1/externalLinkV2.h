/*
 * externalLinkV2.h
 *
 *  Created on: 16 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_ACSE_ASN1_EXTERNALLINKV2_H_
#define INCLUDE_ACSE_ASN1_EXTERNALLINKV2_H_

#include "osistack_global.h"
#include "berAny.h"
#include "berOctetString.h"
#include "berBitString.h"

class OSISTACK_SHAREDEXPORT CExternalLinkV2: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier* Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(IBerBaseType* any READ getAny)
	Q_PROPERTY(IBerBaseType* octstr READ getOctetString)
	Q_PROPERTY(IBerBaseType* bitstr READ getBitString)

	bool is_copy;

protected:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier* getIdentifier() { return nullptr; }
	IBerBaseType* getAny() { return m_pAny; }
	IBerBaseType* getOctetString() { return m_pOctetString; }
	IBerBaseType* getBitString() { return m_pBitString; }

	void create_objects(const CExternalLinkV2& rhs)
	{
		std::unique_ptr<CBerAny> p1
				( (rhs.m_pAny != nullptr) ? new CBerAny(*rhs.m_pAny): nullptr );
		std::unique_ptr<CBerOctetString> p2
				( (rhs.m_pOctetString != nullptr) ? new CBerOctetString(*rhs.m_pOctetString) : nullptr );
		std::unique_ptr<CBerBitString> p3
				( (rhs.m_pBitString != nullptr) ? new CBerBitString(*rhs.m_pBitString) : nullptr );

		m_pAny = p1.release();
		m_pOctetString = p2.release();
		m_pBitString = p3.release();
	}

	void delete_all_objects()
	{
		if (is_copy)
		{
			delete m_pAny;
			delete m_pOctetString;
			delete m_pBitString;
		}
	}

protected:
	QByteArray m_Code;

	CBerAny* m_pAny;
	CBerOctetString* m_pOctetString;
	CBerBitString* m_pBitString;

public:

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	CExternalLinkV2(CBerAny* pAny, CBerOctetString* pOctetString, CBerBitString* pBitString):
		is_copy(false),
		m_pAny(pAny),
		m_pOctetString(pOctetString),
		m_pBitString(pBitString)
	{}

	CExternalLinkV2(const CExternalLinkV2& rhs): QObject()
	{
		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;
	}

	CExternalLinkV2& operator=(const CExternalLinkV2& rhs)
	{
		if (this == &rhs) return *this;

		delete_all_objects();

		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;

		return *this;
	}

	bool operator!=(const CExternalLinkV2& rhs)
	{
		if (this == &rhs) return false;

		if (*m_pAny != *rhs.m_pAny) return true;
		if (*m_pOctetString != *rhs.m_pOctetString) return true;
		if (*m_pBitString != *rhs.m_pBitString) return true;

		return false;
	}

	bool operator==(const CExternalLinkV2& rhs)
	{
		if (*this != rhs) return false;
		return true;
	}

	virtual ~CExternalLinkV2()
	{
		delete_all_objects();
	}
};

Q_DECLARE_METATYPE(CExternalLinkV2*)

#endif /* INCLUDE_ACSE_ASN1_EXTERNALLINKV2_H_ */
