/*
 * ServerAcseSap.cpp
 *
 *  Created on: 29 февр. 2016 г.
 *      Author: alex
 */

#include "ServerAcseSap.h"

CServerAcseSap::CServerAcseSap(quint16 port, quint32 backlog, QHostAddress bindAddr, CAcseAssociationListener* associationListener):
	m_pServerTSAP(nullptr)
{
	m_pAssociationListener = associationListener;

	m_pServerTSAP = new CServerTSAP(port, backlog, bindAddr);
	m_pServerTSAP->setMessageTimeout(500);
	m_pServerTSAP->setMessageFragmentTimeout(500);
	m_pConnectionListener = m_pServerTSAP->createServer();

	for (auto v: CClientAcseSap::P_SEL_DEFAULT)
		m_pSelLocal.push_back(v);

	connect( m_pConnectionListener, SIGNAL(signalConnected(const CConnection*)),
			this, SLOT(slotServerAcceptConnection(const CConnection*)) );

}

CServerAcseSap::CServerAcseSap(quint16 port, quint32 backlog, QHostAddress bindAddr, CAcseAssociationListener* associationListener,
		CSocketFactory serverSocketFactory):
			m_pServerTSAP(nullptr)
{

	m_pAssociationListener = associationListener;

	m_pServerTSAP = new CServerTSAP(port, backlog, bindAddr, serverSocketFactory);
	m_pServerTSAP->setMessageTimeout(500);
	m_pServerTSAP->setMessageFragmentTimeout(500);
	m_pConnectionListener = m_pServerTSAP->createServer();

	for (auto v: CClientAcseSap::P_SEL_DEFAULT)
		m_pSelLocal.push_back(v);

	connect( m_pConnectionListener, SIGNAL(signalConnected(const CConnection*)),
			this, SLOT(slotServerAcceptConnection(const CConnection*)) );

}

CAcseAssociation* CServerAcseSap::createNewAcseAssociation(CConnection* pconn)
{
	try
	{
		CAcseAssociation* acseAssoc = new CAcseAssociation(pconn, m_pSelLocal);

		QByteArray pduBuffer;
		acseAssoc->listenForCn(pduBuffer);

		CBerByteArrayOutputStream acceptData(pduBuffer, 0);
		acseAssoc->accept(acceptData);

		// signals from Connection to ServerAcseSap
		connect(pconn, SIGNAL(signalConnectionClosed(const CConnection*)),
				this, SLOT(slotServerConnectionClosed(const CConnection*)));

		// signal from server to AcseAssociationListener
		connect(this, SIGNAL(signalClientConnected(const CConnection*)),
				m_pAssociationListener, SLOT(slotClientConnected(const CConnection*)));
		connect(this, SIGNAL(signalClientDisconnected(const CConnection*)),
				m_pAssociationListener, SLOT(slotClientDisconnected(const CConnection*)));

		// signals from Connection to AcseAssociationListener
		connect(pconn, SIGNAL(signalTSduReady(const CConnection*)),
				m_pAssociationListener, SLOT(slotPduReady(const CConnection*)));

		// signals from AcseAssociation to AcseAssociationListener
		connect( acseAssoc, SIGNAL(signalAcseAssociationReady(const CAcseAssociation*)),
				m_pAssociationListener, SLOT(slotAcseAssociationReady(const CAcseAssociation*)) );
		connect( acseAssoc, SIGNAL(signalAcseAssociationClosed(const CAcseAssociation*)),
				m_pAssociationListener, SLOT(slotAcseAssociationClosed(const CAcseAssociation*)) );
		connect( acseAssoc, SIGNAL(signalAcseCnReady(const CAcseAssociation*)),
				m_pAssociationListener, SLOT(slotAcseCnReady(const CAcseAssociation*)) );
		connect( acseAssoc, SIGNAL(signalAcseIOError(QString strErr)),
				m_pAssociationListener, SLOT(slotAcseIOError(QString strErr)) );

		emit signalAcseClientConnected(acseAssoc);  // -> CAcseAssociationListener

		return acseAssoc;
	}

	catch (std::bad_alloc& ex)
	{
		qDebug() << "CServerAcseSap::createNewAcseAssociation: " << ex.what();
		throw;
	}

	catch (std::exception& ex)
	{
		qDebug() << "CServerAcseSap::createNewAcseAssociation: " << ex.what();
		throw;
	}

}


/*** Slot Section ***/
void CServerAcseSap::slotServerAcseAcceptConnection(const CConnection* pconn)
{
	qDebug() << "CServerAcseSap::slotServerAcceptConnection";

	createNewAcseAssociation( const_cast<CConnection*> (pconn) );
}

void CServerAcseSap::slotServerAcseConnectionClosed(const CAcseAssociation* that)
{
	qDebug() << "CServerAcseSap::slotServerConnectionClosed";

	emit signalAcseClientDisconnected(that);

	Q_CHECK_PTR(that);

	emit signalAcseClientDisconnected(that);

}



