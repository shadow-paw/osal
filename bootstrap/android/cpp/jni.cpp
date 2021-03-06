#include <jni.h>
#include <mutex>
#include "bootapp.h"

using namespace cat;
using namespace app;

struct CAT_INSTANCE {
    Kernel*    kernel;
};
extern "C" JNIEXPORT jobject JNICALL
Java_com_shadowpaw_cat_CatView_jniInit(JNIEnv *env, jobject self, jobject assmgr, jstring docpath) {
    JNIHelper::init(env);
    CAT_INSTANCE* data = new CAT_INSTANCE();
    PlatformSpecificData psd;
    psd.rootview = self;
    psd.asset_manager = assmgr;
    data->kernel = new Kernel();
    data->kernel->init(psd);
    data->kernel->vfs()->mount("/assets/", new AssetDriver(assmgr));
    {
        JNIHelper jni;
        data->kernel->vfs()->mount("/doc/", new FileDriver(jni.GetStringUTFChars(docpath), FileDriver::FLAG_WRITABLE));
    }
    return env->NewDirectByteBuffer((void*)data, sizeof(CAT_INSTANCE));
}
extern "C" JNIEXPORT void JNICALL
Java_com_shadowpaw_cat_CatView_jniFini(JNIEnv *env, jobject self, jobject handle) {
    CAT_INSTANCE* data = (CAT_INSTANCE*)env->GetDirectBufferAddress(handle);
    if (data) {
        if (data->kernel) delete data->kernel;
        delete data;
    }
    JNIHelper::fini();
}
extern "C" JNIEXPORT void JNICALL
Java_com_shadowpaw_cat_CatView_jniStartup(JNIEnv *env, jobject self, jobject handle) {
    CAT_INSTANCE* data = (CAT_INSTANCE*)env->GetDirectBufferAddress(handle);
    data->kernel->startup();
    data->kernel->run(new BootApp());
}
extern "C" JNIEXPORT void JNICALL
Java_com_shadowpaw_cat_CatView_jniShutdown(JNIEnv *env, jobject self, jobject handle) {
    CAT_INSTANCE* data = (CAT_INSTANCE*)env->GetDirectBufferAddress(handle);
    data->kernel->shutdown();
}
extern "C" JNIEXPORT void JNICALL
Java_com_shadowpaw_cat_CatView_jniContextRestored(JNIEnv *env, jobject self, jobject handle) {
    CAT_INSTANCE* data = (CAT_INSTANCE*)env->GetDirectBufferAddress(handle);
    data->kernel->context_restored();
}
extern "C" JNIEXPORT void JNICALL
Java_com_shadowpaw_cat_CatView_jniContextLost(JNIEnv *env, jobject self, jobject handle) {
    CAT_INSTANCE* data = (CAT_INSTANCE*)env->GetDirectBufferAddress(handle);
    data->kernel->context_lost();
}
extern "C" JNIEXPORT void JNICALL
Java_com_shadowpaw_cat_CatView_jniPause(JNIEnv *env, jobject self, jobject handle) {
    CAT_INSTANCE* data = (CAT_INSTANCE*)env->GetDirectBufferAddress(handle);
    data->kernel->pause();
}
extern "C" JNIEXPORT void JNICALL
Java_com_shadowpaw_cat_CatView_jniResume(JNIEnv *env, jobject self, jobject handle) {
    CAT_INSTANCE* data = (CAT_INSTANCE*)env->GetDirectBufferAddress(handle);
    data->kernel->resume();
}
extern "C" JNIEXPORT void JNICALL
Java_com_shadowpaw_cat_CatView_jniResize(JNIEnv *env, jobject self, jobject handle, jint width, jint height) {
    CAT_INSTANCE* data = (CAT_INSTANCE*)env->GetDirectBufferAddress(handle);
    data->kernel->resize(width, height);
}
extern "C" JNIEXPORT void JNICALL
Java_com_shadowpaw_cat_CatView_jniRender(JNIEnv *env, jobject self, jobject handle) {
    CAT_INSTANCE* data = (CAT_INSTANCE*)env->GetDirectBufferAddress(handle);
    data->kernel->render();
}
extern "C" JNIEXPORT void JNICALL
Java_com_shadowpaw_cat_CatView_jniTouch(JNIEnv *env, jobject self, jobject handle, jint type, jint pointerId, jint x, jint y) {
    CAT_INSTANCE* data = (CAT_INSTANCE*)env->GetDirectBufferAddress(handle);
    TouchEvent ev;
    switch (type) {
        case 1: ev.type = TouchEvent::EventType::TouchDown; break;
        case 2: ev.type = TouchEvent::EventType::TouchUp; break;
        case 3: ev.type = TouchEvent::EventType::TouchMove; break;
        default: return;
    }
    ev.pointer_id = pointerId;
    ev.x = x;
    ev.y = y;
    ev.button = 1<<0;
    data->kernel->touch(ev);
}
extern "C" JNIEXPORT void JNICALL
Java_com_shadowpaw_cat_CatView_jniTimer(JNIEnv *env, jobject self, jobject handle) {
    CAT_INSTANCE* data = (CAT_INSTANCE*)env->GetDirectBufferAddress(handle);
    data->kernel->timer();
}
