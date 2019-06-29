package com.example.self_balancebotapplication;

import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class CarStateFragment extends Fragment {
    MainActivity mainActivity;

    private TextView textViewPsi;
    private TextView textViewOutput;
    private TextView textViewThetaL;
    private TextView textViewThetaR;
    private TextView textViewTheta;
    private TextView textViewPhi;
    private TextView textViewIndex;

    private double psi = 0;
    private double output = 0;
    private double thetaL = 0;
    private double thetaR = 0;
    private double theta = 0;
    private double phi = 0;
    private double index = 0;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_car_state, container, false);

        textViewPsi = view.findViewById(R.id.textView_state_psi);
        textViewPsi.setText("0");
        textViewOutput = view.findViewById(R.id.textView_state_output);
        textViewOutput.setText("0");
        textViewThetaL = view.findViewById(R.id.textView_thetaL);
        textViewThetaL.setText("0");
        textViewThetaR = view.findViewById(R.id.textView_thetaR);
        textViewThetaR.setText("0");
        textViewTheta = view.findViewById(R.id.textView_theta);
        textViewTheta.setText("0");
        textViewPhi = view.findViewById(R.id.textView_phi);
        textViewPhi.setText("0");
        textViewIndex = view.findViewById(R.id.textView_index);
        textViewIndex.setText("0");

        return view;
    }

    public void receiveData(double[] data){
        if( data.length==9 ){
            psi = Math.toDegrees(data[2]);
            output = data[3];
            thetaL = data[4];
            thetaR = data[5];
            theta = data[6];
            phi = data[7];
            index = data[8];
        }
    }

    public void updateInformation(){
//        if( (textViewPsi!=null) && (textViewOutput!=null) && (textViewThetaL!=null) && (textViewThetaR!=null) && (textViewPhi!=null) && (textViewOutputDiff!=null) && (textViewMode!=null) ){
        if( (textViewPsi!=null) && (textViewOutput!=null) && (textViewThetaL!=null) && (textViewThetaR!=null) && (textViewTheta!=null) && (textViewPhi!=null) && (textViewIndex!=null) ){
            textViewPsi.setText(String.format("%.02f  (degree)", psi));
            textViewOutput.setText(String.format("%.02f  (voltage)", output));
            textViewThetaL.setText(String.format("%.02f (rad)", thetaL));
            textViewThetaR.setText(String.format("%.02f (rad)", thetaR));
            textViewTheta.setText(String.format("%.02f  (cm)", theta));
            textViewPhi.setText(String.format("%.02f (rad)", phi));
            textViewIndex.setText(String.format("%.02f (cm)", index));
        }
    }

    public void setActivity(MainActivity mainActivity) {
        this.mainActivity = mainActivity;
    }
}
