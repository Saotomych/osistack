/*
 * CServerAcseSap.h
 *
 *  Created on: 12 февр. 2016 г.
 *      Author: alex
 */

#ifndef INCLUDE_SERVERACSESAP_H_
#define INCLUDE_SERVERACSESAP_H_

#include "osistack_global.h"
#include <connection.h>
#include <servertsap.h>
#include "AcseAssociation.h"
#include "ClientAcseSap.h"
#include "berOctetString.h"

/**
 * This class implements the server Service Access Point (SAP) for the Application Control Service Element (ACSE)
 * protocol as defined by ISO 8650 or ITU X.217/X.227. The ACSE provides services for establishing and releasing
 * application-associations. The class also realizes the lower ISO Presentation Layer as defined by ISO 8823/ITU X226
 * and the ISO Session Layer as defined by 8327/ITU X.225.
 *
 */
class OSISTACK_SHAREDEXPORT CServerAcseSap: public QObject
{

	Q_OBJECT

public:

	QByteArray m_pSelLocal; // = CClientAcseSap::P_SEL_DEFAULT;

	/**
	 * @brief This constructor to create a server ACSE SAP that listens on a fixed port.
	 *
	 * @param port
	 *            the local port listen on
	 * @param backlog
	 *            the backlog
	 * @param bindAddr
	 *            the InetAddress to bind to
	 */
	CServerAcseSap(quint16 port, quint32 backlog, QHostAddress bindAddr);

	/**
	 * @brief This constructor to create a server ACSE SAP that listens on a fixed port. The server socket is created with
	 * the given socket factory.
	 *
	 * @param port
	 *            the local port listen on
	 * @param backlog
	 *            the backlog
	 * @param bindAddr
	 *            the InetAddress to bind to
	 * @param serverSocketFactory
	 *            the server socket factory to create the socket
	 */
	CServerAcseSap(quint16 port, quint32 backlog, QHostAddress bindAddr,
			CSocketFactory* serverSocketFactory);

	/**
	 * @brief Start listening for incoming connections. Only for server SAPs.
	 */
	void startListening();

	/**
	 * @brief Stop listening for incoming connections. Only for server SAPs.
	 */
	void stopListening();

	/**
	 * @brief Set the CConnection timeout for waiting for the first byte of a new message.
	 *
	 * @param messageTimeout. Default is 0 (unlimited).
	 *            in milliseconds
	 */
	void setMessageTimeout(quint32 messageTimeout);

	/**
	 * @brief Set the CConnection timeout for receiving data once the beginning of a message has been received.
	 *
	 * @param messageFragmentTimeout. Default is 60000 (60 seconds).
	 *            in milliseconds
	 */
	void setMessageFragmentTimeout(quint32 messageFragmentTimeout);

	/**
	 * @brief creates new ACSE Association for client or server
	 * @param pconn
	 * 			that's a connection to attach to association
	 * @return new ACSE association
	 */
	CAcseAssociation* createNewAcseAssociation(CConnection* pconn);

	/**
	 * @brief takes connection listener for connect signals to slots, is used for server application
	 * @return connection listener pointer
	 */
	CConnectionListener* getConnectionListener();

private:

	CServerTSAP* m_pServerTSAP;

	CConnectionListener* m_pConnectionListener;

public slots:
	void slotServerAcseAcceptConnection(const CConnection* that);

signals:
	void signalAcseClientConnected(CAcseAssociation* that);

	// Error signals
	void signalIllegalClassMember(QString strErr);

};


#endif /* INCLUDE_SERVERACSESAP_H_ */
