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
	Q_PROPERTY(CBerIdentifier* Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(QList<CResultSubsequence>* OI READ getObjectIdentifierList)

	bool is_copy;

protected:
	CBerIdentifier m_Identifier;
	QByteArray m_Code;

	QList<CResultSubsequence>* m_pSeqOf;

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier* getIdentifier() { return &m_Identifier; }
	QList<CResultSubsequence>* getObjectIdentifierList() { return m_pSeqOf; }

public:

	typedef CContainerStorage< QList<CResultSubsequence>, CResultSubsequence > TLocalStorage;
	ASN1_CODEC( TLocalStorage )

	static CBerIdentifier s_Identifier;
	static quint32 s_metaTypeIdentifier;
	static quint32 s_metaTypeListId;

	explicit CResultList(QList<CResultSubsequence>* pResultSubsequenceList):
		is_copy(false),
		m_Identifier(s_Identifier),
		m_pSeqOf(pResultSubsequenceList)
	{}

	CResultList(const CResultList& rhs): QObject()
	{
		m_Identifier = rhs.m_Identifier;
		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QList<CResultSubsequence>(*rhs.m_pSeqOf);

		is_copy = true;
	}

	CResultList operator=(const CResultList& rhs)
	{
		if (this == &rhs) return *this;

		m_Identifier = rhs.m_Identifier;
		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QList<CResultSubsequence>(*rhs.m_pSeqOf);

		is_copy = true;

		return *this;
	}

	bool operator!=(const CResultList& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<QList<CResultSubsequence> >(m_pSeqOf, rhs.m_pSeqOf) ) return true;

		return false;
	}

	virtual ~CResultList()
	{
		if (is_copy)
			delete m_pSeqOf;
	}

};

Q_DECLARE_METATYPE(CResultList*)
Q_DECLARE_METATYPE(QList<CResultSubsequence>*)

#endif /* SRC_PRESENTATION_ASN1_RESULTLIST_H_ */
