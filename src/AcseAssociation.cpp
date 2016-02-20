/*
 * AcseAssocitation.cpp
 *
 *  Created on: 12 февр. 2016 г.
 *      Author: alex
 */

#include "AcseAssociation.h"
#include "presentation-asn1/CpaPpdu.h"

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


CAcseAssociation::CAcseAssociation(CConnection* tConnection, CBerOctetString* pSelLocalBerOctetString):
		m_connected(false),
		m_tConnection(tConnection),
		m_currentCallingSessionSelector(0),
		m_pSelLocalBerOctetString(pSelLocalBerOctetString)
	{	}

QByteArray CAcseAssociation::decodePConResponse(QByteArray& ppdu)
{
	CCpaPpdu cpaPpdu;
	CBerByteArrayInputStream iStream(ppdu);
	cpaPpdu.decode(iStream, true);

	CAcseApdu acseApdu;
	acseApdu.decode(iStream, (CBerIdentifier*)nullptr);

	return ppdu;
}

CUserData CAcseAssociation::getPresentationUserDataField( quint32 userDataLength )
{
	NsPdvList::SubchoicePresentationDataValues presDataValues(
			std::move(new CBerAnyNoDecode(userDataLength)),
			(CBerOctetString*) nullptr,
			(CBerBitString*) nullptr );

	CPdvList pdvList(
			(CBerObjectIdentifier*) nullptr,
			&acsePresentationContextId,
			&presDataValues);

	QList<CPdvList> listPdvList;
	listPdvList.push_back(pdvList);

	CFullyEncodedData fullyEncodedData(&listPdvList);

	CUserData userData( (CBerOctetString*) nullptr, &fullyEncodedData);

	return userData;
}

void CAcseAssociation::accept(CBerByteArrayOutputStream& payload)
{
	quint32 payloadLength = payload.size();

	CBerAnyNoDecode berAny(payloadLength);
	NsExternalLinkV1::SubChoiceEncoding subChEncoding( &berAny, (CBerOctetString*) nullptr, (CBerBitString*) nullptr );

	CExternalLinkV1 external(&directReference, &indirectReference, &subChEncoding);

	QList<CExternalLinkV1> listExternal;
	listExternal.push_back(external);

	CAssociationInformation userInformation(&listExternal);

	CAAreApdu aare(nullptr, &applicationContextName, &aareAccepted, &associateSourceDiagnostic, nullptr,
			nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &userInformation);
	CAcseApdu acse(nullptr, &aare, nullptr, nullptr);
	CBerByteArrayOutputStream berOStream(100, true);
	acse.encode(berOStream, true);
	quint32 acseHeaderLength = berOStream.size() - berOStream.index() + 1;

	CUserData userData = getPresentationUserDataField(acseHeaderLength + payloadLength);

	NsCpaPpdu::CSubSecNormalModeParameters normalModeParameters(nullptr, m_pSelLocalBerOctetString, &presentationResultList,
			(CBerBitString*) nullptr, (CBerBitString*) nullptr, &userData);

	CCpaPpdu cpaPpdu(&normalModeSelector, &normalModeParameters);

	cpaPpdu.encode(berOStream, true);

	QLinkedList<QByteArray> ssduList;
	QLinkedList<quint32> ssduOffsets;
	QLinkedList<quint32> ssduLengths;

	ssduList.push_back(berOStream.getByteArray());
	ssduOffsets.push_back(berOStream.index() + 1);
	ssduLengths.push_back(berOStream.size() - berOStream.index() + 1);

	ssduList.push_back(payload.getByteArray());
	ssduOffsets.push_back(payload.index() + 1);
	ssduLengths.push_back(payload.size() - payload.index() + 1);

	writeSessionAccept(ssduList, ssduOffsets, ssduLengths);
}

void CAcseAssociation::writeSessionAccept(QLinkedList<QByteArray>& ssdu, QLinkedList<quint32>& ssduOffsets, QLinkedList<quint32>& ssduLengths)
{
	QByteArray sduAcceptHeader(20, 0);
	quint32 idx = 0;

	quint32 ssduLength = 0;
	for (quint32 ssduElementLength : ssduLengths) {
		ssduLength += ssduElementLength;
	}

	// write ISO 8327-1 Header
	// SPDU Type: ACCEPT (14)
	sduAcceptHeader[idx++] = 0x0e;
	// Length: length of session user data + 22 ( header data after length
	// field )
	sduAcceptHeader[idx++] = (quint8) ((ssduLength + 18) & 0xff);

	// -- start Connect Accept Item
	// Parameter type: Connect Accept Item (5)
	sduAcceptHeader[idx++] = 0x05;
	// Parameter length
	sduAcceptHeader[idx++] = 0x06;

	// Protocol options:
	// Parameter Type: Protocol Options (19)
	sduAcceptHeader[idx++] = 0x13;
	// Parameter length
	sduAcceptHeader[idx++] = 0x01;
	// flags: (.... ...0 = Able to receive extended concatenated SPDU:
	// False)
	sduAcceptHeader[idx++] = 0x00;

	// Version number:
	// Parameter type: Version Number (22)
	sduAcceptHeader[idx++] = 0x16;
	// Parameter length
	sduAcceptHeader[idx++] = 0x01;
	// flags: (.... ..1. = Protocol Version 2: True)
	sduAcceptHeader[idx++] = 0x02;
	// -- end Connect Accept Item

	// Session Requirement
	// Parameter type: Session Requirement (20)
	sduAcceptHeader[idx++] = 0x14;
	// Parameter length
	sduAcceptHeader[idx++] = 0x02;
	// flags: (.... .... .... ..1. = Duplex functional unit: True)
	sduAcceptHeader[idx++] = 0x00;
	sduAcceptHeader[idx++] = 0x02;

	// Called Session Selector
	// Parameter type: Called Session Selector (52)
	sduAcceptHeader[idx++] = 0x34;
	// Parameter length
	sduAcceptHeader[idx++] = 0x02;
	// Called Session Selector
	sduAcceptHeader[idx++] = 0x00;
	sduAcceptHeader[idx++] = 0x01;

	// Session user data
	// Parameter type: Session user data (193)
	sduAcceptHeader[idx++] = (quint8) 0xc1;

	// Parameter length
	sduAcceptHeader[idx++] = (quint8) ssduLength;

	ssdu.push_front(sduAcceptHeader);
	ssduOffsets.push_front(0);
	ssduLengths.push_front(sduAcceptHeader.size());

	m_tConnection->send(ssdu, ssduOffsets, ssduLengths);

}

QByteArray CAcseAssociation::getAssociateResponseAPdu()
{
	QByteArray returnBuffer = m_associateResponseAPDU;
	m_associateResponseAPDU.clear();
	return returnBuffer;
}

void CAcseAssociation::startAssociation(
		QByteArray payload,
		QHostAddress address,
		quint16 port,
		QHostAddress localAddr,
		quint16 localPort,
		QString authenticationParameter,
		QByteArray sSelRemote,
		QByteArray sSelLocal,
		QByteArray pSelRemote,
		CClientTSAP tSAP,
		QVector<quint32> apTitleCalled,
		QVector<quint32> apTitleCalling,
		quint32 aeQualifierCalled,
		quint32 aeQualifierCalling)
{

}

QByteArray CAcseAssociation::startSConnection(
		QList<QByteArray> ssduList,
		QList<quint32> ssduOffsets,
		QList<quint32> ssduLengths,
		QHostAddress address,
		quint32 port,
		QHostAddress localAddr,
		quint32 localPort,
		CClientTSAP tSAP,
		QByteArray sSelRemote,
		QByteArray sSelLocal)
{

}

void CAcseAssociation::send(QByteArray payload)
{

}

void CAcseAssociation::receive(QByteArray pduBuffer)
{

}

void CAcseAssociation::disconnect()
{
	m_connected = false;
	if (m_tConnection != nullptr)
	{
		m_tConnection->disconnect();
	}
}

void CAcseAssociation::close()
{
	m_connected = false;
	if (m_tConnection != nullptr)
	{
		m_tConnection->close();
	}
}

void CAcseAssociation::listenForCn(QByteArray pduBuffer)
{

}

quint32 CAcseAssociation::getMessageTimeout()
{
	return m_tConnection->getMessageTimeout();
}

void CAcseAssociation::setMessageTimeout(quint32 tout)
{
	m_tConnection->setMessageTimeout(tout);
}

void CAcseAssociation::sendSessionLayer(
		QList<QByteArray> ssduList,
		QList<quint32> ssduOffsets,
		QList<quint32> ssduLengths)
{

}

quint64 CAcseAssociation::extractInteger(QByteArray buffer, quint32 size)
{

	switch (size)
	{
	case 1: return (quint64) buffer[0];
	case 2: return (quint64) ((quint64)buffer[0] + (quint64)(buffer[1] << 8));
	case 4: return (quint64) ( (quint64)buffer[0] + ((quint64)buffer[1] << 8) +
					((quint64)buffer[2] << 16) + ((quint64)buffer[3] << 24) );
	case 8: return (quint64) ( (quint64)buffer[0] + ((quint64)buffer[1] << 8) +
					((quint64)buffer[2] << 16) + ((quint64)buffer[3] << 24) +
					((quint64)buffer[4] << 32) + ((quint64)buffer[5] << 40) +
					((quint64)buffer[6] << 48) + ((quint64)buffer[7] << 56) );
	}

	return (quint64) 0;
}

QString CAcseAssociation::getSPDUTypeString(qint8 spduType)
{
	switch (spduType) {
	case 0:
		return "EXCEPTION REPORT (ER)";
	case 1:
		return "DATA TRANSFER (DT)";
	case 2:
		return "PLEASE TOKENS (PT)";
	case 5:
		return "EXPEDITED (EX)";
	case 7:
		return "PREPARE (PR)";
	case 8:
		return "NOT FINISHED (NF)";
	case 9:
		return "FINISH (FN)";
	case 10:
		return "DISCONNECT (DN)";
	case 12:
		return "REFUSE (RF)";
	case 13:
		return "CONNECT (CN)";
	case 14:
		return "ACCEPT (AC)";
	case 15:
		return "CONNECT DATA OVERFLOW (CDO)";
	case 16:
		return "OVERFLOW ACCEPT (OA)";
	case 21:
		return "GIVE TOKENS CONFIRM (GTC)";
	case 22:
		return "GIVE TOKENS ACK (GTA)";
	case 25:
		return "ABORT (AB)";
	case 26:
		return "ABORT ACCEPT (AA)";
	case 29:
		return "ACTIVITY RESUME (AR)";
	case 33:
		return "TYPED DATA (TD)";
	case 34:
		return "RESYNCHRONIZE ACK (RA)";
	case 41:
		return "MAJOR SYNC POINT (MAP)";
	case 42:
		return "MAJOR SYNC ACK (MAA)";
	case 45:
		return "ACTIVITY START (AS)";
	case 48:
		return "EXCEPTION DATA (ED)";
	case 49:
		return "MINOR SYNC POINT (MIP)";
	case 50:
		return "MINOR SYNC ACK (MIA)";
	case 53:
		return "RESYNCHRONIZE (RS)";
	case 57:
		return "ACTIVITY DISCARD (AD)";
	case 58:
		return "ACTIVITY DISCARD ACK (ADA)";
	case 61:
		return "CAPABILITY DATA (CD)";
	case 62:
		return "CAPABILITY DATA ACK (CDA)";
	case 64:
		return "UNIT DATA (UD)";
	default:
		return "<unknown SPDU type>";
	}
}

