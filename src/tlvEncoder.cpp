#include "./tlvEncoder.h"
#include <iostream>
#include <apr.h>
#include <apr_general.h>
#include <apr_file_io.h>
#include "tlv.h"


namespace TLV {
    
int TlvEncoder::open(const char* name)
{
    apr_status_t state = apr_file_open(&file_, 
                                        name, 
                                        APR_FOPEN_WRITE | 
                                        APR_FOPEN_CREATE | 
                                        APR_FOPEN_BINARY, 
                                        APR_OS_DEFAULT | 0, 
                                        pool_);
    return state;
}
    
void TlvEncoder::close()
{
    apr_file_close(file_);
}

void TlvEncoder::encode(TLV::TlvBase* tlv)
{
    char buffer[1024] = {0x00};             // Please readme.md JSON object must be small than 1024 bytes length
    int size_ = sizeof(buffer)/sizeof(char);
    
    tlv->dump(buffer, &size_);
    apr_size_t size = size_;
    apr_file_write(file_, (void *)buffer, &size);
}

};
