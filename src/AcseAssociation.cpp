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

CAcseAssociation::CAcseAssociation(CConnection* tConnection, CBerOctetString& SelLocalBerOctetString):
		m_connected(false),
		m_tConnection(tConnection),
		m_currentCallingSessionSelector(0),
		PSelLocal(SelLocalBerOctetString)
	{	}

QDataStream& CAcseAssociation::decodePConResponse(QDataStream& ppdu)
{
	CCpaPpdu cpaPpdu;
	CBerByteArrayInputStream iStream(ppdu);
	cpaPpdu.decode(iStream, true);

	CAcseApdu acseApdu;
	acseApdu.decode(iStream, (CBerIdentifier*)nullptr);

	return ppdu;
}

void CAcseAssociation::acceptSession(CBerByteArrayOutputStream& payload)
{
	quint32 payloadLength = payload.size();

	CBerAnyNoDecode berAny(payloadLength);
	NsExternalLinkV1::SubChoiceEncoding subChEncoding( &berAny, (CBerOctetString*) nullptr, (CBerBitString*) nullptr );

	CExternalLinkV1 external(&directReference, &indirectReference, &subChEncoding);

	QLinkedList<CExternalLinkV1> listExternal;
	listExternal.push_back(external);

	CAssociationInformation userInformation(&listExternal);

	CApplicationContextName acn(&applicationContextName);

	CAAreApdu aare(nullptr, &acn, &aareAccepted, &associateSourceDiagnostic, nullptr,
			nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &userInformation);
	CAcseApdu acse(nullptr, &aare, nullptr, nullptr);
	CBerByteArrayOutputStream berOStream(100, true);

	quint32 codeLength = acse.encode(berOStream, true);

	CBerAnyNoDecode band(codeLength);

	NsPdvList::SubchoicePresentationDataValues presDataValues(
			&band,
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

	NsCpaPpdu::CSubSecNormalModeParameters normalModeParameters(nullptr, &PSelLocal, &presentationResultList,
			(CBerBitString*) nullptr, (CBerBitString*) nullptr, &userData);

	CCpaPpdu cpaPpdu(&normalModeSelector, &normalModeParameters);

	cpaPpdu.encode(berOStream, true);

	QLinkedList<QByteArray> ssduList;
	QLinkedList<quint32> ssduOffsets;
	QLinkedList<quint32> ssduLengths;

	ssduList.push_back(berOStream.getByteArray());
	ssduOffsets.push_back(0);
	ssduLengths.push_back(berOStream.size());

	ssduList.push_back(payload.getByteArray());
	ssduOffsets.push_back(0);
	ssduLengths.push_back(payload.size());

	sendAcceptSession(ssduList, ssduOffsets, ssduLengths);
}

void CAcseAssociation::sendAcceptSession(QLinkedList<QByteArray>& ssdu, QLinkedList<quint32>& ssduOffsets, QLinkedList<quint32>& ssduLengths)
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
	sduAcceptHeader[idx++] = 0x01;	// temporary test client->server
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

	qDebug() << "--------------------------------------";
	qDebug() << "Client -> Server";
	qDebug() << "--------------------------------------";

	quint32 payloadLength = payload.size();

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

	CBerBitString* pSenderAcseRequirements = nullptr;
	CBerObjectIdentifier* pMechanismName = nullptr;
	CAuthenticationValue* pAuthenticationValue = nullptr;

	if (authenticationParameter.size() != 0)
	{
		{
			QByteArray code( (const char*) sender_acse_requirements_char, (int) (sizeof(sender_acse_requirements_char)/sizeof(sender_acse_requirements_char[0])) );
			CBerBitString tmp(code);
			pSenderAcseRequirements = &tmp;
		}

		pMechanismName = &defaultMechanismName;

		{
			QByteArray auth(authenticationParameter.toUtf8());
			CBerGraphicString auString( auth );
			CAuthenticationValue tmp( &auString, nullptr, nullptr);
			pAuthenticationValue = &tmp;
		}
	}

	CBerInteger aeIntCalled(aeQualifierCalled);
	CAeQualifier aeQaCalled(&aeIntCalled);
	CBerInteger aeIntCalling(aeQualifierCalling);
	CAeQualifier aeQaCalling(&aeIntCalling);

	CApplicationContextName acn(&applicationContextName);

	CAArqApdu aarq(
			(CBerBitString*) nullptr,
			&acn,
			&calledApTitle,
			&aeQaCalled,
			(CBerInteger*) nullptr,
			(CBerInteger*) nullptr,
			&callingApTitle,
			&aeQaCalling,
			(CBerInteger*) nullptr,
			(CBerInteger*) nullptr,
			pSenderAcseRequirements,
			pMechanismName,
			pAuthenticationValue,
			(CApplicationContextNameList*) nullptr,
			(CBerGraphicString*) nullptr,
			&userInformation);

	CAcseApdu acse( &aarq, nullptr, nullptr, nullptr );

	// Serialize
	CBerByteArrayOutputStream berOStream(200, true);

	acse.encode(berOStream, true);

	quint32 acseHeaderLength = berOStream.getByteArray().size();

// ------------------------------------------------------------------------
//	getPresentationUserDataField
//	------------------------------------------------------------------------
	CBerAnyNoDecode band(acseHeaderLength + payloadLength);

	NsPdvList::SubchoicePresentationDataValues presDataValues(
			&band,
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

// ------------------------------------------------------------------------

	CBerOctetString SelRemoteBerOctetString(pSelRemote);

	NsCpType::CSubSeqNormalModeParameters normalModeParameter(
			nullptr,
			&PSelLocal,
			&SelRemoteBerOctetString,
			&context_list,
			nullptr,
			nullptr,
			nullptr,
			&userData
			);

	CCpType cpType( &normalModeSelector, &normalModeParameter);

	cpType.encode(berOStream, true);

	QByteArray outarr = berOStream.getByteArray();

	QLinkedList<QByteArray> ssduList;
	QLinkedList<quint32> ssduOffsets;
	QLinkedList<quint32> ssduLengths;

	ssduList.push_back(berOStream.getByteArray());
	ssduOffsets.push_back(0); //berOStream.index() + 1);
	ssduLengths.push_back(berOStream.size());

	qDebug() << "length[0] (data) = " <<  ssduLengths.back();

	ssduList.push_back(payload.getByteArray());
	ssduOffsets.push_back(0); //payload.index() + 1);
	ssduLengths.push_back(payload.size());

	qDebug() << "length[1] (payload) = " <<  ssduLengths.back();

	startSConnection(ssduList, ssduOffsets, ssduLengths, sSelRemote, sSelLocal);

}

CUserData CAcseAssociation::getPresentationUserDataField(qint32 userDataLength)
{

	CBerAnyNoDecode berNoDec(userDataLength);
	NsPdvList::SubchoicePresentationDataValues presDataValues( &berNoDec , nullptr, nullptr);

	CPdvList pdvList(nullptr, &acsePresentationContextId, &presDataValues);
	QLinkedList<CPdvList> pdvListList;
	pdvListList.push_back(pdvList);

	CFullyEncodedData fullyEncodedData( &pdvListList );
	CUserData userData(nullptr, &fullyEncodedData);

	return userData;
}

quint32 CAcseAssociation::receiveDataParser(QDataStream& iStream)
{
	while ( iStream.atEnd() == false )
	{
		// read parameter type
		quint8 parameterType;
		iStream >> parameterType;
		// read parameter length
		quint8 parameterLength;
		iStream >> parameterLength;

		switch (parameterType) {
		// Connect Accept Item (5)
		case 0x05:
			{
				quint32 bytesToRead = parameterLength;

				while (bytesToRead > 0)
				{
					// read parameter type
					quint8 ca_parameterType;
					iStream >> ca_parameterType;
					quint8 ca_parameterLen;
					iStream >> ca_parameterLen;

					bytesToRead -= 2;

					switch (ca_parameterType)
					{

					// Protocol Options (19)
					case 0x13:
						// flags: .... ...0 = Able to receive extended
						// concatenated SPDU: False
						{
							quint8 protocolOptions;
							iStream >> protocolOptions;
							if (protocolOptions != 0x00)
							{
								qDebug() << "CAcseAssociation::receiveDataParser didn't receive connect answer. SPDU Connect Accept Item/Protocol Options is "
										<< protocolOptions << ", expected 0";

								iStream.skipRawData(INT_MAX);
								return 0;
							}

							bytesToRead--;
							break;
						}
					// Version Number
					case 0x16:
						// flags .... ..1. = Protocol Version 2: True
						{
							quint8 versionNumber;
							iStream >> versionNumber;
							if (versionNumber != 0x02)
							{
								qDebug() << "CAcseAssociation::receiveDataParser didn't receive connect answer. SPDU Connect Accept Item/Version Number is "
										<< versionNumber << ", expected 2";

								iStream.skipRawData(INT_MAX);
								return 0;
							}

							bytesToRead--;
							break;
						}

					default:
						{
							qDebug() << "CAcseAssociation::receiveDataParser didn't receive connect answer. SPDU Connect Accept Item: parameter not implemented: "
								<< ca_parameterType;

							iStream.skipRawData(INT_MAX);
							return 0;

						}

					}
				}

			}
			break;

		// Session Requirement (20)
		case 0x14:
			// flags: (.... .... .... ..1. = Duplex functional unit: True)
			{
				quint64 sessionRequirement = 0;
				iStream.readRawData((char*) &sessionRequirement, parameterLength);

				qDebug() << "CAcseAssociation::receiveDataParser: section = 0x14; parameterLength = " << parameterLength;

				if (sessionRequirement != 0x0200) {
					qDebug() << "CAcseAssociation::receiveDataParser didn't receive connect answer. SPDU header parameter 'Session Requirement (0x14)' is "
							<< sessionRequirement << ", expected 2";

					iStream.skipRawData(INT_MAX);
					return 0;
				}
			}
			break;

		// Calling Session Selector (51)
		case 0x33:
			{
				quint64 css = 0;
				iStream.readRawData((char*) &css, parameterLength);

				qDebug() << "CAcseAssociation::receiveDataParser: section = 0x33; parameterLength = " << parameterLength;

				if (css != 0x0100) {
					qDebug() << "CAcseAssociation::receiveDataParser didn't receive connect answer. SPDU header parameter 'Calling Session Selector (0x33)' is "
							<< css << ", expected 1";

					iStream.skipRawData(INT_MAX);
					return 0;
				}
			}
			break;

		// Called Session Selector (52)
		case 0x34:
			{
				quint64 calledSessionSelector = 0;
				iStream.readRawData((char*) &calledSessionSelector, parameterLength);

				qDebug() << "CAcseAssociation::receiveDataParser: section = 0x34; parameterLength = " << parameterLength;

				if (calledSessionSelector != 0x0100) {
					qDebug() << "CAcseAssociation::receiveDataParser didn't receive connect answer. SPDU header parameter 'Called Session Selector (0x34)' is "
							<< calledSessionSelector << ", expected 1";

					iStream.skipRawData(INT_MAX);
					return 0;
				}
			}
			break;

		// Session user data (193)
		case 0xc1:

			return 0;

		default:
			{
				qDebug() << "CAcseAssociation::receiveDataParser didn't receive connect answer. SPDU header parameter type "
				<< parameterType << " not implemented.";

				iStream.skipRawData(INT_MAX);
				return 0;
			}
		}
	}

	return 0;
}

void CAcseAssociation::ISO8327Header(
		QByteArray& spduHeader,
		QByteArray& sSelRemote,
		QByteArray& sSelLocal,
		quint8 ssduLength
		)
{
	spduHeader.resize(24);

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
}

void CAcseAssociation::startSConnection(
		QLinkedList<QByteArray>& ssduList,
		QLinkedList<quint32>& ssduOffsets,
		QLinkedList<quint32>& ssduLengths,
		QByteArray& sSelRemote,
		QByteArray& sSelLocal)
{

	if ( m_connected )
	{
		qDebug() << "ERROR: CAcseAssociation::startAssociation connected already";
		return;
	}

	if (sSelRemote.size() < 2)
	{
		qDebug() << "ERROR: CAcseAssociation::startAssociation sSelRemote size = " << sSelRemote.size();
		return;
	}

	if (sSelLocal.size() < 2)
	{
		qDebug() << "ERROR: CAcseAssociation::startAssociation sSelLocal size = " << sSelLocal.size();
		return;
	}

	QByteArray header;

	quint8 ssduLength=0;
	for (auto v: ssduLengths)
		ssduLength += v;

	qDebug() << "SSDU Length = " << ssduLength;

	ISO8327Header(header, sSelRemote, sSelLocal, ssduLength);

	ssduList.push_front(header);
	ssduOffsets.push_front(0);
	ssduLengths.push_front(header.size());

	qDebug() << "length[2] (header) = " <<  ssduLengths.front();

	m_tConnection->send(ssduList, ssduOffsets, ssduLengths);
}

void CAcseAssociation::send(CBerByteArrayOutputStream& payload)
{
	if ( !m_connected )
	{
		qDebug() << "ERROR: CAcseAssociation::send is not connected";
		return;
	}

	CBerAnyNoDecode noDecode(payload.size());
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
	ssduOffsets.push_back(0);
	ssduLengths.push_back(berOStream.getByteArray().size());

	ssduList.push_back(payload.getByteArray());
	ssduOffsets.push_back(0);
	ssduLengths.push_back(payload.size());

	sendSessionLayer(ssduList, ssduOffsets, ssduLengths);

}

void CAcseAssociation::receive(QByteArray& pduBuffer)
{
	if ( !m_connected )
	{
		qDebug() << "ERROR! CAcseAssociation::receive not connected.";
		return;
	}

	quint8 firstByte = pduBuffer[0];

	if (firstByte == 25) {
		// got an ABORT SPDU
		qDebug() <<  "ERROR! CAcseAssociation::receive: Received an ABORT SPDU";
		return;
	}

	// -- read ISO 8327-1 header
	// SPDU type: Give tokens PDU (1)
	if (firstByte != 0x01) {
		qDebug() <<  "CAcseAssociation::receive: SPDU header syntax error: first SPDU type not 1";
		return;
	}
	// length
	if ( (quint8) pduBuffer[1] != (quint8) 0) {
		qDebug() <<  "CAcseAssociation::receive: SPDU header syntax error: first SPDU type length not 0";
		return;
	}
	// SPDU Type: DATA TRANSFER (DT) SPDU (1)
	if ( (quint8) pduBuffer[2] != (quint8) 0x01) {
		qDebug() <<  "CAcseAssociation::receive: SPDU header syntax error: second SPDU type not 1";
		return;
	}
	// length
	if ( (quint8) pduBuffer[3] != (quint8) 0) {
		qDebug() <<  "CAcseAssociation::receive: SPDU header syntax error: second SPDU type length not 0";
		return;
	}

	// decode PPDU header
	CBerAnyNoDecode noDecode(0);
	NsPdvList::SubchoicePresentationDataValues spdv( &noDecode,
			(CBerOctetString*) nullptr, (CBerBitString*) nullptr);
	CBerInteger int31(31);
	CPdvList pdvList( (CBerObjectIdentifier*) nullptr, &int31, &spdv);

	QLinkedList<CPdvList> listPdvList;
	listPdvList.push_back(pdvList);

	CFullyEncodedData fullyEncodedData(&listPdvList);
	CUserData userData( nullptr, &fullyEncodedData );

	CBerByteArrayInputStream iStream( pduBuffer, 4);
	if (userData.decode( iStream, false) == 0)
	{
		qDebug() <<  "CAcseAssociation::receive: error decoding PPDU header";
		return;
	}

	pduBuffer = iStream.get();

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

QByteArray CAcseAssociation::parseConnectionEstablished(QDataStream& iStream, quint32 payloadSize)
{
	// Decode answer
	quint8 	SPDUType,
			SPDULength;

	iStream >> SPDUType;
	iStream >> SPDULength;

	if ( SPDUType != (quint8) 0x0e)
	{
		qDebug() << "CAcseAssociation::startAssociation didn't receive connect answer. ISO 8327-1 header wrong SPDU type, expected ACCEPT (14), got "
				<< getSPDUTypeString(SPDUType) << " (" << SPDUType << ")";

		QByteArray ret;
		return ret;
	}
	else
	{
		receiveDataParser(iStream);	// Это парсит client

		// Decode to stack

		// CpaPpdu

//		CBerAnyNoDecode band(codeLength);
		CBerAnyNoDecode band(0);

		NsPdvList::SubchoicePresentationDataValues presDataValues(
				&band,
				(CBerOctetString*) nullptr,
				(CBerBitString*) nullptr );

		CBerInteger acsePresentationContextId;
		CPdvList pdvList(
				(CBerObjectIdentifier*) nullptr,
				&acsePresentationContextId,
				&presDataValues);

		QLinkedList<CPdvList> listPdvList;
		listPdvList.push_back(pdvList);

		CFullyEncodedData fullyEncodedData(&listPdvList);

		CUserData userData( (CBerOctetString*) nullptr, &fullyEncodedData);

		CBerOctetString PSelLocal;
		CBerInteger iR1, iR2;
		CBerObjectIdentifier OIR1, OIR2;
		CResultSubsequence r1(&iR1, &OIR1, nullptr);
		CResultSubsequence r2(&iR2, &OIR2, nullptr);
		QLinkedList<CResultSubsequence> listR;
		listR.push_back(r1);
		listR.push_back(r2);
		CResultList presentationResultList(&listR);

		NsCpaPpdu::CSubSecNormalModeParameters normalModeParameters(nullptr, &PSelLocal, &presentationResultList,
				(CBerBitString*) nullptr, (CBerBitString*) nullptr, &userData);

		CBerInteger modeSelector;
		CModeSelector normalModeSelector(&modeSelector);
		CCpaPpdu cpaPpdu(&normalModeSelector, &normalModeParameters);

		// ACSE

		CBerAnyNoDecode berAny(payloadSize);
		NsExternalLinkV1::SubChoiceEncoding subChEncoding( &berAny, (CBerOctetString*) nullptr, (CBerBitString*) nullptr );

		CBerObjectIdentifier directReference;
		CBerInteger indirectReference;
		CExternalLinkV1 external(&directReference, &indirectReference, &subChEncoding);

		QLinkedList<CExternalLinkV1> listExternal;
		listExternal.push_back(external);

		CAssociationInformation userInformation(&listExternal);

		CBerObjectIdentifier applicationContextName;
		CApplicationContextName acn(&applicationContextName);

		CBerInteger aareAccepted;
		CBerInteger acseServiceUser;
		CAssociateSourceDiagnostic associateSourceDiagnostic(&acseServiceUser, (CBerInteger*)nullptr);
		CAAreApdu aare(nullptr, &acn, &aareAccepted, &associateSourceDiagnostic, nullptr,
				nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &userInformation);
		CAcseApdu acse(nullptr, &aare, nullptr, nullptr);

		// ACSE Ready

		CBerByteArrayOutputStream berOStream(100, true);

		CBerByteArrayInputStream InputStream(iStream);

		cpaPpdu.decode(InputStream, true);

		acse.decode(InputStream, true);

		m_connected = true;

		quint32 fakeLen = 0;
		QByteArray retArray = *(lastBerIdentifier::get(InputStream, fakeLen).getCode()) + InputStream.get();

		return retArray;
	}
}

QByteArray CAcseAssociation::parseConnectionRequest(QDataStream& iStream)
{
	QByteArray retArray;

	quint8 spduType;
	iStream >> spduType;
	qDebug() << "CAcseAssociation::parseServerAnswer: spduType = " << spduType;

	if (spduType != 0x0d)
	{
		QString str = QString("CAcseAssociation::parseServerAnswer: ISO 8327-1 header wrong SPDU type, expected CONNECT (13), got %1 (%2)")
				.arg(getSPDUTypeString(spduType))
				.arg(spduType);

		qDebug() << str;
		signalAcseIOError(str);
		return retArray;
	}

	quint8 headerLength;
	iStream >> headerLength;
	qDebug() << "CAcseAssociation::parseServerAnswer: headerLength = " << headerLength;

	receiveDataParser(iStream);

// Test print of all data from stream

	CBerByteArrayInputStream berIStream(iStream);
	QByteArray out = berIStream.get();
	qDebug() << out.toHex();

// Create empty structure for decoding
//	QVector<qint32> bitStringCalled;
//	CBerObjectIdentifier calledId(bitStringCalled);
//	CApTitle calledApTitle( &calledId );
//
//	QVector<qint32> bitStringCalling;
//	CBerObjectIdentifier callingId(bitStringCalling);
//	CApTitle callingApTitle( &callingId );
//
//	CBerAnyNoDecode noDecode;
//	NsExternalLinkV1::SubChoiceEncoding encoding( &noDecode, nullptr, nullptr );
//
//	CBerObjectIdentifier directReference;
//	CBerInteger indirectReference;
//	CExternalLinkV1 externalLink( &directReference, &indirectReference, &encoding);
//
//	QLinkedList<CExternalLinkV1> externalList;
//	externalList.push_back(externalLink);
//
//	CAssociationInformation userInformation( &externalList );
//
//	QByteArray code;
//	CBerBitString SenderAcseRequirements(code);
//
//	CBerGraphicString auString;
//	CAuthenticationValue AuthenticationValue( &auString, nullptr, nullptr);
//
//	CBerObjectIdentifier MechanismName;
//
//	CBerInteger aeIntCalled;
//	CAeQualifier aeQaCalled( &aeIntCalled );
//	CBerInteger aeIntCalling;
//	CAeQualifier aeQaCalling( &aeIntCalling );
//
//	CBerObjectIdentifier applicationContextName;
//	CApplicationContextName acn( &applicationContextName );
//
//	CAArqApdu aarq(
//			(CBerBitString*) nullptr,
//			&acn,
//			&calledApTitle,
//			&aeQaCalled,
//			(CBerInteger*) nullptr,
//			(CBerInteger*) nullptr,
//			&callingApTitle,
//			&aeQaCalling,
//			(CBerInteger*) nullptr,
//			(CBerInteger*) nullptr,
//			(CBerBitString*) nullptr, // &SenderAcseRequirements,
//			(CBerObjectIdentifier*) nullptr, //&MechanismName,
//			(CAuthenticationValue*) nullptr, //&AuthenticationValue,
//			(CApplicationContextNameList*) nullptr,
//			(CBerGraphicString*) nullptr,
//			&userInformation);
//
//	CAcseApdu acse( &aarq, nullptr, nullptr, nullptr );
//
//// ------------------------------------------------------------------------
////	getPresentationUserDataField
//// ------------------------------------------------------------------------
//	CBerAnyNoDecode band;
//
//	NsPdvList::SubchoicePresentationDataValues presDataValues(
//			&band,
//			(CBerOctetString*) nullptr,
//			(CBerBitString*) nullptr );
//
//	CPdvList pdvList(
//			(CBerObjectIdentifier*) nullptr,
//			&acsePresentationContextId,
//			&presDataValues);
//
//	QLinkedList<CPdvList> listPdvList;
//	listPdvList.push_back(pdvList);
//
//	CFullyEncodedData fullyEncodedData(&listPdvList);
//
//	CUserData userData( (CBerOctetString*) nullptr, &fullyEncodedData);
//
//// ------------------------------------------------------------------------
//
//	QByteArray selRemote;
//	CBerOctetString SelRemoteBerOctetString(selRemote);
//
//	CBerObjectIdentifier oid1;
//	CBerObjectIdentifier oid2;
//	CBerObjectIdentifier oid3;
//	CBerObjectIdentifier oid4;
//	CBerObjectIdentifier oid5;
//	CBerObjectIdentifier oid6;
//	QLinkedList<CBerObjectIdentifier> tsnl1;
//	CContextListSubSeqOfTransferSyntaxName tsn1(&tsnl1);
//	tsnl1.push_back(oid5);
//	QLinkedList<CBerObjectIdentifier> tsnl2;
//	CContextListSubSeqOfTransferSyntaxName tsn2(&tsnl2);
//	tsnl2.push_back(oid6);
//	CBerInteger int1;
//	CBerInteger int2;
//	CContextListSubSeq appCN1(&int1, &oid1, &tsn1);
//	CContextListSubSeq appCN2(&int2, &oid2, &tsn2);
//	QLinkedList<CContextListSubSeq> appCNList;
//	appCNList.push_back(appCN1);
//	appCNList.push_back(appCN2);
//	CContextList contextList(&appCNList);
//
//	NsCpType::CSubSeqNormalModeParameters normalModeParameter(
//			nullptr,
//			&PSelLocal,
//			&SelRemoteBerOctetString,
//			&contextList,
//			nullptr,
//			nullptr,
//			nullptr,
//			&userData
//			);
//
//	CCpType cpType( &normalModeSelector, &normalModeParameter);

	CCpType cpType;
	CAcseApdu acse;

	cpType.decode(berIStream, true);

	acse.decode(berIStream, true);

	quint32 fakeLength = 0;
	retArray += *(lastBerIdentifier::get(berIStream, fakeLength).getCode()) + berIStream.get();
	lastBerIdentifier::reset();

	m_connected = true;

	return retArray;
}

QByteArray CAcseAssociation::listenForCn(QDataStream& InputStream)
{
	qDebug() << "CAcseAssociation::listenForCn called and m_connected = " << m_connected;

	if (m_connected)
	{
		qDebug() << "CAcseAssociation::listenForCn: connected already.";
		signalAcseIOError(QString("CAcseAssociation::listenForCn: connected already."));
		QByteArray ret;
		return ret;
	}

	QByteArray retArray = parseConnectionRequest(InputStream);
	if ( retArray.size() > 0)
	{
		emit signalAcseCnReady(this);
	}

	return retArray;
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

