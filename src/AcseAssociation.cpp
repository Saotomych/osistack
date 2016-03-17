/*
 * AcseAssocitation.cpp
 *
 *  Created on: 12 февр. 2016 г.
 *      Author: alex
 */

#include "AcseAssociation.h"

namespace
{

	quint8 sender_acse_requirements_char[] = { 0x02, 0x07, 0x80 };

}

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

	QLinkedList<CPdvList> listPdvList;
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

	QLinkedList<CExternalLinkV1> listExternal;
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
		CBerByteArrayOutputStream& payload,
		QString& authenticationParameter,
		QByteArray& sSelRemote,
		QByteArray& sSelLocal,
		QByteArray& pSelRemote,
		QVector<qint32>& apTitleCalled,
		QVector<qint32>& apTitleCalling,
		quint32 aeQualifierCalled,
		quint32 aeQualifierCalling)
{
	if ( m_connected )
	{
		qDebug() << "CAcseAssociation::startAssociation connected already";
		return;
	}

	quint32 payloadLength = payload.size() - payload.index();

	CBerObjectIdentifier calledId(apTitleCalled);
	CApTitle calledApTitle( &calledId );
	CBerObjectIdentifier callingId(apTitleCalling);
	CApTitle callingApTitle( &callingId );

	CBerAnyNoDecode noDecode( payloadLength );
	NsExternalLinkV1::SubChoiceEncoding encoding( &noDecode, nullptr, nullptr );

	CExternalLinkV1 externalLink( &directReference, &indirectReference, &encoding);

	QLinkedList<CExternalLinkV1> externalList;
	externalList.push_back(externalLink);

	CAssociationInformation userInformation( &externalList );

	CBerBitString senderAcseRequirements;
	CBerObjectIdentifier mechanismName;
	CAuthenticationValue authenticationValue;

	if (authenticationParameter.size() != 0)
	{
		{
			QByteArray code( (const char*) sender_acse_requirements_char, (int) (sizeof(sender_acse_requirements_char)/sizeof(sender_acse_requirements_char[0])) );
			CBerBitString tmp(code);
			senderAcseRequirements = tmp;
		}

		mechanismName = defaultMechanismName;

		{
			QByteArray auth(authenticationParameter.toUtf8());
			CBerGraphicString auString( auth );
			CAuthenticationValue tmp( &auString, nullptr, nullptr);
			authenticationValue = tmp;
		}
	}

	CBerInteger aeIntCalled(aeQualifierCalled);
	CAeQualifier aeQaCalled(&aeIntCalled);
	CBerInteger aeIntCalling(aeQualifierCalling);
	CAeQualifier aeQaCalling(&aeIntCalling);
	CAArqApdu aarq(
			(CBerBitString*)nullptr,
			&applicationContextName,
			&calledApTitle, &aeQaCalled, (CBerInteger*) nullptr, (CBerInteger*) nullptr,
			&callingApTitle, &aeQaCalling, (CBerInteger*) nullptr, (CBerInteger*) nullptr,
			&senderAcseRequirements, &mechanismName,
			&authenticationValue, (CApplicationContextNameList*) nullptr,
			(CBerGraphicString*) nullptr, &userInformation);

	CAcseApdu acse( &aarq, nullptr, nullptr, nullptr );

	// Serialize
	CBerByteArrayOutputStream berOStream(200, true);
	acse.encode(berOStream, true);

	QLinkedList<QByteArray> ssduList;
	QLinkedList<quint32> ssduOffsets;
	QLinkedList<quint32> ssduLengths;

	ssduList.push_back(berOStream.getByteArray());
	ssduOffsets.push_back(berOStream.index() + 1);
	ssduLengths.push_back(payloadLength);

	QByteArray res = startSConnection( ssduList, ssduOffsets, ssduLengths, sSelRemote, sSelLocal);

	m_associateResponseAPDU = decodePConResponse(res);

	emit signalAcseAssociationReady(this);

}

quint32 CAcseAssociation::receiveDataParser(QByteArray& pduBuffer, quint32 offset)
{
	qint32 i = (qint32) offset;
	for (; i < pduBuffer.size(); i++)
	{
		// read parameter type
		quint32 parameterType = pduBuffer[i++] & 0xff;
		// read parameter length
		quint32 parameterLength = pduBuffer[i++] & 0xff;

		switch (parameterType) {
		// Connect Accept Item (5)
		case 0x05:
			{
				quint32 bytesToRead = parameterLength;
				//	m_tConnection = tSAP.createConnection(address, port, localAddr, localPort);


				while (bytesToRead > 0)
				{
					// read parameter type
					int ca_parameterType = pduBuffer[i++];
					bytesToRead -= 2;

					switch (ca_parameterType & 0xff)
					{

					// Protocol Options (19)
					case 0x13:
						// flags: .... ...0 = Able to receive extended
						// concatenated SPDU: False
						{
							quint8 protocolOptions = pduBuffer[i++];
							if (protocolOptions != 0x00)
							{
								qDebug() << "CAcseAssociation::startAssociation didn't receive connect answer. SPDU Connect Accept Item/Protocol Options is "
										<< protocolOptions << ", expected 0";

								pduBuffer.clear();
								return 0;
							}

							bytesToRead--;
							break;
						}
					// Version Number
					case 0x16:
						// flags .... ..1. = Protocol Version 2: True
						{
							quint8 versionNumber = pduBuffer[i++];
							if (versionNumber != 0x02)
							{
								qDebug() << "CAcseAssociation::startAssociation didn't receive connect answer. SPDU Connect Accept Item/Version Number is "
										<< versionNumber << ", expected 2";

								pduBuffer.clear();
								return 0;
							}

							bytesToRead--;
							break;
						}

					default:
						{
							qDebug() << "CAcseAssociation::startAssociation didn't receive connect answer. SPDU Connect Accept Item: parameter not implemented: "
								<< ca_parameterType;

							pduBuffer.clear();
							return 0;

						}

					}
				}

				i--;

			}
			break;

		// Session Requirement (20)
		case 0x14:
			// flags: (.... .... .... ..1. = Duplex functional unit: True)
			{
				QByteArray val(&pduBuffer.data()[i], parameterLength);
				quint64 sessionRequirement = extractInteger(val, parameterLength);

				if (sessionRequirement != 0x02) {
					qDebug() << "CAcseAssociation::startAssociation didn't receive connect answer. SPDU header parameter 'Session Requirement (20)' is "
							<< sessionRequirement << ", expected 2";

					pduBuffer.clear();
					return 0;
				}
			}
			break;

		// Calling Session Selector (51)
		case 0x33:
			{
				QByteArray val(&pduBuffer.data()[i], parameterLength);
				quint64 css = extractInteger(val, parameterLength);

				if (css != 0x01) {
					qDebug() << "CAcseAssociation::startAssociation didn't receive connect answer. SPDU header parameter 'Calling Session Selector (51)' is "
							<< css << ", expected 1";

					pduBuffer.clear();
					return 0;
				}
			}
			break;

		// Called Session Selector (52)
		case 0x34:
			{
				QByteArray val(&pduBuffer.data()[i], parameterLength);
				quint64 calledSessionSelector = extractInteger(val, parameterLength);

				if (calledSessionSelector != 0x01) {
					qDebug() << "CAcseAssociation::startAssociation didn't receive connect answer. SPDU header parameter 'Called Session Selector (52)' is "
							<< calledSessionSelector << ", expected 1";

					pduBuffer.clear();
					return 0;
				}
			}
			break;

		// Session user data (193)
		case 0xc1:

			break;

		default:
			{
				qDebug() << "CAcseAssociation::startAssociation didn't receive connect answer. SPDU header parameter type "
				<< parameterType << " not implemented.";

				pduBuffer.clear();
				return 0;
			}
		}
	}

	return i;
}

QByteArray CAcseAssociation::startSConnection(
		QLinkedList<QByteArray>& ssduList,
		QLinkedList<quint32>& ssduOffsets,
		QLinkedList<quint32>& ssduLengths,
		QByteArray& sSelRemote,
		QByteArray& sSelLocal)
{

	if ( m_connected )
	{
		qDebug() << "CAcseAssociation::startAssociation connected already";
		QByteArray ret;
		return ret;
	}

	QByteArray spduHeader(24, 0);

	quint32 ssduLength=0;
	for (auto v: ssduLengths)
		ssduLength += v;

	// write ISO 8327-1 Header
	// SPDU Type: CONNECT (13)
	spduHeader[0] = 0x0d;
	// Length: length of session user data + 22 ( header data after
	// length field )
	spduHeader[1] = (quint8) ((ssduLength + 22) & 0xff);

	// -- start Connect Accept Item
	// Parameter type: Connect Accept Item (5)
	spduHeader[2] = 0x05;
	// Parameter length
	spduHeader[3] = 0x06;

	// Protocol options:
	// Parameter Type: Protocol Options (19)
	spduHeader[4] = 0x13;
	// Parameter length
	spduHeader[5] = 0x01;
	// flags: (.... ...0 = Able to receive extended concatenated SPDU:
	// False)
	spduHeader[6] = 0x00;

	// Version number:
	// Parameter type: Version Number (22)
	spduHeader[7] = 0x16;
	// Parameter length
	spduHeader[8] = 0x01;
	// flags: (.... ..1. = Protocol Version 2: True)
	spduHeader[9] = 0x02;
	// -- end Connect Accept Item

	// Session Requirement
	// Parameter type: Session Requirement (20)
	spduHeader[10] = 0x14;
	// Parameter length
	spduHeader[11] = 0x02;
	// flags: (.... .... .... ..1. = Duplex functional unit: True)
	spduHeader[12] = 0x00;
	spduHeader[13] = 0x02;

	// Calling Session Selector
	// Parameter type: Calling Session Selector (51)
	spduHeader[14] = 0x33;
	// Parameter length
	spduHeader[15] = 0x02;
	// Calling Session Selector
	spduHeader[16] = sSelRemote[0];
	spduHeader[17] = sSelRemote[1];

	// Called Session Selector
	// Parameter type: Called Session Selector (52)
	spduHeader[18] = 0x34;
	// Parameter length
	spduHeader[19] = 0x02;
	// Called Session Selector
	spduHeader[20] = sSelLocal[0];
	spduHeader[21] = sSelLocal[1];

	// Session user data
	// Parameter type: Session user data (193)
	spduHeader[22] = (quint8) 0xc1;
	// Parameter length
	spduHeader[23] = (quint8) (ssduLength & 0xff);
	// write session user data

	ssduList.push_front(spduHeader);
	ssduOffsets.push_front(0);
	ssduLengths.push_front(spduHeader.size());

	m_tConnection->send(ssduList, ssduOffsets, ssduLengths);

	// TODO asynchronous receive must be in the future
	QByteArray pduBuffer;
	if (m_tConnection->receive(pduBuffer) == false)
	{
		qDebug() << "CAcseAssociation::startAssociation didn't receive connect answer. ResponseTimeout waiting for connection response.";
		QByteArray ret;
		return ret;
	}

	// read ISO 8327-1 Header
	// SPDU Type: ACCEPT (14)
	if ( (quint8)pduBuffer[0] != (quint8) 0x0e)
	{
		qDebug() << "CAcseAssociation::startAssociation didn't receive connect answer. ISO 8327-1 header wrong SPDU type, expected ACCEPT (14), got "
				<< getSPDUTypeString(pduBuffer[0]) << " (" << pduBuffer[0] << ")";

		QByteArray ret;
		return ret;
	}

	quint32 i = receiveDataParser(pduBuffer, 2);

	m_connected = true;

	return &pduBuffer.data()[i];
}

void CAcseAssociation::send(CBerByteArrayOutputStream& payload)
{
	CBerAnyNoDecode noDecode(payload.size() - payload.index());
	NsPdvList::SubchoicePresentationDataValues spdv( &noDecode,
			(CBerOctetString*) nullptr, (CBerBitString*) nullptr);
	CBerInteger int31(31);
	CPdvList pdvList( (CBerObjectIdentifier*) nullptr, &int31, &spdv);

	QLinkedList<CPdvList> listPdvList;
	listPdvList.push_back(pdvList);

	CFullyEncodedData fullyEncodedData(&listPdvList);
	CUserData userData( nullptr, &fullyEncodedData );

	CBerByteArrayOutputStream berOStream(200,true);
	userData.encode(berOStream, true);

	QLinkedList<QByteArray> ssduList;
	QLinkedList<quint32> ssduOffsets;
	QLinkedList<quint32> ssduLengths;

	ssduList.push_back(berOStream.getByteArray());
	ssduOffsets.push_back(berOStream.index() + 1);
	ssduLengths.push_back(berOStream.getByteArray().size() - berOStream.index() + 1);

	ssduList.push_back(payload.getByteArray());
	ssduOffsets.push_back(payload.index());
	ssduLengths.push_back(payload.size() - payload.index());

	sendSessionLayer(ssduList, ssduOffsets, ssduLengths);

}

void CAcseAssociation::receive(QByteArray& pduBuffer)
{
	if ( m_connected )
	{
		qDebug() << "CAcseAssociation::receive not connected.";
		return;
	}

	QByteArray localBuffer;
	m_tConnection->receive(localBuffer);

	quint8 firstByte = localBuffer[0];

	if (firstByte == 25) {
		// got an ABORT SPDU
		qDebug() <<  "CAcseAssociation::receive: Received an ABORT SPDU";
		return;
	}

	// -- read ISO 8327-1 header
	// SPDU type: Give tokens PDU (1)
	if (firstByte != 0x01) {
		qDebug() <<  "CAcseAssociation::receive: SPDU header syntax error: first SPDU type not 1";
		return;
	}
	// length
	if ( (quint8) localBuffer[1] != (quint8) 0) {
		qDebug() <<  "CAcseAssociation::receive: SPDU header syntax error: first SPDU type length not 0";
		return;
	}
	// SPDU Type: DATA TRANSFER (DT) SPDU (1)
	if ( (quint8) localBuffer[2] != (quint8) 0x01) {
		qDebug() <<  "CAcseAssociation::receive: SPDU header syntax error: second SPDU type not 1";
		return;
	}
	// length
	if ( (quint8) localBuffer[3] != (quint8) 0) {
		qDebug() <<  "CAcseAssociation::receive: SPDU header syntax error: second SPDU type length not 0";
		return;
	}

	// decode PPDU header
	CUserData user_data;

	CBerByteArrayInputStream iStream( localBuffer, 4);
	if (user_data.decode( iStream, false) == 0)
	{
		qDebug() <<  "CAcseAssociation::receive: error decoding PPDU header";
		return;
	}

	qint32 startingIndex = localBuffer.size() - iStream.available();

	iStream.read( pduBuffer, startingIndex, iStream.available());

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

void CAcseAssociation::listenForCn(QByteArray& pduBuffer)
{
	if (m_connected)
	{
		qDebug() << "CAcseAssociation::listenForCn: connected already.";
		return;
	}

	QByteArray localPduBuffer;
	m_tConnection->receive(localPduBuffer);

	quint8 spduType = localPduBuffer[0];
	if (spduType != 0x0d)
	{
		qDebug() << "CAcseAssociation::listenForCn: ISO 8327-1 header wrong SPDU type, expected CONNECT (13), got "
				<< getSPDUTypeString(spduType) << " (" << spduType << ")";
		return;
	}

	quint32 i = receiveDataParser(pduBuffer, 2);

	CCpType cpType;
	CBerByteArrayInputStream iStream( localPduBuffer, i );
	cpType.decode(iStream, true);

	CAcseApdu acseApdu;
	acseApdu.decode(iStream, (CBerIdentifier*) nullptr);

	emit signalAcseCnReady(this);

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
		QLinkedList<QByteArray>& ssduList,
		QLinkedList<quint32>& ssduOffsets,
		QLinkedList<quint32>& ssduLengths)
{
	QByteArray spduHeader(4, 0);

	// --write iso 8327-1 Header--
	// write SPDU Type: give tokens PDU
	spduHeader[0] = 0x01;
	// length 0
	spduHeader[1] = 0;
	// write SPDU Type: DATA TRANSFER (DT)
	spduHeader[2] = 0x01;
	// length 0
	spduHeader[3] = 0;

	ssduList.push_front(spduHeader);
	ssduOffsets.push_front(0);
	ssduLengths.push_front(spduHeader.size());
	m_tConnection->send(ssduList, ssduOffsets, ssduLengths);

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

/*** Slot Section ***/
void CAcseAssociation::slotAcseConnectionClosed(const CConnection* pconn)
{
	qDebug() << "CAcseAssociation::slotServerConnectionClosed";

	Q_CHECK_PTR(pconn);

	emit signalAcseAssociationClosed(this);

}

void CAcseAssociation::slotAcseTSduReady(const CConnection* pconn)
{
	qDebug() << "CAcseAssociation::slotAcseTSduReady";

	Q_CHECK_PTR(pconn);

	emit signalAcseTSduReady(this);
}

