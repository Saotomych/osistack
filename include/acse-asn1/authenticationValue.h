/*
 * authenticationValue.h
 *
 *  Created on: 16 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_ACSE_ASN1_AUTHENTICATIONVALUE_H_
#define INCLUDE_ACSE_ASN1_AUTHENTICATIONVALUE_H_

#include "osistack_global.h"
#include "externalLinkV2.h"
#include "berGraphicString.h"
#include "berBitString.h"

class OSISTACK_SHAREDEXPORT CAuthenticationValue: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier Idgraphstr READ getIdGraphString)
	Q_PROPERTY(IBerBaseType* graphstr READ getGraphString)
	Q_PROPERTY(CBerIdentifier Idbitstr READ getIdBitString)
	Q_PROPERTY(IBerBaseType* bitstr READ getBitString)
	Q_PROPERTY(CBerIdentifier Idextlink READ getIdExternalLink)
	Q_PROPERTY(IBerBaseType* extlink READ getExternalLink)

	bool is_copy;

protected:

	const CBerIdentifier c_Identifier;

public:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdentifier() { return c_Identifier; }

	CBerIdentifier getIdGraphString() { return CBerGraphicString::getBerIdentifier(); }
	CBerIdentifier getIdBitString() { return CBerBitString::getBerIdentifier(); }
	CBerIdentifier getIdExternalLink() { return CExternalLinkV2::getBerIdentifier(); }

	IBerBaseType* getGraphString() { return m_pGraphString; }
	IBerBaseType* getBitString() { return m_pBitString; }
	IBerBaseType* getExternalLink() { return m_pExternalLink; }

protected:

	inline IBerBaseType* create_object_by_id(const CBerIdentifier& id)
	{
		qDebug() << "INFO: CAuthenticationValue create member by id = " << id.getCode()->toHex();

		if ( getIdGraphString() == id )
			{ m_pGraphString = new CBerGraphicString(); is_copy = true; return m_pGraphString; }
		if ( getIdBitString() == id )
			{ m_pBitString = new CBerBitString(); is_copy = true; return m_pBitString; }
		if ( getIdExternalLink() == id )
			{ m_pExternalLink = new CExternalLinkV2(); is_copy = true; return m_pExternalLink; }

		return nullptr;
	}

	inline void create_objects(const CAuthenticationValue& rhs)
	{
		std::unique_ptr<CBerGraphicString> p1
				( (rhs.m_pGraphString != nullptr) ? new CBerGraphicString(*rhs.m_pGraphString): nullptr );
		std::unique_ptr<CBerBitString> p2
				( (rhs.m_pBitString != nullptr) ? new CBerBitString(*rhs.m_pBitString) : nullptr );
		std::unique_ptr<CExternalLinkV2> p3
				( (rhs.m_pExternalLink != nullptr) ? new CExternalLinkV2(*rhs.m_pExternalLink) : nullptr );

		m_pGraphString = p1.release();
		m_pBitString = p2.release();
		m_pExternalLink = p3.release();
	}

	inline void delete_all_objects()
	{
		if (is_copy)
		{
			delete m_pGraphString;
			delete m_pBitString;
			delete m_pExternalLink;
		}
	}

protected:
	QByteArray m_Code;

	CBerGraphicString* m_pGraphString;
	CBerBitString* m_pBitString;
	CExternalLinkV2* m_pExternalLink;

public:

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	static CBerIdentifier getBerIdentifier()
	{
		return CBerIdentifier();
	}

	CAuthenticationValue():
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		m_pGraphString(nullptr),
		m_pBitString(nullptr),
		m_pExternalLink(nullptr)
	{}

	CAuthenticationValue(CBerGraphicString* pGraphString, CExternalLinkV2* pExternalLink, CBerBitString* pBitString):
		c_Identifier(getBerIdentifier())
	{
		m_pGraphString = pGraphString;
		m_pExternalLink = pExternalLink;
		m_pBitString = pBitString;

		is_copy = false;
	}

	CAuthenticationValue(const CAuthenticationValue& rhs): QObject(),
		c_Identifier(getBerIdentifier())
	{
		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;
	}

	CAuthenticationValue operator=(const CAuthenticationValue& rhs)
	{
		if (this == &rhs) return *this;

		delete_all_objects();

		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;

		return *this;
	}

	bool operator !=(const CAuthenticationValue& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerGraphicString>(m_pGraphString, rhs.m_pGraphString) ) return true;
		if ( notEqualsPointersAndValues<CExternalLinkV2>(m_pExternalLink, rhs.m_pExternalLink) ) return true;
		if ( notEqualsPointersAndValues<CBerBitString>(m_pBitString, rhs.m_pBitString) ) return true;

		return false;
	}

	virtual ~CAuthenticationValue()
	{
		delete_all_objects();
	}

};

Q_DECLARE_METATYPE(CAuthenticationValue*)

#endif /* INCLUDE_ACSE_ASN1_AUTHENTICATIONVALUE_H_ */
