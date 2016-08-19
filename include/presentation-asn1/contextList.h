/*
 * contextList.h
 *
 *  Created on: 24 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_PRESENTATION_ASN1_CONTEXTLIST_H_
#define INCLUDE_PRESENTATION_ASN1_CONTEXTLIST_H_

#include "osistack_global.h"
#include "berInteger.h"
#include "berObjectIdentifier.h"
#include "applicationContextNameList.h"

class OSISTACK_SHAREDEXPORT CContextListSubSeqOfTransferSyntaxName: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
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

	typedef CContainerStorage< CContextListSubSeqOfTransferSyntaxName,
								QLinkedList<CBerObjectIdentifier>,
								CBerObjectIdentifier > TLocalStorage;
	ASN1_CODEC( TLocalStorage )

	static quint32 s_metaTypeIdentifier;
	static quint32 s_metaTypeListId;

	explicit CContextListSubSeqOfTransferSyntaxName(QByteArray code):
		is_copy(false),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16),
		m_Code(code),
		c_IdOID(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16),
		m_pSeqOf(nullptr)
	{}

	explicit CContextListSubSeqOfTransferSyntaxName(QLinkedList<CBerObjectIdentifier>* pObjectIdentifierList):
		is_copy(false),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16),
		c_IdOID(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16),
		m_pSeqOf(pObjectIdentifierList)
	{}

	CContextListSubSeqOfTransferSyntaxName(const CContextListSubSeqOfTransferSyntaxName& rhs): QObject(),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16),
		c_IdOID(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16)
	{
		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QLinkedList<CBerObjectIdentifier>(*rhs.m_pSeqOf);

		is_copy = true;
	}

	CContextListSubSeqOfTransferSyntaxName operator=(const CContextListSubSeqOfTransferSyntaxName& rhs)
	{
		if (this == &rhs) return *this;

		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QLinkedList<CBerObjectIdentifier>(*rhs.m_pSeqOf);

		is_copy = true;

		return *this;
	}

	bool operator!=(const CContextListSubSeqOfTransferSyntaxName& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues< QLinkedList<CBerObjectIdentifier> >(m_pSeqOf, rhs.m_pSeqOf) ) return true;

		return false;
	}

	virtual ~CContextListSubSeqOfTransferSyntaxName()
	{
		if (is_copy)
			delete m_pSeqOf;
	}
};

class OSISTACK_SHAREDEXPORT CContextListSubSeq: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(IBerBaseType* PresentationContextIdentifier READ getPresentationContextIdentifier)
	Q_PROPERTY(IBerBaseType* AbstractSyntaxName READ getAbstractSyntaxName)
	Q_PROPERTY(IBerBaseType* TransferSyntaxNameList READ getTransferSyntaxNameList)

	bool is_copy;

public:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdentifier() { return c_Identifier; }
	IBerBaseType* getPresentationContextIdentifier() { return m_pPresentationContextIdentifier; }
	IBerBaseType* getAbstractSyntaxName() { return m_pAbstractSyntaxName; }
	IBerBaseType* getTransferSyntaxNameList() { return m_pTransferSyntaxNameList; }

protected:

	void create_objects(const CContextListSubSeq& rhs)
	{
		std::unique_ptr<CBerInteger> p1
				( (rhs.m_pPresentationContextIdentifier != nullptr) ? new CBerInteger(*rhs.m_pPresentationContextIdentifier): nullptr );
		std::unique_ptr<CBerObjectIdentifier> p2
				( (rhs.m_pAbstractSyntaxName != nullptr) ? new CBerObjectIdentifier(*rhs.m_pAbstractSyntaxName) : nullptr );
		std::unique_ptr<CContextListSubSeqOfTransferSyntaxName> p3
				( (rhs.m_pTransferSyntaxNameList != nullptr) ? new CContextListSubSeqOfTransferSyntaxName(*rhs.m_pTransferSyntaxNameList) : nullptr );

		m_pPresentationContextIdentifier = p1.release();
		m_pAbstractSyntaxName = p2.release();
		m_pTransferSyntaxNameList = p3.release();
	}

	void delete_all_objects()
	{
		if (is_copy)
		{
			delete m_pPresentationContextIdentifier;
			delete m_pAbstractSyntaxName;
			delete m_pTransferSyntaxNameList;
		}
	}

protected:

	const CBerIdentifier c_Identifier;
	QByteArray m_Code;

	CBerInteger* m_pPresentationContextIdentifier;
	CBerObjectIdentifier* m_pAbstractSyntaxName;
	CContextListSubSeqOfTransferSyntaxName* m_pTransferSyntaxNameList;

public:

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	CContextListSubSeq(CBerInteger* pPresentationContextIdentifier, CBerObjectIdentifier* pAbstractSyntaxName, CContextListSubSeqOfTransferSyntaxName* pTransferSyntaxNameList):
		is_copy(false),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16),
		m_pPresentationContextIdentifier(pPresentationContextIdentifier),
		m_pAbstractSyntaxName(pAbstractSyntaxName),
		m_pTransferSyntaxNameList(pTransferSyntaxNameList)
	{}

	CContextListSubSeq(QByteArray code):
		is_copy(false),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16),
		m_Code(code),
		m_pPresentationContextIdentifier(nullptr),
		m_pAbstractSyntaxName(nullptr),
		m_pTransferSyntaxNameList(nullptr)
	{}

	CContextListSubSeq(const CContextListSubSeq& rhs): QObject(),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16)
	{
		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;
	}

	CContextListSubSeq& operator=(const CContextListSubSeq& rhs)
	{
		if (this == &rhs) return *this;

		delete_all_objects();

		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;

		return *this;
	}

	bool operator!=(const CContextListSubSeq& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerInteger>(m_pPresentationContextIdentifier, rhs.m_pPresentationContextIdentifier) ) return true;
		if ( notEqualsPointersAndValues<CBerObjectIdentifier>(m_pAbstractSyntaxName, rhs.m_pAbstractSyntaxName) ) return true;
		if ( notEqualsPointersAndValues<CContextListSubSeqOfTransferSyntaxName>(m_pTransferSyntaxNameList, rhs.m_pTransferSyntaxNameList) ) return true;

		return false;
	}

	bool operator==(const CContextListSubSeq& rhs)
	{
		if (*this != rhs) return false;
		return true;
	}

	virtual ~CContextListSubSeq()
	{
		delete_all_objects();
	}

};

class OSISTACK_SHAREDEXPORT CContextList: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(QLinkedList<CContextListSubSeq>* OI READ getObjectIdentifierList)

	bool is_copy;

protected:
	CBerIdentifier c_Identifier;
	CBerIdentifier c_emptyId;
	QByteArray m_Code;
	QLinkedList<CContextListSubSeq>* m_pSeqOf;

public:

	CBerIdentifier getIdentifier() { return c_Identifier; }
	QByteArray* getCode() { return &m_Code; }

	CBerLength getLength() { CBerLength t; return t; }

	QLinkedList<CContextListSubSeq>* getObjectIdentifierList() { return m_pSeqOf; }

	typedef CContainerStorage<CContextList, QLinkedList<CContextListSubSeq>, CContextListSubSeq > TLocalStorage;
	ASN1_CODEC( TLocalStorage )

	static quint32 s_metaTypeIdentifier;
	static quint32 s_metaTypeListId;

	explicit CContextList(QByteArray code):
		is_copy(false),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16),
		c_emptyId(),
		m_Code(code),
		m_pSeqOf(nullptr)
	{}

	explicit CContextList(QLinkedList<CContextListSubSeq>* pObjectIdentifierList):
		is_copy(false),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16),
		c_emptyId(),
		m_pSeqOf(pObjectIdentifierList)
	{}

	CContextList(const CContextList& rhs): QObject(),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16)
	{
		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QLinkedList<CContextListSubSeq>(*rhs.m_pSeqOf);

		is_copy = true;
	}

	CContextList operator=(const CContextList& rhs)
	{
		if (this == &rhs) return *this;

		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QLinkedList<CContextListSubSeq>(*rhs.m_pSeqOf);

		is_copy = true;

		return *this;
	}

	bool operator!=(const CContextList& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues< QLinkedList<CContextListSubSeq> >(m_pSeqOf, rhs.m_pSeqOf) ) return true;

		return false;
	}

	virtual ~CContextList()
	{
		if (is_copy)
			delete m_pSeqOf;
	}
};

Q_DECLARE_METATYPE(CContextList*)
Q_DECLARE_METATYPE(QLinkedList<CContextListSubSeq>*)
Q_DECLARE_METATYPE(CContextListSubSeq*)
Q_DECLARE_METATYPE(CContextListSubSeqOfTransferSyntaxName*)

#endif /* INCLUDE_PRESENTATION_ASN1_CONTEXTLIST_H_ */
