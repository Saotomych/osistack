/*
 * PdvList.h
 *
 *  Created on: 24 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_PRESENTATION_ASN1_PDVLIST_H_
#define INCLUDE_PRESENTATION_ASN1_PDVLIST_H_

#include "osistack_global.h"
#include "berAnyNoDecode.h"
#include "berBitString.h"
#include "berOctetString.h"

namespace NsPdvList
{
	/*
	 * This class make optional encode/decode of types
	 * CExternalLinkV1 make full encode/decode
	 */
	class SubchoicePresentationDataValues: public QObject, public IBerBaseType
	{
		Q_OBJECT
		Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
		Q_PROPERTY(QByteArray* Code READ getCode)
		Q_PROPERTY(CBerIdentifier Idany READ getIdAny)
		Q_PROPERTY(IBerBaseType* any READ getAny)
		Q_PROPERTY(CBerIdentifier Idoctstr READ getIdOctetString)
		Q_PROPERTY(IBerBaseType* octstr READ getOctetString)
		Q_PROPERTY(CBerIdentifier Idbitstr READ getIdBitString)
		Q_PROPERTY(IBerBaseType* bitstr READ getBitString)

		bool is_copy;

	protected:

		const CBerIdentifier c_Identifier;

		QByteArray* getCode() { return &m_Code; }
		CBerIdentifier getIdentifier() { return c_Identifier; }

		CBerIdentifier getIdAny() { return c_IdSingleAsn1Type; }
		CBerIdentifier getIdOctetString() { return c_IdOctetAligned; }
		CBerIdentifier getIdBitString() { return c_IdArbitrary; }

		IBerBaseType* getAny() { return m_pSingleAsn1Type; }
		IBerBaseType* getOctetString() { return m_pOctetAligned; }
		IBerBaseType* getBitString() { return m_pArbitrary; }

		inline IBerBaseType* create_object_by_id(const CBerIdentifier& id)
		{
			qDebug() << "INFO: NsPdvList::SubchoicePresentationDataValues create member by id = " << id.getCode()->toHex();

			if ( c_IdSingleAsn1Type == id )
				{ m_pSingleAsn1Type = new CBerAnyNoDecode(); is_copy = true; return m_pSingleAsn1Type; }
			if ( c_IdOctetAligned == id )
				{ m_pOctetAligned = new CBerOctetString(); is_copy = true; return m_pOctetAligned; }
			if ( c_IdArbitrary == id )
				{ m_pArbitrary = new CBerBitString(); is_copy = true; return m_pArbitrary; }

			return nullptr;
		}

		inline void create_objects(const SubchoicePresentationDataValues& rhs)
		{
			std::unique_ptr<CBerAnyNoDecode> p1
					( (rhs.m_pSingleAsn1Type != nullptr) ? new CBerAnyNoDecode(*rhs.m_pSingleAsn1Type): nullptr );
			std::unique_ptr<CBerOctetString> p2
					( (rhs.m_pOctetAligned != nullptr) ? new CBerOctetString(*rhs.m_pOctetAligned) : nullptr );
			std::unique_ptr<CBerBitString> p3
					( (rhs.m_pArbitrary != nullptr) ? new CBerBitString(*rhs.m_pArbitrary) : nullptr );

			m_pSingleAsn1Type = p1.release();
			m_pOctetAligned = p2.release();
			m_pArbitrary = p3.release();
		}

		inline void delete_all_objects()
		{
			if (is_copy)
			{
				delete m_pSingleAsn1Type;
				delete m_pOctetAligned;
				delete m_pArbitrary;
			}
		}



	protected:
		QByteArray m_Code;

		CBerAnyNoDecode* m_pSingleAsn1Type;
		CBerOctetString* m_pOctetAligned;
		CBerBitString* m_pArbitrary;

		CBerIdentifier c_IdSingleAsn1Type;
		CBerIdentifier c_IdOctetAligned;
		CBerIdentifier c_IdArbitrary;

	public:

		ASN1_CODEC(CUnionStorage)

		static quint32 s_metaTypeIdentifier;

		static CBerIdentifier getBerIdentifier()
		{
			return CBerIdentifier();
		}

		SubchoicePresentationDataValues():
			is_copy(false),
			c_Identifier(getBerIdentifier()),
			m_pSingleAsn1Type(nullptr),
			m_pOctetAligned(nullptr),
			m_pArbitrary(nullptr),
			c_IdSingleAsn1Type(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 0),
			c_IdOctetAligned(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 1),
			c_IdArbitrary(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 2)
		{}

		SubchoicePresentationDataValues(CBerAnyNoDecode* pSingleAsn1Type, CBerOctetString* pOctetAligned, CBerBitString* pArbitrary):
			is_copy(false),
			c_Identifier(getBerIdentifier()),
			m_pSingleAsn1Type(pSingleAsn1Type),
			m_pOctetAligned(pOctetAligned),
			m_pArbitrary(pArbitrary),
			c_IdSingleAsn1Type(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 0),
			c_IdOctetAligned(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 1),
			c_IdArbitrary(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 2)
		{}

		SubchoicePresentationDataValues(const SubchoicePresentationDataValues& rhs): QObject(),
			c_Identifier(getBerIdentifier()),
			c_IdSingleAsn1Type(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 0),
			c_IdOctetAligned(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 1),
			c_IdArbitrary(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 2)
		{
			create_objects(rhs);

			m_Code = rhs.m_Code;
			is_copy = true;
		}

		SubchoicePresentationDataValues& operator=(const SubchoicePresentationDataValues& rhs)
		{
			if (this == &rhs) return *this;

			delete_all_objects();

			create_objects(rhs);

			m_Code = rhs.m_Code;
			is_copy = true;

			return *this;
		}

		bool operator!=(const SubchoicePresentationDataValues& rhs)
		{
			if (this == &rhs) return false;

			if ( notEqualsPointersAndValues<CBerAnyNoDecode>(m_pSingleAsn1Type, rhs.m_pSingleAsn1Type) ) return true;
			if ( notEqualsPointersAndValues<CBerOctetString>(m_pOctetAligned, rhs.m_pOctetAligned) ) return true;
			if ( notEqualsPointersAndValues<CBerBitString>(m_pArbitrary, rhs.m_pArbitrary) ) return true;

			return false;
		}

		bool operator==(const SubchoicePresentationDataValues& rhs)
		{
			if (*this != rhs) return false;
			return true;
		}

		virtual ~SubchoicePresentationDataValues()
		{
			delete_all_objects();
		}

	};
	// End of SubchoicePresentationDataValues class
} // end namespace


class OSISTACK_SHAREDEXPORT CPdvList: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier idTransferSyntaxName READ getIdTransferSyntaxName)
	Q_PROPERTY(IBerBaseType* transferSyntaxName READ getTransferSyntaxName)
	Q_PROPERTY(CBerIdentifier idPresentationContextIdentifier READ getIdPresentationContextIdentifier)
	Q_PROPERTY(IBerBaseType* presentationContextIdentifier READ getPresentationContextIdentifier)
	Q_PROPERTY(CBerIdentifier idSPDV READ getIdSPDV)
	Q_PROPERTY(IBerBaseType* SPDV READ getSPDV)

	bool is_copy;

protected:

	QByteArray m_Code;

	const CBerIdentifier c_Identifier;

	CBerObjectIdentifier* m_transferSyntaxName;
	CBerInteger* m_presentationContextIdentifier;
	NsPdvList::SubchoicePresentationDataValues* m_pSPDV; // Subchoice Presentation Data Values

	CBerIdentifier getIdentifier() { return c_Identifier; }
	QByteArray* getCode() { return &m_Code; }

	CBerIdentifier getIdTransferSyntaxName() { return CBerObjectIdentifier::getBerIdentifier(); }
	CBerIdentifier getIdPresentationContextIdentifier() { return CBerInteger::getBerIdentifier(); }
	CBerIdentifier getIdSPDV() { return NsPdvList::SubchoicePresentationDataValues::getBerIdentifier(); }

	IBerBaseType* getTransferSyntaxName() { return m_transferSyntaxName; }
	IBerBaseType* getPresentationContextIdentifier() { return m_presentationContextIdentifier; }
	IBerBaseType* getSPDV() { return m_pSPDV; }

	inline IBerBaseType* create_object_by_id(const CBerIdentifier& id)
	{
		qDebug() << "INFO: CPdvList create member by id = " << id.getCode()->toHex();

		if ( getIdTransferSyntaxName() == id )
			{ m_transferSyntaxName = new CBerObjectIdentifier(); is_copy = true; return m_transferSyntaxName; }
		if ( getIdPresentationContextIdentifier() == id )
			{ m_presentationContextIdentifier = new CBerInteger(); is_copy = true; return m_presentationContextIdentifier; }
		if ( getIdSPDV() == id )
			{ m_pSPDV = new NsPdvList::SubchoicePresentationDataValues(); is_copy = true; return m_pSPDV; }

		return nullptr;
	}

public:

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	static CBerIdentifier getBerIdentifier()
	{
		return CBerIdentifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
	}

	CPdvList():
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		m_transferSyntaxName(nullptr),
		m_presentationContextIdentifier(nullptr),
		m_pSPDV(nullptr)
	{ }

	CPdvList(CBerObjectIdentifier* transferSyntaxName,
			CBerInteger* presentationContextIdentifier,
			NsPdvList::SubchoicePresentationDataValues* pSPDV):
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		m_transferSyntaxName(transferSyntaxName),
		m_presentationContextIdentifier(presentationContextIdentifier),
		m_pSPDV(pSPDV)
	{ }

	CPdvList(const CPdvList& rhs): QObject(),
		c_Identifier(getBerIdentifier())
	{
		m_Code = rhs.m_Code;

		std::unique_ptr<NsPdvList::SubchoicePresentationDataValues> p1
				( (rhs.m_pSPDV != nullptr) ?
						new NsPdvList::SubchoicePresentationDataValues(*rhs.m_pSPDV): nullptr );

		std::unique_ptr<CBerInteger> p2
				( (rhs.m_presentationContextIdentifier != nullptr) ? new CBerInteger(*rhs.m_presentationContextIdentifier): nullptr );

		std::unique_ptr<CBerObjectIdentifier> p3
				( (rhs.m_transferSyntaxName != nullptr) ? new CBerObjectIdentifier(*rhs.m_transferSyntaxName): nullptr );

		m_pSPDV = p1.release();
		m_presentationContextIdentifier = p2.release();
		m_transferSyntaxName = p3.release();

		is_copy = true;
	}

	CPdvList& operator=(const CPdvList& rhs)
	{
		if (this == &rhs) return *this;

		m_Code = rhs.m_Code;

		std::unique_ptr<NsPdvList::SubchoicePresentationDataValues> p1
				( (rhs.m_pSPDV != nullptr) ?
						new NsPdvList::SubchoicePresentationDataValues(*rhs.m_pSPDV): nullptr );

		std::unique_ptr<CBerInteger> p2
				( (rhs.m_presentationContextIdentifier != nullptr) ? new CBerInteger(*rhs.m_presentationContextIdentifier): nullptr );

		std::unique_ptr<CBerObjectIdentifier> p3
				( (rhs.m_transferSyntaxName != nullptr) ? new CBerObjectIdentifier(*rhs.m_transferSyntaxName): nullptr );

		m_pSPDV = p1.release();
		m_presentationContextIdentifier = p2.release();
		m_transferSyntaxName = p3.release();

		is_copy = true;

		return *this;
	}

	bool operator!=(const CPdvList& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<NsPdvList::SubchoicePresentationDataValues>(m_pSPDV, rhs.m_pSPDV) ) return true;
		if ( notEqualsPointersAndValues<CBerInteger>(m_presentationContextIdentifier, rhs.m_presentationContextIdentifier) ) return true;
		if ( notEqualsPointersAndValues<CBerObjectIdentifier>(m_transferSyntaxName, rhs.m_transferSyntaxName) ) return true;

		return false;
	}

	bool operator==(const CPdvList& rhs)
	{
		if (this == &rhs) return true;

		if ( *this != rhs ) return false;
		else return true;
	}

	virtual ~CPdvList()
	{
		if (is_copy)
		{
			delete m_pSPDV;
			delete m_presentationContextIdentifier;
			delete m_transferSyntaxName;
		}
	}

};

Q_DECLARE_METATYPE(NsPdvList::SubchoicePresentationDataValues*)
Q_DECLARE_METATYPE(CPdvList*)


#endif /* INCLUDE_PRESENTATION_ASN1_PDVLIST_H_ */
