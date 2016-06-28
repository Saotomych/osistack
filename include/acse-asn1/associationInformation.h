/*
 * associationInformation.h
 *
 *  Created on: 16 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_ASSOCIATIONINFORMATION_H_
#define INCLUDE_ASSOCIATIONINFORMATION_H_

#include "osistack_global.h"
#include "externalLinkV1.h"

class OSISTACK_SHAREDEXPORT CAssociationInformation: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(QLinkedList<CExternalLinkV1>* seqof READ getSeqOf)

	bool is_copy;

protected:
	CBerIdentifier c_Identifier;
	QByteArray m_Code;

	QLinkedList<CExternalLinkV1>* m_pSeqOf;

public:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdentifier() { return c_Identifier; }
	QLinkedList<CExternalLinkV1>* getSeqOf() { return m_pSeqOf; }

//	typedef CContainerStorage<QLinkedList<CExternalLinkV1>, CExternalLinkV1> LocalStorage;
//	ASN1_CODEC( LocalStorage )

	virtual quint32 encode(CBerByteArrayOutputStream& berOStream, bool explct)
	{
		int codeLength;

		if (m_Code != nullptr) {
			codeLength = m_Code.size();
			berOStream.write(m_Code);
		}
		else {
			codeLength = 0;

			for (auto& val: *m_pSeqOf) {
				codeLength += val.encode(berOStream, true);
			}

			codeLength += CBerLength::encodeLength(berOStream, codeLength);

		}

		if (explct) {
			codeLength += c_Identifier.encode(berOStream);
		}

		return codeLength;
	}

	virtual quint32 decode(CBerByteArrayInputStream& iStream, bool explct)
	{
		quint32 codeLength = 0;
		quint32 subCodeLength = 0;
		QLinkedList<CExternalLinkV1> seqOf;

		if (explct) {
			codeLength += c_Identifier.decodeAndCheck(iStream);
		}

		CBerLength length;
		codeLength += length.decode(iStream);

		while (subCodeLength < length.getVal()) {
			CExternalLinkV1 element;
			subCodeLength += element.decode(iStream, true);
			seqOf.push_back(element);
		}

		if (subCodeLength != length.getVal()) {
			return 0;
		}
		codeLength += subCodeLength;

		return codeLength;
	}

	static quint32 s_metaTypeIdentifier;
	static quint32 s_metaTypeListId;

	CAssociationInformation(QLinkedList<CExternalLinkV1>* pExternalListV1):
		is_copy(false),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16),
		m_pSeqOf(pExternalListV1)
	{}

	CAssociationInformation(const CAssociationInformation& rhs): QObject(),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16)
	{
		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QLinkedList<CExternalLinkV1>(*rhs.m_pSeqOf);

		is_copy = true;
	}

	CAssociationInformation operator=(const CAssociationInformation& rhs)
	{
		if (this == &rhs) return *this;

		m_Code = rhs.m_Code;

		if (rhs.m_pSeqOf != nullptr)
			m_pSeqOf = new QLinkedList<CExternalLinkV1>(*rhs.m_pSeqOf);

		is_copy = true;

		return *this;
	}

	bool operator!=(const CAssociationInformation& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<QLinkedList<CExternalLinkV1> >(m_pSeqOf, rhs.m_pSeqOf) ) return true;

		return false;
	}

	virtual ~CAssociationInformation()
	{
		if (is_copy)
			delete m_pSeqOf;
	}

};

Q_DECLARE_METATYPE(CAssociationInformation*)
Q_DECLARE_METATYPE(QLinkedList<CExternalLinkV1>*)

#endif /* INCLUDE_ASSOCIATIONINFORMATION_H_ */
