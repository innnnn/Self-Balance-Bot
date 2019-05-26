package com.example.self_balancebotapplication;

import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Toast;

public class PIDControlWheelFragment extends Fragment implements RadioGroup.OnCheckedChangeListener{
    MainActivity mainActivity;

    // left motor
    private EditText editTextKpLeft;
    private Button buttonKpLeftDown;
    private Button buttonKpLeftUp;

    private EditText editTextKiLeft;
    private Button buttonKiLeftDown;
    private Button buttonKiLeftUp;

    private EditText editTextKdLeft;
    private Button buttonKdLeftDown;
    private Button buttonKdLeftUp;

    private EditText editTextReferenceLeft;
    private Button buttonReferenceLeftDown;
    private Button buttonReferenceLeftUp;

    // right motor
    private EditText editTextKpRight;
    private Button buttonKpRightDown;
    private Button buttonKpRightUp;

    private EditText editTextKiRight;
    private Button buttonKiRightDown;
    private Button buttonKiRightUp;

    private EditText editTextKdRight;
    private Button buttonKdRightDown;
    private Button buttonKdRightUp;

    private EditText editTextReferenceRight;
    private Button buttonReferenceRightDown;
    private Button buttonReferenceRightUp;

    // radio button
    private RadioButton radioButtonSame;
    private RadioButton radioButtonDifferent;
    private RadioGroup radioGroup;

    // bottom
    private Button buttonSendPid;
    private Button buttonStopPid;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_pid_control_wheel, container, false);

        // left motor
        editTextKpLeft = view.findViewById(R.id.editText_wheel_kp_left);
        buttonKpLeftDown = view.findViewById(R.id.button_wheel_kp_left_down);
        buttonKpLeftDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKpLeft.setText(String.format("%.2f", Double.parseDouble(editTextKpLeft.getText().toString()) - 0.01));
                if(radioButtonSame.isChecked()){
                    editTextKpRight.setText(editTextKpLeft.getText());
                }
            }
        });
        buttonKpLeftUp = view.findViewById(R.id.button_wheel_kp_left_up);
        buttonKpLeftUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKpLeft.setText(String.format("%.2f", Double.parseDouble(editTextKpLeft.getText().toString()) + 0.01));
                if(radioButtonSame.isChecked()){
                    editTextKpRight.setText(editTextKpLeft.getText());
                }
            }
        });

        editTextKiLeft = view.findViewById(R.id.editText_wheel_ki_left);
        buttonKiLeftDown = view.findViewById(R.id.button_wheel_ki_left_down);
        buttonKiLeftDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKiLeft.setText(String.format("%.2f", Double.parseDouble(editTextKiLeft.getText().toString()) - 0.01));
                if(radioButtonSame.isChecked()){
                    editTextKiRight.setText(editTextKiLeft.getText());
                }
            }
        });
        buttonKiLeftUp = view.findViewById(R.id.button_wheel_ki_left_up);
        buttonKiLeftUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKiLeft.setText(String.format("%.2f", Double.parseDouble(editTextKiLeft.getText().toString()) + 0.01));
                if(radioButtonSame.isChecked()){
                    editTextKiRight.setText(editTextKiLeft.getText());
                }
            }
        });

        editTextKdLeft = view.findViewById(R.id.editText_wheel_kd_left);
        buttonKdLeftDown = view.findViewById(R.id.button_wheel_kd_left_down);
        buttonKdLeftDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKdLeft.setText(String.format("%.2f", Double.parseDouble(editTextKdLeft.getText().toString()) - 0.01));
                if(radioButtonSame.isChecked()){
                    editTextKdRight.setText(editTextKdLeft.getText());
                }
            }
        });
        buttonKdLeftUp = view.findViewById(R.id.button_wheel_kd_left_up);
        buttonKdLeftUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKdLeft.setText(String.format("%.2f", Double.parseDouble(editTextKdLeft.getText().toString()) + 0.01));
                if(radioButtonSame.isChecked()){
                    editTextKdRight.setText(editTextKdLeft.getText());
                }
            }
        });

        editTextReferenceLeft = view.findViewById(R.id.editText_wheel_reference_left);
        buttonReferenceLeftDown = view.findViewById(R.id.button_wheel_reference_left_down);
        buttonReferenceLeftDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextReferenceLeft.setText(String.format("%.2f", Double.parseDouble(editTextReferenceLeft.getText().toString()) - 0.01));
                if(radioButtonSame.isChecked()){
                    editTextReferenceRight.setText(editTextReferenceLeft.getText());
                }
            }
        });
        buttonReferenceLeftUp = view.findViewById(R.id.button_wheel_reference_left_up);
        buttonReferenceLeftUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextReferenceLeft.setText(String.format("%.2f", Double.parseDouble(editTextReferenceLeft.getText().toString()) + 0.01));
                if(radioButtonSame.isChecked()){
                    editTextReferenceRight.setText(editTextReferenceLeft.getText());
                }
            }
        });

        // right motor
        editTextKpRight = view.findViewById(R.id.editText_wheel_kp_right);
        buttonKpRightDown = view.findViewById(R.id.button_wheel_kp_right_down);
        buttonKpRightDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKpRight.setText(String.format("%.2f", Double.parseDouble(editTextKpRight.getText().toString()) - 0.01));
                if(radioButtonSame.isChecked()){
                    editTextKpLeft.setText(editTextKpRight.getText());
                }
            }
        });
        buttonKpRightUp = view.findViewById(R.id.button_wheel_kp_right_up);
        buttonKpRightUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKpRight.setText(String.format("%.2f", Double.parseDouble(editTextKpRight.getText().toString()) + 0.01));
                if(radioButtonSame.isChecked()){
                    editTextKpLeft.setText(editTextKpRight.getText());
                }
            }
        });

        editTextKiRight = view.findViewById(R.id.editText_wheel_ki_right);
        buttonKiRightDown = view.findViewById(R.id.button_wheel_ki_right_down);
        buttonKiRightDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKiRight.setText(String.format("%.2f", Double.parseDouble(editTextKiRight.getText().toString()) - 0.01));
                if(radioButtonSame.isChecked()){
                    editTextKiLeft.setText(editTextKiRight.getText());
                }
            }
        });
        buttonKiRightUp = view.findViewById(R.id.button_wheel_ki_right_up);
        buttonKiRightUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKiRight.setText(String.format("%.2f", Double.parseDouble(editTextKiRight.getText().toString()) + 0.01));
                if(radioButtonSame.isChecked()){
                    editTextKiLeft.setText(editTextKiRight.getText());
                }
            }
        });

        editTextKdRight = view.findViewById(R.id.editText_wheel_kd_right);
        buttonKdRightDown = view.findViewById(R.id.button_wheel_kd_right_down);
        buttonKdRightDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKdRight.setText(String.format("%.2f", Double.parseDouble(editTextKdRight.getText().toString()) - 0.01));
                if(radioButtonSame.isChecked()){
                    editTextKdLeft.setText(editTextKdRight.getText());
                }
            }
        });
        buttonKdRightUp = view.findViewById(R.id.button_wheel_kd_right_up);
        buttonKdRightUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKdRight.setText(String.format("%.2f", Double.parseDouble(editTextKdRight.getText().toString()) + 0.01));
                if(radioButtonSame.isChecked()){
                    editTextKdLeft.setText(editTextKdRight.getText());
                }
            }
        });

        editTextReferenceRight = view.findViewById(R.id.editText_wheel_reference_right);
        buttonReferenceRightDown = view.findViewById(R.id.button_wheel_reference_right_down);
        buttonReferenceRightDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextReferenceRight.setText(String.format("%.2f", Double.parseDouble(editTextReferenceRight.getText().toString()) - 0.01));
                if(radioButtonSame.isChecked()){
                    editTextReferenceLeft.setText(editTextReferenceRight.getText());
                }
            }
        });
        buttonReferenceRightUp = view.findViewById(R.id.button_wheel_reference_right_up);
        buttonReferenceRightUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextReferenceRight.setText(String.format("%.2f", Double.parseDouble(editTextReferenceRight.getText().toString()) + 0.01));
                if(radioButtonSame.isChecked()){
                    editTextReferenceLeft.setText(editTextReferenceRight.getText());
                }
            }
        });

        // radio button
        radioButtonSame = view.findViewById(R.id.radioButton_wheel_same);
        radioButtonDifferent = view.findViewById(R.id.radioButton_wheel_different);
        radioGroup = view.findViewById(R.id.radioGroup_wheel);
        radioGroup.setOnCheckedChangeListener(this);

        // bottom
        buttonSendPid = view.findViewById(R.id.button_send_pid_wheel);
        buttonSendPid.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                send();
            }
        });
        buttonStopPid = view.findViewById(R.id.button_stop_pid_wheel);
        buttonStopPid.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                stop();
            }
        });

        return view;
    }

    @Override
    public void onCheckedChanged(RadioGroup group, int checkedId) {
        if(checkedId == R.id.radioButton_wheel_same){
            editTextKpRight.setText( editTextKpLeft.getText() );
            editTextKiRight.setText( editTextKiLeft.getText() );
            editTextKdRight.setText( editTextKdLeft.getText() );
            editTextReferenceRight.setText( editTextReferenceLeft.getText() );
        }
    }

    public void send(){
        String kpLeft = editTextKpLeft.getText().toString();
        String kiLeft = editTextKiLeft.getText().toString();
        String kdLeft = editTextKdLeft.getText().toString();
        String referenceLeft = editTextReferenceLeft.getText().toString();

        String kpRight = editTextKpRight.getText().toString();
        String kiRight = editTextKiRight.getText().toString();
        String kdRight = editTextKdRight.getText().toString();
        String referenceRight = editTextReferenceRight.getText().toString();

        if( kpLeft.isEmpty() || kiLeft.isEmpty() || kdLeft.isEmpty() || referenceLeft.isEmpty() || kpRight.isEmpty() || kiRight.isEmpty() || kdRight.isEmpty() || referenceRight.isEmpty() ){
            Toast.makeText(mainActivity, "Please Input All Parameters", Toast.LENGTH_LONG).show();
        } else{
            String data = "~2,"                                                             // send mode 2
                        + "2,"                                                              // control mode 2
                        + kpLeft + "," + kiLeft + "," + kdLeft + "," + referenceLeft + ","   // left motor
                        + kpRight + "," + kiRight + "," + kdRight + "," + referenceRight + "#";    // right motor

            System.out.println(data);
            mainActivity.bluetoothFragment.bluetoothSendData(data);
        }
    }

    public void stop(){
        String data = "~2,"                                              // send mode 2
                    + "0#";                                              // control mode 0
        System.out.println(data);
        mainActivity.bluetoothFragment.bluetoothSendData(data);
    }

    public void setActivity(MainActivity mainActivity) {
        this.mainActivity = mainActivity;
    }
}
