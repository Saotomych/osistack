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
	Q_PROPERTY(CBerIdentifier* Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(IBerBaseType* graphstr READ getGraphString)
	Q_PROPERTY(IBerBaseType* bitstr READ getBitString)
	Q_PROPERTY(IBerBaseType* extlink READ getExternalLink)

	bool is_copy;

protected:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier* getIdentifier() { return nullptr; }
	IBerBaseType* getGraphString() { return m_pGraphString; }
	IBerBaseType* getBitString() { return m_pBitString; }
	IBerBaseType* getExternalLink() { return m_pExternalLink; }

	void create_objects(const CAuthenticationValue& rhs)
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

	void delete_all_objects()
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

	CAuthenticationValue(CBerGraphicString* pGraphString, CExternalLinkV2* pExternalLink, CBerBitString* pBitString)
	{
		m_pGraphString = pGraphString;
		m_pExternalLink = pExternalLink;
		m_pBitString = pBitString;

		is_copy = false;
	}

	CAuthenticationValue(const CAuthenticationValue& rhs): QObject()
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

		if (*m_pGraphString != *rhs.m_pGraphString) return true;
		if (*m_pExternalLink != *rhs.m_pExternalLink) return true;
		if (*m_pBitString != *rhs.m_pBitString) return true;

		return false;
	}

	virtual ~CAuthenticationValue()
	{
		delete_all_objects();
	}

};

Q_DECLARE_METATYPE(CAuthenticationValue*)

#endif /* INCLUDE_ACSE_ASN1_AUTHENTICATIONVALUE_H_ */
