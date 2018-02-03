#ifndef __CAT_DATA_SERIALIZE_H__
#define __CAT_DATA_SERIALIZE_H__

#include <stdint.h>
#include <string>
#include "cat_data_buffer.h"

namespace cat {
// ----------------------------------------------------------------------------
class SerializableWriter {
public:
    virtual bool put(uint8_t v) = 0;
    virtual bool put(uint16_t v) = 0;
    virtual bool put(uint32_t v) = 0;
    virtual bool put(uint64_t v) = 0;
    virtual bool put(const std::string& v) = 0;
};
class SerializableReader {
    virtual bool get(uint8_t* des) = 0;
    virtual bool get(uint16_t* des) = 0;
    virtual bool get(uint32_t* des) = 0;
    virtual bool get(uint64_t* des) = 0;
    virtual bool get(std::string* des) = 0;
};
// ----------------------------------------------------------------------------
class BufferWriter : public SerializableWriter {
public:
    BufferWriter(Buffer& buffer);
    virtual bool put(uint8_t v);
    virtual bool put(uint16_t v);
    virtual bool put(uint32_t v);
    virtual bool put(uint64_t v);
    virtual bool put(const std::string& v);

    size_t cursor() const { return m_cursor; }
private:
    Buffer* m_buffer;
    size_t m_cursor;
};
class BufferReader : public SerializableReader {
public:
    BufferReader(const Buffer& buffer);
    virtual bool get(uint8_t* des);
    virtual bool get(uint16_t* des);
    virtual bool get(uint32_t* des);
    virtual bool get(uint64_t* des);
    virtual bool get(std::string* des);

    size_t cursor() const { return m_cursor; }
private:
    const Buffer* m_buffer;
    size_t m_cursor;
};
// ----------------------------------------------------------------------------
} // namespace cat

#endif // __CAT_DATA_SERIALIZE_H__
