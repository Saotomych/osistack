#ifndef OSISTACK_GLOBAL_H
#define OSISTACK_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QObject>
#include <QHostAddress>
#include <QMutex>
#include <QDebug>
#include <QLinkedList>
#include <QVector>
#include <QDebug>
#include <QDataStream>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QByteArray>
#include <QBitArray>
#include <QtCore/qmath.h>

#include <exception>
#include <stdexcept>
#include <limits>
#include <memory>

#include "berOctetString.h"
#include "berInteger.h"
#include "berIdentifier.h"
#include "berObjectIdentifier.h"
#include "berBase.h"
#include "storages/berBaseType.h"
#include "storages/decoder.h"
#include "storages/containerStorage.h"
#include "storages/unionStorage.h"

#if defined(OSISTACK_LIBRARY)
#  define OSISTACK_SHAREDEXPORT Q_DECL_EXPORT
#else
#  define OSISTACK_SHAREDEXPORT Q_DECL_IMPORT
#endif

#include "../ASN1/include/DeclareCommonTypes.h"
#include "../ASN1/include/NotEqualsPointer.h"

#endif // OSITRANSPORT_GLOBAL_H
