/*
 * externalLinkV1.h
 *
 *  Created on: 16 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_ACSE_ASN1_EXTERNALLINKV1_H_
#define INCLUDE_ACSE_ASN1_EXTERNALLINKV1_H_

#include "osistack_global.h"
#include "berAnyNoDecode.h"
#include "berOctetString.h"
#include "berBitString.h"

namespace NsExternalLinkV1
{
	/*
	 * This class make optional encode/decode of types
	 * CExternalLinkV1 make full encode/decode
	 */
	class SubChoiceEncoding: public QObject, public IBerBaseType
	{
		Q_OBJECT
		Q_PROPERTY(CBerIdentifier* Identifier READ getIdentifier)
		Q_PROPERTY(QByteArray* Code READ getCode)
		Q_PROPERTY(IBerBaseType* any READ getAny)
		Q_PROPERTY(IBerBaseType* octstr READ getOctetString)
		Q_PROPERTY(IBerBaseType* bitstr READ getBitString)

		bool is_copy;

		protected:

		QByteArray* getCode() { return &m_Code; }
		CBerIdentifier* getIdentifier() { return nullptr; }
		IBerBaseType* getAny() { return m_pSingleAsn1Type; }
		IBerBaseType* getOctetString() { return m_pOctetAligned; }
		IBerBaseType* getBitString() { return m_pArbitrary; }

		void create_objects(const SubChoiceEncoding& rhs)
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

	public:

		virtual quint32 encode(CBerByteArrayOutputStream& berOStream, bool explct)
		{
			if (m_Code.size())
			{
				return berOStream.write(m_Code);
			}

			quint32 codeLength = 0;

			if (m_pArbitrary != nullptr)
			{
				codeLength += m_pArbitrary->encode(berOStream, false);

				CBerIdentifier id(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 2);
				codeLength += id.encode(berOStream);
				return codeLength;
			}

			if (m_pOctetAligned != nullptr)
			{
				codeLength += m_pOctetAligned->encode(berOStream, false);

				CBerIdentifier id(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 1);
				codeLength += id.encode(berOStream);
				return codeLength;
			}

			if (m_pSingleAsn1Type != nullptr)
			{
				quint32 subLength = m_pSingleAsn1Type->encode(berOStream, true);
				codeLength += subLength;
				codeLength += CBerLength::encodeLength(berOStream, subLength);

				CBerIdentifier id(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 0);
				codeLength += id.encode(berOStream);
				return codeLength;
			}

			qDebug() << "ERROR: Encoding BerChoice failed. No item in choice was selected.";

			return 0;
		}

		virtual quint32 decode(CBerByteArrayInputStream& iStream, bool explct)
		{
			return 0;
		}

		virtual quint32 decode(CBerByteArrayInputStream& iStream, CBerIdentifier* berIdentifier)
		{
			quint32 codeLength = 0;

			CBerIdentifier* workIdentifier = berIdentifier;

			if (workIdentifier == nullptr)
			{
				workIdentifier = new CBerIdentifier();
				codeLength += workIdentifier->decode(iStream);
			}

			if (workIdentifier->equals(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 0))
			{
				CBerAnyNoDecode singleAsn1Type;
				codeLength += singleAsn1Type.decode(iStream, false);
				return codeLength;
			}

			if (workIdentifier->equals(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 1))
			{
				CBerOctetString octetAligned;
				codeLength += octetAligned.decode(iStream, false);
				return codeLength;
			}

			if (workIdentifier->equals(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 2))
			{
				CBerBitString arbitrary;
				codeLength += arbitrary.decode(iStream, false);
				return codeLength;
			}

			if (berIdentifier != nullptr)
			{
				return 0;
			}

			qDebug() << "SubChoiceEncoding decode: Error decoding BerChoice: Identifier matches to no item";

			return 0;
		}

		static quint32 s_metaTypeIdentifier;

		SubChoiceEncoding(CBerAnyNoDecode* pSingleAsn1Type, CBerOctetString* pOctetAligned, CBerBitString* pArbitrary):
			is_copy(false),
			m_pSingleAsn1Type(pSingleAsn1Type),
			m_pOctetAligned(pOctetAligned),
			m_pArbitrary(pArbitrary)
		{}

		SubChoiceEncoding(const SubChoiceEncoding& rhs): QObject()
		{
			create_objects(rhs);

			m_Code = rhs.m_Code;
			is_copy = true;
		}

		SubChoiceEncoding& operator=(const SubChoiceEncoding& rhs)
		{
			if (this == &rhs) return *this;

			delete_all_objects();

			create_objects(rhs);

			m_Code = rhs.m_Code;
			is_copy = true;

			return *this;
		}

		bool operator!=(const SubChoiceEncoding& rhs)
		{
			if (this == &rhs) return false;

			if ( notEqualsPointersAndValues<CBerAnyNoDecode>(m_pSingleAsn1Type, rhs.m_pSingleAsn1Type) ) return true;
			if ( notEqualsPointersAndValues<CBerOctetString>(m_pOctetAligned, rhs.m_pOctetAligned) ) return true;
			if ( notEqualsPointersAndValues<CBerBitString>(m_pArbitrary, rhs.m_pArbitrary) ) return true;

			return false;
		}

		bool operator==(const SubChoiceEncoding& rhs)
		{
			if (*this != rhs) return false;
			return true;
		}

		virtual ~SubChoiceEncoding()
		{
			delete_all_objects();
		}

	};
	// End of SubChoiceEncoding class
} // end namespace

class OSISTACK_SHAREDEXPORT CExternalLinkV1: public QObject, public IBerBaseType
{

private:

	Q_OBJECT
	Q_PROPERTY(CBerIdentifier* Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(IBerBaseType* any READ getDirectReference)
	Q_PROPERTY(IBerBaseType* octstr READ getIndirectReference)
	Q_PROPERTY(IBerBaseType* bitstr READ getEncoding)

	bool is_copy;

protected:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier* getIdentifier() { return nullptr; }
	IBerBaseType* getDirectReference() { return m_pDirectReference; }
	IBerBaseType* getIndirectReference() { return m_pIndirectReference; }
	IBerBaseType* getEncoding() { return m_pEncoding; }

	void create_objects(const CExternalLinkV1& rhs)
	{
		std::unique_ptr<CBerObjectIdentifier> p1
				( (rhs.m_pDirectReference != nullptr) ? new CBerObjectIdentifier(*rhs.m_pDirectReference): nullptr );
		std::unique_ptr<CBerInteger> p2
				( (rhs.m_pIndirectReference != nullptr) ? new CBerInteger(*rhs.m_pIndirectReference) : nullptr );
		std::unique_ptr<NsExternalLinkV1::SubChoiceEncoding> p3
				( (rhs.m_pEncoding != nullptr) ? new NsExternalLinkV1::SubChoiceEncoding(*rhs.m_pEncoding) : nullptr );

		m_pDirectReference = p1.release();
		m_pIndirectReference = p2.release();
		m_pEncoding = p3.release();
	}

	void delete_all_objects()
	{
		if (is_copy)
		{
			delete m_pDirectReference;
			delete m_pIndirectReference;
			delete m_pEncoding;
		}
	}

protected:
	QByteArray m_Code;

	CBerObjectIdentifier* m_pDirectReference;
	CBerInteger* m_pIndirectReference;
	NsExternalLinkV1::SubChoiceEncoding* m_pEncoding;

public:

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	CExternalLinkV1(CBerObjectIdentifier* pDirectReference, CBerInteger* pIndirectReference, NsExternalLinkV1::SubChoiceEncoding* pEncoding):
		is_copy(false),
		m_pDirectReference(pDirectReference),
		m_pIndirectReference(pIndirectReference),
		m_pEncoding(pEncoding)
	{}

	CExternalLinkV1(const CExternalLinkV1& rhs): QObject()
	{
		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;
	}

	CExternalLinkV1& operator=(const CExternalLinkV1& rhs)
	{
		if (this == &rhs) return *this;

		delete_all_objects();

		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;

		return *this;
	}

	bool operator!=(const CExternalLinkV1& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerObjectIdentifier>(m_pDirectReference, rhs.m_pDirectReference) ) return true;
		if ( notEqualsPointersAndValues<CBerInteger>(m_pIndirectReference, rhs.m_pIndirectReference) ) return true;
		if ( notEqualsPointersAndValues<NsExternalLinkV1::SubChoiceEncoding>(m_pEncoding, rhs.m_pEncoding) ) return true;

		return false;
	}

	bool operator==(const CExternalLinkV1& rhs)
	{
		if (*this != rhs) return false;
		return true;
	}

	virtual ~CExternalLinkV1()
	{
		delete_all_objects();
	}
};

Q_DECLARE_METATYPE(CExternalLinkV1*)
Q_DECLARE_METATYPE(NsExternalLinkV1::SubChoiceEncoding*)

#endif /* INCLUDE_ACSE_ASN1_EXTERNALLINKV1_H_ */
