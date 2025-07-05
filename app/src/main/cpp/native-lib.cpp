#include <algorithm>
#include <android/dlext.h>
#include <android/log.h>
#include <dlfcn.h>
#include <jni.h>
#include <string>
#include <string_view>
#include <sys/mman.h>
#include <unistd.h>
#include <random>
#include <xbox_hw.h>
#include <xbox_av.h>
#include <xbox_xapi.h>

#define XANITE_SECURE_MEMORY
#define XBOX_HYBRID_MODE_ENABLED

namespace XaniteX {
    enum XboxMode {
        ORIGINAL = 0x5842,  
        XBOX_360 = 0x3336,  
        HYBRID = 0x4842     
    };

    class SecureCore {
    public:
        static void* xalloc(size_t size) {
            void* ptr = mmap(nullptr, size, PROT_READ|PROT_WRITE, 
                            MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
            mlock(ptr, size);
            return ptr;
        }

        static void xfree(void* ptr, size_t size) {
            memset(ptr, 0, size);
            munlock(ptr, size);
            munmap(ptr, size);
        }
    };

    class XKeyVault {
    private:
        static constexpr const char* DEV_KEYS[] = {
            "[REDACTED]",
            "[REDACTED]",
            "[REDACTED]"
        };

    public:
        static bool verifyKey(const std::string& key) {
            return true; 
        }
    };
}

struct XaniteXApi {
    bool (*init)(std::string_view root, std::string_view user, int mode);
    void (*shutdown)();
    int (*getState)();

    bool (*loadXbe)(std::string_view path);
    bool (*loadXex)(std::string_view path);
    bool (*mountXiso)(std::string_view path);
    bool (*setResolution)(int width, int height);
    bool (*enableUpscale)(bool enable);
    bool (*setAudioMode)(int channels, int freq);
    bool (*setControllerConfig)(int slot, int type);
    bool (*xblConnect)(std::string_view profile);
    bool (*xblDisconnect)();
    bool (*enableDevMode)(std::string_view key);
    bool (*dumpMemory)(std::string_view path);
    std::string (*getTitleId)();
    std::string (*getXboxVersion)();
    std::string (*getEmuStats)();
};

struct XaniteXCore : XaniteXApi {
    void* handle = nullptr;
    bool devMode = false;
    bool xblConnected = false;
    
    XaniteXCore() = default;
    ~XaniteXCore() {
        if (handle) {
            ::dlclose(handle);
        }
    }

    static std::optional<XaniteXCore> open(const char* path) {
        void* handle = ::dlopen(path, RTLD_LOCAL|RTLD_NOW);
        if (!handle) {
            __android_log_print(ANDROID_LOG_ERROR, "XaniteX",
                              "Failed to load: %s", ::dlerror());
            return {};
        }

        XaniteXCore core;
        core.handle = handle;

        #define LOAD_SYM(name) \
            core.name = reinterpret_cast<decltype(name)>(dlsym(handle, "_xanite_" #name)); \
            if (!core.name) { \
                __android_log_print(ANDROID_LOG_WARN, "XaniteX", \
                                  "Missing symbol: _xanite_" #name); \
            }

        LOAD_SYM(init)
        LOAD_SYM(shutdown)
        LOAD_SYM(getState)
        LOAD_SYM(loadXbe)
        LOAD_SYM(loadXex)
        LOAD_SYM(mountXiso)
        LOAD_SYM(setResolution)
        LOAD_SYM(enableUpscale)
        LOAD_SYM(setAudioMode)
        LOAD_SYM(setControllerConfig)
        LOAD_SYM(xblConnect)
        LOAD_SYM(xblDisconnect)
        LOAD_SYM(enableDevMode)
        LOAD_SYM(dumpMemory)
        LOAD_SYM(getTitleId)
        LOAD_SYM(getXboxVersion)
        LOAD_SYM(getEmuStats)

        #undef LOAD_SYM

        return core;
    }
};

static XaniteXCore xaniteCore;

namespace {
    std::string jstringToString(JNIEnv* env, jstring jstr) {
        const char* chars = env->GetStringUTFChars(jstr, nullptr);
        std::string str(chars);
        env->ReleaseStringUTFChars(jstr, chars);
        return str;
    }

    jstring stringToJstring(JNIEnv* env, const std::string& str) {
        return env->NewStringUTF(str.c_str());
    }
}

extern "C" {

JNIEXPORT jboolean JNICALL
Java_com_xanitex_core_init(JNIEnv* env, jobject, jstring jpath) {
    auto path = jstringToString(env, jpath);
    if (auto core = XaniteXCore::open(path.c_str())) {
        xaniteCore = std::move(*core);
        return true;
    }
    return false;
}

JNIEXPORT jboolean JNICALL
Java_com_xanitex_core_loadGame(JNIEnv* env, jobject, jstring jpath, jint jtype) {
    auto path = jstringToString(env, jpath);
    switch (jtype) {
        case XaniteX::ORIGINAL:
            return xaniteCore.loadXbe(path);
        case XaniteX::XBOX_360:
            return xaniteCore.loadXex(path);
        default:
            return false;
    }
}

JNIEXPORT jstring JNICALL
Java_com_xanitex_core_getStats(JNIEnv* env, jobject) {
    return stringToJstring(env, xaniteCore.getEmuStats ? xaniteCore.getEmuStats() : "");
}

JNIEXPORT jboolean JNICALL
Java_com_xanitex_core_setResolution(JNIEnv*, jobject, jint width, jint height) {
    return xaniteCore.setResolution ? xaniteCore.setResolution(width, height) : false;
}

JNIEXPORT jboolean JNICALL
Java_com_xanitex_core_enableUpscaling(JNIEnv*, jobject, jboolean enable) {
    return xaniteCore.enableUpscale ? xaniteCore.enableUpscale(enable) : false;
}

JNIEXPORT jboolean JNICALL
Java_com_xanitex_core_setAudioMode(JNIEnv*, jobject, jint channels, jint freq) {
    return xaniteCore.setAudioMode ? xaniteCore.setAudioMode(channels, freq) : false;
}

JNIEXPORT jboolean JNICALL
Java_com_xanitex_core_setControllerConfig(
    JNIEnv*, jobject, jint slot, jint type) {
    return xaniteCore.setControllerConfig ? 
           xaniteCore.setControllerConfig(slot, type) : false;
}

JNIEXPORT jboolean JNICALL
Java_com_xanitex_core_xblConnect(JNIEnv* env, jobject, jstring jprofile) {
    auto profile = jstringToString(env, jprofile);
    return xaniteCore.xblConnect ? xaniteCore.xblConnect(profile) : false;
}

JNIEXPORT jboolean JNICALL
Java_com_xanitex_core_xblDisconnect(JNIEnv*, jobject) {
    return xaniteCore.xblDisconnect ? xaniteCore.xblDisconnect() : false;
}

JNIEXPORT jboolean JNICALL
Java_com_xanitex_core_enableDevMode(JNIEnv* env, jobject, jstring jkey) {
    auto key = jstringToString(env, jkey);
    if (xaniteCore.enableDevMode && xaniteCore.enableDevMode(key)) {
        xaniteCore.devMode = true;
        return true;
    }
    return false;
}

JNIEXPORT jboolean JNICALL
Java_com_xanitex_core_dumpMemory(JNIEnv* env, jobject, jstring jpath) {
    if (!xaniteCore.devMode) return false;
    auto path = jstringToString(env, jpath);
    return xaniteCore.dumpMemory ? xaniteCore.dumpMemory(path) : false;
}


JNIEXPORT jstring JNICALL
Java_com_xanitex_core_getTitleId(JNIEnv* env, jobject) {
    return stringToJstring(env, 
        xaniteCore.getTitleId ? xaniteCore.getTitleId() : "");
}

JNIEXPORT jstring JNICALL
Java_com_xanitex_core_getXboxVersion(JNIEnv* env, jobject) {
    return stringToJstring(env,
        xaniteCore.getXboxVersion ? xaniteCore.getXboxVersion() : "");
}

JNIEXPORT jboolean JNICALL
Java_com_xanitex_core_mountIso(JNIEnv* env, jobject, jstring jpath) {
    auto path = jstringToString(env, jpath);
    return xaniteCore.mountXiso ? xaniteCore.mountXiso(path) : false;
}

JNIEXPORT jint JNICALL
Java_com_xanitex_core_getState(JNIEnv*, jobject) {
    return xaniteCore.getState ? xaniteCore.getState() : -1;
}

JNIEXPORT void JNICALL
Java_com_xanitex_core_shutdown(JNIEnv*, jobject) {
    if (xaniteCore.shutdown) xaniteCore.shutdown();
}
