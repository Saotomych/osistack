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
#include <connectionlistener.h>
#include <servertsap.h>
#include "AcseAssociationListener.h"
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

private:

	CAcseAssociationListener* m_pAssociationListener;
	CConnectionListener* m_pConnectionListener;

public:

	CServerTSAP* m_pServerTSAP;

	QByteArray m_pSelLocal; // = CClientAcseSap::P_SEL_DEFAULT;

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
	CServerAcseSap(quint16 port, quint32 backlog, QHostAddress bindAddr, CAcseAssociationListener* associationListener);

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
	CServerAcseSap(quint16 port, quint32 backlog, QHostAddress bindAddr,
			CAcseAssociationListener* associationListener,
			CSocketFactory* serverSocketFactory);

	/**
	 * Start listening for incoming connections. Only for server SAPs.
	 *
	 * @throws IOException
	 *             if an error occures starting to listen
	 */
	void startListening();
	void stopListening();
	void setMessageTimeout(quint32 messageTimeout);
	void setMessageFragmentTimeout(quint32 messageFragmentTimeout);

	CConnectionListener* getConnectionListener();

	CAcseAssociation* createNewAcseAssociation(CConnection* pconn);

public slots:
	void slotServerAcseAcceptConnection(const CConnection* that);

signals:
	void signalAcseClientConnected(CAcseAssociation* that);

	// Error signals
	void signalIllegalClassMember(QString strErr);

};


#endif /* INCLUDE_SERVERACSESAP_H_ */
