package com.example.self_balancebotapplication;

import android.content.pm.ActivityInfo;
import android.support.annotation.NonNull;
import android.support.design.widget.NavigationView;
import android.support.v4.app.Fragment;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.view.MenuItem;

import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity implements NavigationView.OnNavigationItemSelectedListener {
    private Toolbar toolbar;
    private DrawerLayout drawer;

    // update ui component
    private Timer timer;
    private TimerTask task;

    // fragment
    public HomeFragment homeFragment = new HomeFragment();
    public BluetoothFragment bluetoothFragment = new BluetoothFragment();
    public JoystickControlFragment joystickControlFragment = new JoystickControlFragment();
    public PIDControlInclinationFragment pidControlInclinationFragment = new PIDControlInclinationFragment();
    public PIDControlWheelFragment pidControlWheelFragment = new PIDControlWheelFragment();
    private StatefeedbackControlFragment statefeedbackControlFragment = new StatefeedbackControlFragment();
    private CarStateInclinationFragment carStateInclinationFragment = new CarStateInclinationFragment();
    private CarStateWheelFragment carStateWheelFragment = new CarStateWheelFragment();
    private Fragment lastFragment;
    private Fragment currentFragment;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);

        toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        drawer = findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(this, drawer, toolbar,
                R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.addDrawerListener(toggle);
        toggle.syncState();

        // add navigation item select listener
        NavigationView navigationView = findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);

        // set the homeFragment as first fragment
        // ******* bug !!!!!
        getSupportFragmentManager().beginTransaction().add(R.id.fragment_container, homeFragment).commit();
        getSupportFragmentManager().beginTransaction().hide(homeFragment).commit();
        //getSupportFragmentManager().beginTransaction().show(homeFragment).commit();
        lastFragment = homeFragment;
        navigationView.setCheckedItem(R.id.nav_home);

        // set mainActivity to each fragment
        bluetoothFragment.setActivity(this);
        pidControlInclinationFragment.setActivity(this);
        pidControlWheelFragment.setActivity(this);
        statefeedbackControlFragment.setActivity(this);
        carStateInclinationFragment.setActivity(this);
        carStateWheelFragment.setActivity(this);

        task = new TimerTask() {
            @Override
            public void run() {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        carStateInclinationFragment.updateInformation();
                    }
                });
            }
        };
        timer = new Timer();
        timer.scheduleAtFixedRate(task, 1000, 250);
    }

    @Override
    public boolean onNavigationItemSelected(@NonNull MenuItem menuItem) { // which fragment is selected
        int id = menuItem.getItemId();
        switch(id){
            case R.id.nav_home:
                currentFragment = homeFragment;
                break;
            case R.id.nav_bluetooth:
                currentFragment = bluetoothFragment;
                break;
            case R.id.nav_joystick_control:
                currentFragment = joystickControlFragment;
                break;
            case R.id.nav_pid_control_inclination:
                currentFragment = pidControlInclinationFragment;
                break;
            case R.id.nav_pid_control_wheel:
                currentFragment = pidControlWheelFragment;
                break;
            case R.id.nav_statefeedback_control:
                currentFragment = statefeedbackControlFragment;
                break;
            case R.id.nav_car_state_inclination:
                currentFragment = carStateInclinationFragment;
                break;
            case R.id.nav_car_state_wheel:
                currentFragment = carStateWheelFragment;
                break;
        }

        // use hide and show , instead of replace
        // hide, show: does not destroy fragment
        // replace: destroy old fragment and create an new fragment
        if(currentFragment != lastFragment){
            if(!currentFragment.isAdded()){
                getSupportFragmentManager().beginTransaction().add(R.id.fragment_container, currentFragment).commit();
                getSupportFragmentManager().beginTransaction().hide(lastFragment).commit();
                getSupportFragmentManager().beginTransaction().show(currentFragment).commit();
            } else {
                getSupportFragmentManager().beginTransaction().hide(lastFragment).commit();
                getSupportFragmentManager().beginTransaction().show(currentFragment).commit();
            }

            lastFragment = currentFragment;
        }

        drawer.closeDrawer(GravityCompat.START);
        return true;
    }

    @Override
    public void onBackPressed() {
        if(drawer.isDrawerOpen(GravityCompat.START)){
            drawer.closeDrawer(GravityCompat.START);
        } else{
            super.onBackPressed();
        }
    }

    public void processData(String rawData){
        String temp[] = rawData.split(",");
        System.out.println(temp.length);
        double data[] = new double[temp.length];
        for(int i=0; i<temp.length; i++){
            data[i] = Double.parseDouble(temp[i]);
            System.out.println(data[i]);
        }

        switch( (int)data[0] ){
            case 1:
                carStateInclinationFragment.receiveData(data);
                break;
            case 2:

                break;
        }


    }
}