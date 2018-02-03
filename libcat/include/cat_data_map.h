#ifndef __CAT_DATA_MAP_H__
#define __CAT_DATA_MAP_H__

#include <stdint.h>
#include <stddef.h>
#include <string>
#include <unordered_map>
#include <initializer_list>
#include "cat_data_buffer.h"
#include "cat_data_serialize.h"

namespace cat {
// ----------------------------------------------------------------------------
//! Serializable map
class DataMap {
public:
    DataMap() = default;
    DataMap(const DataMap& o);
    DataMap(DataMap&& o);
    DataMap& operator=(const DataMap& o);
    DataMap& operator=(DataMap&& o);
    DataMap(std::initializer_list<DataMap> list);

    void clear();
    DataMap& operator[](const std::string& key);

    DataMap(int v);
    DataMap(long v);
    DataMap(double v);
    DataMap(const std::string& v);
    DataMap(const char* v);
    int get_int() const;
    long get_long() const;
    double get_double() const;
    const std::string& get_string() const;
    const char* get_cstring() const;

    bool has(const std::string& key) const;

    bool save(Buffer* buffer, size_t maxsize) const;
    bool load(const Buffer& buffer);

private:
    bool save(BufferWriter& writer) const;
    bool load(BufferReader& reader);

private:
    std::string m_string;
    std::unordered_map<std::string, DataMap> m_map;
};
// ----------------------------------------------------------------------------
} // namespace cat

#endif // __CAT_DATA_MAP_H__
