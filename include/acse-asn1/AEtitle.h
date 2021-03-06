/*
 * AEtitle.h
 *
 *  Created on: 23 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_ACSE_ASN1_AETITLE_H_
#define INCLUDE_ACSE_ASN1_AETITLE_H_

#include "osistack_global.h"
#include "berObjectIdentifier.h"

class OSISTACK_SHAREDEXPORT CAeTitle: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier IdOI READ getIdAeTitleForm2)
	Q_PROPERTY(IBerBaseType* OI READ getAeTitleForm2)

	bool is_copy;

protected:
	QByteArray m_Code;

	CBerObjectIdentifier* m_pAeTitleForm2;

	const CBerIdentifier c_Identifier;

	inline IBerBaseType* create_object_by_id(const CBerIdentifier& id)
	{
		qDebug() << "INFO: CAeTitle create member by id = " << id.getCode()->toHex();

		if ( getIdAeTitleForm2() == id )
			{ m_pAeTitleForm2 = new CBerObjectIdentifier(); is_copy = true; return m_pAeTitleForm2; }

		return nullptr;
	}

public:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdentifier() { return c_Identifier; }

	CBerIdentifier getIdAeTitleForm2() { return CBerObjectIdentifier::getBerIdentifier(); }

	IBerBaseType* getAeTitleForm2() { return m_pAeTitleForm2; }

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	static CBerIdentifier getBerIdentifier()
	{
		return CBerIdentifier();
	}

	CAeTitle(CBerObjectIdentifier* pApTitleForm2):
		is_copy(false),
		m_pAeTitleForm2(pApTitleForm2),
		c_Identifier(getBerIdentifier())
	{ }

	CAeTitle(const CAeTitle& rhs): QObject()
	{
		m_Code = rhs.m_Code;

		if (rhs.m_pAeTitleForm2 != nullptr)
			m_pAeTitleForm2 = new CBerObjectIdentifier(*rhs.m_pAeTitleForm2);

		is_copy = true;
	}

	CAeTitle& operator=(const CAeTitle& rhs)
	{
		if (this == &rhs) return *this;

		m_Code = rhs.m_Code;

		if (is_copy)
			delete m_pAeTitleForm2;

		if (rhs.m_pAeTitleForm2 != nullptr)
			m_pAeTitleForm2 = new CBerObjectIdentifier(*rhs.m_pAeTitleForm2);

		is_copy = true;

		return *this;
	}

	bool operator!=(const CAeTitle& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerObjectIdentifier>(m_pAeTitleForm2, rhs.m_pAeTitleForm2) ) return true;

		return false;
	}

	virtual ~CAeTitle()
	{
		if (is_copy)
			delete m_pAeTitleForm2;
	}
};

Q_DECLARE_METATYPE(CAeTitle*)

#endif /* INCLUDE_ACSE_ASN1_AETITLE_H_ */
