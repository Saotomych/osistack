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

class OSISTACK_SHAREDEXPORT CContextList: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier* Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(IBerBaseType* PresentationContextIdentifier READ getPresentationContextIdentifier)
	Q_PROPERTY(IBerBaseType* AbstractSyntaxName READ getAbstractSyntaxName)
	Q_PROPERTY(IBerBaseType* TransferSyntaxNameList READ getTransferSyntaxNameList)

	bool is_copy;

protected:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier* getIdentifier() { return nullptr; }
	IBerBaseType* getPresentationContextIdentifier() { return m_pPresentationContextIdentifier; }
	IBerBaseType* getAbstractSyntaxName() { return m_pAbstractSyntaxName; }
	IBerBaseType* getTransferSyntaxNameList() { return m_pTransferSyntaxNameList; }

	void create_objects(const CContextList& rhs)
	{
		std::unique_ptr<CBerInteger> p1
				( (rhs.m_pPresentationContextIdentifier != nullptr) ? new CBerInteger(*rhs.m_pPresentationContextIdentifier): nullptr );
		std::unique_ptr<CBerObjectIdentifier> p2
				( (rhs.m_pAbstractSyntaxName != nullptr) ? new CBerObjectIdentifier(*rhs.m_pAbstractSyntaxName) : nullptr );
		std::unique_ptr<CApplicationContextNameList> p3
				( (rhs.m_pTransferSyntaxNameList != nullptr) ? new CApplicationContextNameList(*rhs.m_pTransferSyntaxNameList) : nullptr );

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

	CBerIdentifier m_Identifier;
	QByteArray m_Code;

	CBerInteger* m_pPresentationContextIdentifier;
	CBerObjectIdentifier* m_pAbstractSyntaxName;
	CApplicationContextNameList* m_pTransferSyntaxNameList;

public:

	ASN1_CODEC(CBerBaseStorage)

	static CBerIdentifier s_Identifier;
	static quint32 s_metaTypeIdentifier;

	CContextList(CBerInteger* pPresentationContextIdentifier, CBerObjectIdentifier* pAbstractSyntaxName, CApplicationContextNameList* pTransferSyntaxNameList):
		is_copy(false),
		m_Identifier(s_Identifier),
		m_pPresentationContextIdentifier(pPresentationContextIdentifier),
		m_pAbstractSyntaxName(pAbstractSyntaxName),
		m_pTransferSyntaxNameList(pTransferSyntaxNameList)
	{}

	CContextList(QByteArray code):
		is_copy(false),
		m_Identifier(s_Identifier),
		m_Code(code),
		m_pPresentationContextIdentifier(nullptr),
		m_pAbstractSyntaxName(nullptr),
		m_pTransferSyntaxNameList(nullptr)
	{}

	CContextList(const CContextList& rhs): QObject()
	{
		create_objects(rhs);

		m_Identifier = s_Identifier;
		m_Code = rhs.m_Code;
		is_copy = true;
	}

	CContextList& operator=(const CContextList& rhs)
	{
		if (this == &rhs) return *this;

		delete_all_objects();

		create_objects(rhs);

		m_Identifier = s_Identifier;
		m_Code = rhs.m_Code;
		is_copy = true;

		return *this;
	}

	bool operator!=(const CContextList& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerInteger>(m_pPresentationContextIdentifier, rhs.m_pPresentationContextIdentifier) ) return true;
		if ( notEqualsPointersAndValues<CBerObjectIdentifier>(m_pAbstractSyntaxName, rhs.m_pAbstractSyntaxName) ) return true;
		if ( notEqualsPointersAndValues<CApplicationContextNameList>(m_pTransferSyntaxNameList, rhs.m_pTransferSyntaxNameList) ) return true;

		return false;
	}

	bool operator==(const CContextList& rhs)
	{
		if (*this != rhs) return false;
		return true;
	}

	virtual ~CContextList()
	{
		delete_all_objects();
	}
};

Q_DECLARE_METATYPE(CContextList*)

#endif /* INCLUDE_PRESENTATION_ASN1_CONTEXTLIST_H_ */
