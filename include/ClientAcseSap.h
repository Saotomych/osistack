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

class CServerAcseSap;

class OSISTACK_SHAREDEXPORT CClientAcseSap: public QObject
{

	Q_OBJECT

	friend CServerAcseSap;

private:

	QVector<qint32> m_ApTitleCalled; //   { 1, 1, 999, 1, 1 };
	QVector<qint32> m_ApTitleCalling; //  { 1, 1, 999, 1 };
	quint32 m_aeQualifierCalled;  // 12;
	quint32 m_aeQualifierCalling; // 12;

	CClientTSAP* m_pClientTSap;

	static const quint8 P_SEL_DEFAULT[4]; // = { 0, 0, 0, 1 };
	static const quint8 S_SEL_DEFAULT[2]; // = { 0, 1 };
	static const qint32 s_titleCalled[5];
	static const qint32 s_titleCalling[4];

	QByteArray m_PSelRemote; // P_SEL_DEFAULT;
	QByteArray m_PSelLocal; // P_SEL_DEFAULT;
	QByteArray m_SSelRemote; // S_SEL_DEFAULT;
	QByteArray m_SSelLocal; // S_SEL_DEFAULT;

public:

	/**
	 * @brief Use this constructor to create a client ACSE Service Access Point (SAP) that will start connections to remote ACSE SAPs.
	 * 			Once constructed the AcseSAP contains a public TSAP that can be accessed to set its configuration.
	 *
	 * @param socketFactory
	 * 			is the socket factory getting in the ositransport library
	 */
	CClientAcseSap(CSocketFactory* socketFactory);

	~CClientAcseSap();

	// TODO briefs and params for title and qualifier setters
	/**
	 * @brief
	 * @param title
	 */
	void setApTitleCalled(QVector<qint32>& title);

	/**
	 * @brief
	 * @param title
	 */
	void setApTitleCalling(QVector<qint32>& title);

	/**
	 * @brief
	 * @param qualifier
	 */
	void setAeQualifierCalled(quint32 qualifier);

	/**
	 * @brief
	 * @param qualifier
	 */
	void setAeQualifierCalling(quint32 qualifier);

	/**
	 * @brief Associate to a remote ServerAcseSAP that is listening at the destination address.
	 *
	 * @param tConnection
	 * 			is connection will be attached to the new association
	 *
	 * @return the association object
	 */
	CAcseAssociation* createAssociate(CConnection* tConnection);

	/**
	 * @brief starts association
	 * @param pAssoc
	 * 			association that will be started
	 * @param authenticationParameter
	 * 			authentication string
	 * @param apdu
	 * 			payload parameter
	 */
	void startAssociation(CAcseAssociation* pAssoc, QString authenticationParameter, CBerByteArrayOutputStream& apdu);

	/**
	 * @brief Set the maxTPDUSize. The default maxTPduSize is 65531 (see RFC 1006).
	 * Needs to be set before listening or connecting.
	 *
	 * @param maxTPduSizeParam
	 *            The maximum length is equal to 2^(maxTPduSizeParam) octets. Note that the actual TSDU size that can be
	 *            transfered is equal to TPduSize-3. Default is 65531 octets (see RFC 1006),
	 *            7 >= maxTPduSizeParam <= 16.
	 * @return emit signalIllegalArgument("CClientTSAP::setMaxTPDUSizeParam: parameter is out of bound")
	 *             is argument illegal
	 */
	void setMaxTPDUSizeParam(quint32 maxTPduSizeParam);

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
	 * @brief returns pointer to TSAP client
	 * @return pointer to TSAP client
	 */
	CClientTSAP* getClientTsap()
	{
		return m_pClientTSap;
	}

	/**
	 * @brief creates connection for ACSE client
	 * @param address
	 * 			remote address
	 * @param port
	 * 			remote port
	 * @return new connection for the actual user
	 */
	CConnection* createConnection(QHostAddress& address, qint32 port)
	{
		return m_pClientTSap->createConnection(address, port);
	}

signals:

	// Error signals
	void signalConnectError(QString strErr);
	void signalIllegalClassMember(QString strErr);

};

#endif /* INCLUDE_CLIENTACSESAP_H_ */
