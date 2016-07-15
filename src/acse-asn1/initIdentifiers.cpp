/*
 * initIdentifiers.cpp
 *
 *  Created on: 20 нояб. 2015 г.
 *      Author: alexey
 */

#include "AAreApdu.h"
#include "AArqApdu.h"
#include "RLreApdu.h"
#include "RLrqApdu.h"
#include "AcseApdu.h"
#include "AEqualifier.h"
#include "applicationContextNameList.h"
#include "APtitle.h"
#include "AEtitle.h"
#include "associateSourceDiagnostic.h"
#include "associationInformation.h"
#include "authenticationValue.h"
#include "externalLinkV1.h"
#include "externalLinkV2.h"
#include "ResultSubsequence.h"
#include "ResultList.h"
#include "PdvList.h"
#include "fullyEncodedData.h"
#include "userData.h"
#include "CpaPpdu.h"
#include "contextList.h"
#include "defaultContextName.h"
#include "CpType.h"
#include "modeSelector.h"
#include "AcseAssociation.h"

// asce-asn1/AAreApdu.h
quint32 CAAreApdu::s_metaTypeIdentifier = qRegisterMetaType<CAAreApdu*>();

// asce-asn1/AArqApdu.h
quint32 CAArqApdu::s_metaTypeIdentifier = qRegisterMetaType<CAArqApdu*>();

// asce-asn1/RLreApdu.h
quint32 CRLreApdu::s_metaTypeIdentifier = qRegisterMetaType<CRLreApdu*>();

// asce-asn1/RLrqApdu.h
quint32 CRLrqApdu::s_metaTypeIdentifier = qRegisterMetaType<CRLrqApdu*>();

// asce-asn1/AcseApdu.h
quint32 CAcseApdu::s_metaTypeIdentifier = qRegisterMetaType<CAcseApdu*>();

// asce-asn1/AEqualifier.h
quint32 CAeQualifier::s_metaTypeIdentifier = qRegisterMetaType<CAeQualifier*>();

// asce-asn1/applicationContextNameList.h
quint32 CApplicationContextName::s_metaTypeIdentifier = qRegisterMetaType<CApplicationContextName*>();
quint32 CApplicationContextNameList::s_metaTypeIdentifier = qRegisterMetaType<CApplicationContextNameList*>();
quint32 CApplicationContextNameList::s_metaTypeListId = qRegisterMetaType<QLinkedList<CBerObjectIdentifier>*>();

// asce-asn1/APtitle.h
quint32 CApTitle::s_metaTypeIdentifier = qRegisterMetaType<CApTitle*>();

// asce-asn1/AEtitle.h
quint32 CAeTitle::s_metaTypeIdentifier = qRegisterMetaType<CAeTitle*>();

// asce-asn1/associateSourcediagnoctic.h
quint32 CAssociateSourceDiagnostic::s_metaTypeIdentifier = qRegisterMetaType<CAssociateSourceDiagnostic*>();

// asce-asn1/associationInformation.h
quint32 CAssociationInformation::s_metaTypeIdentifier = qRegisterMetaType<CAssociationInformation*>();
quint32 CAssociationInformation::s_metaTypeListId = qRegisterMetaType<QLinkedList<CExternalLinkV1>*>();

// asce-asn1/externalLinkV1.h
quint32 CExternalLinkV1::s_metaTypeIdentifier = qRegisterMetaType<CExternalLinkV1*>();
quint32 NsExternalLinkV1::SubChoiceEncoding::s_metaTypeIdentifier = qRegisterMetaType<NsExternalLinkV1::SubChoiceEncoding*>();

// asce-asn1/externalLinkV2.h
quint32 CExternalLinkV2::s_metaTypeIdentifier = qRegisterMetaType<CExternalLinkV2*>();

// presentation-asn1/ResultSubsequence.h
quint32 CResultSubsequence::s_metaTypeIdentifier = qRegisterMetaType<CResultSubsequence*>();

// presentation-asn1/ResultList.h
quint32 CResultList::s_metaTypeIdentifier =  qRegisterMetaType<CResultList*>();
quint32 CResultList::s_metaTypeListId =  qRegisterMetaType<QLinkedList<CResultSubsequence>*>();

// presentation-asn1/PdvList.h
quint32 CPdvList::s_metaTypeIdentifier =  qRegisterMetaType<CPdvList*>();
quint32 NsPdvList::SubchoicePresentationDataValues::s_metaTypeIdentifier = qRegisterMetaType<NsPdvList::SubchoicePresentationDataValues*>();

// presentation-asn1/fullyEncodedData.h
quint32 CFullyEncodedData::s_metaTypeIdentifier =  qRegisterMetaType<CFullyEncodedData*>();
quint32 CFullyEncodedData::s_metaTypeListId =  qRegisterMetaType<QLinkedList<CPdvList>*>();

// presentation-asn1/userData.h
quint32 CUserData::s_metaTypeIdentifier =  qRegisterMetaType<CUserData*>();

// presentation-asn1/CpaPpdu.h, 6 variables
quint32 CCpaPpdu::s_metaTypeIdentifier = qRegisterMetaType<CCpaPpdu*>();
quint32 NsCpaPpdu::CSubSecNormalModeParameters::s_metaTypeIdentifier = qRegisterMetaType<NsCpaPpdu::CSubSecNormalModeParameters*>();

// presentation-asn1/contextList.h
quint32 CContextList::s_metaTypeIdentifier = qRegisterMetaType<CContextList*>();

// presentation-asn1/defaultContextName.h, 2 variables
quint32 CDefaultContextName::s_metaTypeIdentifier = qRegisterMetaType<CDefaultContextName*>();

// presentation-asn1/CpType.h, 3 variables
quint32 CCpType::s_metaTypeIdentifier = qRegisterMetaType<CCpType*>();
// 8 variables
quint32 NsCpType::CSubSeqNormalModeParameters::s_metaTypeIdentifier = qRegisterMetaType<NsCpType::CSubSeqNormalModeParameters*>();

// presentation-asn1/modeSelector.h, 2 variables
quint32 CModeSelector::s_metaTypeIdentifier = qRegisterMetaType<CModeSelector*>();

// Initialization of AcseAssociation class
namespace {
	quint8 context_list_char[] = { 0x23, 0x30,
				0x0f, 0x02, 0x01, 0x01, 0x06, 0x04, 0x52, 0x01,
				0x00, 0x01, 0x30, 0x04, 0x06, 0x02, 0x51, 0x01,
				0x30, 0x10, 0x02, 0x01, 0x03, 0x06, 0x05, 0x28,
				0xca, 0x22, 0x02, 0x01, 0x30, 0x04, 0x06, 0x02,
				0x51, 0x01 };

	quint8 acsePresentationContextId_char[] = { 0x01, 0x01 };

	quint8 presentationResultList_char[] = { 0x12, 0x30, 0x07, 0x80, 0x01, 0x00, 0x81, 0x02, 0x51, 0x01,
			  0x30, 0x07, 0x80, 0x01, 0x00, 0x81, 0x02, 0x51, 0x01 };

	quint8 aareAccepted_char[] = { 0x01, 0x00 };

	quint8 associateSourceDiagnostic_char[] = { 0xa1, 0x03, 0x02, 0x01, 0x00 };

	quint8 application_context_name_char[] = { 0x05, 0x28, 0xca, 0x22, 0x02, 0x03 };

	quint8 directReference_char[] = { 0x02,	0x51, 0x01 };

	quint8 indirectReference_char[] = { 0x01, 0x03 };

	quint8 default_mechanism_name_char[] = { 0x03, 0x52, 0x03, 0x01 };

};

CContextList CAcseAssociation::context_list ( QByteArray ( (char*) context_list_char, sizeof(context_list_char)));

CBerInteger CAcseAssociation::acsePresentationContextId (
		QByteArray ((char*)acsePresentationContextId_char, sizeof(acsePresentationContextId_char) ) );

// warning: утечка памяти
CModeSelector CAcseAssociation::normalModeSelector = CModeSelector( new CBerInteger(1) );

CResultList CAcseAssociation::presentationResultList = CResultList(
		QByteArray ((char*)presentationResultList_char, sizeof(presentationResultList_char) ) );

CBerInteger CAcseAssociation::aareAccepted ( QByteArray ((char*) aareAccepted_char, sizeof(aareAccepted_char) ) );

CAssociateSourceDiagnostic CAcseAssociation::associateSourceDiagnostic (
		QByteArray ((char*)associateSourceDiagnostic_char, sizeof(associateSourceDiagnostic_char) ));

// is always equal to 1.0.9506.2.3 (MMS)
CBerObjectIdentifier CAcseAssociation::applicationContextName (
		QByteArray ((char*)application_context_name_char, sizeof(application_context_name_char)  ));

CBerObjectIdentifier CAcseAssociation::directReference (
		QByteArray ((char*) directReference_char, sizeof(directReference_char) ));

CBerInteger CAcseAssociation::indirectReference = CBerInteger(
		QByteArray ((char*) indirectReference_char, sizeof(indirectReference_char)));


CBerObjectIdentifier CAcseAssociation::defaultMechanismName = CBerObjectIdentifier(
		QByteArray ((char*) default_mechanism_name_char, sizeof(default_mechanism_name_char)));


