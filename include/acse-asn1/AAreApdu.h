/*
 * AARE_apdu.h
 *
 *  Created on: 18 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_ACSE_ASN1_AARE_APDU_H_
#define INCLUDE_ACSE_ASN1_AARE_APDU_H_

#include "osistack_global.h"
#include "berInteger.h"
#include "berBitString.h"
#include "berObjectIdentifier.h"
#include "berGraphicString.h"
#include "APtitle.h"
#include "authenticationValue.h"
#include "applicationContextNameList.h"
#include "associationInformation.h"
#include "associateSourceDiagnostic.h"
#include "AEqualifier.h"

class OSISTACK_SHAREDEXPORT CAAreApdu: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier IdProtocolVersion READ getIdProtocolVersion)
	Q_PROPERTY(IBerBaseType* ProtocolVersion READ getProtocolVersion)
	Q_PROPERTY(CBerIdentifier IdApplicationContextName READ getIdApplicationContextName)
	Q_PROPERTY(IBerBaseType* ApplicationContextName READ getApplicationContextName)
	Q_PROPERTY(CBerIdentifier IdResult READ getIdResult)
	Q_PROPERTY(IBerBaseType* Result READ getResult)
	Q_PROPERTY(CBerIdentifier IdResultSourceDiagnostic READ getIdResultSourceDiagnostic)
	Q_PROPERTY(IBerBaseType* ResultSourceDiagnostic READ getResultSourceDiagnostic)
	Q_PROPERTY(CBerIdentifier IdApTitle READ getIdApTitle)
	Q_PROPERTY(IBerBaseType* ApTitle READ getApTitle)
	Q_PROPERTY(CBerIdentifier IdRespondingAeQualifier READ getIdRespondingAeQualifier)
	Q_PROPERTY(IBerBaseType* RespondingAeQualifier READ getRespondingAeQualifier)
	Q_PROPERTY(CBerIdentifier IdRespondingApInvocationIdentifier READ getIdRespondingApInvocationIdentifier)
	Q_PROPERTY(IBerBaseType* RespondingApInvocationIdentifier READ getRespondingApInvocationIdentifier)
	Q_PROPERTY(CBerIdentifier IdRespondingAeInvocationIdentifier READ getIdRespondingAeInvocationIdentifier)
	Q_PROPERTY(IBerBaseType* RespondingAeInvocationIdentifier READ getRespondingAeInvocationIdentifier)
	Q_PROPERTY(CBerIdentifier IdResponderAcseRequrements READ getIdResponderAcseRequrements)
	Q_PROPERTY(IBerBaseType* ResponderAcseRequrements READ getResponderAcseRequrements)
	Q_PROPERTY(CBerIdentifier IdMechanismName READ getIdMechanismName)
	Q_PROPERTY(IBerBaseType* MechanismName READ getMechanismName)
	Q_PROPERTY(CBerIdentifier IdRespondingAuthenticationValue READ getIdRespondingAuthenticationValue)
	Q_PROPERTY(IBerBaseType* RespondingAuthenticationValue READ getRespondingAuthenticationValue)
	Q_PROPERTY(CBerIdentifier IdApplicationContextNameList READ getIdApplicationContextNameList)
	Q_PROPERTY(IBerBaseType* ApplicationContextNameList READ getApplicationContextNameList)
	Q_PROPERTY(CBerIdentifier IdImplementationInformation READ getIdImplementationInformation)
	Q_PROPERTY(IBerBaseType* ImplementationInformation READ getImplementationInformation)
	Q_PROPERTY(CBerIdentifier IdUserInformation READ getIdUserInformation)
	Q_PROPERTY(IBerBaseType* UserInformation READ getUserInformation)

	bool is_copy;

public:

	QByteArray* getCode() { return &m_Code; }
	CBerIdentifier getIdentifier() { return c_Identifier; }
	CBerIdentifier getIdProtocolVersion() {return c_IdProtocolVersion;}
	CBerIdentifier getIdApplicationContextName() {return c_IdApplicationContextName;}
	CBerIdentifier getIdResult() {return c_IdResult;}
	CBerIdentifier getIdResultSourceDiagnostic() {return c_IdResultSourceDiagnostic;}
	CBerIdentifier getIdApTitle() {return c_IdApTitle;}
	CBerIdentifier getIdRespondingAeQualifier() {return c_IdRespondingAeQualifier;}
	CBerIdentifier getIdRespondingApInvocationIdentifier() {return c_IdRespondingApInvocationIdentifier;}
	CBerIdentifier getIdRespondingAeInvocationIdentifier() {return c_IdRespondingAeInvocationIdentifier;}
	CBerIdentifier getIdResponderAcseRequrements() {return c_IdResponderAcseRequrements;}
	CBerIdentifier getIdMechanismName() {return c_IdMechanismName;}
	CBerIdentifier getIdRespondingAuthenticationValue() {return c_IdRespondingAuthenticationValue;}
	CBerIdentifier getIdApplicationContextNameList() {return c_IdApplicationContextNameList;}
	CBerIdentifier getIdImplementationInformation() {return c_IdImplementationInformation;}
	CBerIdentifier getIdUserInformation() {return c_IdUserInformation;}

	IBerBaseType* getProtocolVersion() {return m_pProtocolVersion;}
	IBerBaseType* getApplicationContextName() {return m_pApplicationContextName;}
	IBerBaseType* getResult() {return m_pResult;}
	IBerBaseType* getResultSourceDiagnostic() {return m_pResultSourceDiagnostic;}
	IBerBaseType* getApTitle() {return m_pApTitle;}
	IBerBaseType* getRespondingAeQualifier() {return m_pRespondingAeQualifier;}
	IBerBaseType* getRespondingApInvocationIdentifier() {return m_pRespondingApInvocationIdentifier;}
	IBerBaseType* getRespondingAeInvocationIdentifier() {return m_pRespondingAeInvocationIdentifier;}
	IBerBaseType* getResponderAcseRequrements() {return m_pResponderAcseRequrements;}
	IBerBaseType* getMechanismName() {return m_pMechanismName;}
	IBerBaseType* getRespondingAuthenticationValue() {return m_pRespondingAuthenticationValue;}
	IBerBaseType* getApplicationContextNameList() {return m_pApplicationContextNameList;}
	IBerBaseType* getImplementationInformation() {return m_pImplementationInformation;}
	IBerBaseType* getUserInformation() {return m_pUserInformation;}

protected:

	void create_objects(const CAAreApdu& rhs)
	{
		std::unique_ptr<CBerBitString> p1
				( (rhs.m_pProtocolVersion != nullptr) ? new CBerBitString(*rhs.m_pProtocolVersion): nullptr );
		std::unique_ptr<CApplicationContextName> p2
				( (rhs.m_pApplicationContextName != nullptr) ? new CApplicationContextName(*rhs.m_pApplicationContextName): nullptr );
		std::unique_ptr<CBerInteger> p3
				( (rhs.m_pResult != nullptr) ? new CBerInteger(*rhs.m_pResult): nullptr );
		std::unique_ptr<CAssociateSourceDiagnostic> p4
				( (rhs.m_pResultSourceDiagnostic != nullptr) ? new CAssociateSourceDiagnostic(*rhs.m_pResultSourceDiagnostic): nullptr );
		std::unique_ptr<CApTitle> p5
				( (rhs.m_pApTitle != nullptr) ? new CApTitle(*rhs.m_pApTitle): nullptr );
		std::unique_ptr<CAeQualifier> p6
				( (rhs.m_pRespondingAeQualifier != nullptr) ? new CAeQualifier(*rhs.m_pRespondingAeQualifier): nullptr );
		std::unique_ptr<CBerInteger> p7
				( (rhs.m_pRespondingApInvocationIdentifier != nullptr) ? new CBerInteger(*rhs.m_pRespondingApInvocationIdentifier): nullptr );
		std::unique_ptr<CBerInteger> p8
				( (rhs.m_pRespondingAeInvocationIdentifier != nullptr) ? new CBerInteger(*rhs.m_pRespondingAeInvocationIdentifier): nullptr );
		std::unique_ptr<CBerBitString> p9
				( (rhs.m_pResponderAcseRequrements != nullptr) ? new CBerBitString(*rhs.m_pResponderAcseRequrements): nullptr );
		std::unique_ptr<CBerObjectIdentifier> p10
				( (rhs.m_pMechanismName != nullptr) ? new CBerObjectIdentifier(*rhs.m_pMechanismName): nullptr );
		std::unique_ptr<CAuthenticationValue> p11
				( (rhs.m_pRespondingAuthenticationValue != nullptr) ? new CAuthenticationValue(*rhs.m_pRespondingAuthenticationValue): nullptr );
		std::unique_ptr<CApplicationContextNameList> p12
				( (rhs.m_pApplicationContextNameList != nullptr) ? new CApplicationContextNameList(*rhs.m_pApplicationContextNameList): nullptr );
		std::unique_ptr<CBerGraphicString> p13
				( (rhs.m_pImplementationInformation != nullptr) ? new CBerGraphicString(*rhs.m_pImplementationInformation): nullptr );
		std::unique_ptr<CAssociationInformation> p14
				( (rhs.m_pUserInformation != nullptr) ? new CAssociationInformation(*rhs.m_pUserInformation): nullptr );

		m_pProtocolVersion = p1.release();
		m_pApplicationContextName = p2.release();
		m_pResult = p3.release();
		m_pResultSourceDiagnostic = p4.release();
		m_pApTitle = p5.release();
		m_pRespondingAeQualifier = p6.release();
		m_pRespondingApInvocationIdentifier = p7.release();
		m_pRespondingAeInvocationIdentifier = p8.release();
		m_pResponderAcseRequrements = p9.release();
		m_pMechanismName = p10.release();
		m_pRespondingAuthenticationValue = p11.release();
		m_pApplicationContextNameList = p12.release();
		m_pImplementationInformation = p13.release();
		m_pUserInformation = p14.release();

	}

	void delete_all_objects()
	{
		if (is_copy)
		{
			delete m_pProtocolVersion;
			delete m_pApplicationContextName;
			delete m_pResult;
			delete m_pResultSourceDiagnostic;
			delete m_pApTitle;
			delete m_pRespondingAeQualifier;
			delete m_pRespondingApInvocationIdentifier;
			delete m_pRespondingAeInvocationIdentifier;
			delete m_pResponderAcseRequrements;
			delete m_pMechanismName;
			delete m_pRespondingAuthenticationValue;
			delete m_pApplicationContextNameList;
			delete m_pImplementationInformation;
			delete m_pUserInformation;
		}
	}

protected:

	const CBerIdentifier c_Identifier;

	QByteArray m_Code;

	CBerIdentifier c_IdProtocolVersion;
	CBerIdentifier c_IdApplicationContextName;
	CBerIdentifier c_IdResult;
	CBerIdentifier c_IdResultSourceDiagnostic;
	CBerIdentifier c_IdApTitle;
	CBerIdentifier c_IdRespondingAeQualifier;
	CBerIdentifier c_IdRespondingApInvocationIdentifier;
	CBerIdentifier c_IdRespondingAeInvocationIdentifier;
	CBerIdentifier c_IdResponderAcseRequrements;
	CBerIdentifier c_IdMechanismName;
	CBerIdentifier c_IdRespondingAuthenticationValue;
	CBerIdentifier c_IdApplicationContextNameList;
	CBerIdentifier c_IdImplementationInformation;
	CBerIdentifier c_IdUserInformation;

	CBerBitString* m_pProtocolVersion;
	CApplicationContextName* m_pApplicationContextName;
	CBerInteger* m_pResult;
	CAssociateSourceDiagnostic* m_pResultSourceDiagnostic;
	CApTitle* m_pApTitle;
	CAeQualifier* m_pRespondingAeQualifier;
	CBerInteger* m_pRespondingApInvocationIdentifier;
	CBerInteger* m_pRespondingAeInvocationIdentifier;
	CBerBitString* m_pResponderAcseRequrements;
	CBerObjectIdentifier* m_pMechanismName;
	CAuthenticationValue* m_pRespondingAuthenticationValue;
	CApplicationContextNameList* m_pApplicationContextNameList;
	CBerGraphicString* m_pImplementationInformation;
	CAssociationInformation* m_pUserInformation;

public:

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	CAAreApdu():
			is_copy(false),
			c_Identifier(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::CONSTRUCTED, 1),
			c_IdProtocolVersion(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 0),
			c_IdApplicationContextName(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 1),
			c_IdResult(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 2),
			c_IdResultSourceDiagnostic(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 3),
			c_IdApTitle(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 4),
			c_IdRespondingAeQualifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 5),
			c_IdRespondingApInvocationIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 6),
			c_IdRespondingAeInvocationIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 7),
			c_IdResponderAcseRequrements(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 8),
			c_IdMechanismName(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 9),
			c_IdRespondingAuthenticationValue(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 10),
			c_IdApplicationContextNameList(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 11),
			c_IdImplementationInformation(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 29),
			c_IdUserInformation(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 30),
			m_pProtocolVersion(nullptr),
			m_pApplicationContextName(nullptr),
			m_pResult(nullptr),
			m_pResultSourceDiagnostic(nullptr),
			m_pApTitle(nullptr),
			m_pRespondingAeQualifier(nullptr),
			m_pRespondingApInvocationIdentifier(nullptr),
			m_pRespondingAeInvocationIdentifier(nullptr),
			m_pResponderAcseRequrements(nullptr),
			m_pMechanismName(nullptr),
			m_pRespondingAuthenticationValue(nullptr),
			m_pApplicationContextNameList(nullptr),
			m_pImplementationInformation(nullptr),
			m_pUserInformation(nullptr)
	{}

	CAAreApdu(
			CBerBitString* pProtocolVersion,
			CApplicationContextName* pApplicationContextName,
			CBerInteger* pResult,
			CAssociateSourceDiagnostic* pResultSourceDiagnostic,
			CApTitle* pApTitle,
			CAeQualifier* pRespondingAeQualifier,
			CBerInteger* pRespondingApInvocationIdentifier,
			CBerInteger* pRespondingAeInvocationIdentifier,
			CBerBitString* pResponderAcseRequrements,
			CBerObjectIdentifier* pMechanismName,
			CAuthenticationValue* pRespondingAuthenticationValue,
			CApplicationContextNameList* pApplicationContextNameList,
			CBerGraphicString* pImplementationInformation,
			CAssociationInformation* pUserInformation
		):
			is_copy(false),
			c_Identifier(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::CONSTRUCTED, 1),
			c_IdProtocolVersion(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 0),
			c_IdApplicationContextName(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 1),
			c_IdResult(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 2),
			c_IdResultSourceDiagnostic(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 3),
			c_IdApTitle(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 4),
			c_IdRespondingAeQualifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 5),
			c_IdRespondingApInvocationIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 6),
			c_IdRespondingAeInvocationIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 7),
			c_IdResponderAcseRequrements(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 8),
			c_IdMechanismName(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 9),
			c_IdRespondingAuthenticationValue(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 10),
			c_IdApplicationContextNameList(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 11),
			c_IdImplementationInformation(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 29),
			c_IdUserInformation(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 30),
			m_pProtocolVersion(pProtocolVersion),
			m_pApplicationContextName(pApplicationContextName),
			m_pResult(pResult),
			m_pResultSourceDiagnostic(pResultSourceDiagnostic),
			m_pApTitle(pApTitle),
			m_pRespondingAeQualifier(pRespondingAeQualifier),
			m_pRespondingApInvocationIdentifier(pRespondingApInvocationIdentifier),
			m_pRespondingAeInvocationIdentifier(pRespondingAeInvocationIdentifier),
			m_pResponderAcseRequrements(pResponderAcseRequrements),
			m_pMechanismName(pMechanismName),
			m_pRespondingAuthenticationValue(pRespondingAuthenticationValue),
			m_pApplicationContextNameList(pApplicationContextNameList),
			m_pImplementationInformation(pImplementationInformation),
			m_pUserInformation(pUserInformation)
	{}

	CAAreApdu(const CAAreApdu& rhs): QObject(),
		c_Identifier(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::CONSTRUCTED, 1),
		c_IdProtocolVersion(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 0),
		c_IdApplicationContextName(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 1),
		c_IdResult(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 2),
		c_IdResultSourceDiagnostic(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 3),
		c_IdApTitle(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 4),
		c_IdRespondingAeQualifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 5),
		c_IdRespondingApInvocationIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 6),
		c_IdRespondingAeInvocationIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 7),
		c_IdResponderAcseRequrements(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 8),
		c_IdMechanismName(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 9),
		c_IdRespondingAuthenticationValue(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 10),
		c_IdApplicationContextNameList(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 11),
		c_IdImplementationInformation(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 29),
		c_IdUserInformation(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 30)
	{
		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;
	}

	CAAreApdu& operator=(const CAAreApdu& rhs)
	{
		if (this == &rhs) return *this;

		delete_all_objects();

		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;

		return *this;
	}

	bool operator!=(const CAAreApdu& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerBitString>(m_pProtocolVersion, rhs.m_pProtocolVersion) ) return true;
		if ( notEqualsPointersAndValues<CApplicationContextName>(m_pApplicationContextName, rhs.m_pApplicationContextName) ) return true;
		if ( notEqualsPointersAndValues<CBerInteger>(m_pResult, rhs.m_pResult) ) return true;
		if ( notEqualsPointersAndValues<CAssociateSourceDiagnostic>(m_pResultSourceDiagnostic, rhs.m_pResultSourceDiagnostic) ) return true;
		if ( notEqualsPointersAndValues<CApTitle>(m_pApTitle, rhs.m_pApTitle) ) return true;
		if ( notEqualsPointersAndValues<CAeQualifier>(m_pRespondingAeQualifier, rhs.m_pRespondingAeQualifier) ) return true;
		if ( notEqualsPointersAndValues<CBerInteger>(m_pRespondingApInvocationIdentifier, rhs.m_pRespondingApInvocationIdentifier) ) return true;
		if ( notEqualsPointersAndValues<CBerInteger>(m_pRespondingAeInvocationIdentifier, rhs.m_pRespondingAeInvocationIdentifier) ) return true;
		if ( notEqualsPointersAndValues<CBerBitString>(m_pResponderAcseRequrements, rhs.m_pResponderAcseRequrements) ) return true;
		if ( notEqualsPointersAndValues<CBerObjectIdentifier>(m_pMechanismName, rhs.m_pMechanismName) ) return true;
		if ( notEqualsPointersAndValues<CAuthenticationValue>(m_pRespondingAuthenticationValue, rhs.m_pRespondingAuthenticationValue) ) return true;
		if ( notEqualsPointersAndValues<CApplicationContextNameList>(m_pApplicationContextNameList, rhs.m_pApplicationContextNameList) ) return true;
		if ( notEqualsPointersAndValues<CBerGraphicString>(m_pImplementationInformation, rhs.m_pImplementationInformation) ) return true;
		if ( notEqualsPointersAndValues<CAssociationInformation>(m_pUserInformation, rhs.m_pUserInformation) ) return true;

		return false;
	}

	bool operator==(const CAAreApdu& rhs)
	{
		if (this == &rhs) return true;

		if (this != &rhs) return false;
		return true;
	}

	virtual ~CAAreApdu()
	{
		delete_all_objects();
	}

};

Q_DECLARE_METATYPE(CAAreApdu*)

#endif /* INCLUDE_ACSE_ASN1_AARE_APDU_H_ */
