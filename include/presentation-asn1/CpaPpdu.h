/*
 * CpaPpdu.h
 *
 *  Created on: 24 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_PRESENTATION_ASN1_CPAPPDU_H_
#define INCLUDE_PRESENTATION_ASN1_CPAPPDU_H_

#include "osistack_global.h"
#include "berBitString.h"
#include "berOctetString.h"
#include "ResultList.h"
#include "userData.h"
#include "presentation-asn1/modeSelector.h"

namespace NsCpaPpdu
{

class OSISTACK_SHAREDEXPORT CSubSecNormalModeParameters: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier* Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(IBerBaseType* ProtocolVersion READ getProtocolVersion)
	Q_PROPERTY(IBerBaseType* RespondingPresentationSelector READ getRespondingPresentationSelector)
	Q_PROPERTY(IBerBaseType* PresentationContextDefinitionResultList READ getPresentationContextDefinitionResultList)
	Q_PROPERTY(IBerBaseType* PresentationRequirements READ getPresentationRequirements)
	Q_PROPERTY(IBerBaseType* UserSessionRequirements READ getUserSessionRequirements)
	Q_PROPERTY(IBerBaseType* UserData READ getUserData)

	bool is_copy;

protected:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier* getIdentifier() { return &m_Identifier; }

	IBerBaseType* getProtocolVersion() {return m_pProtocolVersion;}
	IBerBaseType* getRespondingPresentationSelector() {return m_pRespondingPresentationSelector;}
	IBerBaseType* getPresentationContextDefinitionResultList() {return m_pPresentationContextDefinitionResultList;}
	IBerBaseType* getPresentationRequirements() {return m_pPresentationRequirements;}
	IBerBaseType* getUserSessionRequirements() {return m_pPresentationContextDefinitionResultList;}
	IBerBaseType* getUserData() {return m_pPresentationRequirements;}

	void create_objects(const CSubSecNormalModeParameters& rhs)
	{
		std::unique_ptr<CBerBitString> p1
				( (rhs.m_pProtocolVersion != nullptr) ? new CBerBitString(*rhs.m_pProtocolVersion): nullptr );
		std::unique_ptr<CBerOctetString> p2
				( (rhs.m_pRespondingPresentationSelector != nullptr) ? new CBerOctetString(*rhs.m_pRespondingPresentationSelector): nullptr );
		std::unique_ptr<CResultList> p3
				( (rhs.m_pPresentationContextDefinitionResultList != nullptr) ? new CResultList(*rhs.m_pPresentationContextDefinitionResultList): nullptr );
		std::unique_ptr<CBerBitString> p4
				( (rhs.m_pPresentationRequirements != nullptr) ? new CBerBitString(*rhs.m_pPresentationRequirements): nullptr );
		std::unique_ptr<CBerBitString> p5
				( (rhs.m_pUserSessionRequirements != nullptr) ? new CBerBitString(*rhs.m_pUserSessionRequirements): nullptr );
		std::unique_ptr<CUserData> p6
				( (rhs.m_pUserData != nullptr) ? new CUserData(*rhs.m_pUserData): nullptr );

		m_pProtocolVersion = p1.release();
		m_pRespondingPresentationSelector = p2.release();
		m_pPresentationContextDefinitionResultList = p3.release();
		m_pPresentationRequirements = p4.release();
		m_pUserSessionRequirements = p5.release();
		m_pUserData = p6.release();
	}

	void delete_all_objects()
	{
		if (is_copy)
		{
			delete m_pProtocolVersion;
			delete m_pRespondingPresentationSelector;
			delete m_pPresentationContextDefinitionResultList;
			delete m_pPresentationRequirements;
			delete m_pUserSessionRequirements;
			delete m_pUserData;
		}
	}

protected:

	CBerIdentifier m_Identifier;
	QByteArray m_Code;

	CBerBitString* m_pProtocolVersion;
	CBerOctetString* m_pRespondingPresentationSelector;
	CResultList* m_pPresentationContextDefinitionResultList;
	CBerBitString* m_pPresentationRequirements;
	CBerBitString* m_pUserSessionRequirements;
	CUserData* m_pUserData;

public:

	ASN1_CODEC(CBerBaseStorage)

	static CBerIdentifier s_Identifier;
	static quint32 s_metaTypeIdentifier;

	CSubSecNormalModeParameters():
		is_copy(false),
		m_Identifier(s_Identifier),
		m_pProtocolVersion(nullptr),
		m_pRespondingPresentationSelector(nullptr),
		m_pPresentationContextDefinitionResultList(nullptr),
		m_pPresentationRequirements(nullptr),
		m_pUserSessionRequirements(nullptr),
		m_pUserData(nullptr)
	{}

	CSubSecNormalModeParameters(
			CBerBitString* pProtocolVersion,
			CBerOctetString* pRespondingPresentationSelector,
			CResultList* pPresentationContextDefinitionResultList,
			CBerBitString* pPresentationRequirements,
			CBerBitString* pUserSessionRequirements,
			CUserData* pUserData
	):
		is_copy(false),
		m_Identifier(s_Identifier),
		m_pProtocolVersion(pProtocolVersion),
		m_pRespondingPresentationSelector(pRespondingPresentationSelector),
		m_pPresentationContextDefinitionResultList(pPresentationContextDefinitionResultList),
		m_pPresentationRequirements(pPresentationRequirements),
		m_pUserSessionRequirements(pUserSessionRequirements),
		m_pUserData(pUserData)
	{}

	CSubSecNormalModeParameters(const CSubSecNormalModeParameters& rhs): QObject()
	{
		create_objects(rhs);

		m_Identifier = rhs.m_Identifier;
		m_Code = rhs.m_Code;
		is_copy = true;
	}

	CSubSecNormalModeParameters& operator=(const CSubSecNormalModeParameters& rhs)
	{
		if (this == &rhs) return *this;

		delete_all_objects();

		create_objects(rhs);

		m_Identifier = rhs.m_Identifier;
		m_Code = rhs.m_Code;
		is_copy = true;

		return *this;
	}

	bool operator!=(const CSubSecNormalModeParameters& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerBitString>(m_pProtocolVersion, rhs.m_pProtocolVersion) ) return true;
		if ( notEqualsPointersAndValues<CBerOctetString>(m_pRespondingPresentationSelector, rhs.m_pRespondingPresentationSelector) ) return true;
		if ( notEqualsPointersAndValues<CResultList>(m_pPresentationContextDefinitionResultList, rhs.m_pPresentationContextDefinitionResultList) ) return true;
		if ( notEqualsPointersAndValues<CBerBitString>(m_pPresentationRequirements, rhs.m_pPresentationRequirements) ) return true;
		if ( notEqualsPointersAndValues<CBerBitString>(m_pUserSessionRequirements, rhs.m_pUserSessionRequirements) ) return true;
		if ( notEqualsPointersAndValues<CUserData>(m_pUserData, rhs.m_pUserData) ) return true;

		return false;
	}

	virtual ~CSubSecNormalModeParameters()
	{
		delete_all_objects();
	}

};

} // end of namespace

class CCpaPpdu: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier* Identifier READ getIdentifier)
	Q_PROPERTY(CModeSelector* presentationContextIdentifier READ getPresentationContextIdentifier)
	Q_PROPERTY(IBerBaseType* Integer READ getSPDV)

	bool is_copy;

protected:

	QByteArray m_Code;

	CBerIdentifier m_Identifier;

	CModeSelector* m_pModeSelector;
	NsCpaPpdu::CSubSecNormalModeParameters* m_pSSNMP;

	CBerIdentifier* getIdentifier() { return &m_Identifier; }
	CModeSelector* getPresentationContextIdentifier() { return m_pModeSelector; }
	NsCpaPpdu::CSubSecNormalModeParameters* getSPDV() { return m_pSSNMP; }

public:

	ASN1_CODEC(CBerBaseStorage)

	static CBerIdentifier s_Identifier;
	static quint32 s_metaTypeIdentifier;

	CCpaPpdu():
		is_copy(false),
		m_Identifier(s_Identifier),
		m_pModeSelector(nullptr),
		m_pSSNMP(nullptr)
	{ }

	CCpaPpdu(CModeSelector* presentationContextIdentifier,
			NsCpaPpdu::CSubSecNormalModeParameters* pSPDV):
		is_copy(false),
		m_Identifier(s_Identifier),
		m_pModeSelector(presentationContextIdentifier),
		m_pSSNMP(pSPDV)
	{ }

	CCpaPpdu(const CCpaPpdu& rhs): QObject()
	{
		m_Identifier = s_Identifier;
		m_Code = rhs.m_Code;

		std::unique_ptr<NsCpaPpdu::CSubSecNormalModeParameters> p1
				( (rhs.m_pSSNMP != nullptr) ?
						new NsCpaPpdu::CSubSecNormalModeParameters(*rhs.m_pSSNMP): nullptr );

		std::unique_ptr<CModeSelector> p2
				( (rhs.m_pModeSelector != nullptr) ? new CModeSelector(*rhs.m_pModeSelector): nullptr );

		m_pSSNMP = p1.release();
		m_pModeSelector = p2.release();

		is_copy = true;
	}

	CCpaPpdu& operator=(const CCpaPpdu& rhs)
	{
		if (this == &rhs) return *this;

		m_Code = rhs.m_Code;

		if (is_copy)
		{
			delete m_pSSNMP;
			delete m_pModeSelector;
		}

		m_Identifier = s_Identifier;
		m_Code = rhs.m_Code;

		std::unique_ptr<NsCpaPpdu::CSubSecNormalModeParameters> p1
				( (rhs.m_pSSNMP != nullptr) ?
						new NsCpaPpdu::CSubSecNormalModeParameters(*rhs.m_pSSNMP): nullptr );

		std::unique_ptr<CModeSelector> p2
				( (rhs.m_pModeSelector != nullptr) ? new CModeSelector(*rhs.m_pModeSelector): nullptr );

		m_pSSNMP = p1.release();
		m_pModeSelector = p2.release();

		is_copy = true;

		return *this;
	}

	bool operator!=(const CCpaPpdu& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<NsCpaPpdu::CSubSecNormalModeParameters>(m_pSSNMP, rhs.m_pSSNMP) ) return true;

		return false;
	}

	bool operator==(const CCpaPpdu& rhs)
	{
		if (this == &rhs) return true;

		if ( *this != rhs ) return false;
		else return true;
	}

	virtual ~CCpaPpdu()
	{
		if (is_copy)
			delete m_pSSNMP;
	}

};

Q_DECLARE_METATYPE(CCpaPpdu*)
Q_DECLARE_METATYPE(NsCpaPpdu::CSubSecNormalModeParameters*)

#endif /* INCLUDE_PRESENTATION_ASN1_CPAPPDU_H_ */
