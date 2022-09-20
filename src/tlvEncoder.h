#ifndef _TLV_ENCODER_H_
#define _TLV_ENCODER_H_

#include <apr.h>
#include <apr_general.h>
#include <apr_file_io.h>
#include "IEncoder.h"

namespace TLV {
    
class Tlv;

class TlvEncoder : public IEncoder {
private:
    TlvEncoder() {}
public:
    TlvEncoder(apr_pool_t* pool) : pool_{pool} {}

    virtual int open(const char* name) override;
    virtual void close() override;
    virtual void encode(TLV::TlvBase* tlv) override;

private:
    apr_file_t* file_;
    apr_pool_t* pool_;
    char buffer[1024];
};

};


#endif // _TLV_ENCODER_H_
