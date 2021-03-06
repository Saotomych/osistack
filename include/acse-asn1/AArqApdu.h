/*
 * AARQ_apdu.h
 *
 *  Created on: 17 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_ACSE_ASN1_AARQ_APDU_H_
#define INCLUDE_ACSE_ASN1_AARQ_APDU_H_

#include "osistack_global.h"
#include "berInteger.h"
#include "berBitString.h"
#include "berObjectIdentifier.h"
#include "berGraphicString.h"
#include "APtitle.h"
#include "AEqualifier.h"
#include "authenticationValue.h"
#include "applicationContextNameList.h"
#include "associationInformation.h"

class OSISTACK_SHAREDEXPORT CAArqApdu: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier IdProtocolVersion READ getIdProtocolVersion)
	Q_PROPERTY(IBerBaseType* ProtocolVersion READ getProtocolVersion)
	Q_PROPERTY(CBerIdentifier IdApplicationContextName READ getIdApplicationContextName)
	Q_PROPERTY(IBerBaseType* ApplicationContextName READ getApplicationContextName)
	Q_PROPERTY(CBerIdentifier IdCalledApTitle READ getIdCalledApTitle)
	Q_PROPERTY(IBerBaseType* CalledApTitle READ getCalledApTitle)
	Q_PROPERTY(CBerIdentifier IdCalledAeQualifier READ getIdCalledAeQualifier)
	Q_PROPERTY(IBerBaseType* CalledAeQualifier READ getCalledAeQualifier)
	Q_PROPERTY(CBerIdentifier IdCalledApInvocationIdentifier READ getIdCalledApInvocationIdentifier)
	Q_PROPERTY(IBerBaseType* CalledApInvocationIdentifier READ getCalledApInvocationIdentifier)
	Q_PROPERTY(CBerIdentifier IdCalledAeInvocationIdentifier READ getIdCalledAeInvocationIdentifier)
	Q_PROPERTY(IBerBaseType* CalledAeInvocationIdentifier READ getCalledAeInvocationIdentifier)
	Q_PROPERTY(CBerIdentifier IdCallingApTitle READ getIdCallingApTitle)
	Q_PROPERTY(IBerBaseType* CallingApTitle READ getCallingApTitle)
	Q_PROPERTY(CBerIdentifier IdCallingAeQualifier READ getIdCallingAeQualifier)
	Q_PROPERTY(IBerBaseType* CallingAeQualifier READ getCallingAeQualifier)
	Q_PROPERTY(CBerIdentifier IdCallingApInvocationIdentifier READ getIdCallingApInvocationIdentifier)
	Q_PROPERTY(IBerBaseType* CallingApInvocationIdentifier READ getCallingApInvocationIdentifier)
	Q_PROPERTY(CBerIdentifier IdCallingAeInvocationIdentifier READ getIdCallingAeInvocationIdentifier)
	Q_PROPERTY(IBerBaseType* CallingAeInvocationIdentifier READ getCallingAeInvocationIdentifier)
	Q_PROPERTY(CBerIdentifier IdSenderAcseRequerements READ getIdSenderAcseRequerements)
	Q_PROPERTY(IBerBaseType* SenderAcseRequerements READ getSenderAcseRequerements)
	Q_PROPERTY(CBerIdentifier IdMechanismName READ getIdMechanismName)
	Q_PROPERTY(IBerBaseType* MechanismName READ getMechanismName)
	Q_PROPERTY(CBerIdentifier IdCallingAuthenticationValue READ getIdCallingAuthenticationValue)
	Q_PROPERTY(IBerBaseType* CallingAuthenticationValue READ getCallingAuthenticationValue)
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
	CBerIdentifier getIdCalledApTitle() {return c_IdCalledApTitle;}
	CBerIdentifier getIdCalledAeQualifier() {return c_IdCalledAeQualifier;}
	CBerIdentifier getIdCalledApInvocationIdentifier() {return c_IdCalledApInvocationIdentifier;}
	CBerIdentifier getIdCalledAeInvocationIdentifier() {return c_IdCalledAeInvocationIdentifier;}
	CBerIdentifier getIdCallingApTitle() {return c_IdCallingApTitle;}
	CBerIdentifier getIdCallingAeQualifier() {return c_IdCallingAeQualifier;}
	CBerIdentifier getIdCallingApInvocationIdentifier() {return c_IdCallingApInvocationIdentifier;}
	CBerIdentifier getIdCallingAeInvocationIdentifier() {return c_IdCallingAeInvocationIdentifier;}
	CBerIdentifier getIdSenderAcseRequerements() {return c_IdSenderAcseRequerements;}
	CBerIdentifier getIdMechanismName() {return c_IdMechanismName;}
	CBerIdentifier getIdCallingAuthenticationValue() {return c_IdCallingAuthenticationValue;}
	CBerIdentifier getIdApplicationContextNameList() {return c_IdApplicationContextNameList;}
	CBerIdentifier getIdImplementationInformation() {return c_IdImplementationInformation;}
	CBerIdentifier getIdUserInformation() {return c_IdUserInformation;}

	IBerBaseType* getProtocolVersion() {return m_pProtocolVersion;}
	IBerBaseType* getApplicationContextName() {return m_pApplicationContextName;}
	IBerBaseType* getCalledApTitle() {return m_pCalledApTitle;}
	IBerBaseType* getCalledAeQualifier() {return m_pCalledAeQualifier;}
	IBerBaseType* getCalledApInvocationIdentifier() {return m_pCalledApInvocationIdentifier;}
	IBerBaseType* getCalledAeInvocationIdentifier() {return m_pCalledAeInvocationIdentifier;}
	IBerBaseType* getCallingApTitle() {return m_pCallingApTitle;}
	IBerBaseType* getCallingAeQualifier() {return m_pCallingAeQualifier;}
	IBerBaseType* getCallingApInvocationIdentifier() {return m_pCallingApInvocationIdentifier;}
	IBerBaseType* getCallingAeInvocationIdentifier() {return m_pCallingAeInvocationIdentifier;}
	IBerBaseType* getSenderAcseRequerements() {return m_pSenderAcseRequerements;}
	IBerBaseType* getMechanismName() {return m_pMechanismName;}
	IBerBaseType* getCallingAuthenticationValue() {return m_pCallingAuthenticationValue;}
	IBerBaseType* getApplicationContextNameList() {return m_pApplicationContextNameList;}
	IBerBaseType* getImplementationInformation() {return m_pImplementationInformation;}
	IBerBaseType* getUserInformation() {return m_pUserInformation;}

protected:

	inline IBerBaseType* create_object_by_id(const CBerIdentifier& id)
	{
		qDebug() << "INFO: CAArqApdu create member by id = " << id.getCode()->toHex();

		if ( c_IdProtocolVersion == id )
			{ m_pProtocolVersion = new CBerBitString(); is_copy=true; return m_pProtocolVersion; }
		if ( c_IdApplicationContextName == id )
			{ m_pApplicationContextName = new CApplicationContextName(); is_copy=true; return m_pApplicationContextName; }
		if ( c_IdCalledApTitle == id )
			{ m_pCalledApTitle = new CApTitle(); is_copy=true; return m_pCalledApTitle; }
		if ( c_IdCalledAeQualifier == id )
			{ m_pCalledAeQualifier = new CAeQualifier(); is_copy=true; return m_pCalledAeQualifier; }
		if ( c_IdCalledApInvocationIdentifier == id )
			{ m_pCalledApInvocationIdentifier = new CBerInteger(); is_copy=true; return m_pCalledApInvocationIdentifier; }
		if ( c_IdCalledAeInvocationIdentifier == id )
			{ m_pCalledAeInvocationIdentifier = new CBerInteger(); is_copy=true; return m_pCalledAeInvocationIdentifier; }
		if ( c_IdCallingApTitle == id )
			{ m_pCallingApTitle = new CApTitle(); is_copy=true; return m_pCallingApTitle; }
		if ( c_IdCallingAeQualifier == id )
			{ m_pCallingAeQualifier = new CAeQualifier(); is_copy=true; return m_pCallingAeQualifier; }
		if ( c_IdCallingApInvocationIdentifier == id )
			{ m_pCallingApInvocationIdentifier = new CBerInteger(); is_copy=true; return m_pCallingApInvocationIdentifier; }
		if ( c_IdCallingAeInvocationIdentifier == id )
			{ m_pCallingAeInvocationIdentifier = new CBerInteger(); is_copy=true; return m_pCallingAeInvocationIdentifier; }
		if ( c_IdSenderAcseRequerements == id )
			{ m_pSenderAcseRequerements = new CBerBitString(); is_copy=true; return m_pSenderAcseRequerements; }
		if ( c_IdMechanismName == id )
			{ m_pMechanismName = new CBerObjectIdentifier(); is_copy=true; return m_pMechanismName; }
		if ( c_IdCallingAuthenticationValue == id )
			{ m_pCallingAuthenticationValue = new CAuthenticationValue(); is_copy=true; return m_pCallingAuthenticationValue; }
		if ( c_IdApplicationContextNameList == id )
			{ m_pApplicationContextNameList = new CApplicationContextNameList(); is_copy=true; return m_pApplicationContextNameList; }
		if ( c_IdImplementationInformation == id )
			{ m_pImplementationInformation = new CBerGraphicString(); is_copy=true; return m_pImplementationInformation; }
		if ( c_IdUserInformation == id )
			{ m_pUserInformation = new CAssociationInformation(); is_copy=true; return m_pUserInformation; }

		return nullptr;
	}

	inline void create_objects(const CAArqApdu& rhs)
	{
		std::unique_ptr<CBerBitString> p1
				( (rhs.m_pProtocolVersion != nullptr) ? new CBerBitString(*rhs.m_pProtocolVersion): nullptr );
		std::unique_ptr<CApplicationContextName> p2
				( (rhs.m_pApplicationContextName != nullptr) ? new CApplicationContextName(*rhs.m_pApplicationContextName) : nullptr );
		std::unique_ptr<CApTitle> p3
				( (rhs.m_pCalledApTitle != nullptr) ? new CApTitle(*rhs.m_pCalledApTitle) : nullptr );
		std::unique_ptr<CAeQualifier> p4
				( (rhs.m_pCalledAeQualifier != nullptr) ? new CAeQualifier(*rhs.m_pCalledAeQualifier) : nullptr );
		std::unique_ptr<CBerInteger> p5
				( (rhs.m_pCalledApInvocationIdentifier != nullptr) ? new CBerInteger(*rhs.m_pCalledApInvocationIdentifier) : nullptr );
		std::unique_ptr<CBerInteger> p6
				( (rhs.m_pCalledAeInvocationIdentifier != nullptr) ? new CBerInteger(*rhs.m_pCalledAeInvocationIdentifier) : nullptr );
		std::unique_ptr<CApTitle> p7
				( (rhs.m_pCallingApTitle != nullptr) ? new CApTitle(*rhs.m_pCallingApTitle) : nullptr );
		std::unique_ptr<CAeQualifier> p8
				( (rhs.m_pCallingAeQualifier != nullptr) ? new CAeQualifier(*rhs.m_pCallingAeQualifier) : nullptr );
		std::unique_ptr<CBerInteger> p9
				( (rhs.m_pCallingApInvocationIdentifier != nullptr) ? new CBerInteger(*rhs.m_pCallingApInvocationIdentifier) : nullptr );
		std::unique_ptr<CBerInteger> p10
				( (rhs.m_pCallingAeInvocationIdentifier != nullptr) ? new CBerInteger(*rhs.m_pCallingAeInvocationIdentifier) : nullptr );
		std::unique_ptr<CBerBitString> p11
				( (rhs.m_pSenderAcseRequerements != nullptr) ? new CBerBitString(*rhs.m_pSenderAcseRequerements) : nullptr );
		std::unique_ptr<CBerObjectIdentifier> p12
				( (rhs.m_pMechanismName != nullptr) ? new CBerObjectIdentifier(*rhs.m_pMechanismName) : nullptr );
		std::unique_ptr<CAuthenticationValue> p13
				( (rhs.m_pCallingAuthenticationValue != nullptr) ? new CAuthenticationValue(*rhs.m_pCallingAuthenticationValue) : nullptr);
		std::unique_ptr<CApplicationContextNameList> p14
				( (rhs.m_pApplicationContextNameList != nullptr) ? new CApplicationContextNameList(*rhs.m_pApplicationContextNameList) : nullptr);
		std::unique_ptr<CBerGraphicString> p15
				( (rhs.m_pImplementationInformation != nullptr) ? new CBerGraphicString(*rhs.m_pImplementationInformation) : nullptr );
		std::unique_ptr<CAssociationInformation> p16
				( (rhs.m_pUserInformation != nullptr) ? new CAssociationInformation(*rhs.m_pUserInformation) : nullptr );

		m_pProtocolVersion = p1.release();
		m_pApplicationContextName = p2.release();
		m_pCalledApTitle = p3.release();
		m_pCalledAeQualifier = p4.release();
		m_pCalledApInvocationIdentifier = p5.release();
		m_pCalledAeInvocationIdentifier = p6.release();
		m_pCallingApTitle = p7.release();
		m_pCallingAeQualifier = p8.release();
		m_pCallingApInvocationIdentifier = p9.release();
		m_pCallingAeInvocationIdentifier = p10.release();
		m_pSenderAcseRequerements = p11.release();
		m_pMechanismName = p12.release();
		m_pCallingAuthenticationValue = p13.release();
		m_pApplicationContextNameList = p14.release();
		m_pImplementationInformation = p15.release();
		m_pUserInformation = p16.release();

	}

	inline void delete_all_objects()
	{
		if (is_copy)
		{
			delete m_pProtocolVersion;
			delete m_pApplicationContextName;
			delete m_pCalledApTitle;
			delete m_pCalledAeQualifier;
			delete m_pCalledApInvocationIdentifier;
			delete m_pCalledAeInvocationIdentifier;
			delete m_pCallingApTitle;
			delete m_pCallingAeQualifier;
			delete m_pCallingApInvocationIdentifier;
			delete m_pCallingAeInvocationIdentifier;
			delete m_pSenderAcseRequerements;
			delete m_pMechanismName;
			delete m_pCallingAuthenticationValue;
			delete m_pApplicationContextNameList;
			delete m_pImplementationInformation;
			delete m_pUserInformation;
		}
	}

protected:
	const CBerIdentifier c_Identifier;
	QByteArray m_Code;

	const CBerIdentifier c_IdProtocolVersion;
	const CBerIdentifier c_IdApplicationContextName;
	const CBerIdentifier c_IdCalledApTitle;
	const CBerIdentifier c_IdCalledAeQualifier;
	const CBerIdentifier c_IdCalledApInvocationIdentifier;
	const CBerIdentifier c_IdCalledAeInvocationIdentifier;
	const CBerIdentifier c_IdCallingApTitle;
	const CBerIdentifier c_IdCallingAeQualifier;
	const CBerIdentifier c_IdCallingApInvocationIdentifier;
	const CBerIdentifier c_IdCallingAeInvocationIdentifier;
	const CBerIdentifier c_IdSenderAcseRequerements;
	const CBerIdentifier c_IdMechanismName;
	const CBerIdentifier c_IdCallingAuthenticationValue;
	const CBerIdentifier c_IdApplicationContextNameList;
	const CBerIdentifier c_IdImplementationInformation;
	const CBerIdentifier c_IdUserInformation;

	CBerBitString* m_pProtocolVersion;
	CApplicationContextName* m_pApplicationContextName;
	CApTitle* m_pCalledApTitle;
	CAeQualifier* m_pCalledAeQualifier;
	CBerInteger* m_pCalledApInvocationIdentifier;
	CBerInteger* m_pCalledAeInvocationIdentifier;
	CApTitle* m_pCallingApTitle;
	CAeQualifier* m_pCallingAeQualifier;
	CBerInteger* m_pCallingApInvocationIdentifier;
	CBerInteger* m_pCallingAeInvocationIdentifier;
	CBerBitString* m_pSenderAcseRequerements;
	CBerObjectIdentifier* m_pMechanismName;
	CAuthenticationValue* m_pCallingAuthenticationValue;
	CApplicationContextNameList* m_pApplicationContextNameList;
	CBerGraphicString* m_pImplementationInformation;
	CAssociationInformation* m_pUserInformation;

public:

	ASN1_CODEC(CBerBaseStorage)

	static quint32 s_metaTypeIdentifier;

	static CBerIdentifier getBerIdentifier()
	{
		return CBerIdentifier(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::CONSTRUCTED, 0);
	}

	CAArqApdu():
		is_copy(false),
		c_Identifier(getBerIdentifier()),
		c_IdProtocolVersion(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 0),
		c_IdApplicationContextName(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 1),
		c_IdCalledApTitle(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 2),
		c_IdCalledAeQualifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 3),
		c_IdCalledApInvocationIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 4),
		c_IdCalledAeInvocationIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 5),
		c_IdCallingApTitle(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 6),
		c_IdCallingAeQualifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 7),
		c_IdCallingApInvocationIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 8),
		c_IdCallingAeInvocationIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 9),
		c_IdSenderAcseRequerements(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 10),
		c_IdMechanismName(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 11),
		c_IdCallingAuthenticationValue(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 12),
		c_IdApplicationContextNameList(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 13),
		c_IdImplementationInformation(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 29),
		c_IdUserInformation(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 30),
		m_pProtocolVersion(nullptr),
		m_pApplicationContextName(nullptr),
		m_pCalledApTitle(nullptr),
		m_pCalledAeQualifier(nullptr),
		m_pCalledApInvocationIdentifier(nullptr),
		m_pCalledAeInvocationIdentifier(nullptr),
		m_pCallingApTitle(nullptr),
		m_pCallingAeQualifier(nullptr),
		m_pCallingApInvocationIdentifier(nullptr),
		m_pCallingAeInvocationIdentifier(nullptr),
		m_pSenderAcseRequerements(nullptr),
		m_pMechanismName(nullptr),
		m_pCallingAuthenticationValue(nullptr),
		m_pApplicationContextNameList(nullptr),
		m_pImplementationInformation(nullptr),
		m_pUserInformation(nullptr)
	{}

	CAArqApdu(
			CBerBitString* pProtocolVersion,
			CApplicationContextName* pApplicationContextName,
			CApTitle* pCalledApTitle,
			CAeQualifier* pCalledAeQualifier,
			CBerInteger* pCalledApInvocationIdentifier,
			CBerInteger* pCalledAeInvocationIdentifier,
			CApTitle* pCallingApTitle,
			CAeQualifier* pCallingAeQualifier,
			CBerInteger* pCallingApInvocationIdentifier,
			CBerInteger* pCallingAeInvocationIdentifier,
			CBerBitString* pSenderAcseRequerements,
			CBerObjectIdentifier* pMechanismName,
			CAuthenticationValue* pCallingAuthenticationValue,
			CApplicationContextNameList* pApplicationContextNameList,
			CBerGraphicString* pImplementationInformation,
			CAssociationInformation* pUserInformation	):
				is_copy(false),
				c_Identifier(getBerIdentifier()),
				c_IdProtocolVersion(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 0),
				c_IdApplicationContextName(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 1),
				c_IdCalledApTitle(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 2),
				c_IdCalledAeQualifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 3),
				c_IdCalledApInvocationIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 4),
				c_IdCalledAeInvocationIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 5),
				c_IdCallingApTitle(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 6),
				c_IdCallingAeQualifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 7),
				c_IdCallingApInvocationIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 8),
				c_IdCallingAeInvocationIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 9),
				c_IdSenderAcseRequerements(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 10),
				c_IdMechanismName(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 11),
				c_IdCallingAuthenticationValue(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 12),
				c_IdApplicationContextNameList(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 13),
				c_IdImplementationInformation(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 29),
				c_IdUserInformation(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 30),
				m_pProtocolVersion(pProtocolVersion),
				m_pApplicationContextName(pApplicationContextName),
				m_pCalledApTitle(pCalledApTitle),
				m_pCalledAeQualifier(pCalledAeQualifier),
				m_pCalledApInvocationIdentifier(pCalledApInvocationIdentifier),
				m_pCalledAeInvocationIdentifier(pCalledAeInvocationIdentifier),
				m_pCallingApTitle(pCallingApTitle),
				m_pCallingAeQualifier(pCallingAeQualifier),
				m_pCallingApInvocationIdentifier(pCallingApInvocationIdentifier),
				m_pCallingAeInvocationIdentifier(pCallingAeInvocationIdentifier),
				m_pSenderAcseRequerements(pSenderAcseRequerements),
				m_pMechanismName(pMechanismName),
				m_pCallingAuthenticationValue(pCallingAuthenticationValue),
				m_pApplicationContextNameList(pApplicationContextNameList),
				m_pImplementationInformation(pImplementationInformation),
				m_pUserInformation(pUserInformation)
	{}

	CAArqApdu(const CAArqApdu& rhs): QObject(),
		c_Identifier(getBerIdentifier()),
		c_IdProtocolVersion(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 0),
		c_IdApplicationContextName(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 1),
		c_IdCalledApTitle(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 2),
		c_IdCalledAeQualifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 3),
		c_IdCalledApInvocationIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 4),
		c_IdCalledAeInvocationIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 5),
		c_IdCallingApTitle(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 6),
		c_IdCallingAeQualifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 7),
		c_IdCallingApInvocationIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 8),
		c_IdCallingAeInvocationIdentifier(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 9),
		c_IdSenderAcseRequerements(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 10),
		c_IdMechanismName(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 11),
		c_IdCallingAuthenticationValue(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 12),
		c_IdApplicationContextNameList(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 13),
		c_IdImplementationInformation(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::PRIMITIVE, 29),
		c_IdUserInformation(CBerIdentifier::CONTEXT_CLASS, CBerIdentifier::CONSTRUCTED, 30)
	{
		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;
	}

	CAArqApdu& operator=(const CAArqApdu& rhs)
	{
		if (this == &rhs) return *this;

		delete_all_objects();

		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;

		return *this;
	}

	bool operator!=(const CAArqApdu& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CBerBitString>(m_pProtocolVersion, rhs.m_pProtocolVersion) ) return true;
		if ( notEqualsPointersAndValues<CApplicationContextName>(m_pApplicationContextName, rhs.m_pApplicationContextName) ) return true;
		if ( notEqualsPointersAndValues<CApTitle>(m_pCalledApTitle, rhs.m_pCalledApTitle) ) return true;
		if ( notEqualsPointersAndValues<CAeQualifier>(m_pCalledAeQualifier, rhs.m_pCalledAeQualifier) ) return true;
		if ( notEqualsPointersAndValues<CBerInteger>(m_pCalledApInvocationIdentifier, rhs.m_pCalledApInvocationIdentifier) ) return true;
		if ( notEqualsPointersAndValues<CBerInteger>(m_pCalledAeInvocationIdentifier, rhs.m_pCalledAeInvocationIdentifier) ) return true;
		if ( notEqualsPointersAndValues<CApTitle>(m_pCallingApTitle, rhs.m_pCallingApTitle) ) return true;
		if ( notEqualsPointersAndValues<CAeQualifier>(m_pCallingAeQualifier, rhs.m_pCallingAeQualifier) ) return true;
		if ( notEqualsPointersAndValues<CBerInteger>(m_pCallingApInvocationIdentifier, rhs.m_pCallingApInvocationIdentifier) ) return true;
		if ( notEqualsPointersAndValues<CBerInteger>(m_pCallingAeInvocationIdentifier, rhs.m_pCallingAeInvocationIdentifier) ) return true;
		if ( notEqualsPointersAndValues<CBerBitString>(m_pSenderAcseRequerements, rhs.m_pSenderAcseRequerements) ) return true;
		if ( notEqualsPointersAndValues<CBerObjectIdentifier>(m_pMechanismName, rhs.m_pMechanismName) ) return true;
		if ( notEqualsPointersAndValues<CAuthenticationValue>(m_pCallingAuthenticationValue, rhs.m_pCallingAuthenticationValue) ) return true;
		if ( notEqualsPointersAndValues<CApplicationContextNameList>(m_pApplicationContextNameList, rhs.m_pApplicationContextNameList) ) return true;
		if ( notEqualsPointersAndValues<CBerGraphicString>(m_pImplementationInformation, rhs.m_pImplementationInformation) ) return true;
		if ( notEqualsPointersAndValues<CAssociationInformation>(m_pUserInformation, rhs.m_pUserInformation) ) return true;

		return false;
	}

	virtual ~CAArqApdu()
	{
		delete_all_objects();
	}

};

Q_DECLARE_METATYPE(CAArqApdu*)

#endif /* INCLUDE_ACSE_ASN1_AARQ_APDU_H_ */
