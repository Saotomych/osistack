/*
 * CpType.h
 *
 *  Created on: 24 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_PRESENTATION_ASN1_CPTYPE_H_
#define INCLUDE_PRESENTATION_ASN1_CPTYPE_H_

#include "osistack_global.h"
#include "berBitString.h"
#include "berOctetString.h"
#include "ResultList.h"
#include "userData.h"
#include "contextList.h"
#include "defaultContextName.h"

class OSISTACK_SHAREDEXPORT CCpType: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier* Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(IBerBaseType* ProtocolVersion READ getProtocolVersion)
	Q_PROPERTY(IBerBaseType* CallingPresentationSelector READ getCallingPresentationSelector)
	Q_PROPERTY(IBerBaseType* CalledPresentationSelector READ getCalledPresentationSelector)
	Q_PROPERTY(IBerBaseType* PresentationContextDefinitionList READ getPresentationContextDefinitionList)
	Q_PROPERTY(IBerBaseType* DefaultContextName READ getDefaultContextName)
	Q_PROPERTY(IBerBaseType* PresentationRequirements READ getPresentationRequirements)
	Q_PROPERTY(IBerBaseType* UserSessionRequirements READ getUserSessionRequirements)
	Q_PROPERTY(IBerBaseType* UserData READ getUserData)

	bool is_copy;

protected:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier* getIdentifier() { return &m_Identifier; }

	IBerBaseType* getProtocolVersion() {return m_pProtocolVersion;}
	IBerBaseType* getCallingPresentationSelector() {return m_pCallingPresentationSelector;}
	IBerBaseType* getCalledPresentationSelector() {return m_pCalledPresentationSelector;}
	IBerBaseType* getPresentationContextDefinitionList() {return m_pPresentationContextDefinitionList;}
	IBerBaseType* getDefaultContextName() {return m_pDefaultContextName;}
	IBerBaseType* getPresentationRequirements() {return m_pPresentationRequirements;}
	IBerBaseType* getUserSessionRequirements() {return m_pUserSessionRequirements;}
	IBerBaseType* getUserData() {return m_pUserData;}

	void create_objects(const CCpType& rhs)
	{
		std::unique_ptr<CBerBitString> p1
				( (rhs.m_pProtocolVersion != nullptr) ? new CBerBitString(*rhs.m_pProtocolVersion): nullptr );
		std::unique_ptr<CBerOctetString> p2
				( (rhs.m_pCallingPresentationSelector != nullptr) ? new CBerOctetString(*rhs.m_pCallingPresentationSelector): nullptr );
		std::unique_ptr<CBerOctetString> p3
				( (rhs.m_pCalledPresentationSelector != nullptr) ? new CBerOctetString(*rhs.m_pCalledPresentationSelector): nullptr );
		std::unique_ptr<CContextList> p4
				( (rhs.m_pPresentationContextDefinitionList != nullptr) ? new CContextList(*rhs.m_pPresentationContextDefinitionList): nullptr );
		std::unique_ptr<CDefaultContextName> p5
				( (rhs.m_pDefaultContextName != nullptr) ? new CDefaultContextName(*rhs.m_pDefaultContextName): nullptr );
		std::unique_ptr<CBerBitString> p6
				( (rhs.m_pPresentationRequirements != nullptr) ? new CBerBitString(*rhs.m_pPresentationRequirements): nullptr );
		std::unique_ptr<CBerBitString> p7
				( (rhs.m_pUserSessionRequirements != nullptr) ? new CBerBitString(*rhs.m_pUserSessionRequirements): nullptr );
		std::unique_ptr<CUserData> p8
				( (rhs.m_pUserData != nullptr) ? new CUserData(*rhs.m_pUserData): nullptr );

		m_pProtocolVersion = p1.release();
		m_pCallingPresentationSelector = p2.release();
		m_pCalledPresentationSelector = p3.release();
		m_pPresentationContextDefinitionList = p4.release();
		m_pDefaultContextName = p5.release();
		m_pPresentationRequirements = p6.release();
		m_pUserSessionRequirements = p7.release();
		m_pUserData = p8.release();

	}

	void delete_all_objects()
	{
		if (is_copy)
		{
			delete m_pProtocolVersion;
			delete m_pCallingPresentationSelector;
			delete m_pCalledPresentationSelector;
			delete m_pPresentationContextDefinitionList;
			delete m_pDefaultContextName;
			delete m_pPresentationRequirements;
			delete m_pUserSessionRequirements;
			delete m_pUserData;
		}
	}

protected:

	CBerIdentifier m_Identifier;
	QByteArray m_Code;

	CBerBitString* m_pProtocolVersion;
	CBerOctetString* m_pCallingPresentationSelector;
	CBerOctetString* m_pCalledPresentationSelector;
	CContextList* m_pPresentationContextDefinitionList;
	CDefaultContextName* m_pDefaultContextName;
	CBerBitString* m_pPresentationRequirements;
	CBerBitString* m_pUserSessionRequirements;
	CUserData* m_pUserData;

public:

	ASN1_CODEC(CBerBaseStorage)

	static CBerIdentifier s_Identifier;
	static quint32 s_metaTypeIdentifier;

	CCpType(
		CBerBitString* pProtocolVersion,
		CBerOctetString* pCallingPresentationSelector,
		CBerOctetString* pCalledPresentationSelector,
		CContextList* pPresentationContextDefinitionList,
		CDefaultContextName* pDefaultContextName,
		CBerBitString* pPresentationRequirements,
		CBerBitString* pUserSessionRequirements,
		CUserData* pUserData
	):
		is_copy(false),
		m_Identifier(s_Identifier),
		m_pProtocolVersion(pProtocolVersion),
		m_pCallingPresentationSelector(pCallingPresentationSelector),
		m_pCalledPresentationSelector(pCalledPresentationSelector),
		m_pPresentationContextDefinitionList(pPresentationContextDefinitionList),
		m_pDefaultContextName(pDefaultContextName),
		m_pPresentationRequirements(pPresentationRequirements),
		m_pUserSessionRequirements(pUserSessionRequirements),
		m_pUserData(pUserData)
	{}

	CCpType(const CCpType& rhs): QObject()
	{
		create_objects(rhs);

		m_Identifier = rhs.m_Identifier;
		m_Code = rhs.m_Code;
		is_copy = true;
	}

	CCpType& operator=(const CCpType& rhs)
	{
		if (this == &rhs) return *this;

		delete_all_objects();

		create_objects(rhs);

		m_Identifier = rhs.m_Identifier;
		m_Code = rhs.m_Code;
		is_copy = true;

		return *this;
	}

	bool operator!=(const CCpType& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerBitString>(m_pProtocolVersion, rhs.m_pProtocolVersion) ) return true;
		if ( notEqualsPointersAndValues<CBerOctetString>(m_pCallingPresentationSelector, rhs.m_pCallingPresentationSelector) ) return true;
		if ( notEqualsPointersAndValues<CBerOctetString>(m_pCalledPresentationSelector, rhs.m_pCalledPresentationSelector) ) return true;
		if ( notEqualsPointersAndValues<CContextList>(m_pPresentationContextDefinitionList, rhs.m_pPresentationContextDefinitionList) ) return true;
		if ( notEqualsPointersAndValues<CDefaultContextName>(m_pDefaultContextName, rhs.m_pDefaultContextName) ) return true;
		if ( notEqualsPointersAndValues<CBerBitString>(m_pPresentationRequirements, rhs.m_pPresentationRequirements) ) return true;
		if ( notEqualsPointersAndValues<CBerBitString>(m_pUserSessionRequirements, rhs.m_pUserSessionRequirements) ) return true;
		if ( notEqualsPointersAndValues<CUserData>(m_pUserData, rhs.m_pUserData) ) return true;

		return false;
	}

	virtual ~CCpType()
	{
		delete_all_objects();
	}

};

Q_DECLARE_METATYPE(CCpType*)

#endif /* INCLUDE_PRESENTATION_ASN1_CPTYPE_H_ */
