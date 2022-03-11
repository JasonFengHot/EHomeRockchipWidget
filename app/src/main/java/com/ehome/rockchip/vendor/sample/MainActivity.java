package com.ehome.rockchip.vendor.sample;

import android.os.Bundle;
import android.util.Log;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.AppCompatTextView;

import com.ehome.rockchip.vendor.RockchipStorageManager;

public class MainActivity extends AppCompatActivity {
    private RockchipStorageManager mManager;

    private AppCompatTextView mTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mTextView = findViewById(R.id.text);

        mManager = new RockchipStorageManager();
    }

    public void get(View view) {

        String sn = mManager.getSerialNumber();
        mTextView.setText(sn);
        Log.d("RockchipStorageManager", "sn -> " + sn);
    }

    public void set(View view) {
        String sn = "1122334455";
        mManager.putSerialNumber(sn);
        Log.d("RockchipStorageManager", "sn -> " + sn);
    }
}