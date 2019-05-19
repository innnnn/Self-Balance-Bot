package com.example.self_balancebotapplication;

import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.jjoe64.graphview.LineGraphView;

public class CarStateFragment extends Fragment {
    private TextView textViewShowState;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_car_state, container, false);
        textViewShowState = (TextView) view.findViewById(R.id.textView_show_state);

        return view;
    }

    public void receiveData(String data){
        if(textViewShowState !=null ){
            try{
                textViewShowState.setText(data);
            } catch (NullPointerException e){
                e.printStackTrace();
            }
        } else{
            System.out.println("receive null pointer");
        }
    }
}
