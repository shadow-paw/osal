#include "cat_data_map.h"
#include "cat_util_log.h"

using namespace cat;

// ----------------------------------------------------------------------------
DataMap::DataMap(const DataMap& o) {
    m_string = o.m_string;
    m_map = o.m_map;
}
DataMap::DataMap(DataMap&& o) {
    m_string = std::move(o.m_string);
    m_map = std::move(o.m_map);
}
DataMap& DataMap::operator=(const DataMap& o) {
    m_string = o.m_string;
    m_map = o.m_map;
    return *this;
}
DataMap& DataMap::operator=(DataMap&& o) {
    m_string = std::move(o.m_string);
    m_map = std::move(o.m_map);
    return *this;
}
// ----------------------------------------------------------------------------
DataMap::DataMap(std::initializer_list<DataMap> list) {
    for (auto it = list.begin(); it!=list.end(); ) {
        auto value = std::next(it);
        if (value == list.end()) {
            Logger::e("libcat", "DataMap incomplete initializer_list");
            break;
        }
        m_map.emplace(it->get_string(), *value);
        std::advance(it, 2);
    }
}
// ----------------------------------------------------------------------------
void DataMap::clear() {
    m_map.clear();
}
// ----------------------------------------------------------------------------
DataMap& DataMap::operator[](const std::string& key) {
    return m_map[key];
}
// ----------------------------------------------------------------------------
DataMap::DataMap(int v) {
    m_string = std::to_string(v);
}
DataMap::DataMap(long v) {
    m_string = std::to_string(v);
}
DataMap::DataMap(double v) {
    m_string = std::to_string(v);
}
DataMap::DataMap(const std::string& v) {
    m_string = v;
}
DataMap::DataMap(const char* v) {
    m_string = v;
}
// ----------------------------------------------------------------------------
bool DataMap::has(const std::string& key) const {
    return m_map.find(key) != m_map.end();
}
// ----------------------------------------------------------------------------
int DataMap::get_int() const {
    try {
        return std::stoi(m_string);
    } catch (std::exception e) {
        return 0;
    }
}
long DataMap::get_long() const {
    try {
        return std::stol(m_string);
    } catch (std::exception e) {
        return 0;
    }
}
double DataMap::get_double() const {
    try {
        return std::stod(m_string);
    } catch (std::exception e) {
        return 0.0;
    }
}
const std::string& DataMap::get_string() const {
    return m_string;
}
const char* DataMap::get_cstring() const {
    return m_string.c_str();
}
// ----------------------------------------------------------------------------
bool DataMap::save(Buffer* buffer, size_t maxsize) const {
    if (!buffer->realloc(maxsize)) return false;
    BufferWriter writer(*buffer);
    if (!save(writer)) return false;
    buffer->shrink(writer.cursor());
    return true;
}
bool DataMap::save(BufferWriter& writer) const {
    if (!writer.put(m_string)) return false;
    if (!writer.put((uint16_t)m_map.size())) return false;
    for (auto it = m_map.begin(); it != m_map.end(); it++) {
        if (!writer.put(it->first)) return false;
        if (!it->second.save(writer)) return false;
    } return true;
}
bool DataMap::load(const Buffer& buffer) {
    BufferReader reader(buffer);
    return load(reader);
}
bool DataMap::load(BufferReader& reader) {
    uint16_t count = 0;
    if (!reader.get(&m_string)) return false;
    if (!reader.get(&count)) return false;
    for (uint16_t i = 0; i < count; i++) {
        std::string key;
        DataMap value;
        if (!reader.get(&key)) return false;
        if (!value.load(reader)) return false;
        m_map.emplace(key, value);
    } return true;
}
// ----------------------------------------------------------------------------
