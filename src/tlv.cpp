#include "tlv.h"

namespace TLV {

int TlvString::dump(char* buffer, int* pSize) const
{
    if (*pSize < value_.length() + 2) {
        *pSize = 0;
        return 0;
    }

    buffer[0] = (char)tag_;
    buffer[1] = (char)len_;

    std::sprintf(buffer+2, "%s", value_.c_str());
    *pSize = len_ + 2;
    return *pSize;
}
    
//-----------------------------------------

int TlvInteger::dump(char* buffer, int* pSize) const
{
    if (*pSize < 6) {
        *pSize = 0;
        return 0;
    }

    buffer[0] = (char)tag_;
    buffer[1] = (char)len_;
    buffer[2] = value_ & 0xFF;
    buffer[3] = (value_ >> 8) & 0xFF;
    buffer[4] = (value_ >> 16) & 0xFF;
    buffer[5] = (value_ >> 24) & 0xFF;

    return *pSize = 6;

}
    
//-----------------------------------------

int TlvBoolean::dump(char* buffer, int* pSize) const
{
    if (*pSize < 1) {
        return 0;
    }

    buffer[0] = (char)tag_;
    return *pSize = 1;
}


};