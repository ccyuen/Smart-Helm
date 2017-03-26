package com.example.eren.bluetooth_comm_app;

import java.lang.Object;
    import java.util.*;
    import java.util.stream.*;
    import java.lang.*;
        import java.io.IOException;
        import java.io.InputStream;
        import java.io.OutputStream;
        import android.os.Handler;
	    import android.os.Message;
        import java.lang.String;


import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.view.View;
    import android.widget.TextView;
        import android.widget.EditText;
import android.content.Intent;


import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    public static TextView textViewObj;
    BluetoothAdapter mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (mBluetoothAdapter == null) { // Device does not support Bluetooth
            ((TextView) findViewById(R.id.mainText)).setText("Device Doesn't Support Bluetooth");
        }

        if (!mBluetoothAdapter.isEnabled()) { //turn on bluetooth if disabled
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, 1);
        }

        Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
        BluetoothDevice mDevice = null;
        String [] pairedList =  new String [pairedDevices.size()];
        int listCounter = 0;
        //String pairedName = "";
        String pairedAddress = "98:4F:EE:02:DC:9A";

        if (pairedDevices.size() > 0) {

            ((TextView) findViewById(R.id.mainText)).setText("Paired Devices:");

            for (BluetoothDevice device : pairedDevices) {

                if (device.getAddress().equals(pairedAddress)) {
                    mDevice = device;
                }

                pairedList[listCounter] = device.getName();
                listCounter++;
            }

            for (int i = 0; i < pairedDevices.size(); i ++) {
                ((TextView)findViewById(R.id.pairedList)).append("\n" + pairedList[i]);
            }

            if (mDevice != null) {
                ((TextView) findViewById(R.id.connectText)).append(mDevice.getName());
                 ConnectThread mConnectThread = new ConnectThread(mDevice);
                 mConnectThread.start();
            }
        }
    }

    private class ConnectThread extends Thread {
        private final BluetoothSocket mmSocket;
        private final BluetoothDevice mmDevice;
        //private final BluetoothAdapter mBluetoothAdapter = null;
        private /*static*/ final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");

        public ConnectThread(BluetoothDevice device) {
            BluetoothSocket tmp = null;
            mmDevice = device;
            try {
                tmp = device.createRfcommSocketToServiceRecord(MY_UUID);
            } catch (IOException e) { }
            mmSocket = tmp;
        }

        public void run() {
            mBluetoothAdapter.cancelDiscovery();
            try {
                mmSocket.connect();
            } catch (IOException connectException) {
                try {
                    mmSocket.close();
                } catch (IOException closeException) { }
                return;
            }
        }

        public void cancel() {
            try {
                mmSocket.close();
            } catch (IOException e) { }
        }
    }

    private class ConnectedThread extends Thread {
        private final BluetoothSocket mmSocket;
        private final InputStream mmInStream;
        private final OutputStream mmOutStream;
        public ConnectedThread(BluetoothSocket socket) {
            mmSocket = socket;
            InputStream tmpIn = null;
            OutputStream tmpOut = null;
            try {
                tmpIn = socket.getInputStream();
                tmpOut = socket.getOutputStream();
            } catch (IOException e) { }
            mmInStream = tmpIn;
            mmOutStream = tmpOut;
        }
        public void run() {
            byte[] buffer = new byte[1024];
            int begin = 0;
            int bytes = 0;
            while (true) {
                try {
                    bytes += mmInStream.read(buffer, bytes, buffer.length - bytes);

                    write(buffer);

                    for(int i = begin; i < bytes; i++) {
                        if(buffer[i] == "#".getBytes()[0]) {
                            mHandler.obtainMessage(1, begin, i, buffer).sendToTarget();
                            begin = i + 1;
                            if(i == bytes - 1) {
                                bytes = 0;
                                begin = 0;
                            }
                        }
                    }
                } catch (IOException e) {
                    break;
                }
            }
        }
        public void write(byte[] bytes) {
            try {
                mmOutStream.write(bytes);
            } catch (IOException e) { }
        }
        public void cancel() {
            try {
                mmSocket.close();
            } catch (IOException e) { }
        }
    }

    Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            byte[] writeBuf = (byte[]) msg.obj;
            int begin = (int)msg.arg1;
            int end = (int)msg.arg2;

            switch(msg.what) {
                case 1:
                    String writeMessage = new String(writeBuf);
                    writeMessage = writeMessage.substring(begin, end);
                    break;
            }
        }
    };

}
