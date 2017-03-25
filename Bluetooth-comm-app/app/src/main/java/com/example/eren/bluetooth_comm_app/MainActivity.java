package com.example.eren.bluetooth_comm_app;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.bluetooth.BluetoothAdapter;
import android.view.View;
import android.widget.TextView;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    public static TextView textViewObj;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        BluetoothAdapter mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (mBluetoothAdapter == null) {
            // Device does not support Bluetooth
            ((TextView) findViewById(R.id.mainText)).setText("Device Doesn't Support Bluetooth");
        } else {
            ((TextView) findViewById(R.id.mainText)).setText("Device Supports Bluetooth...");
        }

    }
}
