/*
 * associateSourceDiagnostic.h
 *
 *  Created on: 17 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_ACSE_ASN1_ASSOCIATESOURCEDIAGNOSTIC_H_
#define INCLUDE_ACSE_ASN1_ASSOCIATESOURCEDIAGNOSTIC_H_

#include "osistack_global.h"
#include "berAny.h"
#include "berInteger.h"

class OSISTACK_SHAREDEXPORT CAssociateSourceDiagnostic: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier* Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(IBerBaseType* AcseServiceUser READ getAcseServiceUser)
	Q_PROPERTY(IBerBaseType* AcseServiceProvider READ getAcseServiceProvider)

	bool is_copy;

protected:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier* getIdentifier() { return nullptr; }
	IBerBaseType* getAcseServiceUser() { return m_pAcseServiceUser; }
	IBerBaseType* getAcseServiceProvider() { return m_pAcseServiceProvider; }

	void create_objects(const CAssociateSourceDiagnostic& rhs)
	{
		std::unique_ptr<CBerInteger> p1
				( (rhs.m_pAcseServiceUser != nullptr) ? new CBerInteger(*rhs.m_pAcseServiceUser): nullptr );
		std::unique_ptr<CBerInteger> p2
				( (rhs.m_pAcseServiceProvider != nullptr) ? new CBerInteger(*rhs.m_pAcseServiceProvider) : nullptr );

		m_pAcseServiceUser = p1.release();
		m_pAcseServiceProvider = p2.release();
	}

	void delete_all_objects()
	{
		if (is_copy)
		{
			delete m_pAcseServiceUser;
			delete m_pAcseServiceProvider;
		}
	}

protected:
	QByteArray m_Code;

	CBerInteger* m_pAcseServiceUser;
	CBerInteger* m_pAcseServiceProvider;

public:

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	CAssociateSourceDiagnostic(CBerInteger* pAcseServiceUser, CBerInteger* pAcseServiceProvider):
		is_copy(false),
		m_pAcseServiceUser(pAcseServiceUser),
		m_pAcseServiceProvider(pAcseServiceProvider)
	{ }

	CAssociateSourceDiagnostic(const CAssociateSourceDiagnostic& rhs): QObject()
	{
		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;
	}

	CAssociateSourceDiagnostic& operator=(const CAssociateSourceDiagnostic& rhs)
	{
		if (this == &rhs) return *this;

		delete_all_objects();

		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;

		return *this;
	}

	bool operator!=(const CAssociateSourceDiagnostic& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerInteger>(m_pAcseServiceUser, rhs.m_pAcseServiceUser) ) return true;
		if ( notEqualsPointersAndValues<CBerInteger>(m_pAcseServiceProvider, rhs.m_pAcseServiceProvider) ) return true;

		return false;
	}

	virtual ~CAssociateSourceDiagnostic()
	{
		delete_all_objects();
	}
};

Q_DECLARE_METATYPE(CAssociateSourceDiagnostic*)

#endif /* INCLUDE_ACSE_ASN1_ASSOCIATESOURCEDIAGNOSTIC_H_ */
