#-------------------------------------------------
#
# Project created by QtCreator 2015-09-23T17:47:31
#
#-------------------------------------------------

QT       += network

QT       -= gui

TEMPLATE = lib
CONFIG += staticlib

DESTDIR = bin
VERSION = 0.0.0.0
CONFIG += build_all
CONFIG += c++11

DEFINES += OSISTACK_LIBRARY

INCLUDEPATH += ../ositransport
INCLUDEPATH += $(JENKINS_HOME)/jobs/ositransport/workspace
INCLUDEPATH += ../ASN1/include
INCLUDEPATH += $(JENKINS_HOME)/jobs/ASN1/workspace/include
INCLUDEPATH += ../ASN1
INCLUDEPATH += $(JENKINS_HOME)/jobs/ASN1/workspace
INCLUDEPATH += ./include
INCLUDEPATH += $(JENKINS_HOME)/jobs/osistack/workspace/include
INCLUDEPATH += ./include/acse-asn1
INCLUDEPATH += $(JENKINS_HOME)/jobs/osistack/workspace/include/acse-asn1
INCLUDEPATH += ./include/presentation-asn1
INCLUDEPATH += $(JENKINS_HOME)/jobs/osistack/workspace/include/presentation-asn1

SOURCES += src/acse-asn1/InitIdentifiers.cpp \
		src/AcseAssociation.cpp \
		src/ServerAcseSap.cpp \
		src/ClientAcseSap.cpp \
		../ASN1/src/berByteArrayOutputStream.cpp \
		../ASN1/src/berByteArrayInputStream.cpp \
		../ASN1/src/InitIdentifiers.cpp \
		../ASN1/src/berIdentifier.cpp \
		../ASN1/src/berLength.cpp \
		../ASN1/src/berBase.cpp \
		../ASN1/src/types/berBitString.cpp \
		../ASN1/src/types/berBoolean.cpp \
		../ASN1/src/types/berInteger.cpp \
		../ASN1/src/types/berObjectIdentifier.cpp \
		../ASN1/src/types/berReal.cpp \
		../ASN1/src/types/berVisibleString.cpp \
		../ASN1/src/storages/berBitStringStorage.cpp \
		../ASN1/src/storages/berBooleanStorage.cpp \
		../ASN1/src/storages/berIntegerStorage.cpp \
		../ASN1/src/storages/berNullStorage.cpp \
		../ASN1/src/storages/berObjectIdentifierStorage.cpp \
		../ASN1/src/storages/berOctetStringStorage.cpp \
		../ASN1/src/storages/berRealStorage.cpp \
		../ositransport/clienttsap.cpp \
		../ositransport/connection.cpp \
		../ositransport/connectionlistener.cpp \
		../ositransport/servertsap.cpp \
		../ositransport/connectionserver.cpp \
		../ositransport/socketfactory.cpp \
		../ositransport/tcpeasysocket.cpp
    
HEADERS += \
		include/osistack_global.h \
		include/acse-asn1/APtitle.h \
		include/acse-asn1/AEtitle.h \
		include/acse-asn1/AEqualifier.h \		
		include/acse-asn1/externalLinkV1.h \
		include/acse-asn1/externalLinkV2.h \
		include/acse-asn1/associateSourceDiagnostic.h \
		include/acse-asn1/authenticationValue.h \
		include/acse-asn1/applicationContextNameList.h \
		include/acse-asn1/associationInformation.h \
		include/acse-asn1/RLreApdu.h \
		include/acse-asn1/RLrqApdu.h \
		include/acse-asn1/AAreApdu.h \
		include/acse-asn1/AArqApdu.h \
		include/acse-asn1/AcseApdu.h \
		include/presentation-asn1/ResultSubsequence.h \
		include/presentation-asn1/ResultList.h \
		include/presentation-asn1/PdvList.h \
		include/presentation-asn1/fullyEncodedData.h \
		include/presentation-asn1/userData.h \
		include/presentation-asn1/contextList.h \
		include/presentation-asn1/defaultContextName.h \
		include/presentation-asn1/CpType.h \
		include/presentation-asn1/modeSelector.h \
		include/presentation-asn1/CpaPpdu.h \
		include/AcseAssociation.h \
		include/ClientAcseSap.h \
		include/ServerAcseSap.h \
		../ASN1/include/DeclareCommonTypes.h \
		../ASN1/include/berByteArrayOutputStream.h \
		../ASN1/include/berByteArrayInputStream.h \
		../ASN1/include/berIdentifier.h \
		../ASN1/include/berLength.h \
		../ASN1/include/berBase.h \
		../ASN1/include/berAny.h \
		../ASN1/include/berAnyNoDecode.h \
		../ASN1/include/berBitString.h \
		../ASN1/include/berBoolean.h \
		../ASN1/include/berEnum.h \
		../ASN1/include/berInteger.h \
		../ASN1/include/berNull.h \
		../ASN1/include/berObjectIdentifier.h \
		../ASN1/include/berOctetString.h \
		../ASN1/include/berReal.h \
		../ASN1/include/berBMPString.h \
		../ASN1/include/berGeneralizedTime.h \
		../ASN1/include/berGeneralString.h \
		../ASN1/include/berGraphicString.h \
		../ASN1/include/berIA5String.h \
		../ASN1/include/berNumericString.h \
		../ASN1/include/berPrintableString.h \
		../ASN1/include/berTeletexString.h \
		../ASN1/include/berUniversalString.h \
		../ASN1/include/berUTF8String.h \
		../ASN1/include/berVideotexString.h \
		../ASN1/include/berVisibleString.h \
		../ASN1/include/compositeValue.h \
		../ASN1/include/storages/berBitStringStorage.h \
		../ASN1/include/storages/berBooleanStorage.h \
		../ASN1/include/storages/berIntegerStorage.h \
		../ASN1/include/storages/berNullStorage.h \
		../ASN1/include/storages/berObjectIdentifierStorage.h \
		../ASN1/include/storages/berOctetStringStorage.h \
		../ASN1/include/storages/berRealStorage.h \
		../ASN1/include/storages/berBaseType.h \
		../ASN1/include/storages/containerStorage.h \
		../ASN1/include/storages/decoder.h \
		../ositransport/clienttsap.h \
		../ositransport/connection.h \
		../ositransport/connectionlistener.h \
		../ositransport/servertsap.h \
		../ositransport/connectionserver.h \
		../ositransport/socketfactory.h \
		../ositransport/tcpeasysocket.h
    
unix {
    CONFIG (debug, debug|release) {
        TARGET = $$qtLibraryTarget(osistackd)
	    OBJECTS_DIR = build/debug
	    DEFINES += DEBUG
        LIBS += -lgcov

	    QMAKE_CXXFLAGS -= -O
		QMAKE_CXXFLAGS -= -O1
		QMAKE_CXXFLAGS -= -O2
		QMAKE_CXXFLAGS += -O0 -fprofile-arcs -ftest-coverage
    }else{
        TARGET = $$qtLibraryTarget(osistack)
	    OBJECTS_DIR = build/release
    }
    target.path = /usr/lib
    INSTALLS += target

   	QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
}else{
    TARGET = $$qtLibraryTarget(osistack-notunix)
}

CONFIG += debug_and_release build_all
INCLUDEPATH += src include
