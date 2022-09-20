#include <iostream>
#include <gtest/gtest.h>
#include "tlv.h"

TEST(TlvTest, TlvInteger) {
    TLV::TlvInteger t(1);
    EXPECT_EQ(TLV::TlvBase::INTEGER, t.getTag());
    EXPECT_EQ(4, t.getLen());
}

TEST(TlvTest, TlvInteger_dump_size_ok) {
    TLV::TlvInteger t(1);
    char tmp[256] = {0x00};
    int size = sizeof(tmp)/sizeof(char);
    int ret = t.dump(tmp, &size);
    EXPECT_EQ(6, size);
    EXPECT_EQ(6, ret);
}

TEST(TlvTest, TlvInteger_dump_ok) {
    int value = 120;
    TLV::TlvInteger t(value);
    char tmp[256] = {0x00};
    int size = sizeof(tmp)/sizeof(char);
    int ret = t.dump(tmp, &size);
    EXPECT_EQ(6, size);
    EXPECT_EQ(6, ret);

    // There must be an array comparision, I did byte by byte
    EXPECT_EQ(TLV::TlvBase::INTEGER, tmp[0]); // tag
    EXPECT_EQ(4, tmp[1]); // len
    EXPECT_EQ(((value >>  0) & 0xFF), tmp[2]); // Integer value ...
    EXPECT_EQ(((value >>  8) & 0xFF), tmp[3]); // Integer value ...
    EXPECT_EQ(((value >> 16) & 0xFF), tmp[4]); // Integer value ...
    EXPECT_EQ(((value >> 24) & 0xFF), tmp[5]); // Integer value ...
    
}

TEST(TlvTest, TlvInteger_dump_buffer_error) {
    TLV::TlvInteger t(2);
    char tmp[2] = {0x00};
    int size = sizeof(tmp)/sizeof(char);
    int ret = t.dump(tmp, &size);
    EXPECT_EQ(0, size);
    EXPECT_EQ(0, ret);
}

//--------------------------------------

TEST(TlvTest, TlvString) {
    TLV::TlvString t("Hello");
    EXPECT_EQ(TLV::TlvBase::STRING, t.getTag());
    EXPECT_EQ(5, t.getLen());
}

TEST(TlvTest, TlvString_dump_size_ok) {
    TLV::TlvString t("HELLO");
    char tmp[256] = {0x00};
    int size = sizeof(tmp)/sizeof(char);
    int ret = t.dump(tmp, &size);
    EXPECT_EQ(7, size);
    EXPECT_EQ(7, ret);
}

TEST(TlvTest, TlvString_dump_ok) {
    TLV::TlvString t("HELLO WORLD");
    char tmp[256] = {0x00};
    int size = sizeof(tmp)/sizeof(char);
    int ret = t.dump(tmp, &size);
    EXPECT_EQ(13, size);
    EXPECT_EQ(13, ret);

    // There must be an array comparision, I did byte by byte
    EXPECT_EQ(TLV::TlvBase::STRING, tmp[0]); // tag
    EXPECT_EQ(11, tmp[1]); // len
    EXPECT_EQ('H', tmp[2]);
    EXPECT_EQ('E', tmp[3]);
    EXPECT_EQ('L', tmp[4]);
    EXPECT_EQ('L', tmp[5]);
    EXPECT_EQ('O', tmp[6]);
    EXPECT_EQ(' ', tmp[7]);
    EXPECT_EQ('W', tmp[8]);
    EXPECT_EQ('O', tmp[9]);
    EXPECT_EQ('R', tmp[10]);
    EXPECT_EQ('L', tmp[11]);
    EXPECT_EQ('D', tmp[12]);
}

TEST(TlvTest, TlvString_dump_buffer_error) {
    TLV::TlvString t("DEADBEEF");
    char tmp[2] = {0x00};
    int size = sizeof(tmp)/sizeof(char);
    int ret = t.dump(tmp, &size);
    EXPECT_EQ(0, size);
    EXPECT_EQ(0, ret);
}

//-------------------------------
TEST(TlvTest, TlvBooleanTrue) {
    TLV::TlvBoolean t(true);
    EXPECT_EQ(TLV::TlvBase::BOOLEAN_TRUE, t.getTag());
    EXPECT_EQ(0, t.getLen()); // No length. Read readme.md
}

TEST(TlvTest, TlvBooleanFalse) {
    TLV::TlvBoolean t(false);
    EXPECT_EQ(TLV::TlvBase::BOOLEAN_FALSE, t.getTag());
    EXPECT_EQ(0, t.getLen()); // No length. Read readme.md
}

TEST(TlvTest, TlvBoolean_dump_size_ok) {
    TLV::TlvBoolean t(true);
    char tmp[256] = {0x00};
    int size = sizeof(tmp)/sizeof(char);
    int ret = t.dump(tmp, &size);
    EXPECT_EQ(1, size);
    EXPECT_EQ(1, ret);
}

TEST(TlvTest, TlvBooleanTrue_dump_ok) {
    TLV::TlvBoolean t(true);
    char tmp[256] = {0x00};
    int size = sizeof(tmp)/sizeof(char);
    int ret = t.dump(tmp, &size);
    EXPECT_EQ(1, size);
    EXPECT_EQ(1, ret);

    EXPECT_EQ(TLV::TlvBase::BOOLEAN_TRUE, tmp[0]); // tag    
}

TEST(TlvTest, TlvBooleanFalse_dump_ok) {
    TLV::TlvBoolean t(false);
    char tmp[256] = {0x00};
    int size = sizeof(tmp)/sizeof(char);
    int ret = t.dump(tmp, &size);
    EXPECT_EQ(1, size);
    EXPECT_EQ(1, ret);

    EXPECT_EQ(TLV::TlvBase::BOOLEAN_FALSE, tmp[0]); // tag    
}

TEST(TlvTest, TlvBoolean_dump_buffer_error) {
    TLV::TlvBoolean t(true);
    int size = 0;
    int ret = t.dump(nullptr, &size);
    EXPECT_EQ(0, size);
    EXPECT_EQ(0, ret);
}

