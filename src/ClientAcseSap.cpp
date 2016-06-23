/*
 * ClientAcseSap.cpp
 *
 *  Created on: 11 марта 2016 г.
 *      Author: alex
 */

#include "ClientAcseSap.h"

const quint8 CClientAcseSap::P_SEL_DEFAULT[] = { 0, 0, 0, 1 };
const quint8 CClientAcseSap::S_SEL_DEFAULT[] = { 0, 1 };
const qint32 CClientAcseSap::s_titleCalled[] = { 1, 1, 999, 1, 1 };
const qint32 CClientAcseSap::s_titleCalling[] = { 1, 1, 999, 1 };


CClientAcseSap::CClientAcseSap(CSocketFactory* socketFactory):
	m_aeQualifierCalled(12),
	m_aeQualifierCalling(12)
{
	m_pClientTSap = new CClientTSAP(*socketFactory);

	{
		quint32 size = sizeof(CClientAcseSap::P_SEL_DEFAULT) / sizeof(CClientAcseSap::P_SEL_DEFAULT[0]);
		for (quint32 i=0; i < size; ++i)
			m_PSelRemote.push_back(CClientAcseSap::P_SEL_DEFAULT[i]);

		m_PSelLocal = m_PSelRemote;
	}

	{
		quint32 size = sizeof(CClientAcseSap::S_SEL_DEFAULT) / sizeof(CClientAcseSap::S_SEL_DEFAULT[0]);
		for (quint32 i=0; i < size; ++i)
			m_SSelRemote.push_back(CClientAcseSap::S_SEL_DEFAULT[i]);

		m_SSelLocal = m_SSelRemote;
	}

	{
		quint32 size = sizeof(CClientAcseSap::s_titleCalled) / sizeof(CClientAcseSap::s_titleCalled[0]);
		for (quint32 i=0; i < size; ++i)
			m_ApTitleCalled.push_back(CClientAcseSap::s_titleCalled[i]);
	}

	{
		quint32 size = sizeof(CClientAcseSap::s_titleCalling) / sizeof(CClientAcseSap::s_titleCalling[0]);
		for (quint32 i=0; i < size; ++i)
			m_ApTitleCalling.push_back(CClientAcseSap::s_titleCalling[i]);
	}
}

CClientAcseSap::~CClientAcseSap()
{
	delete m_pClientTSap;
}

void CClientAcseSap::setApTitleCalled(QVector<qint32>& title) {
	m_ApTitleCalled = title;
}

void CClientAcseSap::setApTitleCalling(QVector<qint32>& title) {
	m_ApTitleCalling = title;
}

void CClientAcseSap::setAeQualifierCalled(quint32 qualifier) {
	m_aeQualifierCalled = qualifier;
}

void CClientAcseSap::setAeQualifierCalling(quint32 qualifier) {
	m_aeQualifierCalling = qualifier;
}

/**
 * Associate to a remote ServerAcseSAP that is listening at the destination address.
 *
 * @param address
 *            remote InetAddress
 * @param port
 *            remote port
 * @param localAddr
 *            local InetAddress
 * @param localPort
 *            local port
 * @param authenticationParameter
 *            an authentication parameter
 * @param apdu
 *            the payload to send with the association request
 * @return the association object
 * @throws IOException
 *             if an error occurs connecting
 */
CAcseAssociation* CClientAcseSap::createAssociate(CConnection* tConnection)
{
	if ( !m_pClientTSap )
	{
		emit signalIllegalClassMember("CClientAcseSap::associate: m_pClientTSap is NULL!");

		return nullptr;
	}

	char local[4] = {1, 1, 1, 1};
	QByteArray SelLocal(local, 4);
	CBerOctetString str(SelLocal);
	CAcseAssociation* pAssoc = new CAcseAssociation(tConnection, str);

	return pAssoc;
}


void CClientAcseSap::startAssociation(CAcseAssociation* pAssoc, QString authenticationParameter, CBerByteArrayOutputStream& apdu)
{
	pAssoc->startAssociation(apdu, authenticationParameter,
				m_SSelRemote, m_SSelLocal, m_PSelRemote, m_ApTitleCalled, m_ApTitleCalling,
				m_aeQualifierCalled, m_aeQualifierCalling);

	return;
}

void CClientAcseSap::setMaxTPDUSizeParam(quint32 maxTPduSizeParam)
{
	if ( !m_pClientTSap )
	{
		emit signalIllegalClassMember("CClientAcseSap::associate: m_pClientTSap is NULL!");
		return;
	}

	m_pClientTSap->setMaxTPDUSizeParam(maxTPduSizeParam);
}

void CClientAcseSap::setMessageTimeout(quint32 messageTimeout)
{
	if ( !m_pClientTSap )
	{
		emit signalIllegalClassMember("CAcseAssociation::associate: m_pClientTSap is NULL!");
		return;
	}

	m_pClientTSap->setMessageTimeout(messageTimeout);
}

void CClientAcseSap::setMessageFragmentTimeout(quint32 messageFragmentTimeout)
{
	if ( !m_pClientTSap )
	{
		emit signalIllegalClassMember("CAcseAssociation::associate: m_pClientTSap is NULL!");
		return;
	}

	m_pClientTSap->setMessageFragmentTimeout(messageFragmentTimeout);
}

