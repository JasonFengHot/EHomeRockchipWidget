package com.ehome.rockchip.vendor;

public class RockchipStorageManager {
    static {
        System.loadLibrary("RockchipVendor");
    }
    public native String getSerialNumber() ;

    public native void putSerialNumber(String number);
}
