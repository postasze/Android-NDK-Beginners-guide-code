package com.packtpub.store;

import java.util.Arrays;
import java.util.List;
import java.util.regex.Pattern;

import android.app.Activity;
import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

import com.google.common.base.Function;
import com.google.common.base.Joiner;
import com.google.common.collect.Lists;
import com.google.common.primitives.Booleans;
import com.google.common.primitives.Bytes;
import com.google.common.primitives.Chars;
import com.google.common.primitives.Doubles;
import com.google.common.primitives.Floats;
import com.google.common.primitives.Ints;
import com.google.common.primitives.Longs;
import com.google.common.primitives.Shorts;
import com.packtpub.exception.InvalidTypeException;
import com.packtpub.exception.NotExistingKeyException;
import com.packtpub.exception.StoreFullException;

public class StoreActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_store);

        if (savedInstanceState == null) {
            getFragmentManager().beginTransaction()
                                .add(R.id.container,
                                     new PlaceholderFragment())
                                .commit();
        }
    }

    public static class PlaceholderFragment extends Fragment
    implements StoreListener {
        private Store mStore = new Store(this);
        private EditText mUIKeyEdit, mUIValueEdit;
        private Spinner mUITypeSpinner;
        private Button mUIGetButton, mUISetButton;
        private Pattern mKeyPattern;

        public PlaceholderFragment() {
        }

        @Override
        public View onCreateView(LayoutInflater inflater,
                                 ViewGroup container,
                                 Bundle savedInstanceState)
        {
            View rootView = inflater.inflate(R.layout.fragment_store,
                                             container, false);
            updateTitle();

            // Initializes text components.
            mKeyPattern = Pattern.compile("\\p{Alnum}+");
            mUIKeyEdit = (EditText) rootView.findViewById(
                                                      R.id.uiKeyEdit);
            mUIValueEdit = (EditText) rootView.findViewById(
                                                    R.id.uiValueEdit);
    
            // Initializes type selector.
            ArrayAdapter<StoreType> adapter =
                new ArrayAdapter<StoreType>(getActivity(),
                                android.R.layout.simple_spinner_item,
                                StoreType.values());
            adapter.setDropDownViewResource(
                       android.R.layout.simple_spinner_dropdown_item);
            mUITypeSpinner = (Spinner) rootView.findViewById(
                                                  R.id.uiTypeSpinner);
            mUITypeSpinner.setAdapter(adapter);
    
            // Initializes buttons.
            mUIGetButton = (Button) rootView.findViewById(
                                               R.id.uiGetValueButton);
            mUIGetButton.setOnClickListener(new OnClickListener() {
                public void onClick(View pView) {
                    onGetValue();
                }
            });
            mUISetButton = (Button) rootView.findViewById(
                                               R.id.uiSetValueButton);
            mUISetButton.setOnClickListener(new OnClickListener() {
                public void onClick(View pView) {
                    onSetValue();
                }
            });
            return rootView;
        }

        private void updateTitle() {
            int numEntries = mStore.getCount();
            getActivity().setTitle(String.format("Store (%1$s)",
                                                         numEntries));
        }

        private void onGetValue() {
            // Retrieves key and type entered by the user.
            String key = mUIKeyEdit.getText().toString();
            StoreType type = (StoreType) mUITypeSpinner
                                                   .getSelectedItem();
            // Checks key is correct.
            if (!mKeyPattern.matcher(key).matches()) {
                displayMessage("Incorrect key.");
                return;
            }

            // Retrieves value from the store and displays it.
            try {
                switch (type) {
                case Boolean:
                    mUIValueEdit.setText(Boolean.toString(mStore
                                    .getBoolean(key)));
                    break;
                case Byte:
                    mUIValueEdit.setText(Byte.toString(mStore
                                    .getByte(key)));
                    break;
                case Char:
                    mUIValueEdit.setText(Character.toString(mStore
                                    .getChar(key)));
                    break;
                case Double:
                    mUIValueEdit.setText(Double.toString(mStore
                                    .getDouble(key)));
                    break;
                case Float:
                    mUIValueEdit.setText(Float.toString(mStore
                                    .getFloat(key)));
                    break;
                case Integer:
                    mUIValueEdit.setText(Integer.toString(mStore
                                    .getInteger(key)));
                    break;
                case Long:
                    mUIValueEdit.setText(Long.toString(mStore
                                    .getLong(key)));
                    break;
                case Short:
                    mUIValueEdit.setText(Short.toString(mStore
                                    .getShort(key)));
                    break;
                case String:
                    mUIValueEdit.setText(mStore.getString(key));
                    break;
                case Color:
                    Color color = mStore.getColor(key);
                    mUIValueEdit.setText(color != null ?
                            color.toString() : null);
                    break;
                case BooleanArray:
                    mUIValueEdit.setText(Booleans.join(";", mStore
                                    .getBooleanArray(key)));
                    break;
                case ByteArray:
                    mUIValueEdit.setText(Joiner.on(";").join(
                        Bytes.asList(mStore.getByteArray(key))));
                    break;
                case CharArray:
                    mUIValueEdit.setText(Chars.join(";", mStore
                                    .getCharArray(key)));
                    break;
                case DoubleArray:
                    mUIValueEdit.setText(Doubles.join(";", mStore
                                    .getDoubleArray(key)));
                    break;
                case FloatArray:
                    mUIValueEdit.setText(Floats.join(";", mStore
                                    .getFloatArray(key)));
                    break;
                case IntegerArray:
                    mUIValueEdit.setText(Ints.join(";", mStore
                                    .getIntegerArray(key)));
                    break;
                case LongArray:
                    mUIValueEdit.setText(Longs.join(";",
                                    mStore.getLongArray(key)));
                    break;
                case ShortArray:
                    mUIValueEdit.setText(Shorts.join(";",
                                    mStore.getShortArray(key)));
                    break;
                case StringArray:
                    mUIValueEdit.setText(Joiner.on(";").join(
                                    mStore.getStringArray(key)));
                    break;
                case ColorArray:
                    mUIValueEdit.setText(Joiner.on(";").join(mStore
                                    .getColorArray(key)));
                    break;
                }
            }
            // Process any exception raised while retrieving data.
            catch (NotExistingKeyException eNotExistingKeyException) {
                displayMessage(eNotExistingKeyException.getMessage());
            } catch (InvalidTypeException eInvalidTypeException) {
                displayMessage(eInvalidTypeException.getMessage());
            }
        }

        private void onSetValue() {
            // Retrieves key and type entered by the user.
            String key = mUIKeyEdit.getText().toString();
            String value = mUIValueEdit.getText().toString();
            StoreType type = (StoreType) mUITypeSpinner
                                                   .getSelectedItem();
            // Checks key is correct.
            if (!mKeyPattern.matcher(key).matches()) {
                displayMessage("Incorrect key.");
                return;
            }

            // Parses user entered value and saves it in the store.
            try {
                switch (type) {
                case Boolean:
                    if (value.equals("true") || value.equals("1")) {
                        mStore.setBoolean(key, true);
                    } else if (value.equals("false")
                                    || value.equals("0")) {
                        mStore.setBoolean(key, false);
                    } else {
                        throw new IllegalArgumentException();
                    }
                    break;
                case Byte:
                    mStore.setByte(key, Byte.parseByte(value));
                    break;
                case Char:
                    if (value.length() == 1) {
                        mStore.setChar(key, value.charAt(0));
                    } else {
                        throw new IllegalArgumentException();
                    }
                    break;
                case Double:
                    mStore.setDouble(key, Double.parseDouble(value));
                    break;
                case Float:
                    mStore.setFloat(key, Float.parseFloat(value));
                    break;
                case Integer:
                    mStore.setInteger(key, Integer.parseInt(value));
                    break;
                case Long:
                    mStore.setLong(key, Long.parseLong(value));
                    break;
                case Short:
                    mStore.setShort(key, Short.parseShort(value));
                    break;
                case String:
                    mStore.setString(key, value);
                    break;
                case Color:
                    mStore.setColor(key, new Color(value));
                    break;
                case BooleanArray:
                    mStore.setBooleanArray(key, Booleans.toArray(
                        stringToList(new Function<String, Boolean>() {
                            public Boolean apply(String pSubValue) {
                                if (pSubValue.equals("true")
                                           || pSubValue.equals("1")) {
                                    return Boolean.TRUE;
                                } else if (pSubValue.equals("false")
                                           || pSubValue.equals("0")) {
                                    return Boolean.FALSE;
                                } else {
                                    throw
                                       new IllegalArgumentException();
                                }
                            }
                        }, value)));
                    break;
                case ByteArray:
                    mStore.setByteArray(key, Bytes.toArray(
                        stringToList(new Function<String, Byte>() {
                            public Byte apply(String pSubValue) {
                                return Byte.parseByte(pSubValue);
                            }
                        }, value)));
                    break;
                case CharArray:
                    mStore.setCharArray(key, Chars.toArray(
                      stringToList(new Function<String, Character>() {
                            public Character apply(String pSubValue) {
                                if (pSubValue.length() == 1) {
                                    return pSubValue.charAt(0);
                                } else {
                                    throw
                                       new IllegalArgumentException();
                                }
                            }
                        }, value)));
                    break;
                case DoubleArray:
                    mStore.setDoubleArray(key, Doubles.toArray(
                        stringToList(new Function<String, Double>() {
                            public Double apply(String pSubValue) {
                                return Double.parseDouble(pSubValue);
                            }
                        }, value)));
                    break;
                case FloatArray:
                    mStore.setFloatArray(key, Floats.toArray(
                        stringToList(new Function<String, Float>() {
                            public Float apply(String pSubValue) {
                                return Float.parseFloat(pSubValue);
                            }
                        }, value)));
                    break;
                case IntegerArray:
                    mStore.setIntegerArray(key, Ints.toArray(
                        stringToList(new Function<String, Integer>() {
                            public Integer apply(String pSubValue) {
                                return Integer.parseInt(pSubValue);
                            }
                        }, value)));
                    break;
                case LongArray:
                    mStore.setLongArray(key, Longs.toArray(
                        stringToList(new Function<String, Long>() {
                            public Long apply(String pSubValue) {
                                return Long.parseLong(pSubValue);
                            }
                        }, value)));
                    break;
                case ShortArray:
                    mStore.setShortArray(key, Shorts.toArray(
                        stringToList(new Function<String, Short>() {
                            public Short apply(String pSubValue) {
                                return Short.parseShort(pSubValue);
                            }
                        }, value)));
                    break;
                case StringArray:
                    String[] stringArray = value.split(";");
                    mStore.setStringArray(key, stringArray);
                    break;
                case ColorArray:
                    List<Color> idList = stringToList(
                        new Function<String, Color>() {
                            public Color apply(String pSubValue) {
                                return new Color(pSubValue);
                            }
                        }, value);
                    mStore.setColorArray(key, idList.toArray(
                                          new Color[idList.size()]));
                    break;
                }
            } catch (StoreFullException eStoreFullException) {
                displayMessage(eStoreFullException.getMessage());
            } catch (Exception eException) {
                displayMessage("Incorrect value.");
            }
            updateTitle();
        }

        // Helper method to display a message.
        private void displayMessage(String pMessage) {
            Toast.makeText(getActivity(), pMessage, Toast.LENGTH_LONG)
                 .show();
        }

        // Helper method to convert a string to a list of values.
        private <TType> List<TType> stringToList(
                 Function<String, TType> pConversion, String pValue) {
            String[] splitArray = pValue.split(";");
            List<String> splitList = Arrays.asList(splitArray);
            return Lists.transform(splitList, pConversion);
        }

        @Override
        public void onSuccess(int pValue) {
            displayMessage(String.format(
                "Integer '%1$d' successfuly saved!", pValue));
        }

        @Override
        public void onSuccess(String pValue) {
            displayMessage(String.format(
                "String '%1$s' successfuly saved!", pValue));
        }

        @Override
        public void onSuccess(Color pValue) {
            displayMessage(String.format(
                "Color '%1$s' successfuly saved!", pValue));
        }
    }
}
