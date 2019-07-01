package com.example.self_balancebotapplication;

import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Switch;
import android.widget.TextView;

import com.jmedeisis.bugstick.Joystick;
import com.jmedeisis.bugstick.JoystickListener;

public class JoystickControlFragment extends Fragment {
    MainActivity mainActivity;

    TextView yTextView;
    TextView xTextView;

    TextView iTextValue;

    String xNoneString;
    String xValueString;
    String yNoneString;
    String yValueString;

    Joystick joystick_r;
    Joystick joystick_l;

    private double psi = 0;
    private double phi = 0;
    private String i_value = "0";

    private Switch switchOffRoad;
    private double maxPsi = 0.03;
    private double maxPhi = 3*Math.PI/4;

    private Switch switchClear;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_joystick_control, container, false);

        yTextView = (TextView) view.findViewById(R.id.y_value);
        xTextView = (TextView) view.findViewById(R.id.x_value);

        iTextValue = (TextView) view.findViewById(R.id.textView_I_value);
        iTextValue.setText("0");

        xNoneString = "0 : X";
        xValueString = "%.04f : X";
        yNoneString = "Y : 0";
        yValueString = "Y : %.04f";

        joystick_r = (Joystick) view.findViewById(R.id.joystick_r);
        joystick_l = (Joystick) view.findViewById(R.id.joystick_l);

        // phi
        joystick_r.setJoystickListener(new JoystickListener() {
            @Override
            public void onDown() {}

            @Override
            public void onDrag(float degrees, float offset) {
                float value = (float) (offset * Math.cos(Math.toRadians(degrees)));
                phi = -value * maxPhi ;
                xTextView.setText(String.format(xValueString, phi));
            }

            @Override
            public void onUp() {
                xTextView.setText(xNoneString);
                phi = 0;
            }
        });

        // psi
        joystick_l.setJoystickListener(new JoystickListener() {
            @Override
            public void onDown() {}

            @Override
            public void onDrag(float degrees, float offset) {
                float value = (float) (offset * Math.sin(Math.toRadians(degrees)));
                psi = -value * maxPsi;
                yTextView.setText(String.format(yValueString, psi));
            }

            @Override
            public void onUp() {
                yTextView.setText(yNoneString);
                psi = 0;
            }
        });

        switchOffRoad = view.findViewById(R.id.switch_off_road);
        switchOffRoad.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String data;
                if (switchOffRoad.isChecked()) {
                    maxPsi = 0.04;
                } else {
                    maxPsi = 0.03;
                }
            }
        });

        switchClear = view.findViewById(R.id.switch_clear);
        switchClear.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String data;
                if (switchClear.isChecked()) {
                    data = "~1# ";
                    mainActivity.bluetoothFragment.bluetoothSendData(data);
                }
            }
        });

        return view;
    }

    // integral term
    public void receiveData(String[] data){
        if( data.length==3 ){
            i_value = data[2];
        }
    }

    public void updateInformation(){
        if( iTextValue != null ){
            iTextValue.setText(i_value);
        }
    }

    public void setActivity(MainActivity mainActivity) {
        this.mainActivity = mainActivity;
    }

    public String getValue() {
        return "~1,1," + String.format("%.04f", psi) + "," + String.format("%.04f", phi) + "#";
    }
}
