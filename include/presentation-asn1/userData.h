/*
 * userData.h
 *
 *  Created on: 24 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_PRESENTATION_ASN1_USERDATA_H_
#define INCLUDE_PRESENTATION_ASN1_USERDATA_H_


#include "osistack_global.h"
#include "berOctetString.h"
#include "fullyEncodedData.h"

class CUserData: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier IdSimpleEncodedData READ getIdSimpleEncodedData)
	Q_PROPERTY(IBerBaseType* SimpleEncodedData READ getSimpleEncodedData)
	Q_PROPERTY(CBerIdentifier IdFullyEncodedData READ getIdFullyEncodedData)
	Q_PROPERTY(IBerBaseType* FullyEncodedData READ getFullyEncodedData)

	bool is_copy;

protected:

	const CBerIdentifier c_Identifier;

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdentifier() { return c_Identifier; }
	CBerIdentifier getIdSimpleEncodedData() { return c_IdSimpleEncodedData; }
	CBerIdentifier getIdFullyEncodedData() { return c_IdFullyEncodedData; }

	IBerBaseType* getSimpleEncodedData() { return m_pSimpleEncodedData; }
	IBerBaseType* getFullyEncodedData() { return m_pFullyEncodedData; }

	inline IBerBaseType* create_object_by_id(const CBerIdentifier& id)
	{
		qDebug() << "INFO: CUserData create member by id = " << id.getCode()->toHex();

		if ( c_IdSimpleEncodedData == id )
			{ m_pSimpleEncodedData = new CBerOctetString(); is_copy = true; return m_pSimpleEncodedData; }
		if ( c_IdFullyEncodedData == id )
			{ m_pFullyEncodedData = new CFullyEncodedData(); is_copy = true; return m_pFullyEncodedData; }

		return nullptr;
	}

	inline void create_objects(const CUserData& rhs)
	{
		std::unique_ptr<CBerOctetString> p1
				( (rhs.m_pSimpleEncodedData != nullptr) ? new CBerOctetString(*rhs.m_pSimpleEncodedData): nullptr );
		std::unique_ptr<CFullyEncodedData> p2
				( (rhs.m_pFullyEncodedData != nullptr) ? new CFullyEncodedData(*rhs.m_pFullyEncodedData) : nullptr );

		m_pSimpleEncodedData = p1.release();
		m_pFullyEncodedData = p2.release();
	}

	inline void delete_all_objects()
	{
		if (is_copy)
		{
			delete m_pSimpleEncodedData;
			delete m_pFullyEncodedData;
		}
	}

protected:
	QByteArray m_Code;

	CBerIdentifier c_IdSimpleEncodedData;
	CBerIdentifier c_IdFullyEncodedData;

	CBerOctetString* m_pSimpleEncodedData;
	CFullyEncodedData* m_pFullyEncodedData;

public:

	ASN1_CODEC(CUnionStorage)

//	virtual quint32 encode(CBerByteArrayOutputStream& berOStream, bool)
//	{
//		if (m_Code != nullptr) {
//			berOStream.write(m_Code);
//			return m_Code.size();
//		}
//
//		quint32 codeLength = 0;
//		if (m_pFullyEncodedData != nullptr) {
//			codeLength += m_pFullyEncodedData->encode(berOStream, false);
//			codeLength += c_IdFullyEncodedData.encode(berOStream);
//			return codeLength;
//		}
//
//		if (m_pSimpleEncodedData != nullptr) {
//			codeLength += m_pSimpleEncodedData->encode(berOStream, false);
//			codeLength += c_IdSimpleEncodedData.encode(berOStream);
//			return codeLength;
//		}
//
//		return codeLength;
//	}
//
//	virtual quint32 decode(CBerByteArrayInputStream& iStream, bool)
//	{
//		qint32 codeLength = 0;
//
//		CBerIdentifier BerId;
//		codeLength += BerId.decode(iStream);
//
//		codeLength += decode(iStream, &BerId);
//
//		return codeLength;
//	}
//
//	virtual quint32 decode(CBerByteArrayInputStream& iStream, CBerIdentifier* berIdentifier)
//	{
//		quint32 codeLength = 0;
//
//		CBerIdentifier defaultId;
//
//		CBerIdentifier* workIdentifier = berIdentifier;
//
//		if (berIdentifier == nullptr)
//		{
//			workIdentifier = &defaultId;
//			codeLength += workIdentifier->decode(iStream);
//		}
//
//		CBerOctetString simply_encoded_data;
//		if (*workIdentifier == c_IdSimpleEncodedData) {
//			if (m_pSimpleEncodedData == nullptr)
//				throw std::runtime_error("UserData has m_pSimpleEncodedData = nullptr");
//
//			codeLength += m_pSimpleEncodedData->decode(iStream, false);
//			return codeLength;
//		}
//
//		CFullyEncodedData fully_encoded_data;
//		if (*workIdentifier == c_IdFullyEncodedData) {
//			if (m_pFullyEncodedData == nullptr)
//				throw std::runtime_error("UserData has m_pFullyEncodedData = nullptr");
//
//			codeLength += m_pFullyEncodedData->decode(iStream, false);
//			return codeLength;
//		}
//
//		if (berIdentifier != nullptr) {
//			qDebug() << "CUserData decode: Error decoding CUserData: Identifier matches to no item";
//			return 0;
//		}
//
//		qDebug() << "CUserData decode: Error decoding CUserData: NO Identifier";
//
//		return 0;
//	}

	static quint32 s_metaTypeIdentifier;

	static CBerIdentifier getBerIdentifier()
	{
		return CBerIdentifier();
	}

	CUserData():
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		c_IdSimpleEncodedData(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::PRIMITIVE, 0),
		c_IdFullyEncodedData(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::CONSTRUCTED, 1),
		m_pSimpleEncodedData(nullptr),
		m_pFullyEncodedData(nullptr)
	{}

	CUserData(CBerOctetString* pReason, CFullyEncodedData* pUserInformation):
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		c_IdSimpleEncodedData(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::PRIMITIVE, 0),
		c_IdFullyEncodedData(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::CONSTRUCTED, 1),
		m_pSimpleEncodedData(pReason),
		m_pFullyEncodedData(pUserInformation)
	{}

	CUserData(const CUserData& rhs):QObject(),
		c_Identifier(getBerIdentifier()),
		c_IdSimpleEncodedData(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::PRIMITIVE, 0),
		c_IdFullyEncodedData(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::CONSTRUCTED, 1)
	{
		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;
	}

	CUserData& operator=(const CUserData& rhs)
	{
		if (this == &rhs) return *this;

		delete_all_objects();

		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;

		return *this;
	}

	bool operator!=(const CUserData& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerOctetString>(m_pSimpleEncodedData, rhs.m_pSimpleEncodedData) ) return true;
		if ( notEqualsPointersAndValues<CFullyEncodedData>(m_pFullyEncodedData, rhs.m_pFullyEncodedData) ) return true;

		return false;
	}

	virtual ~CUserData()
	{
		delete_all_objects();
	}

};

Q_DECLARE_METATYPE(CUserData*)

#endif /* INCLUDE_PRESENTATION_ASN1_USERDATA_H_ */
