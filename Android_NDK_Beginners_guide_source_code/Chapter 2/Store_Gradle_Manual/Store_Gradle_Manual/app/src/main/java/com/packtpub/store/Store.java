package com.packtpub.store;

public class Store {
    static {
        System.loadLibrary("com_packtpub_store_Store");
    }

    public native int getCount();
}
