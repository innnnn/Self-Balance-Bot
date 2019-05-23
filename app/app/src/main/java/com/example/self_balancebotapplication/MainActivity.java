package com.example.self_balancebotapplication;

import android.app.FragmentTransaction;
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
import android.view.Gravity;
import android.view.MenuItem;

import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity implements NavigationView.OnNavigationItemSelectedListener {
    private Toolbar toolbar;
    private DrawerLayout drawer;

    // fragment
    public Fragment fragment[] = new Fragment[6];
    public HomeFragment homeFragment = new HomeFragment();
    public BluetoothFragment bluetoothFragment = new BluetoothFragment();
    public JoystickControlFragment joystickControlFragment = new JoystickControlFragment();
    public PIDControlFragment pidControlFragment = new PIDControlFragment();
    private StatefeedbackControlFragment statefeedbackControlFragment = new StatefeedbackControlFragment();
    private CarStateFragment carStateFragment = new CarStateFragment();
    private Fragment lastFragment;
    private Fragment currentFragment;
    private int currentFragmentIndex;
    private int previousFragmentIndex;

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

        // new fragment
        fragment[0] =  new HomeFragment();
        fragment[1] = new BluetoothFragment();
        fragment[2] = new JoystickControlFragment();
        fragment[3] = new PIDControlFragment();
        fragment[4] = new StatefeedbackControlFragment();
        fragment[5] = new CarStateFragment();

        // set the homeFragment as first fragment
        // ******* bug !!!!!
        getSupportFragmentManager().beginTransaction().add(R.id.fragment_container, homeFragment).commit();
        getSupportFragmentManager().beginTransaction().hide(homeFragment).commit();
        //getSupportFragmentManager().beginTransaction().show(homeFragment).commit();
        lastFragment = homeFragment;
        navigationView.setCheckedItem(R.id.nav_home);

        // set mainActivity to each fragment
        bluetoothFragment.setActivity(this);
        pidControlFragment.setActivity(this);
        statefeedbackControlFragment.setActivity(this);
        carStateFragment.setActivity(this);
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
            case R.id.nav_pid_control:
                currentFragment = pidControlFragment;
                break;
            case R.id.nav_statefeedback_control:
                currentFragment = statefeedbackControlFragment;
                break;
            case R.id.nav_car_state:
                currentFragment = carStateFragment;
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
        float data[] = new float[temp.length];
        for(int i=0; i<temp.length; i++){
            System.out.println(temp[i]);
            data[i] = Float.parseFloat(temp[i]);
        }

        switch( (int)data[0] ){
            case 1:
                carStateFragment.receiveData(temp);
                break;
            case 2:
                break;
        }


    }
}