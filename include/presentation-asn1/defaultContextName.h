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

	CBerIdentifier getIdAbstractSyntaxName() { return CBerObjectIdentifier::getBerIdentifier(); }
	CBerIdentifier getIdTransferSyntaxName() { return CBerObjectIdentifier::getBerIdentifier(); }

	IBerBaseType* getAbstractSyntaxName() { return m_pAbstractSyntaxName; }
	IBerBaseType* getTransferSyntaxName() { return m_pTransferSyntaxName; }

	void create_objects(const CDefaultContextName& rhs)
	{
		std::unique_ptr<CBerObjectIdentifier> p1
				( (rhs.m_pAbstractSyntaxName != nullptr) ? new CBerObjectIdentifier(*rhs.m_pAbstractSyntaxName): nullptr );
		std::unique_ptr<CBerObjectIdentifier> p2
				( (rhs.m_pTransferSyntaxName != nullptr) ? new CBerObjectIdentifier(*rhs.m_pTransferSyntaxName) : nullptr );

		m_pAbstractSyntaxName = p1.release();
		m_pTransferSyntaxName = p2.release();
	}

	void delete_all_objects()
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
