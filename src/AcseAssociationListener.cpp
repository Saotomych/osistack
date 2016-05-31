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
	qDebug() << "CAcseAssociationListener constructor";
}

void CAcseAssociationListener::slotAcseTSduReady(CAcseAssociation* that)
{
	qDebug() << "CAcseAssociationListener::slotTSduReady";

	emit signalAcseTSduReady(that);
}

void CAcseAssociationListener::slotAcseCnReady(CAcseAssociation* that)
{
	qDebug() << "CAcseAssociationListener::slotCRReady";

	emit signalAcseCnReady(that);
}

void CAcseAssociationListener::slotAcseIOError(QString strErr)
{
	qDebug() << "CAcseAssociationListener::slotIOError" << strErr;

	emit signalAcseIOError(strErr);
}

void CAcseAssociationListener::slotAcseAssociationOpen(CAcseAssociation* that)
{
	qDebug() << "CAcseAssociationListener::slotClientConnected";

	emit signalAcseConnected(that);
}

void CAcseAssociationListener::slotAcseAssociationClosed(CAcseAssociation* that)
{
	qDebug() << "CAcseAssociationListener::slotClientDisconnected";

	emit signalAcseDisconnected(that);
}



