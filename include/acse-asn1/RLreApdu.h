/*
 * RLRE_apdu.h
 *
 *  Created on: 18 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_ACSE_ASN1_RLRE_APDU_H_
#define INCLUDE_ACSE_ASN1_RLRE_APDU_H_

#include "osistack_global.h"
#include "berInteger.h"
#include "associationInformation.h"

class CRLreApdu: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier* Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(IBerBaseType* ProtocolVersion READ getReason)
	Q_PROPERTY(IBerBaseType* ProtocolVersion READ getUserInformation)

	bool is_copy;

protected:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier* getIdentifier() { return &m_Identifier; }
	IBerBaseType* getReason() { return m_pReason; }
	IBerBaseType* getUserInformation() { return m_pUserInformation; }

	void create_objects(const CRLreApdu& rhs)
	{
		std::unique_ptr<CBerInteger> p1
				( (rhs.m_pReason != nullptr) ? new CBerInteger(*rhs.m_pReason): nullptr );
		std::unique_ptr<CAssociationInformation> p2
				( (rhs.m_pUserInformation != nullptr) ? new CAssociationInformation(*rhs.m_pUserInformation) : nullptr );

		m_pReason = p1.release();
		m_pUserInformation = p2.release();
	}

	void delete_all_objects()
	{
		if (is_copy)
		{
			delete m_pReason;
			delete m_pUserInformation;
		}
	}

protected:
	CBerIdentifier m_Identifier;
	QByteArray m_Code;

	CBerInteger* m_pReason;
	CAssociationInformation* m_pUserInformation;

public:

	ASN1_CODEC(CBerBaseStorage)

	static CBerIdentifier s_Identifier;
	static quint32 s_metaTypeIdentifier;

	CRLreApdu(CBerInteger* pReason, CAssociationInformation* pUserInformation):
		is_copy(false),
		m_Identifier(s_Identifier),
		m_pReason(pReason),
		m_pUserInformation(pUserInformation)
	{}

	CRLreApdu(const CRLreApdu& rhs):QObject()
	{
		create_objects(rhs);

		m_Identifier = rhs.m_Identifier;
		m_Code = rhs.m_Code;
		is_copy = true;
	}

	CRLreApdu& operator=(const CRLreApdu& rhs)
	{
		if (this == &rhs) return *this;

		delete_all_objects();

		create_objects(rhs);

		m_Identifier = rhs.m_Identifier;
		m_Code = rhs.m_Code;
		is_copy = true;

		return *this;
	}

	bool operator!=(const CRLreApdu& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerInteger>(m_pReason, rhs.m_pReason) ) return true;
		if ( notEqualsPointersAndValues<CAssociationInformation>(m_pUserInformation, rhs.m_pUserInformation) ) return true;

		return false;
	}

	virtual ~CRLreApdu()
	{
		delete_all_objects();
	}

};

Q_DECLARE_METATYPE(CRLreApdu*)

#endif /* INCLUDE_ACSE_ASN1_RLRE_APDU_H_ */
