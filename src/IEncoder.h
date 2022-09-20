#ifndef _IENCODER_H_
#define _IENCODER_H_

namespace TLV {

class TlvBase;

class IEncoder {
public:
    virtual int open(const char* name) = 0;
    virtual void close() = 0;
    virtual void encode(TLV::TlvBase* tlv) = 0;
};

};

#endif // _IENCODER_H_
