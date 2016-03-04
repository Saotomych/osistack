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
#include "AcseAssociationListener.h"
#include "AcseAssociation.h"
#include "ClientAcseSap.h"

/**
 * This class implements the server Service Access Point (SAP) for the Application Control Service Element (ACSE)
 * protocol as defined by ISO 8650 or ITU X.217/X.227. The ACSE provides services for establishing and releasing
 * application-associations. The class also realizes the lower ISO Presentation Layer as defined by ISO 8823/ITU X226
 * and the ISO Session Layer as defined by 8327/ITU X.225.
 *
 */
class CServerAcseSap: public QObject
{

private:

	CAcseAssociationListener* m_pAssociationListener;
	CConnectionListener* m_pConnectionListener;

public:

	CServerTSAP* m_pServerTSAP;

	QByteArray m_pSelLocal; // = ClientAcseSap.P_SEL_DEFAULT;

	/**
	 * Use this constructor to create a server ACSE SAP that listens on a fixed port.
	 *
	 * @param port
	 *            the local port listen on
	 * @param backlog
	 *            the backlog
	 * @param bindAddr
	 *            the InetAddress to bind to
	 * @param associationListener
	 *            the AssociationListener that will be notified when remote clients have associated. Once constructed
	 *            the AcseSAP contains a public TSAP that can be accessed to set its configuration.
	 */
	CServerAcseSap(quint16 port, quint32 backlog, QHostAddress bindAddr, CAcseAssociationListener* associationListener):
		m_pConnectionListener(nullptr),
		m_pServerTSAP(nullptr)
	{
		m_pAssociationListener = associationListener;

		m_pServerTSAP = new CServerTSAP(port, backlog, bindAddr);

		// TODO: Подписка на события от ConnectionListener


		// Пока непонятно зачем нужен CAcseAssociationListener
		// Он передает события аксеприложению

	}

	/**
	 * Use this constructor to create a server ACSE SAP that listens on a fixed port. The server socket is created with
	 * the given socket factory.
	 *
	 * @param port
	 *            the local port listen on
	 * @param backlog
	 *            the backlog
	 * @param bindAddr
	 *            the InetAddress to bind to
	 * @param associationListener
	 *            the AssociationListener that will be notified when remote clients have associated. Once constructed
	 *            the AcseSAP contains a public TSAP that can be accessed to set its configuration.
	 * @param serverSocketFactory
	 *            the server socket factory to create the socket
	 */
	CServerAcseSap(quint16 port, quint32 backlog, QHostAddress bindAddr, CAcseAssociationListener* associationListener,
			CSocketFactory serverSocketFactory):
				m_pConnectionListener(nullptr),
				m_pServerTSAP(nullptr)
	{

		m_pAssociationListener = associationListener;

		m_pServerTSAP = new CServerTSAP(port, backlog, bindAddr, serverSocketFactory);

		// TODO: Подписка на события от ConnectionListener
		// Пока непонятно зачем нужен CAcseAssociationListener

	}

	/**
	 * Start listening for incoming connections. Only for server SAPs.
	 *
	 * @throws IOException
	 *             if an error occures starting to listen
	 */
	void startListening()
	{

		if (m_pAssociationListener == nullptr || m_pServerTSAP == nullptr) {
//			throw new IllegalStateException("AcseSAP is unable to listen because it was not initialized.");
			return;
		}

		m_pServerTSAP->startListening();
	}

	void stopListening()
	{
		m_pServerTSAP->stopListening();
	}

protected:
	/**
	 * This function is internal and should not be called by users of this class.
	 */
//	void serverStoppedListeningIndication(IOException e) {
//		m_pAssociationListener->serverStoppedListeningIndication(e);
//	}

	CAcseAssociation* CServerAcseSap::createNewAcseAssociation(CConnection* pconn);

private slots:
	void slotServerAcseAcceptConnection(const CConnection* that);
	void slotServerAcseConnectionClosed(const CAcseAssociation* that);

signals:
	void signalAcseClientConnected(const CAcseAssociation* that);
	void signalAcseClientDisconnected(const CAcseAssociation* that);

};


#endif /* INCLUDE_SERVERACSESAP_H_ */
