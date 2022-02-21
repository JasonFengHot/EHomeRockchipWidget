package com.ehome.rockchip.vendor.sample;

import android.os.Bundle;
import android.util.Log;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import com.ehome.rockchip.vendor.RockchipStorageManager;

public class MainActivity extends AppCompatActivity {
    private RockchipStorageManager mManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mManager = new RockchipStorageManager();
    }

    public void get(View view) {
       String sn =  mManager.getSerialNumber();

        Log.d("RockchipStorageManager", "sn -> " + sn);

    }
}