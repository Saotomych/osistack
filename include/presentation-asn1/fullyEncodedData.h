/*
 * fullyEncodedData.h
 *
 *  Created on: 24 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_PRESENTATION_ASN1_FULLYENCODEDDATA_H_
#define INCLUDE_PRESENTATION_ASN1_FULLYENCODEDDATA_H_

#include "osistack_global.h"
#include "PdvList.h"

class OSISTACK_SHAREDEXPORT CFullyEncodedData: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier idseqof READ getIdSeqOf)
	Q_PROPERTY(QLinkedList<CPdvList>* seqof READ getSeqOf)

	bool is_copy;

protected:
	const CBerIdentifier c_Identifier;
	QByteArray m_Code;

	QLinkedList<CPdvList>* m_pSeqOf;

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdentifier() { return c_Identifier; }

	CBerIdentifier getIdSeqOf() { return CBerIdentifier(); }

	QLinkedList<CPdvList>* getSeqOf() { return m_pSeqOf; }

public:

	typedef CContainerStorage<CFullyEncodedData, QLinkedList<CPdvList>, CPdvList> LocalStorage;
	ASN1_CODEC( LocalStorage )

	static quint32 s_metaTypeIdentifier;
	static quint32 s_metaTypeListId;

	static CBerIdentifier getBerIdentifier()
	{
		return CBerIdentifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
	}

	CFullyEncodedData():
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		m_pSeqOf(nullptr)
	{}

	CFullyEncodedData(QLinkedList<CPdvList>* pExternalListV1):
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		m_pSeqOf(pExternalListV1)
	{}

	CFullyEncodedData(const CFullyEncodedData& rhs): QObject(),
		c_Identifier(getBerIdentifier())
	{
		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QLinkedList<CPdvList>(*rhs.m_pSeqOf);

		is_copy = true;
	}

	CFullyEncodedData operator=(const CFullyEncodedData& rhs)
	{
		if (this == &rhs) return *this;

		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QLinkedList<CPdvList>(*rhs.m_pSeqOf);

		is_copy = true;

		return *this;
	}

	bool operator!=(const CFullyEncodedData& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<QLinkedList<CPdvList> >(m_pSeqOf, rhs.m_pSeqOf) ) return true;

		return false;
	}

	virtual ~CFullyEncodedData()
	{
		if (is_copy)
			delete m_pSeqOf;
	}

};

Q_DECLARE_METATYPE(CFullyEncodedData*)
Q_DECLARE_METATYPE(QLinkedList<CPdvList>*)

#endif /* INCLUDE_PRESENTATION_ASN1_FULLYENCODEDDATA_H_ */
