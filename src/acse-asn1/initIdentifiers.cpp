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

CBerIdentifier CAAreApdu::s_Identifier(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::CONSTRUCTED, 1);
quint32 CAAreApdu::s_metaTypeIdentifier = qRegisterMetaType<CAAreApdu*>();

CBerIdentifier CAArqApdu::s_Identifier(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::CONSTRUCTED, 0);
quint32 CAArqApdu::s_metaTypeIdentifier = qRegisterMetaType<CAArqApdu*>();

CBerIdentifier CRLreApdu::s_Identifier(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::CONSTRUCTED, 3);
quint32 CRLreApdu::s_metaTypeIdentifier = qRegisterMetaType<CRLreApdu*>();

CBerIdentifier CRLrqApdu::s_Identifier(CBerIdentifier::APPLICATION_CLASS, CBerIdentifier::CONSTRUCTED, 2);
quint32 CRLrqApdu::s_metaTypeIdentifier = qRegisterMetaType<CRLrqApdu*>();

quint32 CAcseApdu::s_metaTypeIdentifier = qRegisterMetaType<CAcseApdu*>();

quint32 CAeQualifier::s_metaTypeIdentifier = qRegisterMetaType<CAeQualifier*>();

CBerIdentifier CApplicationContextNameList::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CApplicationContextNameList::s_metaTypeIdentifier = qRegisterMetaType<CApplicationContextNameList*>();
quint32 CApplicationContextNameList::s_metaTypeListId = qRegisterMetaType<QList<CBerObjectIdentifier>*>();

quint32 CApTitle::s_metaTypeIdentifier = qRegisterMetaType<CApTitle*>();

quint32 CAeTitle::s_metaTypeIdentifier = qRegisterMetaType<CAeTitle*>();

quint32 CAssociateSourceDiagnostic::s_metaTypeIdentifier = qRegisterMetaType<CAssociateSourceDiagnostic*>();

CBerIdentifier CAssociationInformation::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CAssociationInformation::s_metaTypeIdentifier = qRegisterMetaType<CAssociationInformation*>();
quint32 CAssociationInformation::s_metaTypeListId = qRegisterMetaType<QList<CExternalLinkV1>*>();

quint32 CExternalLinkV1::s_metaTypeIdentifier = qRegisterMetaType<CExternalLinkV1*>();

quint32 CExternalLinkV2::s_metaTypeIdentifier = qRegisterMetaType<CExternalLinkV2*>();

CBerIdentifier CResultSubsequence::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CResultSubsequence::s_metaTypeIdentifier = qRegisterMetaType<CResultSubsequence*>();

CBerIdentifier CResultList::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CResultList::s_metaTypeIdentifier =  qRegisterMetaType<CResultList*>();
quint32 CResultList::s_metaTypeListId =  qRegisterMetaType<QList<CResultSubsequence>*>();

CBerIdentifier CPdvList::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CPdvList::s_metaTypeIdentifier =  qRegisterMetaType<CPdvList*>();

CBerIdentifier CFullyEncodedData::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CFullyEncodedData::s_metaTypeIdentifier =  qRegisterMetaType<CFullyEncodedData*>();
quint32 CFullyEncodedData::s_metaTypeListId =  qRegisterMetaType<QList<CPdvList>*>();

quint32 CUserData::s_metaTypeIdentifier =  qRegisterMetaType<CUserData*>();

CBerIdentifier CCpaPpdu::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CCpaPpdu::s_metaTypeIdentifier = qRegisterMetaType<CCpaPpdu*>();

CBerIdentifier CContextList::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CContextList::s_metaTypeIdentifier = qRegisterMetaType<CContextList*>();

CBerIdentifier CDefaultContextName::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CDefaultContextName::s_metaTypeIdentifier = qRegisterMetaType<CDefaultContextName*>();

CBerIdentifier CCpType::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 16);
quint32 CCpType::s_metaTypeIdentifier = qRegisterMetaType<CCpType*>();

CBerIdentifier CModeSelector::s_Identifier(CBerIdentifier::UNIVERSAL_CLASS, CBerIdentifier::CONSTRUCTED, 17);
quint32 CModeSelector::s_metaTypeIdentifier = qRegisterMetaType<CModeSelector*>();
