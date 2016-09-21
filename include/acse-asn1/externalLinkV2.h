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
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier Idany READ getIdAny)
	Q_PROPERTY(IBerBaseType* any READ getAny)
	Q_PROPERTY(CBerIdentifier Idoctstr READ getIdOctetString)
	Q_PROPERTY(IBerBaseType* octstr READ getOctetString)
	Q_PROPERTY(CBerIdentifier Idbitstr READ getIdBitStr)
	Q_PROPERTY(IBerBaseType* bitstr READ getBitString)

	bool is_copy;

public:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdentifier() { return c_Identifier; }

	CBerIdentifier getIdAny() { return CBerAny::getBerIdentifier(); }
	CBerIdentifier getIdOctetString() { return CBerOctetString::getBerIdentifier(); }
	CBerIdentifier getIdBitStr() { return CBerBitString::getBerIdentifier(); }

	IBerBaseType* getAny() { return m_pAny; }
	IBerBaseType* getOctetString() { return m_pOctetString; }
	IBerBaseType* getBitString() { return m_pBitString; }

protected:

	inline IBerBaseType* create_object_by_id(const CBerIdentifier& id)
	{
		qDebug() << "INFO: CExternalLinkV2 create member by id = " << id.getCode()->toHex();

		if ( getIdAny() == id )
			{ m_pAny = new CBerAny(); is_copy = true; return m_pAny; }
		if ( getIdOctetString() == id )
			{ m_pOctetString = new CBerOctetString(); is_copy = true; return m_pOctetString; }
		if ( getIdBitStr() == id )
			{ m_pBitString = new CBerBitString(); is_copy = true; return m_pBitString; }

		return nullptr;
	}

	inline void create_objects(const CExternalLinkV2& rhs)
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

	inline void delete_all_objects()
	{
		if (is_copy)
		{
			delete m_pAny;
			delete m_pOctetString;
			delete m_pBitString;
		}
	}

protected:

	const CBerIdentifier c_Identifier;

	QByteArray m_Code;

	CBerAny* m_pAny;
	CBerOctetString* m_pOctetString;
	CBerBitString* m_pBitString;

public:

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	static CBerIdentifier getBerIdentifier()
	{
		return CBerIdentifier();
	}

	CExternalLinkV2():
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		m_pAny(nullptr),
		m_pOctetString(nullptr),
		m_pBitString(nullptr)
	{}

	CExternalLinkV2(CBerAny* pAny, CBerOctetString* pOctetString, CBerBitString* pBitString):
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		m_pAny(pAny),
		m_pOctetString(pOctetString),
		m_pBitString(pBitString)
	{}

	CExternalLinkV2(const CExternalLinkV2& rhs): QObject(),
		c_Identifier(getBerIdentifier())
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

		if ( notEqualsPointersAndValues<CBerAny>(m_pAny, rhs.m_pAny) ) return true;
		if ( notEqualsPointersAndValues<CBerOctetString>(m_pOctetString, rhs.m_pOctetString) ) return true;
		if ( notEqualsPointersAndValues<CBerBitString>(m_pBitString, rhs.m_pBitString) ) return true;

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
