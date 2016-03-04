/*
 * AcseAssociationListener.cpp
 *
 *  Created on: 29 февр. 2016 г.
 *      Author: alex
 */

#include "AcseAssociationListener.h"

CAcseAssociationListener::CAcseAssociationListener(QObject *parent) :
    QObject(parent)
{
}

void CAcseAssociationListener::slotAcseTSduReady(const CConnection* that)
{
	qDebug() << "CAcseAssociationListener::slotTSduReady";

	emit signalAcseTSduReady(that);
}

void CAcseAssociationListener::slotAcseCRReady(const CConnection* that)
{
	qDebug() << "CAcseAssociationListener::slotCRReady";

	emit signalAcseCRReady(that);
}

void CAcseAssociationListener::slotAcseIOError(QString strErr)
{
	qDebug() << "CAcseAssociationListener::slotIOError" << strErr;

	emit signalAcseIOError(strErr);
}

void CAcseAssociationListener::slotAcseClientConnected(const CConnection* that)
{
	qDebug() << "CAcseAssociationListener::slotClientConnected";

	emit signalAcseConnected(that);
}

void CAcseAssociationListener::slotAcseClientDisconnected(const CConnection* that)
{
	qDebug() << "CAcseAssociationListener::slotClientDisconnected";

	emit signalAcseDisconnected(that);
}



