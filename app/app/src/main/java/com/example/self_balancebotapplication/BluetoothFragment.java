package com.example.self_balancebotapplication;

import android.app.Activity;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

public class BluetoothFragment extends Fragment {
    private Button connectButton;
    private Button disconnectButton;
    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_bluetooth, container, false);
        connectButton = (Button) v.findViewById(R.id.connect_button);
        connectButton.setVisibility(View.VISIBLE);
        disconnectButton = (Button) v.findViewById(R.id.disconnect_button);

        return inflater.inflate(R.layout.fragment_bluetooth, container, false);
    }
}
