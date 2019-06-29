package com.example.self_balancebotapplication;

import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class DebugFragment extends Fragment {
    MainActivity mainActivity;

    private TextView textViewKp;
    private TextView textViewKi;
    private TextView textViewKd;
    private TextView textViewReference;

    private String kp;
    private String ki;
    private String kd;
    private String reference;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_debug, container, false);

        textViewKp = view.findViewById(R.id.textView_debug_kp);
        textViewKp.setText(kp);
        textViewKi = view.findViewById(R.id.textView_debug_ki);
        textViewKi.setText(ki);
        textViewKd = view.findViewById(R.id.textView_debug_kd);
        textViewKd.setText(kd);
        textViewReference = view.findViewById(R.id.textView_debug_reference);
        textViewReference.setText(reference);

        return view;
    }

    public void receiveData(String[] data){
        if( data.length==6 ){
            kp = data[2];
            ki = data[3];
            kd = data[4];
            reference = data[5];
        }
    }

    public void updateInformation(){
        if( (textViewKp!=null) && (textViewKi!=null) && (textViewKd!=null) && (textViewReference!=null) ){
            textViewKp.setText(kp);
            textViewKi.setText(ki);
            textViewKd.setText(kd);
            textViewReference.setText(reference);
        }
    }

    public void setActivity(MainActivity mainActivity) {
        this.mainActivity = mainActivity;
    }
}
