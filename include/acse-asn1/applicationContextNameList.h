/*
 * applicationContextNameList.h
 *
 *  Created on: 16 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_ACSE_ASN1_APPLICATIONCONTEXTNAMELIST_H_
#define INCLUDE_ACSE_ASN1_APPLICATIONCONTEXTNAMELIST_H_

#include "osistack_global.h"
#include "berObjectIdentifier.h"

class OSISTACK_SHAREDEXPORT CApplicationContextNameList: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier* Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(QLinkedList<CBerObjectIdentifier>* OI READ getObjectIdentifierList)

	bool is_copy;

protected:
	CBerIdentifier m_Identifier;
	QByteArray m_Code;

	QLinkedList<CBerObjectIdentifier>* m_pSeqOf;

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier* getIdentifier() { return &m_Identifier; }
	QLinkedList<CBerObjectIdentifier>* getObjectIdentifierList() { return m_pSeqOf; }

public:

	typedef CContainerStorage< QLinkedList<CBerObjectIdentifier>, CBerObjectIdentifier > TLocalStorage;
	ASN1_CODEC( TLocalStorage )

	static CBerIdentifier s_Identifier;
	static quint32 s_metaTypeIdentifier;
	static quint32 s_metaTypeListId;

	explicit CApplicationContextNameList(QLinkedList<CBerObjectIdentifier>* pObjectIdentifierList):
		is_copy(false),
		m_Identifier(s_Identifier),
		m_pSeqOf(pObjectIdentifierList)
	{}

	CApplicationContextNameList(const CApplicationContextNameList& rhs): QObject()
	{
		m_Identifier = rhs.m_Identifier;
		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QLinkedList<CBerObjectIdentifier>(*rhs.m_pSeqOf);

		is_copy = true;
	}

	CApplicationContextNameList operator=(const CApplicationContextNameList& rhs)
	{
		if (this == &rhs) return *this;

		m_Identifier = rhs.m_Identifier;
		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QLinkedList<CBerObjectIdentifier>(*rhs.m_pSeqOf);

		is_copy = true;

		return *this;
	}

	bool operator!=(const CApplicationContextNameList& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<QLinkedList<CBerObjectIdentifier> >(m_pSeqOf, rhs.m_pSeqOf) ) return true;

		return false;
	}

	virtual ~CApplicationContextNameList()
	{
		if (is_copy)
			delete m_pSeqOf;
	}

};

Q_DECLARE_METATYPE(CApplicationContextNameList*)
Q_DECLARE_METATYPE(QLinkedList<CBerObjectIdentifier>*)

#endif /* INCLUDE_ACSE_ASN1_APPLICATIONCONTEXTNAMELIST_H_ */
