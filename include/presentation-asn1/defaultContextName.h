/*
 * defaultContextName.h
 *
 *  Created on: 24 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_PRESENTATION_ASN1_DEFAULTCONTEXTNAME_H_
#define INCLUDE_PRESENTATION_ASN1_DEFAULTCONTEXTNAME_H_

#include "osistack_global.h"
#include "berObjectIdentifier.h"

class CDefaultContextName: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier IdAbstractSyntaxName READ getIdAbstractSyntaxName)
	Q_PROPERTY(IBerBaseType* AbstractSyntaxName READ getAbstractSyntaxName)
	Q_PROPERTY(CBerIdentifier IdTransferSyntaxName READ getIdTransferSyntaxName)
	Q_PROPERTY(IBerBaseType* TransferSyntaxName READ getTransferSyntaxName)

	bool is_copy;

protected:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdentifier() { return c_Identifier; }

	CBerIdentifier getIdAbstractSyntaxName() { return CBerIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 0); }
	CBerIdentifier getIdTransferSyntaxName() { return CBerIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 1); }

	IBerBaseType* getAbstractSyntaxName() { return m_pAbstractSyntaxName; }
	IBerBaseType* getTransferSyntaxName() { return m_pTransferSyntaxName; }

	inline IBerBaseType* create_object_by_id(const CBerIdentifier& id)
	{
		qDebug() << "INFO: CDefaultContextName create member by id = " << id.getCode()->toHex();

		if ( getIdAbstractSyntaxName() == id )
			{ m_pAbstractSyntaxName = new CBerObjectIdentifier(); is_copy = true; return m_pAbstractSyntaxName; }
		if ( getIdTransferSyntaxName() == id )
			{ m_pTransferSyntaxName = new CBerObjectIdentifier(); is_copy = true; return m_pTransferSyntaxName; }

		return nullptr;
	}

	inline void create_objects(const CDefaultContextName& rhs)
	{
		std::unique_ptr<CBerObjectIdentifier> p1
				( (rhs.m_pAbstractSyntaxName != nullptr) ? new CBerObjectIdentifier(*rhs.m_pAbstractSyntaxName): nullptr );
		std::unique_ptr<CBerObjectIdentifier> p2
				( (rhs.m_pTransferSyntaxName != nullptr) ? new CBerObjectIdentifier(*rhs.m_pTransferSyntaxName) : nullptr );

		m_pAbstractSyntaxName = p1.release();
		m_pTransferSyntaxName = p2.release();
	}

	inline void delete_all_objects()
	{
		if (is_copy)
		{
			delete m_pAbstractSyntaxName;
			delete m_pTransferSyntaxName;
		}
	}

protected:
	const CBerIdentifier c_Identifier;
	QByteArray m_Code;

	CBerObjectIdentifier* m_pAbstractSyntaxName;
	CBerObjectIdentifier* m_pTransferSyntaxName;

public:

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	static CBerIdentifier getBerIdentifier()
	{
		return CBerIdentifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
	}

	CDefaultContextName():
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		m_pAbstractSyntaxName(nullptr),
		m_pTransferSyntaxName(nullptr)
	{}

	CDefaultContextName(CBerObjectIdentifier* pAbstractSyntaxName, CBerObjectIdentifier* pTransferSyntaxName):
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		m_pAbstractSyntaxName(pAbstractSyntaxName),
		m_pTransferSyntaxName(pTransferSyntaxName)
	{}

	CDefaultContextName(const CDefaultContextName& rhs):QObject(),
		c_Identifier(getBerIdentifier())
	{
		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;
	}

	CDefaultContextName& operator=(const CDefaultContextName& rhs)
	{
		if (this == &rhs) return *this;

		delete_all_objects();

		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;

		return *this;
	}

	bool operator!=(const CDefaultContextName& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerObjectIdentifier>(m_pAbstractSyntaxName, rhs.m_pAbstractSyntaxName) ) return true;
		if ( notEqualsPointersAndValues<CBerObjectIdentifier>(m_pTransferSyntaxName, rhs.m_pTransferSyntaxName) ) return true;

		return false;
	}

	virtual ~CDefaultContextName()
	{
		delete_all_objects();
	}

};

Q_DECLARE_METATYPE(CDefaultContextName*)

#endif /* INCLUDE_PRESENTATION_ASN1_DEFAULTCONTEXTNAME_H_ */
