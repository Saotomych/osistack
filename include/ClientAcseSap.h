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
#include "AcseAssociation.h"

class OSISTACK_SHAREDEXPORT CClientAcseSap: public QObject
{

	Q_OBJECT

private:

	QVector<qint32> m_ApTitleCalled; //   { 1, 1, 999, 1, 1 };
	QVector<qint32> m_ApTitleCalling; //  { 1, 1, 999, 1 };
	quint32 m_aeQualifierCalled;  // 12;
	quint32 m_aeQualifierCalling; // 12;

public:

	CClientTSAP* m_pClientTSap;

	static const quint8 P_SEL_DEFAULT[4]; // = { 0, 0, 0, 1 };
	static const quint8 S_SEL_DEFAULT[2]; // = { 0, 1 };
	static const qint32 s_titleCalled[5];
	static const qint32 s_titleCalling[4];

	QByteArray m_PSelRemote; // P_SEL_DEFAULT;
	QByteArray m_PSelLocal; // P_SEL_DEFAULT;
	QByteArray m_SSelRemote; // S_SEL_DEFAULT;
	QByteArray m_SSelLocal; // S_SEL_DEFAULT;

	/**
	 * Use this constructor to create a client ACSE Service Access Point (SAP) that will start connections to remote
	 * ACSE SAPs. Once constructed the AcseSAP contains a public TSAP that can be accessed to set its configuration.
	 */
	CClientAcseSap(CSocketFactory* socketFactory);
	~CClientAcseSap();

	void setApTitleCalled(QVector<qint32>& title);
	void setApTitleCalling(QVector<qint32>& title);
	void setAeQualifierCalled(quint32 qualifier);
	void setAeQualifierCalling(quint32 qualifier);

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
	CAcseAssociation* createAssociate(CConnection* tConnection);
	void startAssociation(CAcseAssociation* pAssoc, QString authenticationParameter, CBerByteArrayOutputStream& apdu);
	void setMaxTPDUSizeParam(quint32 maxTPduSizeParam);
	void setMessageTimeout(quint32 messageTimeout);
	void setMessageFragmentTimeout(quint32 messageFragmentTimeout);

signals:

	// Error signals
	void signalConnectError(QString strErr);
	void signalIllegalClassMember(QString strErr);

};

#endif /* INCLUDE_CLIENTACSESAP_H_ */
