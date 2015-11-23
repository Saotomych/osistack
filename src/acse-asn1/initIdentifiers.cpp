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
