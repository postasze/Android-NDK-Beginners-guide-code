package com.packtpub.store;

import com.packtpub.exception.InvalidTypeException;
import com.packtpub.exception.NotExistingKeyException;

public class StoreThreadSafe extends Store {
    protected static Object LOCK;
    
    public StoreThreadSafe(StoreListener pListener) {
        super(pListener);
    }

    @Override
    public int getCount() {
        synchronized (LOCK) {
            return super.getCount();
        }
    }

    @Override
    public boolean getBoolean(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getBoolean(pKey);
        }
    }

    @Override
    public void setBoolean(String pKey, boolean pBool) {
        synchronized (LOCK) {
            super.setBoolean(pKey, pBool);
        }
    }

    @Override
    public byte getByte(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getByte(pKey);
        }
    }

    @Override
    public void setByte(String pKey, byte pByte) {
        synchronized (LOCK) {
            super.setByte(pKey, pByte);
        }
    }

    @Override
    public char getChar(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getChar(pKey);
        }
    }

    @Override
    public void setChar(String pKey, char pChar) {
        synchronized (LOCK) {
            super.setChar(pKey, pChar);
        }
    }

    @Override
    public double getDouble(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getDouble(pKey);
        }
    }

    @Override
    public void setDouble(String pKey, double pDouble) {
        synchronized (LOCK) {
            super.setDouble(pKey, pDouble);
        }
    }

    @Override
    public float getFloat(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getFloat(pKey);
        }
    }

    @Override
    public void setFloat(String pKey, float pFloat) {
        synchronized (LOCK) {
            super.setFloat(pKey, pFloat);
        }
    }

    @Override
    public int getInteger(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getInteger(pKey);
        }
    }

    @Override
    public void setInteger(String pKey, int pInt) {
        synchronized (LOCK) {
            super.setInteger(pKey, pInt);
        }
    }

    @Override
    public long getLong(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getLong(pKey);
        }
    }

    @Override
    public void setLong(String pKey, long pLong) {
        synchronized (LOCK) {
            super.setLong(pKey, pLong);
        }
    }

    @Override
    public short getShort(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getShort(pKey);
        }
    }

    @Override
    public void setShort(String pKey, short pShort) {
        synchronized (LOCK) {
            super.setShort(pKey, pShort);
        }
    }

    @Override
    public String getString(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getString(pKey);
        }
    }

    @Override
    public void setString(String pKey, String pString) {
        synchronized (LOCK) {
            super.setString(pKey, pString);
        }
    }

    @Override
    public Color getColor(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getColor(pKey);
        }
    }

    @Override
    public void setColor(String pKey, Color pColor) {
        synchronized (LOCK) {
            super.setColor(pKey, pColor);
        }
    }

    @Override
    public boolean[] getBooleanArray(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getBooleanArray(pKey);
        }
    }

    @Override
    public void setBooleanArray(String pKey, boolean[] pBoolArray) {
        synchronized (LOCK) {
            super.setBooleanArray(pKey, pBoolArray);
        }
    }

    @Override
    public byte[] getByteArray(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getByteArray(pKey);
        }
    }

    @Override
    public void setByteArray(String pKey, byte[] pByteArray) {
        synchronized (LOCK) {
            super.setByteArray(pKey, pByteArray);
        }
    }

    @Override
    public char[] getCharArray(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getCharArray(pKey);
        }
    }

    @Override
    public void setCharArray(String pKey, char[] pCharArray) {
        synchronized (LOCK) {
            super.setCharArray(pKey, pCharArray);
        }
    }

    @Override
    public double[] getDoubleArray(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getDoubleArray(pKey);
        }
    }

    @Override
    public void setDoubleArray(String pKey, double[] pDoubleArray) {
        synchronized (LOCK) {
            super.setDoubleArray(pKey, pDoubleArray);
        }
    }

    @Override
    public float[] getFloatArray(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getFloatArray(pKey);
        }
    }

    @Override
    public void setFloatArray(String pKey, float[] pFloatArray) {
        synchronized (LOCK) {
            super.setFloatArray(pKey, pFloatArray);
        }
    }

    @Override
    public int[] getIntegerArray(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getIntegerArray(pKey);
        }
    }

    @Override
    public void setIntegerArray(String pKey, int[] pIntArray) {
        synchronized (LOCK) {
            super.setIntegerArray(pKey, pIntArray);
        }
    }

    @Override
    public long[] getLongArray(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getLongArray(pKey);
        }
    }

    @Override
    public void setLongArray(String pKey, long[] pLongArray) {
        synchronized (LOCK) {
            super.setLongArray(pKey, pLongArray);
        }
    }

    @Override
    public short[] getShortArray(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getShortArray(pKey);
        }
    }

    @Override
    public void setShortArray(String pKey, short[] pShortArray) {
        synchronized (LOCK) {
            super.setShortArray(pKey, pShortArray);
        }
    }

    @Override
    public String[] getStringArray(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getStringArray(pKey);
        }
    }

    @Override
    public void setStringArray(String pKey, String[] pStringArray) {
        synchronized (LOCK) {
            super.setStringArray(pKey, pStringArray);
        }
    }

    @Override
    public Color[] getColorArray(String pKey)
        throws NotExistingKeyException, InvalidTypeException
    {
        synchronized (LOCK) {
            return super.getColorArray(pKey);
        }
    }

    @Override
    public void setColorArray(String pKey, Color[] pColorArray) {
        synchronized (LOCK) {
            super.setColorArray(pKey, pColorArray);
        }
    }

    @Override
    public void stopWatcher(long pPointer) {
        synchronized (LOCK) {
            super.stopWatcher(pPointer);
        }
    }
}
