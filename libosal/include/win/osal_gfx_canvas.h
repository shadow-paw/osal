#ifndef __OSAL_GFX_CANVAS_WIN_H__
#define __OSAL_GFX_CANVAS_WIN_H__

#include <stdint.h>
#include "osal_platform.h"
#include "osal_type.h"
#include "osal_gfx_type.h"
#include "osal_gfx_tex.h"

namespace osal { namespace gfx {
// ----------------------------------------------------------------------------
class DrawableCanvas {
public:
    DrawableCanvas();
    ~DrawableCanvas();
    bool resize(int w, int h);
    void release();
    void texImage2D(Texture& tex);
    void clear(unsigned int color);
    void set_textstyle(const TextStyle& style);
    void set_textcolor(unsigned int color);
    void calctext(const char* utf8, int* w, int* h);
    void drawtext(const char* utf8, int x, int y, int w, int h);
    void line(unsigned int color, int x1, int y1, int x2, int y2);
    void fill(unsigned int color, int x1, int y1, int x2, int y2);

private:
    HDC       m_hdc;
    HBITMAP   m_hbitmap, m_obitmap;
    HFONT     m_hfont, m_ofont;
    void*     m_bmpixel;
    int       m_width, m_height;
    uint32_t* m_pixel;
    COLORREF rgba2gdicolor(uint32_t color);
    void     update_rgba();
};
// ----------------------------------------------------------------------------
}} // namespace osal::gfx

#endif // __OSAL_GFX_CANVAS_WIN_H__
