#ifndef __CAT_UI_ANIMATOR_H__
#define __CAT_UI_ANIMATOR_H__

#include <memory>
#include <functional>
#include "cat_ui_interpolator.h"
#include "cat_time_type.h"
#include "cat_gfx_type.h"

namespace cat {
class Widget;
// ----------------------------------------------------------------------------
class Animator {
public:
    Animator();
    virtual ~Animator();

    void set_interpolator(std::shared_ptr<Interpolator> interpolator);
    void set_duration(Timestamp duration);
    void set_callback(std::function<void()> cb);
    void cancel();
    bool update(Timestamp now);

protected:
    virtual void cb_animate(Timestamp now) = 0;

protected:
    std::shared_ptr<Interpolator> m_interpolator;
    std::function<void()> m_cb;
    Timestamp m_duration, m_starttime;
    bool m_started;

    void start();
    void stop();
};
// ----------------------------------------------------------------------------
class TranslateAnimator: public Animator {
public:
    TranslateAnimator(Widget* widget);
    void start(const Point2i& from, const Point2i& to);
protected:
    Widget* m_widget;
    Point2i m_from, m_to;
    virtual void cb_animate(Timestamp now);
};
// ----------------------------------------------------------------------------
class OpacityAnimator: public Animator {
public:
    OpacityAnimator(Widget* widget);
    void start(float from, float to);
protected:
    Widget * m_widget;
    float m_from, m_to;
    virtual void cb_animate(Timestamp now);
};
// ----------------------------------------------------------------------------
} // namespace cat

#endif // __CAT_UI_ANIMATOR_H__
