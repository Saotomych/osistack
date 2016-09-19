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

class OSISTACK_SHAREDEXPORT CApplicationContextName: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier IdOI READ getIdObjectIdentifier)
	Q_PROPERTY(IBerBaseType* OI READ getObjectIdentifier)

	bool is_copy;

protected:
	const CBerIdentifier c_Identifier;
	QByteArray m_Code;

	CBerObjectIdentifier* m_pAppContextName;

public:

	CBerIdentifier getIdentifier() { return c_Identifier; }
	QByteArray* getCode() { return &m_Code; }

	CBerIdentifier getIdObjectIdentifier() { return CBerObjectIdentifier::getBerIdentifier(); }

	IBerBaseType* getObjectIdentifier() { return m_pAppContextName; }

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	static CBerIdentifier getBerIdentifier()
	{
		return CBerIdentifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::PRIMITIVE, 16);
	}

	explicit CApplicationContextName(CBerObjectIdentifier* pObjectIdentifier):
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		m_pAppContextName(pObjectIdentifier)
	{}

	explicit CApplicationContextName(QByteArray& code):
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		m_Code(code),
		m_pAppContextName(nullptr)
	{}

	CApplicationContextName(const CApplicationContextName& rhs): QObject(),
		c_Identifier(getBerIdentifier())
	{
		m_Code = rhs.m_Code;

		if (rhs.m_pAppContextName != nullptr)
			m_pAppContextName = new CBerObjectIdentifier(*rhs.m_pAppContextName);

		is_copy = true;
	}

	CApplicationContextName operator=(const CApplicationContextName& rhs)
	{
		if (this == &rhs) return *this;

		m_Code = rhs.m_Code;

		if (rhs.m_pAppContextName != nullptr)
			m_pAppContextName = new CBerObjectIdentifier(*rhs.m_pAppContextName);

		is_copy = true;

		return *this;
	}

	bool operator==(const CApplicationContextName& rhs)
	{
		if (this == &rhs) return true;

		if (*this != rhs) return false;

		return true;
	}

	bool operator!=(const CApplicationContextName& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerObjectIdentifier>(m_pAppContextName, rhs.m_pAppContextName) ) return true;

		return false;
	}

	virtual ~CApplicationContextName()
	{
		if (is_copy)
			delete m_pAppContextName;
	}

};

class OSISTACK_SHAREDEXPORT CApplicationContextNameList: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier IdOID READ getIdOID)
	Q_PROPERTY(QLinkedList<CBerObjectIdentifier>* OI READ getObjectIdentifierList)

	bool is_copy;

protected:
	CBerIdentifier c_Identifier;
	QByteArray m_Code;

	CBerIdentifier c_IdOID;
	QLinkedList<CBerObjectIdentifier>* m_pSeqOf;

public:

	CBerIdentifier getIdentifier() { return c_Identifier; }
	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdOID() { return c_IdOID; }
	QLinkedList<CBerObjectIdentifier>* getObjectIdentifierList() { return m_pSeqOf; }

	typedef CContainerStorage< CApplicationContextNameList, QLinkedList<CBerObjectIdentifier>, CBerObjectIdentifier > TLocalStorage;
	ASN1_CODEC( TLocalStorage )

	static quint32 s_metaTypeIdentifier;
	static quint32 s_metaTypeListId;

	static CBerIdentifier getBerIdentifier()
	{
		return CBerIdentifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
	}

	explicit CApplicationContextNameList(QLinkedList<CBerObjectIdentifier>* pObjectIdentifierList):
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		c_IdOID(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16),
		m_pSeqOf(pObjectIdentifierList)
	{}

	CApplicationContextNameList(const CApplicationContextNameList& rhs): QObject(),
		c_Identifier(getBerIdentifier()),
		c_IdOID(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16)
	{
		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QLinkedList<CBerObjectIdentifier>(*rhs.m_pSeqOf);

		is_copy = true;
	}

	CApplicationContextNameList operator=(const CApplicationContextNameList& rhs)
	{
		if (this == &rhs) return *this;

		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QLinkedList<CBerObjectIdentifier>(*rhs.m_pSeqOf);

		is_copy = true;

		return *this;
	}

	bool operator!=(const CApplicationContextNameList& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues< QLinkedList<CBerObjectIdentifier> >(m_pSeqOf, rhs.m_pSeqOf) ) return true;

		return false;
	}

	virtual ~CApplicationContextNameList()
	{
		if (is_copy)
			delete m_pSeqOf;
	}

};

Q_DECLARE_METATYPE(CApplicationContextName*)
Q_DECLARE_METATYPE(CApplicationContextNameList*)
Q_DECLARE_METATYPE(QLinkedList<CBerObjectIdentifier>*)

#endif /* INCLUDE_ACSE_ASN1_APPLICATIONCONTEXTNAMELIST_H_ */
