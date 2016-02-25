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
	Q_PROPERTY(CBerIdentifier* Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(QLinkedList<CExternalLinkV1>* seqof READ getSeqOf)

	bool is_copy;

protected:
	CBerIdentifier m_Identifier;
	QByteArray m_Code;

	QLinkedList<CExternalLinkV1>* m_pSeqOf;

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier* getIdentifier() { return &m_Identifier; }
	QLinkedList<CExternalLinkV1>* getSeqOf() { return m_pSeqOf; }

public:

	typedef CContainerStorage<QLinkedList<CExternalLinkV1>, CExternalLinkV1> LocalStorage;
	ASN1_CODEC( LocalStorage )

	static CBerIdentifier s_Identifier;
	static quint32 s_metaTypeIdentifier;
	static quint32 s_metaTypeListId;

	CAssociationInformation(QLinkedList<CExternalLinkV1>* pExternalListV1):
		is_copy(false),
		m_Identifier(s_Identifier),
		m_pSeqOf(pExternalListV1)
	{}

	CAssociationInformation(const CAssociationInformation& rhs): QObject()
	{
		m_Identifier = rhs.m_Identifier;
		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QLinkedList<CExternalLinkV1>(*rhs.m_pSeqOf);

		is_copy = true;
	}

	CAssociationInformation operator=(const CAssociationInformation& rhs)
	{
		if (this == &rhs) return *this;

		m_Identifier = rhs.m_Identifier;
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
