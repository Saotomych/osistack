/*
 * RLRQ_apdu.h
 *
 *  Created on: 18 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_ACSE_ASN1_RLRQ_APDU_H_
#define INCLUDE_ACSE_ASN1_RLRQ_APDU_H_

#include "osistack_global.h"
#include "berInteger.h"
#include "associationInformation.h"

class OSISTACK_SHAREDEXPORT CRLrqApdu: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(IBerBaseType* Reason READ getReason)
	Q_PROPERTY(IBerBaseType* UserInformation READ getUserInformation)

	bool is_copy;

public:

	QByteArray* getCode() { return &m_Code; }
	IBerBaseType* getReason() { return m_pReason; }
	IBerBaseType* getUserInformation() { return m_pUserInformation; }

protected:

	void create_objects(const CRLrqApdu& rhs)
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
	const CBerIdentifier c_Identifier;
	QByteArray m_Code;

	CBerInteger* m_pReason;
	CAssociationInformation* m_pUserInformation;

public:

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	CBerIdentifier getIdentifier() { return c_Identifier; }

	CRLrqApdu():
		is_copy(false),
		c_Identifier(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::CONSTRUCTED, 2),
		m_pReason(nullptr),
		m_pUserInformation(nullptr)
	{}

	CRLrqApdu(CBerInteger* pReason, CAssociationInformation* pUserInformation):
		is_copy(false),
		c_Identifier(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::CONSTRUCTED, 2),
		m_pReason(pReason),
		m_pUserInformation(pUserInformation)
	{}

	CRLrqApdu(const CRLrqApdu& rhs):QObject(),
		c_Identifier(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::CONSTRUCTED, 2)
	{
		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;
	}

	CRLrqApdu& operator=(const CRLrqApdu& rhs)
	{
		if (this == &rhs) return *this;

		delete_all_objects();

		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;

		return *this;
	}

	bool operator!=(const CRLrqApdu& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerInteger>(m_pReason, rhs.m_pReason) ) return true;
		if ( notEqualsPointersAndValues<CAssociationInformation>(m_pUserInformation, rhs.m_pUserInformation) ) return true;

		return false;
	}

	virtual ~CRLrqApdu()
	{
		delete_all_objects();
	}

};

Q_DECLARE_METATYPE(CRLrqApdu*)

#endif /* INCLUDE_ACSE_ASN1_RLRQ_APDU_H_ */
