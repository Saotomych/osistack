/*
 * ACSE_apdu.h
 *
 *  Created on: 18 нояб. 2015 г.
 *      Author: alexey
 */

#ifndef INCLUDE_ACSE_ASN1_ACSE_APDU_H_
#define INCLUDE_ACSE_ASN1_ACSE_APDU_H_

#include "osistack_global.h"
#include "AArqApdu.h"
#include "AAreApdu.h"
#include "RLrqApdu.h"
#include "RLreApdu.h"

class OSISTACK_SHAREDEXPORT CAcseApdu: public QObject, public IBerBaseType
{
	Q_OBJECT
	Q_PROPERTY(CBerIdentifier Identifier READ getIdentifier)
	Q_PROPERTY(QByteArray* Code READ getCode)
	Q_PROPERTY(CBerIdentifier IdAarqApdu READ getIdAarqApdu)
	Q_PROPERTY(IBerBaseType* AarqApdu READ getAarqApdu)
	Q_PROPERTY(CBerIdentifier IdAareApdu READ getIdAareApdu)
	Q_PROPERTY(IBerBaseType* AareApdu READ getAareApdu)
	Q_PROPERTY(CBerIdentifier IdRlrqApdu READ getIdRlrqApdu)
	Q_PROPERTY(IBerBaseType* RlrqApdu READ getRlrqApdu)
	Q_PROPERTY(CBerIdentifier IdRlreApdu READ getIdRlreApdu)
	Q_PROPERTY(IBerBaseType* RlreApdu READ getRlreApdu)

	bool is_copy;

protected:

	const CBerIdentifier c_Identifier;

public:

	QByteArray* getCode() { return &m_Code; }

	CBerIdentifier getIdAarqApdu() {return CAArqApdu::getBerIdentifier();}
	CBerIdentifier getIdAareApdu() {return CAAreApdu::getBerIdentifier();}
	CBerIdentifier getIdRlrqApdu() {return CRLrqApdu::getBerIdentifier();}
	CBerIdentifier getIdRlreApdu() {return CRLreApdu::getBerIdentifier();}

	IBerBaseType* getAarqApdu() {return m_pAarqApdu;}
	IBerBaseType* getAareApdu() {return m_pAareApdu;}
	IBerBaseType* getRlrqApdu() {return m_pRlrqApdu;}
	IBerBaseType* getRlreApdu() {return m_pRlreApdu;}

protected:

	inline IBerBaseType* create_object_by_id(const CBerIdentifier& id)
	{
		qDebug() << "INFO: CAcseApdu create member by id = " << id.getCode()->toHex();

		if ( getIdAarqApdu() == id )
			{ m_pAarqApdu = new CAArqApdu(); is_copy = true; return m_pAarqApdu; }
		if ( getIdAareApdu() == id )
			{ m_pAareApdu = new CAAreApdu(); is_copy = true; return m_pAareApdu; }
		if ( getIdRlrqApdu() == id )
			{ m_pRlrqApdu = new CRLrqApdu(); is_copy = true; return m_pRlrqApdu; }
		if ( getIdRlreApdu() == id )
			{ m_pRlreApdu = new CRLreApdu(); is_copy = true; return m_pRlreApdu; }

		return nullptr;
	}

	inline void create_objects(const CAcseApdu& rhs)
	{
		std::unique_ptr<CAArqApdu> p1
				( (rhs.m_pAarqApdu != nullptr) ? new CAArqApdu(*rhs.m_pAarqApdu): nullptr );
		std::unique_ptr<CAAreApdu> p2
				( (rhs.m_pAareApdu != nullptr) ? new CAAreApdu(*rhs.m_pAareApdu): nullptr );
		std::unique_ptr<CRLrqApdu> p3
				( (rhs.m_pRlrqApdu != nullptr) ? new CRLrqApdu(*rhs.m_pRlrqApdu): nullptr );
		std::unique_ptr<CRLreApdu> p4
				( (rhs.m_pRlreApdu != nullptr) ? new CRLreApdu(*rhs.m_pRlreApdu): nullptr );

		m_pAarqApdu = p1.release();
		m_pAareApdu = p2.release();
		m_pRlrqApdu = p3.release();
		m_pRlreApdu = p4.release();
	}

	inline void delete_all_objects()
	{
		if (is_copy)
		{
			delete m_pAarqApdu;
			delete m_pAareApdu;
			delete m_pRlrqApdu;
			delete m_pRlreApdu;
		}
	}

protected:

	QByteArray m_Code;

	CAArqApdu* m_pAarqApdu;
	CAAreApdu* m_pAareApdu;
	CRLrqApdu* m_pRlrqApdu;
	CRLreApdu* m_pRlreApdu;

public:

	ASN1_CODEC(CUnionStorage)

	CBerIdentifier getIdentifier() { return c_Identifier; }

	static quint32 s_metaTypeIdentifier;

	static CBerIdentifier getBerIdentifier()
	{
		return CBerIdentifier();
	}

	CAcseApdu():
		is_copy(false),
		c_Identifier(),
		m_pAarqApdu(nullptr),
		m_pAareApdu(nullptr),
		m_pRlrqApdu(nullptr),
		m_pRlreApdu(nullptr)
	{}

	CAcseApdu(
		CAArqApdu* pAarqApdu,
		CAAreApdu* pAareApdu,
		CRLrqApdu* pRlrqApdu,
		CRLreApdu* pRlreApdu
	):
		is_copy(false),
		c_Identifier(),
		m_pAarqApdu(pAarqApdu),
		m_pAareApdu(pAareApdu),
		m_pRlrqApdu(pRlrqApdu),
		m_pRlreApdu(pRlreApdu)
	{}

	CAcseApdu(const CAcseApdu& rhs): QObject(),
		c_Identifier()
	{
		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;
	}

	CAcseApdu& operator=(const CAcseApdu& rhs)
	{
		if (this == &rhs) return *this;

		delete_all_objects();

		create_objects(rhs);

		m_Code = rhs.m_Code;
		is_copy = true;

		return *this;
	}

	bool operator!=(const CAcseApdu& rhs)
	{
		if (this == &rhs) return false;

		if ( notEqualsPointersAndValues<CAArqApdu>(m_pAarqApdu, rhs.m_pAarqApdu) ) return true;
		if ( notEqualsPointersAndValues<CAAreApdu>(m_pAareApdu, rhs.m_pAareApdu) ) return true;
		if ( notEqualsPointersAndValues<CRLrqApdu>(m_pRlrqApdu, rhs.m_pRlrqApdu) ) return true;
		if ( notEqualsPointersAndValues<CRLreApdu>(m_pRlreApdu, rhs.m_pRlreApdu) ) return true;

		return false;
	}

	virtual ~CAcseApdu()
	{
		delete_all_objects();
	}

};

Q_DECLARE_METATYPE(CAcseApdu*)

#endif /* INCLUDE_ACSE_ASN1_ACSE_APDU_H_ */
