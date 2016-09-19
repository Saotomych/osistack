/*
 * associationInformation.h
 *
 *  Created on: 16 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_ASSOCIATIONINFORMATION_H_
#define INCLUDE_ASSOCIATIONINFORMATION_H_

#include "osistack_global.h"
#include "externalLinkV1.h"

class OSISTACK_SHAREDEXPORT CAssociationInformation: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier Idseqof READ getIdSeqOf)
	Q_PROPERTY(QLinkedList<CExternalLinkV1>* seqof READ getSeqOf)

	bool is_copy;

protected:
	CBerIdentifier c_Identifier;
	QByteArray m_Code;

	QLinkedList<CExternalLinkV1>* m_pSeqOf;

public:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdentifier() { return c_Identifier; }

	CBerIdentifier getIdSeqOf() { return CBerIdentifier(); }

	QLinkedList<CExternalLinkV1>* getSeqOf() { return m_pSeqOf; }

	typedef CContainerStorage<CAssociationInformation, QLinkedList<CExternalLinkV1>, CExternalLinkV1> LocalStorage;
	ASN1_CODEC( LocalStorage )

	static quint32 s_metaTypeIdentifier;
	static quint32 s_metaTypeListId;

	static CBerIdentifier getBerIdentifier()
	{
		return CBerIdentifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
	}

	CAssociationInformation(QLinkedList<CExternalLinkV1>* pExternalListV1):
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		m_pSeqOf(pExternalListV1)
	{}

	CAssociationInformation(const CAssociationInformation& rhs): QObject(),
		c_Identifier(getBerIdentifier())
	{
		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QLinkedList<CExternalLinkV1>(*rhs.m_pSeqOf);

		is_copy = true;
	}

	CAssociationInformation operator=(const CAssociationInformation& rhs)
	{
		if (this == &rhs) return *this;

		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QLinkedList<CExternalLinkV1>(*rhs.m_pSeqOf);

		is_copy = true;

		return *this;
	}

	bool operator!=(const CAssociationInformation& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<QLinkedList<CExternalLinkV1> >(m_pSeqOf, rhs.m_pSeqOf) ) return true;

		return false;
	}

	virtual ~CAssociationInformation()
	{
		if (is_copy)
			delete m_pSeqOf;
	}

};

Q_DECLARE_METATYPE(CAssociationInformation*)
Q_DECLARE_METATYPE(QLinkedList<CExternalLinkV1>*)

#endif /* INCLUDE_ASSOCIATIONINFORMATION_H_ */
