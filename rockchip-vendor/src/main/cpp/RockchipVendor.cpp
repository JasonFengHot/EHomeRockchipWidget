//
// Created by wangchao on 2021/10/18.
//

#include <jni.h>
#include <string>

#include "VendorStorage.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_ehome_rockchip_vendor_RockchipStorageManager_getSerialNumber(JNIEnv *env, jobject thiz) {
    VendorStorage *vendorStorage = new VendorStorage();
    std::string sn = vendorStorage->getSerialNumber();
    delete vendorStorage;
    return env->NewStringUTF(sn.c_str());
}




extern "C"
JNIEXPORT void JNICALL
Java_com_ehome_rockchip_vendor_RockchipStorageManager_putSerialNumber(JNIEnv *env, jobject thiz, jstring number) {
    VendorStorage *vendorStorage = new VendorStorage();
    const char *serialNumber = env->GetStringUTFChars(number, JNI_FALSE);
    vendorStorage->putSerialNumber(serialNumber);
    delete vendorStorage;
}