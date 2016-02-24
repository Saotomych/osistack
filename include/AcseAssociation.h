/*
 * AcseAssociation.h
 *
 *  Created on: 12 февр. 2016 г.
 *      Author: alex
 */

#ifndef INCLUDE_ACSEASSOCIATION_H_
#define INCLUDE_ACSEASSOCIATION_H_

#include "osistack_global.h"

#include <QObject>
#include <connection.h>
#include <clienttsap.h>

#include <berGraphicString.h>
#include "presentation-asn1/contextList.h"
#include "acse-asn1/associateSourceDiagnostic.h"
#include "presentation-asn1/modeSelector.h"
#include "presentation-asn1/ResultList.h"
#include "presentation-asn1/userData.h"
#include "presentation-asn1/CpaPpdu.h"
#include "acse-asn1/AcseApdu.h"
#include "acse-asn1/APtitle.h"
#include "presentation-asn1/PdvList.h"

class CAcseAssociation: public QObject
{
public:

	bool m_connected;
	CConnection* m_tConnection;
	QByteArray m_associateResponseAPDU;
	quint32 m_currentCallingSessionSelector;
	CBerOctetString* m_pSelLocalBerOctetString;

private:

	static CContextList context_list;
	static CBerInteger acsePresentationContextId;
	static CModeSelector normalModeSelector;

	static CResultList presentationResultList;

	static CBerInteger aareAccepted; // = new BerInteger(new byte[] { (byte) 0x01, (byte) 0x00 });

	static CAssociateSourceDiagnostic associateSourceDiagnostic;

	// is always equal to 1.0.9506.2.3 (MMS)
	static CBerObjectIdentifier applicationContextName;

	static CBerObjectIdentifier directReference;

	static CBerInteger indirectReference; // = new BerInteger(new byte[] { (byte) 0x01, (byte) 0x03 });


	static CBerObjectIdentifier defaultMechanismName;

public:

	CAcseAssociation(CConnection* tConnection, CBerOctetString* pSelLocalBerOctetString);

	void accept(CBerByteArrayOutputStream& payload);

	void writeSessionAccept(QLinkedList<QByteArray>& ssdu, QLinkedList<quint32>& ssduOffsets, QLinkedList<quint32>& ssduLengths);

	QByteArray getAssociateResponseAPdu();

	/**
	 * Starts an Application Association by sending an association request and waiting for an association accept message
	 *
	 * @param payload
	 *            payload that can be sent with the association request
	 * @param port
	 * @param address
	 * @param tSAP
	 * @param aeQualifierCalling
	 * @param aeQualifierCalled
	 * @param apTitleCalling
	 * @param apTitleCalled
	 * @throws IOException
	 */
	void startAssociation(
			CBerByteArrayOutputStream& payload,
			QHostAddress address,
			quint16 port,
			QHostAddress localAddr,
			quint16 localPort,
			QString& authenticationParameter,
			QByteArray& sSelRemote,
			QByteArray& sSelLocal,
			QByteArray& pSelRemote,
			CClientTSAP& tSAP,
			QVector<quint32>& apTitleCalled,
			QVector<quint32>& apTitleCalling,
			quint32 aeQualifierCalled,
			quint32 aeQualifierCalling);

	/**
	 * Starts a session layer connection, sends a CONNECT (CN), waits for a ACCEPT (AC) and throws an IOException if not
	 * successful
	 *
	 * @throws IOException
	 */
	QByteArray startSConnection(
			QLinkedList<QByteArray>& ssduList,
			QLinkedList<quint32>& ssduOffsets,
			QLinkedList<quint32>& ssduLengths,
			QHostAddress address,
			quint16 port,
			QHostAddress localAddr,
			quint16 localPort,
			CClientTSAP& tSAP,
			QByteArray& sSelRemote,
			QByteArray& sSelLocal);

	void send(CBerByteArrayOutputStream& payload);

	/**
	 * Listens for a new PDU and writes it into the given buffer. Decodes all ACSE and lower layer headers. The
	 * resulting buffer's position points to the beginning of the ACSE SDU. The limit will point to the byte after the
	 * last byte of the ACSE SDU.
	 *
	 * @param pduBuffer
	 *            buffer to write the received pdu into
	 * @throws DecodingException
	 *             if a decoding error occurs
	 * @throws IOException
	 *             if a non recoverable error occurs. Afterwards the association should be closed by the user
	 * @throws TimeoutException
	 *             if a timeout occurs
	 */
	void receive(QByteArray pduBuffer);

	/**
	 * Disconnects by sending a disconnect request at the Transport Layer and then closing the socket.
	 */
	void disconnect();

	/**
	 * Closes the connection simply by closing the socket.
	 */
	void close();

	void listenForCn(QByteArray pduBuffer);
	quint32 getMessageTimeout();
	void setMessageTimeout(quint32 tout);


private:

	void sendSessionLayer(
			QLinkedList<QByteArray>& ssduList,
			QLinkedList<quint32>& ssduOffsets,
			QLinkedList<quint32>& ssduLengths);

	quint64 extractInteger(QByteArray buffer, quint32 size);

	/* Statics */
public:

	static QString getSPDUTypeString(qint8 spduType);

private: /*statics */

	static QByteArray decodePConResponse(QByteArray& ppdu);

	static CUserData getPresentationUserDataField( quint32 userDataLength );


};



#endif /* INCLUDE_ACSEASSOCIATION_H_ */
