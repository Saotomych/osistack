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
#include "presentation-asn1/CpType.h"
#include "presentation-asn1/fullyEncodedData.h"

/**
 * @class CAcseAssociation
 * 			controls ACSE connection and snd/receive ACSE data
 */

class OSISTACK_SHAREDEXPORT CAcseAssociation: public QObject
{
	Q_OBJECT

public: // class API
	/**
	 * @brief CAcseAssociation constructor
	 * @param tConnection
	 * @param SelLocalBerOctetString
	 */
	CAcseAssociation(CConnection* tConnection, CBerOctetString& SelLocalBerOctetString);

	/**
	 * @brief accept the client session after the signalCnReady and send answer to client
	 * @param payload
	 * 			TODO what is the all payload params?
	 */
	void acceptSession(CBerByteArrayOutputStream& payload);


	/**
	 * @brief Starts an Application Association by sending an association request and waiting for an association accept message
	 *
	 * @param payload
	 *            payload that can be sent with the association request
	 * @param authenticationParameter
	 * @param sSelRemote
	 * 			remote service selector
	 * @param sSelLocal
	 * 			local service selector
	 * @param pSelRemote
	 * 			presentation remote selector
	 * @param apTitleCalled
	 * 			called title
	 * @param apTitleCalling
	 * 			calling title
	 * @param aeQualifierCalled
	 * @param aeQualifierCalling
	 */
	void startAssociation(
			CBerByteArrayOutputStream& payload,
			QString& authenticationParameter,
			QByteArray& sSelRemote,
			QByteArray& sSelLocal,
			QByteArray& pSelRemote,
			QVector<qint32>& apTitleCalled,
			QVector<qint32>& apTitleCalling,
			quint32 aeQualifierCalled,
			quint32 aeQualifierCalling);


	/**
	 * @brief sends data to remote side
	 */
	void send(CBerByteArrayOutputStream& payload);

	/**
	 * @brief Listens for a new PDU and writes it into the given buffer. Decodes all ACSE and lower layer headers. The
	 * resulting buffer's position points to the beginning of the ACSE SDU. The limit will point to the byte after the
	 * last byte of the ACSE SDU.
	 *
	 * @param pduBuffer
	 *            buffer to write the received pdu into
	 */
	void receive(QByteArray& pduBuffer);

	/**
	 * @brief parse data from client as establishing connection frame
	 * @param iStream
	 * 			server application's stream with the received data frame
	 * @param payloadSize
	 * 			expected payload size
	 * @return payload byte array
	 */
	QByteArray parseConnectionEstablished(QDataStream& iStream, quint32 payloadSize);

	/**
	 * @brief Disconnects by sending a disconnect request at the Transport Layer and then closing the socket.
	 */
	void disconnect();

	/**
	 * @brief Closes the connection simply by closing the socket.
	 */
	void close();

	/**
	 * @brief parse data from client with ACSE connection request frame
	 * @param InputStream
	 * @return payload byte array
	 */
	QByteArray listenForCn(QDataStream& InputStream);


	/**
	 * @brief get the timeout for waiting for the first byte of a new message.
	 * @return timeout value
	 */
	quint32 getMessageTimeout();

	/**
	 * @brief set the timeout for waiting for the first byte of a new message.
	 * @param tout
	 * 			timeout value
	 */
	void setMessageTimeout(quint32 tout);

    bool isConnected() const;

protected:

	bool m_connected;
	CConnection* m_tConnection;
	quint32 m_currentCallingSessionSelector;
	CBerOctetString PSelLocal;

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

	static CUserData getPresentationUserDataField(qint32 userDataLength);

	void sendSessionLayer(
			QLinkedList<QByteArray>& ssduList,
			QLinkedList<quint32>& ssduOffsets,
			QLinkedList<quint32>& ssduLengths);

	void ISO8327Header(
				QByteArray& spduHeader,
				QByteArray& sSelRemote,
				QByteArray& sSelLocal,
				quint8 ssduLength
			);

	QByteArray parseConnectionRequest(QDataStream& iStream);

	quint32 receiveDataParser(QDataStream& iStream);

	void sendAcceptSession(QLinkedList<QByteArray>& ssdu, QLinkedList<quint32>& ssduOffsets, QLinkedList<quint32>& ssduLengths);

	void startSConnection(
			QLinkedList<QByteArray>& ssduList,
			QLinkedList<quint32>& ssduOffsets,
			QLinkedList<quint32>& ssduLengths,
			QByteArray& sSelRemote,
			QByteArray& sSelLocal);

	/* Statics */
public:

	static QString getSPDUTypeString(qint8 spduType);

private: /*statics */

	static QDataStream& decodePConResponse(QDataStream& ppdu);

public slots:
	void slotAcseConnectionClosed(const CConnection* pconn);
	void slotAcseTSduReady(const CConnection* pconn);

signals:

	// work signals
	void signalAcseAssociationReady(CAcseAssociation* that);	// for client only
	void signalAcseAssociationClosed(CAcseAssociation* that);	// for all
	void signalAcseCnReady(CAcseAssociation* that);				// for listener only
	void signalAcseTSduReady(CAcseAssociation* that);			// for all

	// Error signals
	void signalAcseIOError(QString strErr);

};

#endif /* INCLUDE_ACSEASSOCIATION_H_ */
