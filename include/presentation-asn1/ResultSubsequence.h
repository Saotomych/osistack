/*
 * ResultSubsequence.h
 *
 *  Created on: 23 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef SRC_PRESENTATION_ASN1_RESULTSUBSEQUENCE_H_
#define SRC_PRESENTATION_ASN1_RESULTSUBSEQUENCE_H_

#include "osistack_global.h"
#include "berInteger.h"
#include "berObjectIdentifier.h"

class OSISTACK_SHAREDEXPORT CResultSubsequence: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(IBerBaseType* result READ getResult)
	Q_PROPERTY(IBerBaseType* transferSyntaxName READ getTransferSyntaxName)
	Q_PROPERTY(IBerBaseType* providerReason READ getProviderReason)

	bool is_copy;

protected:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdentifier() { return c_Identifier; }
	IBerBaseType* getResult() { return m_pResult; }
	IBerBaseType* getTransferSyntaxName() { return m_pTransferSyntaxName; }
	IBerBaseType* getProviderReason() { return m_pProviderReason; }

	void create_objects(const CResultSubsequence& rhs)
	{
		std::unique_ptr<CBerInteger> p1
				( (rhs.m_pResult != nullptr) ? new CBerInteger(*rhs.m_pResult): nullptr );
		std::unique_ptr<CBerObjectIdentifier> p2
				( (rhs.m_pTransferSyntaxName != nullptr) ? new CBerObjectIdentifier(*rhs.m_pTransferSyntaxName) : nullptr );
		std::unique_ptr<CBerInteger> p3
				( (rhs.m_pProviderReason != nullptr) ? new CBerInteger(*rhs.m_pProviderReason) : nullptr );

		m_pResult = p1.release();
		m_pTransferSyntaxName = p2.release();
		m_pProviderReason = p3.release();
	}

	void delete_all_objects()
	{
		if (is_copy)
		{
			delete m_pResult;
			delete m_pTransferSyntaxName;
			delete m_pProviderReason;
		}
	}

protected:
	const CBerIdentifier c_Identifier;
	QByteArray m_Code;

	CBerInteger* m_pResult;
	CBerObjectIdentifier* m_pTransferSyntaxName;
	CBerInteger* m_pProviderReason;

public:

	ASN1_CODEC(CBerBaseStorage)

	static CBerIdentifier s_Identifier;
	static quint32 s_metaTypeIdentifier;

	CResultSubsequence(CBerInteger* pResult, CBerObjectIdentifier* pTransferSyntaxName, CBerInteger* pProviderReason):
		is_copy(false),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16),
		m_pResult(pResult),
		m_pTransferSyntaxName(pTransferSyntaxName),
		m_pProviderReason(pProviderReason)
	{}

	CResultSubsequence(const CResultSubsequence& rhs): QObject(),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16)
	{
		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;
	}

	CResultSubsequence& operator=(const CResultSubsequence& rhs)
	{
		if (this == &rhs) return *this;

		delete_all_objects();

		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;

		return *this;
	}

	bool operator!=(const CResultSubsequence& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerInteger>(m_pResult, rhs.m_pResult) ) return true;
		if ( notEqualsPointersAndValues<CBerObjectIdentifier>(m_pTransferSyntaxName, rhs.m_pTransferSyntaxName) ) return true;
		if ( notEqualsPointersAndValues<CBerInteger>(m_pProviderReason, rhs.m_pProviderReason) ) return true;

		return false;
	}

	bool operator==(const CResultSubsequence& rhs)
	{
		if (*this != rhs) return false;
		return true;
	}

	virtual ~CResultSubsequence()
	{
		delete_all_objects();
	}
};

Q_DECLARE_METATYPE(CResultSubsequence*)

#endif /* SRC_PRESENTATION_ASN1_RESULTSUBSEQUENCE_H_ */
