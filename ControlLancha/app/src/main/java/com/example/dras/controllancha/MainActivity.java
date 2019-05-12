package com.example.dras.controllancha;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

public class MainActivity extends AppCompatActivity {
    int REQUEST_ENABLE_BT =1;
    BluetoothAdapter mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
    Set<BluetoothDevice> pairedDevices;

    private RecyclerView recyclerViewsinc,recyclerViewfound;
    private RecyclerView.Adapter adaptersinc, adapterfound;
    private RecyclerView.LayoutManager layoutManagersinc, layoutManagerfound;

    List<DevicePOJO> itemssinc;
    List<DevicePOJO> itemsfound;

   // private SingBroadcastReceiver mReceiver;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        //Para dispositivos sincronizados
        itemssinc = new ArrayList<DevicePOJO>();
        recyclerViewsinc =(RecyclerView)findViewById(R.id.RV_devicessincronizados);
        recyclerViewsinc.setHasFixedSize(true);
        layoutManagersinc =new LinearLayoutManager(this);
        recyclerViewsinc.setLayoutManager(layoutManagersinc);
        adaptersinc =new DeviceAdapter(itemssinc, this);
        recyclerViewsinc.setAdapter(adaptersinc);


        //Verificar si el phone es compatible con bluethoot
        if (mBluetoothAdapter == null) {
            // Device does not support Bluetooth
        }else{
            if (!mBluetoothAdapter.isEnabled()) {
                Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
                // If there are paired devices
            }else{
                if (itemssinc.size()>0){
                    itemssinc.clear();
                }
                pairedDevices = mBluetoothAdapter.getBondedDevices();
                if (pairedDevices.size() > 0) {
                    // Loop through paired devices
                    for (BluetoothDevice device : pairedDevices) {
                        // Add the name and address to an array adapter to show in a ListView
                        itemssinc.add(new DevicePOJO(device.getName(),device.getAddress()));
                        // mArrayAdapter.add(device.getName() + "\n" + device.getAddress());
                    }
                    adaptersinc.notifyDataSetChanged();
                }
            }

        }



        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //Verificar si el phone es compatible con bluethoot
                if (mBluetoothAdapter == null) {
                    Toast.makeText(MainActivity.this, "Device don't support", Toast.LENGTH_SHORT).show();
                    // Device does not support Bluetooth
                }else{
                    if (!mBluetoothAdapter.isEnabled()) {
                        Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                        startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);

                        // If there are paired devices
                    }else{

                        if (itemssinc.size()>0){
                            itemssinc.clear();
                        }
                         pairedDevices = mBluetoothAdapter.getBondedDevices();
                        if (pairedDevices.size() > 0) {
                            // Loop through paired devices
                            for (BluetoothDevice device : pairedDevices) {
                                // Add the name and address to an array adapter to show in a ListView
                                itemssinc.add(new DevicePOJO(device.getName(),device.getAddress()));
                                // mArrayAdapter.add(device.getName() + "\n" + device.getAddress());
                            }
                    }
                        adaptersinc.notifyDataSetChanged();


                    }
                }



            }
        });

       FloatingActionButton fab2 = (FloatingActionButton) findViewById(R.id.fab2);
        fab2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intentOpenBluetoothSettings = new Intent();
                intentOpenBluetoothSettings.setAction(android.provider.Settings.ACTION_BLUETOOTH_SETTINGS);
                startActivity(intentOpenBluetoothSettings);
            }
        });

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            Intent intent = new Intent(getApplicationContext(),AcelerometroActivity.class);
            intent.putExtra("NAME","EXAMPLE");
            intent.putExtra("MAC","123456789");
            intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            getApplicationContext().startActivity(intent);
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
