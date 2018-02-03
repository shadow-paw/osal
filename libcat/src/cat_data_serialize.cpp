#include "cat_data_serialize.h"
#include "cat_data_byteorder.h"
#include <string.h>

using namespace cat;

// ----------------------------------------------------------------------------
// BufferWriter
// ----------------------------------------------------------------------------
BufferWriter::BufferWriter(Buffer& buffer) {
    m_buffer = &buffer;
    m_cursor = 0;
}
// ----------------------------------------------------------------------------
bool BufferWriter::put(uint8_t v) {
    if (m_buffer->size() < m_cursor + sizeof(v)) return false;
    m_buffer->ptr()[m_cursor] = (uint8_t)v;
    m_cursor += sizeof(v);
    return true;
}
// ----------------------------------------------------------------------------
bool BufferWriter::put(uint16_t v) {
    if (m_buffer->size() < m_cursor + sizeof(v)) return false;
    v = ByteOrder::htoel16(v);
    memcpy(m_buffer->ptr() + m_cursor, &v, sizeof(v));
    m_cursor += sizeof(v);
    return true;
}
// ----------------------------------------------------------------------------
bool BufferWriter::put(uint32_t v) {
    if (m_buffer->size() < m_cursor + sizeof(v)) return false;
    v = ByteOrder::htoel32(v);
    memcpy(m_buffer->ptr() + m_cursor, &v, sizeof(v));
    m_cursor += sizeof(v);
    return true;
}
// ----------------------------------------------------------------------------
bool BufferWriter::put(uint64_t v) {
    if (m_buffer->size() < m_cursor + sizeof(v)) return false;
    v = ByteOrder::htoel64(v);
    memcpy(m_buffer->ptr() + m_cursor, &v, sizeof(v));
    m_cursor += sizeof(v);
    return true;
}
// ----------------------------------------------------------------------------
bool BufferWriter::put(const std::string& v) {
    uint32_t len = (uint32_t)v.length();
    if (m_buffer->size() < m_cursor + sizeof(len) + len) return false;
    uint32_t len_el = ByteOrder::htoel32(len);
    memcpy(m_buffer->ptr() + m_cursor, &len_el, sizeof(len_el));
    memcpy(m_buffer->ptr() + m_cursor + sizeof(len), v.c_str(), len);
    m_cursor += len + sizeof(len_el);
    return true;
}
// ----------------------------------------------------------------------------
// BufferReader
// ----------------------------------------------------------------------------
BufferReader::BufferReader(const Buffer& buffer) {
    m_buffer = &buffer;
    m_cursor = 0;
}
// ----------------------------------------------------------------------------
bool BufferReader::get(uint8_t* des) {
    if (m_buffer->size() < m_cursor + sizeof(*des)) return false;
    *des = m_buffer->ptr()[m_cursor];
    m_cursor ++;
    return true;
}
// ----------------------------------------------------------------------------
bool BufferReader::get(uint16_t* des) {
    uint16_t temp;
    if (m_buffer->size() < m_cursor + sizeof(*des)) return false;
    memcpy(&temp, m_buffer->ptr() + m_cursor, sizeof(temp));
    *des = ByteOrder::eltoh16(temp);
    m_cursor+= sizeof(temp);
    return true;
}
// ----------------------------------------------------------------------------
bool BufferReader::get(uint32_t* des) {
    uint32_t temp;
    if (m_buffer->size() < m_cursor + sizeof(*des)) return false;
    memcpy(&temp, m_buffer->ptr() + m_cursor, sizeof(temp));
    *des = ByteOrder::eltoh32(temp);
    m_cursor += sizeof(temp);
    return true;
}
// ----------------------------------------------------------------------------
bool BufferReader::get(uint64_t* des) {
    uint64_t temp;
    if (m_buffer->size() < m_cursor + sizeof(*des)) return false;
    memcpy(&temp, m_buffer->ptr() + m_cursor, sizeof(temp));
    *des = ByteOrder::eltoh64(temp);
    m_cursor += sizeof(temp);
    return true;
}
// ----------------------------------------------------------------------------
bool BufferReader::get(std::string* des) {
    uint32_t len;
    if (m_buffer->size() < m_cursor + sizeof(len)) return false;
    memcpy(&len, m_buffer->ptr() + m_cursor, sizeof(len));
    len = ByteOrder::eltoh32(len);
    if (m_buffer->size() < m_cursor + sizeof(len) + len) return false;
    *des = std::string((char*)(m_buffer->ptr() + m_cursor + sizeof(len)), (size_t)len);
    m_cursor += sizeof(len) + len;
    return true;
}
// ----------------------------------------------------------------------------
