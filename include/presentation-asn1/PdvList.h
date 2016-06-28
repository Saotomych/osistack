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
		IBerBaseType* getAny() { return m_pSingleAsn1Type; }
		IBerBaseType* getOctetString() { return m_pOctetAligned; }
		IBerBaseType* getBitString() { return m_pArbitrary; }

		CBerIdentifier getIdAny() { return c_IdSingleAsn1Type; }
		CBerIdentifier getIdOctetString() { return c_IdOctetAligned; }
		CBerIdentifier getIdBitString() { return c_IdArbitrary; }

		void create_objects(const SubchoicePresentationDataValues& rhs)
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

		void delete_all_objects()
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

//		ASN1_CODEC(CBerBaseStorage)

		virtual quint32 encode(CBerByteArrayOutputStream& berOStream, bool)
		{
			if (m_Code.size()) {
				berOStream.write(m_Code);
				return m_Code.size();
			}

			int codeLength = 0;
			int sublength;

			if (m_pArbitrary != nullptr) {
				codeLength += m_pArbitrary->encode(berOStream, false);
				codeLength += c_IdArbitrary.encode(berOStream);
				return codeLength;
			}

			if (m_pOctetAligned != nullptr) {
				codeLength += m_pOctetAligned->encode(berOStream, false);
				codeLength += c_IdOctetAligned.encode(berOStream);
				return codeLength;
			}

			if (m_pSingleAsn1Type != nullptr) {
				sublength = m_pSingleAsn1Type->encode(berOStream, true);
				codeLength += sublength;
				codeLength += CBerLength::encodeLength(berOStream, sublength);
				codeLength += c_IdSingleAsn1Type.encode(berOStream);
				return codeLength;
			}

			return codeLength;
		}

		virtual quint32 decode(CBerByteArrayInputStream&, bool)
		{
			return 0;
		}

		virtual bool hasLength()
		{
			return false;
		}

		virtual quint32 decode(CBerByteArrayInputStream& iStream, CBerIdentifier* berIdentifier)
		{
			quint32 codeLength = 0;

			CBerIdentifier defaultId;

			CBerIdentifier* workIdentifier = berIdentifier;

			if (berIdentifier == nullptr)
			{
				workIdentifier = &defaultId;
				codeLength += workIdentifier->decode(iStream);
			}

			if (*workIdentifier == c_IdSingleAsn1Type)
			{
				CBerAnyNoDecode singleAsn1Type;
				codeLength += singleAsn1Type.decode(iStream, false);
				SubchoicePresentationDataValues schoice(&singleAsn1Type, nullptr, nullptr);
				*this = schoice;
				return codeLength;
			}

			if (*workIdentifier == c_IdOctetAligned)
			{
				CBerOctetString octetAligned;
				codeLength += octetAligned.decode(iStream, false);
				SubchoicePresentationDataValues schoice(nullptr, &octetAligned, nullptr);
				*this = schoice;
				return codeLength;
			}

			if (workIdentifier->equals(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 2))
			{
				CBerBitString arbitrary;
				codeLength += arbitrary.decode(iStream, false);
				SubchoicePresentationDataValues schoice(nullptr, nullptr, &arbitrary);
				*this = schoice;
				return codeLength;
			}

			if (berIdentifier != nullptr)
			{
				qDebug() << "SubchoicePresentationDataValues decode: Error decoding BerChoice: Identifier matches to no item";

				return 0;
			}

			qDebug() << "SubchoicePresentationDataValues decode: Error decoding BerChoice: No Identifier";

			return 0;
		}

		static quint32 s_metaTypeIdentifier;

		SubchoicePresentationDataValues(CBerAnyNoDecode* pSingleAsn1Type, CBerOctetString* pOctetAligned, CBerBitString* pArbitrary):
			is_copy(false),
			c_Identifier(),
			m_pSingleAsn1Type(pSingleAsn1Type),
			m_pOctetAligned(pOctetAligned),
			m_pArbitrary(pArbitrary),
			c_IdSingleAsn1Type(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 0),
			c_IdOctetAligned(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 1),
			c_IdArbitrary(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 2)
		{}

		SubchoicePresentationDataValues(const SubchoicePresentationDataValues& rhs): QObject(),
			c_Identifier(),
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
	Q_PROPERTY(IBerBaseType* transferSyntaxName READ getTransferSyntaxName)
	Q_PROPERTY(IBerBaseType* presentationContextIdentifier READ getPresentationContextIdentifier)
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

	IBerBaseType* getTransferSyntaxName() { return m_transferSyntaxName; }
	IBerBaseType* getPresentationContextIdentifier() { return m_presentationContextIdentifier; }
	IBerBaseType* getSPDV() { return m_pSPDV; }

public:

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	CPdvList(CBerObjectIdentifier* transferSyntaxName,
			CBerInteger* presentationContextIdentifier,
			NsPdvList::SubchoicePresentationDataValues* pSPDV):
		is_copy(false),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16),
		m_transferSyntaxName(transferSyntaxName),
		m_presentationContextIdentifier(presentationContextIdentifier),
		m_pSPDV(pSPDV)
	{ }

	CPdvList(const CPdvList& rhs): QObject(),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16)
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
