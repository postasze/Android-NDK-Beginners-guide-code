package com.packtpub.store;

import android.app.Activity;
import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

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
            return rootView;
        }

        private void updateTitle() {
            int numEntries = mStore.getCount();
            getActivity().setTitle(String.format("Store (%1$s)",
                                                         numEntries));
        }
    }
}
