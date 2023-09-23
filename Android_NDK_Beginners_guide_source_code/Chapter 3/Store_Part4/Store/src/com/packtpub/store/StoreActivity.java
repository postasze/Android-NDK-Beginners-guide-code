package com.packtpub.store;

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

    public static class PlaceholderFragment extends Fragment {
        private Store mStore = new Store();
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
            switch (type) {
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
                }
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
    }
}
