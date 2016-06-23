/*
 * APtitle.h
 *
 *  Created on: 16 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_ACSE_ASN1_APTITLE_H_
#define INCLUDE_ACSE_ASN1_APTITLE_H_

#include "osistack_global.h"
#include "berObjectIdentifier.h"

class OSISTACK_SHAREDEXPORT CApTitle: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(IBerBaseType* OI READ getApTitleForm2)

	bool is_copy;

protected:

	QByteArray m_Code;

	CBerObjectIdentifier* m_pApTitleForm2;

	const CBerIdentifier c_Identifier;

public:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdentifier() { return c_Identifier; }
	IBerBaseType* getApTitleForm2() { return m_pApTitleForm2; }

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	CApTitle(CBerObjectIdentifier* pApTitleForm2):
		is_copy(false),
		m_pApTitleForm2(pApTitleForm2),
		c_Identifier()
	{ }

	CApTitle(const CApTitle& rhs): QObject(),
		c_Identifier()
	{
		m_Code = rhs.m_Code;

		if (rhs.m_pApTitleForm2 != nullptr)
			m_pApTitleForm2 = new CBerObjectIdentifier(*rhs.m_pApTitleForm2);

		is_copy = true;
	}

	CApTitle& operator=(const CApTitle& rhs)
	{
		if (this == &rhs) return *this;

		m_Code = rhs.m_Code;

		if (is_copy)
			delete m_pApTitleForm2;

		if (rhs.m_pApTitleForm2 != nullptr)
			m_pApTitleForm2 = new CBerObjectIdentifier(*rhs.m_pApTitleForm2);

		is_copy = true;

		return *this;
	}

	bool operator!=(const CApTitle& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerObjectIdentifier>(m_pApTitleForm2, rhs.m_pApTitleForm2) ) return true;

		return false;
	}

	virtual ~CApTitle()
	{
		if (is_copy)
			delete m_pApTitleForm2;
	}
};

Q_DECLARE_METATYPE(CApTitle*)

#endif /* INCLUDE_ACSE_ASN1_APTITLE_H_ */
