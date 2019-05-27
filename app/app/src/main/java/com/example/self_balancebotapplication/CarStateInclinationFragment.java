package com.example.self_balancebotapplication;

import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class CarStateInclinationFragment extends Fragment {
    MainActivity mainActivity;

    private TextView textViewInclination;
    private TextView textViewLeftWheel;
    private TextView textViewRightWheel;

    private double psi = 0;
    private double leftAngle = 0;
    private double rightAngle = 0;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_car_state_inclination, container, false);

        textViewInclination = view.findViewById(R.id.textView_state_inclination);
        textViewInclination.setText("0");
        textViewLeftWheel = view.findViewById(R.id.textView_state_left_wheel);
        textViewLeftWheel.setText("0");
        textViewRightWheel = view.findViewById(R.id.textView_state_right_wheel);
        textViewRightWheel.setText("0");



        return view;
    }

    public void receiveData(double[] data){
        if( data.length==4 ){
            psi = Math.toDegrees(data[1]);
            leftAngle = Math.toDegrees(data[2]);
            rightAngle = Math.toDegrees(data[3]);
        }
    }

    public void updateInformation(){
        if( (textViewInclination!=null) && (textViewLeftWheel!=null) && (textViewRightWheel!=null) ){
            textViewInclination.setText(String.format("%.02f (degree)", psi));
            textViewLeftWheel.setText(String.format("%.02f (degree)", leftAngle));
            textViewRightWheel.setText(String.format("%.02f (degree)", rightAngle));
        }
    }

    public void setActivity(MainActivity mainActivity) {
        this.mainActivity = mainActivity;
    }
}
