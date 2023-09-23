package com.packtpub.store;

public class Store {
    static {
        System.loadLibrary("com_packtpub_store_Store");
    }

    public native int getCount();

    public native boolean getBoolean(String pKey);
    public native void setBoolean(String pKey, boolean pBool);

    public native byte getByte(String pKey);
    public native void setByte(String pKey, byte pByte);

    public native char getChar(String pKey);
    public native void setChar(String pKey, char pChar);

    public native double getDouble(String pKey);
    public native void setDouble(String pKey, double pDouble);

    public native float getFloat(String pKey);
    public native void setFloat(String pKey, float pFloat);

    public native int getInteger(String pKey);
    public native void setInteger(String pKey, int pInt);

    public native long getLong(String pKey);
    public native void setLong(String pKey, long pLong);

    public native short getShort(String pKey);
    public native void setShort(String pKey, short pShort);

    public native String getString(String pKey);
    public native void setString(String pKey, String pString);
}
