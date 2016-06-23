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

	quint32 size = sizeof(CClientAcseSap::P_SEL_DEFAULT) / sizeof(CClientAcseSap::P_SEL_DEFAULT[0]);
	for (quint32 i=0; i < size; ++i)
		m_pSelLocal.push_back(CClientAcseSap::P_SEL_DEFAULT[i]);

	connect( m_pConnectionListener, SIGNAL(signalConnected(const CConnection*)),
			this, SLOT(slotServerAcseAcceptConnection(const CConnection*)) );

}

CServerAcseSap::CServerAcseSap(quint16 port, quint32 backlog, QHostAddress bindAddr,
		CAcseAssociationListener* associationListener,
		CSocketFactory* serverSocketFactory):
		m_pServerTSAP(nullptr)
{

	m_pAssociationListener = associationListener;

	m_pServerTSAP = new CServerTSAP(port, backlog, bindAddr, serverSocketFactory);
	m_pServerTSAP->setMessageTimeout(500);
	m_pServerTSAP->setMessageFragmentTimeout(500);
	m_pConnectionListener = m_pServerTSAP->createServer();

	quint32 size = sizeof(CClientAcseSap::P_SEL_DEFAULT) / sizeof(CClientAcseSap::P_SEL_DEFAULT[0]);
	for (quint32 i=0; i < size; ++i)
		m_pSelLocal.push_back(CClientAcseSap::P_SEL_DEFAULT[i]);

	connect( m_pConnectionListener, SIGNAL(signalConnected(const CConnection*)),
			this, SLOT(slotServerAcseAcceptConnection(const CConnection*)) );

}

CAcseAssociation* CServerAcseSap::createNewAcseAssociation(CConnection* pconn)
{
	try
	{
		CBerOctetString berStr(m_pSelLocal);
		CAcseAssociation* acseAssoc = new CAcseAssociation(pconn, berStr);

//		QByteArray pduBuffer;
//
//		CBerByteArrayOutputStream acceptData(pduBuffer, 0);
//		acseAssoc->accept(acceptData);
//
		// signals from Connection to CAcseAssociation
		connect(pconn, SIGNAL(signalConnectionClosed(const CConnection*)),
				acseAssoc, SLOT(slotAcseConnectionClosed(const CConnection*)));
		connect(pconn, SIGNAL(signalTSduReady(const CConnection*)),
				acseAssoc, SLOT(slotAcseTSduReady(const CConnection*)));

		// signals from AcseAssociation to AcseAssociationListener
		connect( acseAssoc, SIGNAL(signalAcseAssociationClosed(CAcseAssociation*)),
				m_pAssociationListener, SLOT(slotAcseAssociationClosed(CAcseAssociation*)) );
		connect( acseAssoc, SIGNAL(signalAcseCnReady(CAcseAssociation*)),
				m_pAssociationListener, SLOT(slotAcseCnReady(CAcseAssociation*)) );
		connect( acseAssoc, SIGNAL(signalAcseTSduReady(CAcseAssociation*)),
				m_pAssociationListener, SLOT(slotAcseTSduReady(CAcseAssociation*)) );
		connect( acseAssoc, SIGNAL(signalAcseIOError(QString)),
				m_pAssociationListener, SLOT(slotAcseIOError(QString)) );

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

void CServerAcseSap::startListening()
{

	if (m_pAssociationListener == nullptr || m_pServerTSAP == nullptr) {
		emit signalIllegalClassMember("CServerAcseSap::startListening: AcseSAP is unable to listen because it was not initialized.");
		return;
	}

	m_pServerTSAP->startListening();
}

void CServerAcseSap::stopListening()
{
	m_pServerTSAP->stopListening();
}

void CServerAcseSap::setMessageTimeout(quint32 messageTimeout)
{
	if ( !m_pServerTSAP )
	{
		emit signalIllegalClassMember("CServerAcseSap::associate: m_pServerTSAP is NULL!");
		return;
	}

	m_pServerTSAP->setMessageTimeout(messageTimeout);
}

void CServerAcseSap::setMessageFragmentTimeout(quint32 messageFragmentTimeout)
{
	if ( !m_pServerTSAP )
	{
		emit signalIllegalClassMember("CServerAcseSap::associate: m_pServerTSAP is NULL!");
		return;
	}

	m_pServerTSAP->setMessageFragmentTimeout(messageFragmentTimeout);
}

CConnectionListener* CServerAcseSap::getConnectionListener()
{
	return m_pConnectionListener;
}

// *** slot section

void CServerAcseSap::slotServerAcseAcceptConnection(const CConnection* pconn)
{
	qDebug() << "CAcseAssociation::slotServerAcseAcceptConnection";

	Q_CHECK_PTR(pconn);

	CAcseAssociation* assoc = createNewAcseAssociation( const_cast<CConnection*> (pconn) );

	emit signalAcseClientConnected(assoc);

	assoc->listenForCn();
}

