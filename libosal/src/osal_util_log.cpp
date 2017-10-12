// ----------------------------------------------------------------------------
// Windows
// ----------------------------------------------------------------------------
#if defined(PLATFORM_WIN32) || defined(PLATFORM_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#include <stdarg.h>
#include <stdio.h>
#include "osal_util_log.h"

using namespace osal;

// ----------------------------------------------------------------------------
void Logger::d(const char* tag, const char* fmt, ...) {
    char buf[1024 + 16];
    TCHAR wbuf[1024 + 16];
    va_list va;
    va_start(va, fmt);
    size_t len = vsnprintf(buf, sizeof(buf), fmt, va);
    buf[len] = '\n'; buf[len + 1] = 0;
    MultiByteToWideChar(CP_UTF8, 0, buf, -1, wbuf, 1024);
    OutputDebugString(wbuf);
    va_end(va);
}
// ----------------------------------------------------------------------------
void Logger::e(const char* tag, const char* fmt, ...) {
    char buf[1024 + 16];
    TCHAR wbuf[1024 + 16];
    va_list va;
    va_start(va, fmt);
    size_t len = vsnprintf(buf, sizeof(buf), fmt, va);
    buf[len] = '\n'; buf[len + 1] = 0;
    MultiByteToWideChar(CP_UTF8, 0, buf, -1, wbuf, 1024);
    OutputDebugString(wbuf);
    va_end(va);
}
// ----------------------------------------------------------------------------
// MAC
// ----------------------------------------------------------------------------
#elif defined(PLATFORM_MAC)
#include "osal_util_log.h"
#include <stdio.h>
#include <stdarg.h>

using namespace osal;

// ----------------------------------------------------------------------------
void Logger::d(const char* tag, const char* fmt, ...) {
    va_list va;
    va_start(va, fmt);
    vprintf(fmt, va);
    va_end(va);
    printf("\n");
}
// ----------------------------------------------------------------------------
void Logger::e(const char* tag, const char* fmt, ...) {
    va_list va;
    va_start(va, fmt);
    vprintf(fmt, va);
    va_end(va);
    printf("\n");
}
// ----------------------------------------------------------------------------
// IOS
// ----------------------------------------------------------------------------
#elif defined(PLATFORM_IOS)
#include "osal_util_log.h"
#include <stdio.h>
#include <stdarg.h>

using namespace osal;

// ----------------------------------------------------------------------------
void Logger::d(const char* tag, const char* fmt, ...) {
    va_list va;
    va_start(va, fmt);
    vfprintf(stderr, fmt, va);
    va_end(va);
    printf("\n");
}
// ----------------------------------------------------------------------------
void Logger::e(const char* tag, const char* fmt, ...) {
    va_list va;
    va_start(va, fmt);
    vfprintf(stderr, fmt, va);
    va_end(va);
    printf("\n");
}
// ----------------------------------------------------------------------------
// Android
// ----------------------------------------------------------------------------
#elif defined(PLATFORM_ANDROID)
#include "osal_util_log.h"
#include <android/log.h>

using namespace osal;

// ----------------------------------------------------------------------------
void Logger::d(const char* tag, const char* fmt, ...) {
    va_list va;
    va_start(va, fmt);
    __android_log_vprint(ANDROID_LOG_INFO, tag, fmt, va);
    va_end(va);
}
// ----------------------------------------------------------------------------
void Logger::e(const char* tag, const char* fmt, ...) {
    va_list va;
    va_start(va, fmt);
    __android_log_vprint(ANDROID_LOG_ERROR, tag, fmt, va);
    va_end(va);
}
// ----------------------------------------------------------------------------
#else
  #error Not Implemented!
#endif