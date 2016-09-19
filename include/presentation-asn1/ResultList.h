/*
 * ResultList.h
 *
 *  Created on: 23 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef SRC_PRESENTATION_ASN1_RESULTLIST_H_
#define SRC_PRESENTATION_ASN1_RESULTLIST_H_

#include "osistack_global.h"
#include "ResultSubsequence.h"

class OSISTACK_SHAREDEXPORT CResultList: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier idOI READ getIdObjectIdentifierList)
	Q_PROPERTY(QLinkedList<CResultSubsequence>* OI READ getObjectIdentifierList)

	bool is_copy;

protected:
	const CBerIdentifier c_Identifier;
	QByteArray m_Code;

	QLinkedList<CResultSubsequence>* m_pSeqOf;

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdentifier() { return c_Identifier; }

	CBerIdentifier getIdObjectIdentifierList() { return CResultList::getBerIdentifier(); }

	QLinkedList<CResultSubsequence>* getObjectIdentifierList() { return m_pSeqOf; }

public:

	typedef CContainerStorage< CResultList, QLinkedList<CResultSubsequence>, CResultSubsequence > TLocalStorage;
	ASN1_CODEC( TLocalStorage )

	static quint32 s_metaTypeIdentifier;
	static quint32 s_metaTypeListId;

	static CBerIdentifier getBerIdentifier()
	{
		return CBerIdentifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
	}

	explicit CResultList(QLinkedList<CResultSubsequence>* pResultSubsequenceList):
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		m_pSeqOf(pResultSubsequenceList)
	{}

	explicit CResultList(QByteArray code):
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		m_pSeqOf(nullptr)
	{
		m_Code = code;
	}

	CResultList(const CResultList& rhs): QObject(),
		c_Identifier(getBerIdentifier())
	{
		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QLinkedList<CResultSubsequence>(*rhs.m_pSeqOf);

		is_copy = true;
	}

	CResultList operator=(const CResultList& rhs)
	{
		if (this == &rhs) return *this;

		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QLinkedList<CResultSubsequence>(*rhs.m_pSeqOf);

		is_copy = true;

		return *this;
	}

	bool operator!=(const CResultList& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<QLinkedList<CResultSubsequence> >(m_pSeqOf, rhs.m_pSeqOf) ) return true;

		return false;
	}

	virtual ~CResultList()
	{
		if (is_copy)
			delete m_pSeqOf;
	}

};

Q_DECLARE_METATYPE(CResultList*)
Q_DECLARE_METATYPE(QLinkedList<CResultSubsequence>*)

#endif /* SRC_PRESENTATION_ASN1_RESULTLIST_H_ */
