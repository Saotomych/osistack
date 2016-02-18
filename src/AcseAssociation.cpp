/*
 * AcseAssocitation.cpp
 *
 *  Created on: 12 февр. 2016 г.
 *      Author: alex
 */

#include "AcseAssociation.h"

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
CBerObjectIdentifier CAcseAssociation::application_context_name (
		QByteArray ((char*)application_context_name_char, sizeof(application_context_name_char)  ));

CBerObjectIdentifier CAcseAssociation::directReference (
		QByteArray ((char*) directReference_char, sizeof(directReference_char) ));

CBerInteger CAcseAssociation::indirectReference = CBerInteger(
		QByteArray ((char*) indirectReference_char, sizeof(indirectReference_char)));


CBerObjectIdentifier CAcseAssociation::default_mechanism_name = CBerObjectIdentifier(
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

}

void CAcseAssociation::accept(QByteArray payload)
{

}

void CAcseAssociation::writeSessionAccept(QList<QByteArray> ssdu, QList<quint32> ssduOffsets, QList<quint32> ssduLengths)
{

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

