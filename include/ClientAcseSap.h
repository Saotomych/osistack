/*
 * CClientAcseSap.h
 *
 *  Created on: 12 февр. 2016 г.
 *      Author: alex
 */

#ifndef INCLUDE_CLIENTACSESAP_H_
#define INCLUDE_CLIENTACSESAP_H_

#include "osistack_global.h"
#include <clienttsap.h>

class CClientAcseSap: public QObject
{

	Q_OBJECT

private:

	QVector<qint32> m_ApTitleCalled; //   { 1, 1, 999, 1, 1 };
	QVector<qint32> m_ApTitleCalling; //  { 1, 1, 999, 1 };
	quint32 m_aeQualifierCalled;  // 12;
	quint32 m_aeQualifierCalling; // 12;

public:

	CClientTSAP* m_pClientTSap;

	static quint8 P_SEL_DEFAULT[]; // = { 0, 0, 0, 1 };
	static quint8 S_SEL_DEFAULT[]; // = { 0, 1 };

	QByteArray m_PSelRemote; // P_SEL_DEFAULT;
	QByteArray m_PSelLocal; // P_SEL_DEFAULT;
	QByteArray m_SSelRemote; // S_SEL_DEFAULT;
	QByteArray m_SSelLocal; // S_SEL_DEFAULT;

	/**
	 * Use this constructor to create a client ACSE Service Access Point (SAP) that will start connections to remote
	 * ACSE SAPs. Once constructed the AcseSAP contains a public TSAP that can be accessed to set its configuration.
	 */
	CClientAcseSap():
		m_aeQualifierCalled(12),
		m_aeQualifierCalling(12)
	{
		m_pClientTSap = new CClientTSAP();

		m_PSelRemote.push_back((quint8) 0);
		m_PSelRemote.push_back((quint8) 0);
		m_PSelRemote.push_back((quint8) 0);
		m_PSelRemote.push_back((quint8) 1);
		m_PSelLocal = m_PSelRemote;

		m_SSelRemote.push_back((quint8) 0);
		m_SSelRemote.push_back((quint8) 1);
		m_SSelLocal = m_SSelRemote;
	}

	CClientAcseSap(CSocketFactory socketFactory):
		m_aeQualifierCalled(12),
		m_aeQualifierCalling(12)
	{
		m_pClientTSap = new CClientTSAP(socketFactory);

		m_PSelRemote.push_back((quint8) 0);
		m_PSelRemote.push_back((quint8) 0);
		m_PSelRemote.push_back((quint8) 0);
		m_PSelRemote.push_back((quint8) 1);
		m_PSelLocal = m_PSelRemote;

		m_SSelRemote.push_back((quint8) 0);
		m_SSelRemote.push_back((quint8) 1);
		m_SSelLocal = m_SSelRemote;
	}

	~CClientAcseSap()
	{
		delete m_pClientTSap;
	}

	void setApTitleCalled(QVector<qint32>& title) {
		m_ApTitleCalled = title;
	}

	void setApTitleCalling(QVector<qint32>& title) {
		m_ApTitleCalling = title;
	}

	void setAeQualifierCalled(quint32 qualifier) {
		m_aeQualifierCalled = qualifier;
	}

	void setAeQualifierCalling(quint32 qualifier) {
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
	CAcseAssociation associate(QHostAddress address, quint16 port, QHostAddress localAddr, quint16 localPort,
			QString authenticationParameter, CBerByteArrayOutputStream& apdu)
	{
		if ( !m_pClientTSap )
		{
			CAcseAssociation acseAssociation(nullptr, nullptr);
			emit signalIllegalClassMember("CAcseAssociation::associate: m_pClientTSap is NULL!");

			return acseAssociation;
		}

		CAcseAssociation acseAssociation(nullptr, &m_PSelLocal);

		acseAssociation.startAssociation(apdu, address, port, localAddr, localPort, authenticationParameter,
					m_SSelRemote, m_SSelLocal, m_PSelRemote, *m_pClientTSap, m_ApTitleCalled, m_ApTitleCalling,
					m_aeQualifierCalled, m_aeQualifierCalling);

		return acseAssociation;
	}

signals:

	// Error signals
	void signalConnectError(QString strErr);
	void signalIllegalClassMember(QString strErr);

};

#endif /* INCLUDE_CLIENTACSESAP_H_ */
