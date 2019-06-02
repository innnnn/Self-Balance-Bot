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

public class PIDControlFragment extends Fragment implements RadioGroup.OnCheckedChangeListener {
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
    private RadioButton radioButtonPsi;
    private RadioButton radioButtonTheta;
    public RadioGroup radioGroupController;

    private RadioButton radioButtonSame;
    private RadioButton radioButtonDifferent;
    private RadioGroup radioGroupValue;

    // bottom
    private Button buttonSendPid;
    private Button buttonStopPid;

    // kp, ki, kd, reference
    String kpLeft;
    String kiLeft;
    String kdLeft;
    String referenceLeft;

    String kpRight;
    String kiRight;
    String kdRight;
    String referenceRight;

    // update information
    public boolean needUpdate = false;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_pid_control, container, false);

        // left motor
        editTextKpLeft = view.findViewById(R.id.editText_inclination_kp_left);
        buttonKpLeftDown = view.findViewById(R.id.button_inclination_kp_left_down);
        buttonKpLeftDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKpLeft.setText(String.format("%.1f", Double.parseDouble(editTextKpLeft.getText().toString()) - 0.1));
                if (radioButtonSame.isChecked()) {
                    editTextKpRight.setText(editTextKpLeft.getText());
                }
            }
        });
        buttonKpLeftUp = view.findViewById(R.id.button_inclination_kp_left_up);
        buttonKpLeftUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKpLeft.setText(String.format("%.1f", Double.parseDouble(editTextKpLeft.getText().toString()) + 0.1));
                if (radioButtonSame.isChecked()) {
                    editTextKpRight.setText(editTextKpLeft.getText());
                }
            }
        });

        editTextKiLeft = view.findViewById(R.id.editText_inclination_ki_left);
        buttonKiLeftDown = view.findViewById(R.id.button_inclination_ki_left_down);
        buttonKiLeftDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKiLeft.setText(String.format("%.0f", Double.parseDouble(editTextKiLeft.getText().toString()) - 1));
                if (radioButtonSame.isChecked()) {
                    editTextKiRight.setText(editTextKiLeft.getText());
                }
            }
        });
        buttonKiLeftUp = view.findViewById(R.id.button_inclination_ki_left_up);
        buttonKiLeftUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKiLeft.setText(String.format("%.0f", Double.parseDouble(editTextKiLeft.getText().toString()) + 1));
                if (radioButtonSame.isChecked()) {
                    editTextKiRight.setText(editTextKiLeft.getText());
                }
            }
        });

        editTextKdLeft = view.findViewById(R.id.editText_inclination_kd_left);
        buttonKdLeftDown = view.findViewById(R.id.button_inclination_kd_left_down);
        buttonKdLeftDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKdLeft.setText(String.format("%.2f", Double.parseDouble(editTextKdLeft.getText().toString()) - 0.01));
                if (radioButtonSame.isChecked()) {
                    editTextKdRight.setText(editTextKdLeft.getText());
                }
            }
        });
        buttonKdLeftUp = view.findViewById(R.id.button_inclination_kd_left_up);
        buttonKdLeftUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKdLeft.setText(String.format("%.2f", Double.parseDouble(editTextKdLeft.getText().toString()) + 0.01));
                if (radioButtonSame.isChecked()) {
                    editTextKdRight.setText(editTextKdLeft.getText());
                }
            }
        });

        editTextReferenceLeft = view.findViewById(R.id.editText_inclination_reference_left);
        buttonReferenceLeftDown = view.findViewById(R.id.button_inclination_reference_left_down);
        buttonReferenceLeftDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextReferenceLeft.setText(String.format("%.3f", Double.parseDouble(editTextReferenceLeft.getText().toString()) - 0.005));
                if (radioButtonSame.isChecked()) {
                    editTextReferenceRight.setText(editTextReferenceLeft.getText());
                }
            }
        });
        buttonReferenceLeftUp = view.findViewById(R.id.button_inclination_reference_left_up);
        buttonReferenceLeftUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextReferenceLeft.setText(String.format("%.3f", Double.parseDouble(editTextReferenceLeft.getText().toString()) + 0.005));
                if (radioButtonSame.isChecked()) {
                    editTextReferenceRight.setText(editTextReferenceLeft.getText());
                }
            }
        });

        // right motor
        editTextKpRight = view.findViewById(R.id.editText_inclination_kp_right);
        buttonKpRightDown = view.findViewById(R.id.button_inclination_kp_right_down);
        buttonKpRightDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKpRight.setText(String.format("%.1f", Double.parseDouble(editTextKpRight.getText().toString()) - 0.1));
                if (radioButtonSame.isChecked()) {
                    editTextKpLeft.setText(editTextKpRight.getText());
                }
            }
        });
        buttonKpRightUp = view.findViewById(R.id.button_inclination_kp_right_up);
        buttonKpRightUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKpRight.setText(String.format("%.1f", Double.parseDouble(editTextKpRight.getText().toString()) + 0.1));
                if (radioButtonSame.isChecked()) {
                    editTextKpLeft.setText(editTextKpRight.getText());
                }
            }
        });

        editTextKiRight = view.findViewById(R.id.editText_inclination_ki_right);
        buttonKiRightDown = view.findViewById(R.id.button_inclination_ki_right_down);
        buttonKiRightDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKiRight.setText(String.format("%.0f", Double.parseDouble(editTextKiRight.getText().toString()) - 1));
                if (radioButtonSame.isChecked()) {
                    editTextKiLeft.setText(editTextKiRight.getText());
                }
            }
        });
        buttonKiRightUp = view.findViewById(R.id.button_inclination_ki_right_up);
        buttonKiRightUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKiRight.setText(String.format("%.0f", Double.parseDouble(editTextKiRight.getText().toString()) + 1));
                if (radioButtonSame.isChecked()) {
                    editTextKiLeft.setText(editTextKiRight.getText());
                }
            }
        });

        editTextKdRight = view.findViewById(R.id.editText_inclination_kd_right);
        buttonKdRightDown = view.findViewById(R.id.button_inclination_kd_right_down);
        buttonKdRightDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKdRight.setText(String.format("%.2f", Double.parseDouble(editTextKdRight.getText().toString()) - 0.01));
                if (radioButtonSame.isChecked()) {
                    editTextKdLeft.setText(editTextKdRight.getText());
                }
            }
        });
        buttonKdRightUp = view.findViewById(R.id.button_inclination_kd_right_up);
        buttonKdRightUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextKdRight.setText(String.format("%.2f", Double.parseDouble(editTextKdRight.getText().toString()) + 0.01));
                if (radioButtonSame.isChecked()) {
                    editTextKdLeft.setText(editTextKdRight.getText());
                }
            }
        });

        editTextReferenceRight = view.findViewById(R.id.editText_inclination_reference_right);
        buttonReferenceRightDown = view.findViewById(R.id.button_inclination_reference_right_down);
        buttonReferenceRightDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextReferenceRight.setText(String.format("%.3f", Double.parseDouble(editTextReferenceRight.getText().toString()) - 0.005));
                if (radioButtonSame.isChecked()) {
                    editTextReferenceLeft.setText(editTextReferenceRight.getText());
                }
            }
        });
        buttonReferenceRightUp = view.findViewById(R.id.button_inclination_reference_right_up);
        buttonReferenceRightUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                editTextReferenceRight.setText(String.format("%.3f", Double.parseDouble(editTextReferenceRight.getText().toString()) + 0.005));
                if (radioButtonSame.isChecked()) {
                    editTextReferenceLeft.setText(editTextReferenceRight.getText());
                }
            }
        });

        // radio button
        radioButtonPsi = view.findViewById(R.id.radioButton_psi);
        radioButtonTheta = view.findViewById(R.id.radioButton_theta);
        radioGroupController = view.findViewById(R.id.radioGroup_controller);
        radioGroupController.setOnCheckedChangeListener(this);

        radioButtonSame = view.findViewById(R.id.radioButton_same);
        radioButtonDifferent = view.findViewById(R.id.radioButton_different);
        radioGroupValue = view.findViewById(R.id.radioGroup_value);
        radioGroupValue.setOnCheckedChangeListener(this);

        // bottom
        buttonSendPid = view.findViewById(R.id.button_send_pid_inclination);
        buttonSendPid.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                send();
            }
        });
        buttonStopPid = view.findViewById(R.id.button_stop_pid_inclination);
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
        if (checkedId == R.id.radioButton_same) {
            editTextKpRight.setText(editTextKpLeft.getText());
            editTextKiRight.setText(editTextKiLeft.getText());
            editTextKdRight.setText(editTextKdLeft.getText());
            editTextReferenceRight.setText(editTextReferenceLeft.getText());
        } else if (checkedId == R.id.radioButton_psi || checkedId == R.id.radioButton_theta){
            requestForInformaiton();
        }
    }

    private void send() {
        kpLeft = editTextKpLeft.getText().toString();
        kiLeft = editTextKiLeft.getText().toString();
        kdLeft = editTextKdLeft.getText().toString();
        referenceLeft = editTextReferenceLeft.getText().toString();

        kpRight = editTextKpRight.getText().toString();
        kiRight = editTextKiRight.getText().toString();
        kdRight = editTextKdRight.getText().toString();
        referenceRight = editTextReferenceRight.getText().toString();

        if (kpLeft.isEmpty() || kiLeft.isEmpty() || kdLeft.isEmpty() || referenceLeft.isEmpty() || kpRight.isEmpty() || kiRight.isEmpty() || kdRight.isEmpty() || referenceRight.isEmpty()) {
            Toast.makeText(mainActivity, "Please Input All Parameters", Toast.LENGTH_LONG).show();
        } else {
            String data = "";
            if( radioButtonPsi.isChecked() && radioButtonSame.isChecked() ){
                data = "~1,"                                                              // send mode 1
                     + "2,"                                                               // item mode 2
                     + "1,"                                                               // control 1
                     + kpLeft + "," + kiLeft + "," + kdLeft + "," + referenceLeft + "#";
            } else if( radioButtonPsi.isChecked() && radioButtonDifferent.isChecked() ){
                data = "~1,"                                                              // send mode 1
                     + "2,"                                                               // item mode 2
                     + "2,"                                                               // control 2
                     + kpLeft + "," + kiLeft + "," + kdLeft + "," + referenceLeft + ","
                     + kpRight + "," + kiRight + "," + kdRight + "," + referenceRight + "#";
            } else if( radioButtonTheta.isChecked() && radioButtonSame.isChecked() ){
                data = "~1,"                                                              // send mode 1
                     + "2,"                                                               // item mode 2
                     + "3,"                                                               // control 3
                     + kpLeft + "," + kiLeft + "," + kdLeft + "," + referenceLeft + "#";
            } else if( radioButtonTheta.isChecked() && radioButtonDifferent.isChecked() ){
                data = "~1,"                                                              // send mode 1
                     + "2,"                                                               // item mode 2
                     + "4,"                                                               // control 5
                     + kpLeft + "," + kiLeft + "," + kdLeft + "," + referenceLeft + ","
                     + kpRight + "," + kiRight + "," + kdRight + "," + referenceRight + "#";
            }
            mainActivity.bluetoothFragment.bluetoothSendData(data);
        }
    }

    public void stop() {
        String data = "~2,"                                              // send mode 2
                    + "0#";                                             // control mode 0
        System.out.println(data);
        mainActivity.bluetoothFragment.bluetoothSendData(data);
    }

    public void receiveData(String[] data){
        if( data.length==10 ){
            kpLeft = data[2];
            kiLeft = data[3];
            kdLeft = data[4];
            referenceLeft = data[5];

            kpRight = data[6];
            kiRight = data[7];
            kdRight = data[8];
            referenceRight = data[9];
        }
    }

    public void requestForInformaiton(){
        if (radioButtonPsi.isChecked()) {  // request for psi: kp, ki, kd, reference
            String data = "~2,"
                    + "1#";
            mainActivity.bluetoothFragment.bluetoothSendData(data);
        } else if (radioButtonTheta.isChecked()) {  // request for theta: kp, ki, kd, reference
            String data = "~2,"
                    + "2#";
            mainActivity.bluetoothFragment.bluetoothSendData(data);
        }
    }

    public void updateInformation(){
        if( editTextKpLeft!=null && editTextKiLeft!=null && editTextKdLeft!=null && editTextReferenceLeft!=null && editTextKpRight!=null && editTextKiRight!=null && editTextKdRight!=null && editTextReferenceRight!=null){
            editTextKpLeft.setText(kpLeft);
            editTextKiLeft.setText(kiLeft);
            editTextKdLeft.setText(kdLeft);
            editTextReferenceLeft.setText(referenceLeft);

            editTextKpRight.setText(kpRight);
            editTextKiRight.setText(kiRight);
            editTextKdRight.setText(kdRight);
            editTextReferenceRight.setText(referenceRight);
            needUpdate = false;
        }
    }

    public void checkInformation(double []data){
        double error = 0.0001;
        if( Math.abs(data[2]-Double.parseDouble(kpLeft))<error || Math.abs(data[3]-Double.parseDouble(kiLeft))<error || Math.abs(data[4]-Double.parseDouble(kdLeft))<error || Math.abs(data[5]-Double.parseDouble(referenceLeft))<error
                || Math.abs(data[6]-Double.parseDouble(kpRight))<error || Math.abs(data[7]-Double.parseDouble(kiRight))<error || Math.abs(data[8]-Double.parseDouble(kdRight))<error || Math.abs(data[9]-Double.parseDouble(referenceRight))<error ){
            //Toast.makeText(mainActivity, "Successfully Set the Parameters", Toast.LENGTH_LONG).show();
            System.out.println("Right");
        } else {
            //Toast.makeText(mainActivity, "Fail to Set the Parameters! Please Try Again!", Toast.LENGTH_LONG).show();
            System.out.println("Error");
        }
    }

    public void setActivity(MainActivity mainActivity) {
        this.mainActivity = mainActivity;
    }
}
