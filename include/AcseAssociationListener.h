/*
 * AcseAssociationListener.h
 *
 *  Created on: 26 февр. 2016 г.
 *      Author: alex
 */

#ifndef INCLUDE_ACSEASSOCIATIONLISTENER_H_
#define INCLUDE_ACSEASSOCIATIONLISTENER_H_

#include "osistack_global.h"
#include "AcseAssociation.h"

class OSISTACK_SHAREDEXPORT CAcseAssociationListener: public QObject
{
	Q_OBJECT

public:
    explicit CAcseAssociationListener(QObject *parent = 0);

signals:
	void signalAcseConnected(CAcseAssociation* that);
	void signalAcseDisconnected(CAcseAssociation* that);
	void signalAcseTSduReady(CAcseAssociation* that);
	void signalAcseCnReady(CAcseAssociation* that);
	void signalAcseIOError(QString str);

public slots:
	void slotAcseClientConnected(CAcseAssociation* that);
	void slotAcseClientDisconnected(CAcseAssociation* that);
	void slotAcseTSduReady(CAcseAssociation* that);
	void slotAcseCnReady(CAcseAssociation* that);
	void slotAcseIOError(QString strErr);

};


#endif /* INCLUDE_ACSEASSOCIATIONLISTENER_H_ */
