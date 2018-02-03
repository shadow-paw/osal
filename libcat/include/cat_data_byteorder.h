#ifndef __CAT_DATA_BYTEORDER_H__
#define __CAT_DATA_BYTEORDER_H__

#include <stdint.h>
// ----------------------------------------------------------------------------
#if defined(PLATFORM_WIN32) || defined(PLATFORM_WIN64)
  #define CAT_ENDIANLITTLE
#elif defined (PLATFORM_LINUX) || defined(PLATFORM_ANDROID)
  #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define CAT_ENDIANLITTLE
  #else
    #define CAT_ENDIANBIG
  #endif
#elif defined(PLATFORM_MAC)
  #if defined(__i386__) || defined(__x86_64__)
    #define CAT_ENDIANLITTLE
  #elif defined(__ppc__)
    #define CAT_ENDIANBIG
  #endif
#elif defined(PLATFORM_IOS)
  #define CAT_ENDIANLITTLE
#else
  #error Not Implemented!
#endif

#if defined(PLATFORM_WIN32) || defined(PLATFORM_WIN64)
  #include <stdlib.h>
  #define CAT_SWAP16(x) _byteswap_ushort(x)
  #define CAT_SWAP32(x) _byteswap_ulong(x)
  #define CAT_SWAP64(x) _byteswap_uint64(x)
#else
  #define CAT_SWAP16(x) __builtin_bswap16(x)
  #define CAT_SWAP32(x) __builtin_bswap32(x)
  #define CAT_SWAP64(x) __builtin_bswap64(x)
#endif

namespace cat {
// ----------------------------------------------------------------------------
class ByteOrder {
public:
    static uint16_t htoel16(uint16_t v) {
    #ifdef CAT_ENDIANLITTLE
        return v;
    #else
        return CAT_SWAP16(v);
    #endif
    }
    static uint32_t htoel32(uint32_t v) {
    #ifdef CAT_ENDIANLITTLE
        return v;
    #else
        return CAT_SWAP32(v);
    #endif
    }
    static uint64_t htoel64(uint64_t v) {
    #ifdef CAT_ENDIANLITTLE
        return v;
    #else
        return CAT_SWAP64(v);
    #endif
    }
    // ------------------------------------------------------------------------
    static uint16_t eltoh16(uint16_t v) {
    #ifdef CAT_ENDIANLITTLE
        return v;
    #else
        return CAT_SWAP16(v);
    #endif
    }
    static uint32_t eltoh32(uint32_t v) {
    #ifdef CAT_ENDIANLITTLE
        return v;
    #else
        return CAT_SWAP32(v);
    #endif
    }
    static uint64_t eltoh64(uint64_t v) {
    #ifdef CAT_ENDIANLITTLE
        return v;
    #else
        return CAT_SWAP64(v);
    #endif
    }
    // ------------------------------------------------------------------------
    static uint16_t hton16(uint16_t v) {
    #ifdef CAT_ENDIANLITTLE
        return CAT_SWAP16(v);
    #else
        return v;
    #endif
    }
    static uint32_t hton32(uint32_t v) {
    #ifdef CAT_ENDIANLITTLE
        return CAT_SWAP32(v);
    #else
        return v;
    #endif
    }
    static uint64_t hton64(uint64_t v) {
    #ifdef CAT_ENDIANLITTLE
        return CAT_SWAP64(v);
    #else
        return v;
    #endif
    }
    // ------------------------------------------------------------------------
    static uint16_t ntoh16(uint16_t v) {
    #ifdef CAT_ENDIANLITTLE
        return CAT_SWAP16(v);
    #else
        return v;
    #endif
    }
    static uint32_t ntoh32(uint32_t v) {
    #ifdef CAT_ENDIANLITTLE
        return CAT_SWAP32(v);
    #else
        return v;
    #endif
    }
    static uint64_t ntoh64(uint64_t v) {
    #ifdef CAT_ENDIANLITTLE
        return CAT_SWAP64(v);
    #else
        return v;
    #endif
    }
};
// ----------------------------------------------------------------------------

#undef CAT_SWAP16
#undef CAT_SWAP32
#undef CAT_SWAP64
#undef CAT_ENDIANLITTLE
#undef CAT_ENDIANBIG
// -----------------------------------------------------------
} // namespace cat

#endif // __MEERKAT2_BYTEORDER_H__


