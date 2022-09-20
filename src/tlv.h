#ifndef _TLV_H_
#define _TLV_H_

#include <string>

namespace TLV {

class TlvBase {
public:
    enum TlvTag { 
        INTEGER = 1, 
        STRING,
        BOOLEAN_TRUE, 
        BOOLEAN_FALSE, 
    };
protected:
    TlvBase(int tag, int len) :
        tag_{tag},
        len_{len}
    {}
public:
    /**
     * @brief Builds byte array in TLV format
     * 
     * @param buffer Byte array that will be used 
     * @param pSize Byte array buffer size
     * @return int Returns structured byte array size
     */
    virtual int dump(char* buffer, int* pSize) const = 0;
    virtual int getTag() { return tag_; }
    virtual int getLen() { return len_; }

protected:
    int tag_;
    int len_;
};

//-----------------------------------------

class TlvInteger : public TlvBase {
public:
    TlvInteger(int val) :
        TlvBase(INTEGER, sizeof(int)),
        value_{val}
    {}

    virtual int dump(char* buffer, int* pSize) const override;

private:
    int value_;
};

//-----------------------------------------

class TlvString : public TlvBase {
public:
    TlvString(const std::string& val) :
        TlvBase(STRING, val.length()),
        value_{val}
    {}

    virtual int dump(char* buffer, int* pSize) const override;

private:
    std::string value_;
};

//-----------------------------------------

class TlvBoolean : public TlvBase {
public:
    TlvBoolean(bool val) :
        TlvBase(val ? BOOLEAN_TRUE : BOOLEAN_FALSE, 0),
        value_{val}
    {}

    virtual int dump(char* buffer, int* pSize) const override;

private:
    bool value_;
};

//-----------------------------------------

};

#endif // _TLV_H_