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
	Q_PROPERTY(CBerIdentifier* Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(IBerBaseType* SimpleEncodedData READ getSimpleEncodedData)
	Q_PROPERTY(IBerBaseType* FullyEncodedData READ getFullyEncodedData)

	bool is_copy;

protected:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier* getIdentifier() { return nullptr; }
	IBerBaseType* getSimpleEncodedData() { return m_pSimpleEncodedData; }
	IBerBaseType* getFullyEncodedData() { return m_pFullyEncodedData; }

	void create_objects(const CUserData& rhs)
	{
		std::unique_ptr<CBerOctetString> p1
				( (rhs.m_pSimpleEncodedData != nullptr) ? new CBerOctetString(*rhs.m_pSimpleEncodedData): nullptr );
		std::unique_ptr<CFullyEncodedData> p2
				( (rhs.m_pFullyEncodedData != nullptr) ? new CFullyEncodedData(*rhs.m_pFullyEncodedData) : nullptr );

		m_pSimpleEncodedData = p1.release();
		m_pFullyEncodedData = p2.release();
	}

	void delete_all_objects()
	{
		if (is_copy)
		{
			delete m_pSimpleEncodedData;
			delete m_pFullyEncodedData;
		}
	}

protected:
	QByteArray m_Code;

	CBerOctetString* m_pSimpleEncodedData;
	CFullyEncodedData* m_pFullyEncodedData;

public:

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	CUserData():
		is_copy(false),
		m_pSimpleEncodedData(nullptr),
		m_pFullyEncodedData(nullptr)
	{}

	CUserData(CBerOctetString* pReason, CFullyEncodedData* pUserInformation):
		is_copy(false),
		m_pSimpleEncodedData(pReason),
		m_pFullyEncodedData(pUserInformation)
	{}

	CUserData(const CUserData& rhs):QObject()
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
