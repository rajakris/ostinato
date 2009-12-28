#ifndef _STREAM_BASE_H
#define _STREAM_BASE_H

#include <QString>
#include <QLinkedList>

#include "protocol.pb.h"

class AbstractProtocol;
class ProtocolList;
class ProtocolListIterator;

class StreamBase
{
private:
    OstProto::StreamId         *mStreamId;
    OstProto::StreamCore     *mCore;
    OstProto::StreamControl    *mControl;

    ProtocolList            *currentFrameProtocols;

public:
    StreamBase();
    ~StreamBase();

    void protoDataCopyFrom(const OstProto::Stream &stream);
    void protoDataCopyInto(OstProto::Stream &stream) const;

    ProtocolListIterator* createProtocolListIterator() const;

    //! \todo (LOW) should we have a copy constructor??

public:
    enum FrameLengthMode {
        e_fl_fixed,
        e_fl_inc,
        e_fl_dec,
        e_fl_random
    };

    enum SendUnit {
        e_su_packets,
        e_su_bursts
    };

    enum SendMode {
        e_sm_fixed,
        e_sm_continuous
    };

    enum NextWhat {
        e_nw_stop,
        e_nw_goto_next,
        e_nw_goto_id
    };

    bool operator < (const StreamBase &s) const;

    quint32    id();
    bool setId(quint32 id);

#if 0 // FIXME(HI): needed?
    quint32    portId()
        { return mCore->port_id();}
    bool setPortId(quint32 id)
        { mCore->set_port_id(id); return true;}
#endif

    quint32    ordinal();
    bool setOrdinal(quint32    ordinal);

    bool isEnabled() const;
    bool setEnabled(bool flag);

    const QString name() const ;
    bool setName(QString name) ;

    // Frame Length (includes FCS);
    FrameLengthMode    lenMode() const;
    bool setLenMode(FrameLengthMode    lenMode);

    quint16    frameLen(int streamIndex = 0) const;
    bool setFrameLen(quint16 frameLen);

    quint16    frameLenMin() const;
    bool setFrameLenMin(quint16 frameLenMin);

    quint16    frameLenMax() const;
    bool setFrameLenMax(quint16 frameLenMax);

    SendUnit sendUnit() const;
    bool setSendUnit(SendUnit sendUnit);

    SendMode sendMode() const;
    bool setSendMode(SendMode sendMode);

    NextWhat nextWhat() const;
    bool setNextWhat(NextWhat nextWhat);

    quint32 numPackets() const;
    bool setNumPackets(quint32 numPackets);

    quint32 numBursts() const;
    bool setNumBursts(quint32 numBursts);

    quint32 burstSize() const;
    bool setBurstSize(quint32 packetsPerBurst);

    quint32 packetRate() const;
    bool setPacketRate(quint32 packetsPerSec);

    quint32 burstRate() const;
    bool setBurstRate(quint32 burstsPerSec);

    bool isFrameVariable() const;
    int frameValue(uchar *buf, int bufMaxSize, int n) const;
};

#endif
