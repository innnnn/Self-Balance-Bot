package com.example.self_balancebotapplication;

import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.Toast;

public class CarStateFragment extends Fragment {
    MainActivity mainActivity;
    boolean show = false;

    private TextView textViewInclination;
    private TextView textViewLeftWheel;
    private TextView textViewRightWheel;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_car_state, container, false);

        textViewInclination = view.findViewById(R.id.textView_state_inclination);
        textViewInclination.setText("0");
        textViewLeftWheel = view.findViewById(R.id.textView_state_left_wheel);
        textViewLeftWheel.setText("0");
        textViewRightWheel = view.findViewById(R.id.textView_state_right_wheel);
        textViewRightWheel.setText("0");

        return view;
    }

    public void receiveData(String[] data){
        if( data.length==4 && !(this.isHidden()) ){
            System.out.println("Success");
            textViewInclination.setText(data[1]);
            textViewLeftWheel.setText(data[2]);
            textViewRightWheel.setText(data[3]);
        } else{
            Toast.makeText(mainActivity, "Receive Incorrect Data", Toast.LENGTH_LONG).show();
            System.out.println("Fall");
        }
    }

    public void setActivity(MainActivity mainActivity) {
        this.mainActivity = mainActivity;
    }

    public void setShow(boolean show){
        this.show = show;
    }
}
