/*
 * AcseAssociationListener.h
 *
 *  Created on: 26 февр. 2016 г.
 *      Author: alex
 */

#ifndef INCLUDE_ACSEASSOCIATIONLISTENER_H_
#define INCLUDE_ACSEASSOCIATIONLISTENER_H_

#include "osistack_global.h"

class CAcseAssociationListener: public QObject
{
	Q_OBJECT

public:
    explicit CAcseAssociationListener(QObject *parent = 0);

signals:
	void signalAcseConnected(const CConnection* that);
	void signalAcseDisconnected(const CConnection* that);
	void signalAcseTSduReady(const CConnection* that);
	void signalAcseCRReady(const CConnection* that);
	void signalAcseIOError(QString str);

private slots:
	void slotAcseClientConnected(const CConnection* that);
	void slotAcseClientDisconnected(const CConnection* that);
	void slotAcseTSduReady(const CConnection* that);
	void slotAcseCRReady(const CConnection* that);
	void slotAcseIOError(QString strErr);

};


#endif /* INCLUDE_ACSEASSOCIATIONLISTENER_H_ */
