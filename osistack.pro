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

INCLUDEPATH += ../ASN1/include
INCLUDEPATH += $(JENKINS_HOME)/jobs/ASN1/workspace/include

INCLUDEPATH += ./include
INCLUDEPATH += $(JENKINS_HOME)/jobs/osistack/workspace/include
INCLUDEPATH += ./include/acse-asn1
INCLUDEPATH += $(JENKINS_HOME)/jobs/osistack/workspace/include/acse-asn1

SOURCES += src/acse-asn1/InitIdentifiers.cpp

HEADERS += include/osistack.h \
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
		include/acse-asn1/AcseApdu.h 
		
unix {
    CONFIG (debug, debug|release) {
        TARGET = $$qtLibraryTarget(asn1d)
	    OBJECTS_DIR = build/debug
	    DEFINES += DEBUG
		LIBS += -lgcov

	    QMAKE_CXXFLAGS -= -O
		QMAKE_CXXFLAGS -= -O1
		QMAKE_CXXFLAGS -= -O2
		QMAKE_CXXFLAGS += -O0 -fprofile-arcs -ftest-coverage
    }else{
        TARGET = $$qtLibraryTarget(asn1)
	    OBJECTS_DIR = build/release
    }
    target.path = /usr/lib
    INSTALLS += target

   	QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
}else{
    TARGET = $$qtLibraryTarget(asn1-notunix)
}

CONFIG += debug_and_release build_all
INCLUDEPATH += src include
