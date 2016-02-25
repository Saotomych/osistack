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

// asce-asn1/AAreApdu.h
CBerIdentifier CAAreApdu::s_Identifier(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::CONSTRUCTED, 1);
quint32 CAAreApdu::s_metaTypeIdentifier = qRegisterMetaType<CAAreApdu*>();

// asce-asn1/AArqApdu.h
CBerIdentifier CAArqApdu::s_Identifier(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::CONSTRUCTED, 0);
quint32 CAArqApdu::s_metaTypeIdentifier = qRegisterMetaType<CAArqApdu*>();

// asce-asn1/RLreApdu.h
CBerIdentifier CRLreApdu::s_Identifier(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::CONSTRUCTED, 3);
quint32 CRLreApdu::s_metaTypeIdentifier = qRegisterMetaType<CRLreApdu*>();

// asce-asn1/RLrqApdu.h
CBerIdentifier CRLrqApdu::s_Identifier(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::CONSTRUCTED, 2);
quint32 CRLrqApdu::s_metaTypeIdentifier = qRegisterMetaType<CRLrqApdu*>();

// asce-asn1/AcseApdu.h
quint32 CAcseApdu::s_metaTypeIdentifier = qRegisterMetaType<CAcseApdu*>();

// asce-asn1/AEqualifier.h
quint32 CAeQualifier::s_metaTypeIdentifier = qRegisterMetaType<CAeQualifier*>();

// asce-asn1/applicationContextNameList.h
CBerIdentifier CApplicationContextNameList::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CApplicationContextNameList::s_metaTypeIdentifier = qRegisterMetaType<CApplicationContextNameList*>();
quint32 CApplicationContextNameList::s_metaTypeListId = qRegisterMetaType<QLinkedList<CBerObjectIdentifier>*>();

// asce-asn1/APtitle.h
quint32 CApTitle::s_metaTypeIdentifier = qRegisterMetaType<CApTitle*>();

// asce-asn1/AEtitle.h
quint32 CAeTitle::s_metaTypeIdentifier = qRegisterMetaType<CAeTitle*>();

// asce-asn1/associateSourcediagnoctic.h
quint32 CAssociateSourceDiagnostic::s_metaTypeIdentifier = qRegisterMetaType<CAssociateSourceDiagnostic*>();

// asce-asn1/associationInformation.h
CBerIdentifier CAssociationInformation::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CAssociationInformation::s_metaTypeIdentifier = qRegisterMetaType<CAssociationInformation*>();
quint32 CAssociationInformation::s_metaTypeListId = qRegisterMetaType<QLinkedList<CExternalLinkV1>*>();

// asce-asn1/externalLinkV1.h
quint32 CExternalLinkV1::s_metaTypeIdentifier = qRegisterMetaType<CExternalLinkV1*>();
quint32 NsExternalLinkV1::SubChoiceEncoding::s_metaTypeIdentifier = qRegisterMetaType<NsExternalLinkV1::SubChoiceEncoding*>();

// asce-asn1/externalLinkV2.h
quint32 CExternalLinkV2::s_metaTypeIdentifier = qRegisterMetaType<CExternalLinkV2*>();

// presentation-asn1/ResultSubsequence.h
CBerIdentifier CResultSubsequence::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CResultSubsequence::s_metaTypeIdentifier = qRegisterMetaType<CResultSubsequence*>();

// presentation-asn1/ResultList.h
CBerIdentifier CResultList::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CResultList::s_metaTypeIdentifier =  qRegisterMetaType<CResultList*>();
quint32 CResultList::s_metaTypeListId =  qRegisterMetaType<QLinkedList<CResultSubsequence>*>();

// presentation-asn1/PdvList.h
CBerIdentifier CPdvList::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 17);
quint32 CPdvList::s_metaTypeIdentifier =  qRegisterMetaType<CPdvList*>();
quint32 NsPdvList::SubchoicePresentationDataValues::s_metaTypeIdentifier = qRegisterMetaType<NsPdvList::SubchoicePresentationDataValues*>();

// presentation-asn1/fullyEncodedData.h
CBerIdentifier CFullyEncodedData::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CFullyEncodedData::s_metaTypeIdentifier =  qRegisterMetaType<CFullyEncodedData*>();
quint32 CFullyEncodedData::s_metaTypeListId =  qRegisterMetaType<QLinkedList<CPdvList>*>();

// presentation-asn1/userData.h
quint32 CUserData::s_metaTypeIdentifier =  qRegisterMetaType<CUserData*>();

// presentation-asn1/CpaPpdu.h, 6 variables
CBerIdentifier CCpaPpdu::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CCpaPpdu::s_metaTypeIdentifier = qRegisterMetaType<CCpaPpdu*>();
CBerIdentifier NsCpaPpdu::CSubSecNormalModeParameters::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 NsCpaPpdu::CSubSecNormalModeParameters::s_metaTypeIdentifier = qRegisterMetaType<NsCpaPpdu::CSubSecNormalModeParameters*>();

// presentation-asn1/contextList.h
CBerIdentifier CContextList::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CContextList::s_metaTypeIdentifier = qRegisterMetaType<CContextList*>();

// presentation-asn1/defaultContextName.h, 2 variables
CBerIdentifier CDefaultContextName::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CDefaultContextName::s_metaTypeIdentifier = qRegisterMetaType<CDefaultContextName*>();

// presentation-asn1/CpType.h, 3 variables
CBerIdentifier CCpType::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CCpType::s_metaTypeIdentifier = qRegisterMetaType<CCpType*>();
// 8 variables
CBerIdentifier NsCpType::CSubSeqNormalModeParameters::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 NsCpType::CSubSeqNormalModeParameters::s_metaTypeIdentifier = qRegisterMetaType<NsCpType::CSubSeqNormalModeParameters*>();

// presentation-asn1/modeSelector.h, 2 variables
CBerIdentifier CModeSelector::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 17);
quint32 CModeSelector::s_metaTypeIdentifier = qRegisterMetaType<CModeSelector*>();
