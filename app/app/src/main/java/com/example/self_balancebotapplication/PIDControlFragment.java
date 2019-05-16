package com.example.self_balancebotapplication;

import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.Toast;

public class PIDControlFragment extends Fragment {
    MainActivity mainActivity;

    // inclination
    private CheckBox chackBoxInclination;
    private EditText editTextInclinationKp;
    private EditText editTextInclinationKi;
    private EditText editTextInclinationKd;
    private EditText editTextInclinationReference;

    // wheel
    private CheckBox checkBoxWheel;
    private EditText editTextWheelKp;
    private EditText editTextWheelKi;
    private EditText editTextWheelKd;
    private EditText editTextWheelReference;

    private Button buttonSendPID;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_pid_control, container, false);

        chackBoxInclination = (CheckBox) view.findViewById(R.id.checkBox_inclination);
        editTextInclinationKp = (EditText) view.findViewById(R.id.editText_inclination_kp);
        editTextInclinationKi = (EditText) view.findViewById(R.id.editText_inclination_ki);
        editTextInclinationKd = (EditText) view.findViewById(R.id.editText_inclination_kd);
        editTextInclinationReference = (EditText) view.findViewById(R.id.editText_inclination_reference);

        checkBoxWheel = (CheckBox) view.findViewById(R.id.checkBox_wheel);
        editTextWheelKp = (EditText) view.findViewById(R.id.editText_wheel_kp);
        editTextWheelKi = (EditText) view.findViewById(R.id.editText_wheel_ki);
        editTextWheelKd = (EditText) view.findViewById(R.id.editText_wheel_kd);
        editTextWheelReference = (EditText) view.findViewById(R.id.editText_wheel_reference);

        buttonSendPID = (Button) view.findViewById(R.id.button_send_pid);
        buttonSendPID.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                send();
            }
        });

        return view;
    }

    private void send(){
        // controller mode 2
        if( chackBoxInclination.isChecked() && checkBoxWheel.isChecked() ){
            String kp1 = editTextInclinationKp.getText().toString();
            String ki1 = editTextInclinationKi.getText().toString();
            String kd1 = editTextInclinationKd.getText().toString();
            String reference1 = editTextInclinationReference.getText().toString();

            String kp2 = editTextWheelKp.getText().toString();
            String ki2 = editTextWheelKi.getText().toString();
            String kd2 = editTextWheelKd.getText().toString();
            String reference2 = editTextWheelReference.getText().toString();

            if( kp1.isEmpty() || ki1.isEmpty() || kd1.isEmpty() || reference1.isEmpty() ){
                Toast.makeText(mainActivity, "Please Input All Parameters", Toast.LENGTH_LONG).show();
            }
            else if( kp2.isEmpty() || ki2.isEmpty() || kd2.isEmpty() || reference2.isEmpty() ){
                Toast.makeText(mainActivity, "Please Input All Parameters", Toast.LENGTH_LONG).show();
            }
            else{
                String data = "2,"                                             // send mode 2
                        + "2,"                                                 // control mode 2
                        + kp1 + "," + ki1 + "," + kd1 + "," + reference1 + ","  // inclination
                        + kp2 + "," + ki2 + "," + kd2 + "," + reference2 + "#"; // wheel
                mainActivity.bluetoothFragment.bluetoothSendData(data);
            }
        }
        // controller mode 1
        else if( chackBoxInclination.isChecked() ){
            String kp1 = editTextInclinationKp.getText().toString();
            String ki1 = editTextInclinationKi.getText().toString();
            String kd1 = editTextInclinationKd.getText().toString();
            String reference1 = editTextInclinationReference.getText().toString();

            if( kp1.isEmpty() || ki1.isEmpty() || kd1.isEmpty() || reference1.isEmpty() ){
                Toast.makeText(mainActivity, "Please Input All Parameters", Toast.LENGTH_LONG).show();
            }
            else{
                String data = "2,"                                              // send mode 2
                        + "1,"                                                  // control mode 1
                        + kp1 + "," + ki1 + "," + kd1 + "," + reference1 + "#";  // inclination
                mainActivity.bluetoothFragment.bluetoothSendData(data);
            }
        } else{
            Toast.makeText(mainActivity, "Please Select  a Control Mode", Toast.LENGTH_LONG).show();
        }
    }

    public void setActivity(MainActivity mainActivity) {
        this.mainActivity = mainActivity;
    }
}
