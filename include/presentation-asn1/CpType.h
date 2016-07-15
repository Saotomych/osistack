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
#include "presentation-asn1/modeSelector.h"
#include "../ASN1/include/berInteger.h"
#include "../ASN1/include/berIdentifier.h"

namespace NsCpType
{

class OSISTACK_SHAREDEXPORT CSubSeqNormalModeParameters: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier IdProtocolVersion READ getIdProtocolVersion)
	Q_PROPERTY(IBerBaseType* ProtocolVersion READ getProtocolVersion)
	Q_PROPERTY(CBerIdentifier IdCallingPresentationSelector READ getIdCallingPresentationSelector)
	Q_PROPERTY(IBerBaseType* CallingPresentationSelector READ getCallingPresentationSelector)
	Q_PROPERTY(CBerIdentifier IdCalledPresentationSelector READ getIdCalledPresentationSelector)
	Q_PROPERTY(IBerBaseType* CalledPresentationSelector READ getCalledPresentationSelector)
	Q_PROPERTY(CBerIdentifier IdPresentationContextDefinitionList READ getIdPresentationContextDefinitionList)
	Q_PROPERTY(IBerBaseType* PresentationContextDefinitionList READ getPresentationContextDefinitionList)
	Q_PROPERTY(CBerIdentifier IdDefaultContextName READ getIdDefaultContextName)
	Q_PROPERTY(IBerBaseType* DefaultContextName READ getDefaultContextName)
	Q_PROPERTY(CBerIdentifier IdPresentationRequirements READ getIdPresentationRequirements)
	Q_PROPERTY(IBerBaseType* PresentationRequirements READ getPresentationRequirements)
	Q_PROPERTY(CBerIdentifier IdUserSessionRequirements READ getIdUserSessionRequirements)
	Q_PROPERTY(IBerBaseType* UserSessionRequirements READ getUserSessionRequirements)
//	Q_PROPERTY(CBerIdentifier ClearId READ getClearId)
	Q_PROPERTY(IBerBaseType* UserData READ getUserData)

	bool is_copy;

protected:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdentifier() { return c_Identifier; }

	IBerBaseType* getProtocolVersion() {return m_pProtocolVersion;}
	IBerBaseType* getCallingPresentationSelector() {return m_pCallingPresentationSelector;}
	IBerBaseType* getCalledPresentationSelector() {return m_pCalledPresentationSelector;}
	IBerBaseType* getPresentationContextDefinitionList() {return m_pPresentationContextDefinitionList;}
	IBerBaseType* getDefaultContextName() {return m_pDefaultContextName;}
	IBerBaseType* getPresentationRequirements() {return m_pPresentationRequirements;}
	IBerBaseType* getUserSessionRequirements() {return m_pUserSessionRequirements;}
	IBerBaseType* getUserData() {return m_pUserData;}

	CBerIdentifier getClearId() {return c_clearId;}
	CBerIdentifier getIdProtocolVersion() {return c_IdProtocolVersion;}
	CBerIdentifier getIdCallingPresentationSelector() {return c_IdCallingPresentationSelector;}
	CBerIdentifier getIdCalledPresentationSelector() {return c_IdCalledPresentationSelector;}
	CBerIdentifier getIdPresentationContextDefinitionList() {return c_IdPresentationContextDefinitionList;}
	CBerIdentifier getIdDefaultContextName() {return c_IdDefaultContextName;}
	CBerIdentifier getIdPresentationRequirements() {return c_IdPresentationRequirements;}
	CBerIdentifier getIdUserSessionRequirements() {return c_IdUserSessionRequirements;}

	void create_objects(const CSubSeqNormalModeParameters& rhs)
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

	const CBerIdentifier c_Identifier;
	QByteArray m_Code;

	const CBerIdentifier c_clearId;
	const CBerIdentifier c_IdProtocolVersion;
	const CBerIdentifier c_IdCallingPresentationSelector;
	const CBerIdentifier c_IdCalledPresentationSelector;
	const CBerIdentifier c_IdPresentationContextDefinitionList;
	const CBerIdentifier c_IdDefaultContextName;
	const CBerIdentifier c_IdPresentationRequirements;
	const CBerIdentifier c_IdUserSessionRequirements;

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

	static quint32 s_metaTypeIdentifier;

	CSubSeqNormalModeParameters(
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
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16),
		c_clearId(),
		c_IdProtocolVersion(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 0),
		c_IdCallingPresentationSelector(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 1),
		c_IdCalledPresentationSelector(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 2),
		c_IdPresentationContextDefinitionList(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 4),
		c_IdDefaultContextName(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 6),
		c_IdPresentationRequirements(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 8),
		c_IdUserSessionRequirements(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 9),
		m_pProtocolVersion(pProtocolVersion),
		m_pCallingPresentationSelector(pCallingPresentationSelector),
		m_pCalledPresentationSelector(pCalledPresentationSelector),
		m_pPresentationContextDefinitionList(pPresentationContextDefinitionList),
		m_pDefaultContextName(pDefaultContextName),
		m_pPresentationRequirements(pPresentationRequirements),
		m_pUserSessionRequirements(pUserSessionRequirements),
		m_pUserData(pUserData)
	{}

	CSubSeqNormalModeParameters(const CSubSeqNormalModeParameters& rhs): QObject(),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16),
		c_IdProtocolVersion(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 0),
		c_IdCallingPresentationSelector(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 1),
		c_IdCalledPresentationSelector(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 2),
		c_IdPresentationContextDefinitionList(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 4),
		c_IdDefaultContextName(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 6),
		c_IdPresentationRequirements(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 8),
		c_IdUserSessionRequirements(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 9)
	{
		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;
	}

	CSubSeqNormalModeParameters& operator=(const CSubSeqNormalModeParameters& rhs)
	{
		if (this == &rhs) return *this;

		delete_all_objects();

		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;

		return *this;
	}

	bool operator!=(const CSubSeqNormalModeParameters& rhs)
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

	virtual ~CSubSeqNormalModeParameters()
	{
		delete_all_objects();
	}

};

}

class OSISTACK_SHAREDEXPORT CCpType: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier IdmodeSelector READ getIdModeSelector)
	Q_PROPERTY(IBerBaseType* modeSelector READ getModeSelector)
	Q_PROPERTY(CBerIdentifier IdnormalModeParameters READ getIdNMP)
	Q_PROPERTY(IBerBaseType* normalModeParameters READ getNMP)

	bool is_copy;

protected:

	QByteArray m_Code;

	CModeSelector* m_pModeSelector;
	NsCpType::CSubSeqNormalModeParameters* m_pNMP;

	const CBerIdentifier c_Identifier;
	const CBerIdentifier c_IdModeSelector;
	const CBerIdentifier c_IdNMP;

	CBerIdentifier getIdentifier() { return c_Identifier; }
	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdModeSelector() { return c_IdModeSelector; }
	IBerBaseType* getModeSelector() { return m_pModeSelector; }
	CBerIdentifier getIdNMP() { return c_IdNMP; }
	IBerBaseType* getNMP() { return m_pNMP; }

public:

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	CCpType():
		is_copy(false),
		m_pModeSelector(nullptr),
		m_pNMP(nullptr),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 17),
		c_IdModeSelector(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 0),
		c_IdNMP(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 2)
	{	}

	CCpType(CModeSelector* pModeSelector,
			NsCpType::CSubSeqNormalModeParameters* pNMP):
		is_copy(false),
		m_pModeSelector(pModeSelector),
		m_pNMP(pNMP),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 17),
		c_IdModeSelector(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 0),
		c_IdNMP(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 2)
	{	}

	CCpType(const CCpType& rhs): QObject(),
		c_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 17),
		c_IdModeSelector(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 0),
		c_IdNMP(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 2)
	{
		m_Code = rhs.m_Code;

		std::unique_ptr<NsCpType::CSubSeqNormalModeParameters> p1
				( (rhs.m_pNMP != nullptr) ?
						new NsCpType::CSubSeqNormalModeParameters(*rhs.m_pNMP): nullptr );

		std::unique_ptr<CModeSelector> p2
				( (rhs.m_pModeSelector != nullptr) ? new CModeSelector(*rhs.m_pModeSelector): nullptr );

		m_pNMP = p1.release();
		m_pModeSelector = p2.release();

		is_copy = true;
	}

	CCpType& operator=(const CCpType& rhs)
	{
		if (this == &rhs) return *this;

		m_Code = rhs.m_Code;

		std::unique_ptr<NsCpType::CSubSeqNormalModeParameters> p1
				( (rhs.m_pNMP != nullptr) ?
						new NsCpType::CSubSeqNormalModeParameters(*rhs.m_pNMP): nullptr );

		std::unique_ptr<CModeSelector> p2
				( (rhs.m_pModeSelector != nullptr) ? new CModeSelector(*rhs.m_pModeSelector): nullptr );

		m_pNMP = p1.release();
		m_pModeSelector = p2.release();

		is_copy = true;

		return *this;
	}

	bool operator!=(const CCpType& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<NsCpType::CSubSeqNormalModeParameters>(m_pNMP, rhs.m_pNMP) ) return true;
		if ( notEqualsPointersAndValues<CModeSelector>(m_pModeSelector, rhs.m_pModeSelector) ) return true;

		return false;
	}

	bool operator==(const CCpType& rhs)
	{
		if (this == &rhs) return true;

		if ( *this != rhs ) return false;
		else return true;
	}

	virtual ~CCpType()
	{
		if (is_copy)
		{
			delete m_pNMP;
			delete m_pModeSelector;
		}
	}

};

Q_DECLARE_METATYPE(NsCpType::CSubSeqNormalModeParameters*)
Q_DECLARE_METATYPE(CCpType*)

#endif /* INCLUDE_PRESENTATION_ASN1_CPTYPE_H_ */
