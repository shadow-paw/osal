#ifndef __CAT_UI_LABEL_H__
#define __CAT_UI_LABEL_H__

#include "cat_ui_widget.h"
#include "cat_gfx_type.h"

namespace cat {
// ----------------------------------------------------------------------------
class Label: public Widget {
public:
    static const int TexBackground = 0;

    Label(KernelApi* kernel_api, const Rect2i& rect, unsigned int id = 0);
    virtual ~Label();

    void             set_text(const std::string& s) { m_text = s; }
    std::string      get_text() const { return m_text; }
    void             set_textstyle(const TextStyle& style) { m_textstyle = style; }
    const TextStyle& get_textstyle() const { return m_textstyle; }
    void             set_textsize(int size) { m_textstyle.fontsize = size; }
    void             set_textcolor(uint32_t color) { m_textstyle.color = color; }
    void             set_textappearance(TextStyle::Appearance appearance) { m_textstyle.appearance = appearance; }
    void             set_textgravity(TextStyle::Gravity gravity) { m_textstyle.gravity = gravity; }

protected:
    virtual void cb_render(Renderer* r, Timestamp now);

protected:
    std::string m_text;
    TextStyle m_textstyle;
};
// ----------------------------------------------------------------------------
} // namespace cat

#endif // __CAT_UI_LABEL_H__
