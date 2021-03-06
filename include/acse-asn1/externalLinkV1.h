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

	public:

		QByteArray* getCode() { return &m_Code; }
		CBerIdentifier getIdentifier() { return c_Identifier; }
		CBerIdentifier getIdAny() { return c_IdSingleAsn1Type; }
		CBerIdentifier getIdOctetString() { return c_IdOctetAligned; }
		CBerIdentifier getIdBitString() { return c_IdArbitrary; }

		IBerBaseType* getAny() { return m_pSingleAsn1Type; }
		IBerBaseType* getOctetString() { return m_pOctetAligned; }
		IBerBaseType* getBitString() { return m_pArbitrary; }

	protected:

		inline IBerBaseType* create_object_by_id(const CBerIdentifier& id)
		{
			qDebug() << "INFO: NsExternalLinkV1::SubChoiceEncoding create member by id = " << id.getCode()->toHex();

			if ( c_IdSingleAsn1Type == id )
				{ m_pSingleAsn1Type = new CBerAnyNoDecode(); is_copy = true; return m_pSingleAsn1Type; }
			if ( c_IdOctetAligned == id )
				{ m_pOctetAligned = new CBerOctetString(); is_copy = true; return m_pOctetAligned; }
			if ( c_IdArbitrary == id )
				{ m_pArbitrary = new CBerBitString(); is_copy = true; return m_pArbitrary; }

			return nullptr;
		}

		inline void create_objects(const SubChoiceEncoding& rhs)
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

		CBerIdentifier c_IdSingleAsn1Type;
		CBerIdentifier c_IdOctetAligned;
		CBerIdentifier c_IdArbitrary;

		CBerAnyNoDecode* m_pSingleAsn1Type;
		CBerOctetString* m_pOctetAligned;
		CBerBitString* m_pArbitrary;

	public:

		ASN1_CODEC(CUnionStorage)

		static quint32 s_metaTypeIdentifier;

		static CBerIdentifier getBerIdentifier()
		{
			return CBerIdentifier();
		}

		SubChoiceEncoding():
			is_copy(false),
			c_Identifier(getBerIdentifier()),
			c_IdSingleAsn1Type(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 0),
			c_IdOctetAligned(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 1),
			c_IdArbitrary(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 2),
			m_pSingleAsn1Type(nullptr),
			m_pOctetAligned(nullptr),
			m_pArbitrary(nullptr)
		{}

		SubChoiceEncoding(CBerAnyNoDecode* pSingleAsn1Type, CBerOctetString* pOctetAligned, CBerBitString* pArbitrary):
			is_copy(false),
			c_Identifier(getBerIdentifier()),
			c_IdSingleAsn1Type(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 0),
			c_IdOctetAligned(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 1),
			c_IdArbitrary(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 2),
			m_pSingleAsn1Type(pSingleAsn1Type),
			m_pOctetAligned(pOctetAligned),
			m_pArbitrary(pArbitrary)
		{}

		SubChoiceEncoding(const SubChoiceEncoding& rhs): QObject(),
			c_Identifier(getBerIdentifier()),
			c_IdSingleAsn1Type(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 0),
			c_IdOctetAligned(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 1),
			c_IdArbitrary(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 2)
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
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier Idoid READ getIdDirectReference)
	Q_PROPERTY(IBerBaseType* oid READ getDirectReference)
	Q_PROPERTY(CBerIdentifier Idinteger READ getIdIndirectReference)
	Q_PROPERTY(IBerBaseType* integer READ getIndirectReference)
	Q_PROPERTY(CBerIdentifier Idsubchoice READ getIdEncoding)
	Q_PROPERTY(IBerBaseType* subchoice READ getEncoding)

	bool is_copy;

public:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdentifier() { return c_Identifier; }
	CBerLength getLength() { CBerLength len; return len; }

	CBerIdentifier getIdDirectReference() { return CBerObjectIdentifier::getBerIdentifier(); }
	CBerIdentifier getIdIndirectReference() { return CBerInteger::getBerIdentifier(); }
	CBerIdentifier getIdEncoding() { return NsExternalLinkV1::SubChoiceEncoding::getBerIdentifier(); }

	IBerBaseType* getDirectReference() { return m_pDirectReference; }
	IBerBaseType* getIndirectReference() { return m_pIndirectReference; }
	IBerBaseType* getEncoding() { return m_pEncoding; }

protected:

	inline IBerBaseType* create_object_by_id(const CBerIdentifier& id)
	{
		qDebug() << "INFO: NsExternalLinkV1::CExternalLinkV1 create member by id = " << id.getCode()->toHex();

		if (getIdDirectReference() == id )
			{ m_pDirectReference = new CBerObjectIdentifier(); is_copy = true; return m_pDirectReference; }
		if ( getIdIndirectReference() == id )
			{ m_pIndirectReference = new CBerInteger(); is_copy = true; return m_pIndirectReference; }
		if ( getIdEncoding() == id )
			{ m_pEncoding = new NsExternalLinkV1::SubChoiceEncoding(); is_copy = true; return m_pEncoding; }

		return nullptr;
	}

	inline void create_objects(const CExternalLinkV1& rhs)
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

	inline void delete_all_objects()
	{
		if (is_copy)
		{
			delete m_pDirectReference;
			delete m_pIndirectReference;
			delete m_pEncoding;
		}
	}

protected:

	const CBerIdentifier c_Identifier;

	QByteArray m_Code;

	CBerObjectIdentifier* m_pDirectReference;
	CBerInteger* m_pIndirectReference;
	NsExternalLinkV1::SubChoiceEncoding* m_pEncoding;

public:

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	static CBerIdentifier getBerIdentifier()
	{
		return CBerIdentifier(CBerIdentifier::UNIVERSAL_CLASS,CBerIdentifier::CONSTRUCTED, 8);
	}

	CExternalLinkV1():
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		m_pDirectReference(nullptr),
		m_pIndirectReference(nullptr),
		m_pEncoding(nullptr)
	{}

	CExternalLinkV1(CBerObjectIdentifier* pDirectReference, CBerInteger* pIndirectReference, NsExternalLinkV1::SubChoiceEncoding* pEncoding):
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		m_pDirectReference(pDirectReference),
		m_pIndirectReference(pIndirectReference),
		m_pEncoding(pEncoding)
	{}

	CExternalLinkV1(const CExternalLinkV1& rhs): QObject(),
		c_Identifier(getBerIdentifier())
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
