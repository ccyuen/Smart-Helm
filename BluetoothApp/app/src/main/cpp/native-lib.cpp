#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_wearhacks2017_bluetoothapp_Bluetooth_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
