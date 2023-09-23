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

    public native Color getColor(String pKey);
    public native void setColor(String pKey, Color pColor);

    public native boolean[] getBooleanArray(String pKey);
    public native void setBooleanArray(String pKey,
                                       boolean[] pBoolArray);

    public native byte[] getByteArray(String pKey);
    public native void setByteArray(String pKey, byte[] pByteArray);

    public native char[] getCharArray(String pKey);
    public native void setCharArray(String pKey, char[] pCharArray);

    public native double[] getDoubleArray(String pKey);
    public native void setDoubleArray(String pKey,
                                      double[] pDoubleArray);

    public native float[] getFloatArray(String pKey);
    public native void setFloatArray(String pKey,
                                     float[] pFloatArray);

    public native int[] getIntegerArray(String pKey);
    public native void setIntegerArray(String pKey, int[] pIntArray);

    public native long[] getLongArray(String pKey);
    public native void setLongArray(String pKey, long[] pLongArray);

    public native short[] getShortArray(String pKey);
    public native void setShortArray(String pKey,short[] pShortArray);

    public native String[] getStringArray(String pKey);
    public native void setStringArray(String pKey,
                                      String[] pStringArray);

    public native Color[] getColorArray(String pKey);
    public native void setColorArray(String pKey,Color[] pColorArray);
}
