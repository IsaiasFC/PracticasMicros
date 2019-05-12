package com.example.dras.controllancha;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.ImageButton;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

public class Exoesqueleto extends AppCompatActivity {
    ConnectedThread connectedThread;
    Boolean conexion;
    BluetoothDevice dispositivoblu=null;
    BluetoothAdapter adaptadorblu=BluetoothAdapter.getDefaultAdapter();
    BluetoothSocket socketblu=null;
    UUID uuid=UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");
    String nombreblu,mac,direccion;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_exoesqueleto);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        Bundle bolsa=getIntent().getExtras();
        nombreblu=bolsa.getString("NAME");
        getSupportActionBar().setTitle("Esperando a: "+nombreblu);
        mac=bolsa.getString("MAC");
        conexion=false;
        ImageButton parado=(ImageButton)findViewById(R.id.IB_parado);
        ImageButton sentado=(ImageButton)findViewById(R.id.IB_sentado);
        ImageButton caminar=(ImageButton)findViewById(R.id.IB_caminar);
        ImageButton bailar=(ImageButton)findViewById(R.id.IB_bailar);

        parado.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(conexion){
                    connectedThread.enviar("0");
                    Toast.makeText(Exoesqueleto.this, "Orden de parar enviada", Toast.LENGTH_SHORT).show();
                }else{
                    Toast.makeText(Exoesqueleto.this, "No estas conectado", Toast.LENGTH_SHORT).show();
                }

            }
        });

        caminar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(conexion){
                    connectedThread.enviar("2");
                    Toast.makeText(Exoesqueleto.this, "Orden de caminar enviada", Toast.LENGTH_SHORT).show();
                }else{
                    Toast.makeText(Exoesqueleto.this, "No estas conectado", Toast.LENGTH_SHORT).show();
                }

            }
        });
        sentado.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(conexion){
                    connectedThread.enviar("1");
                    Toast.makeText(Exoesqueleto.this, "Orden de sentar enviada", Toast.LENGTH_SHORT).show();
                }else{
                    Toast.makeText(Exoesqueleto.this, "No estas conectado", Toast.LENGTH_SHORT).show();
                }

            }
        });
        bailar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(conexion){
                    connectedThread.enviar("3");
                    Toast.makeText(Exoesqueleto.this, "Orden de bailar enviada", Toast.LENGTH_SHORT).show();
                }else{
                    Toast.makeText(Exoesqueleto.this, "No estas conectado", Toast.LENGTH_SHORT).show();
                }

            }
        });

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                    dispositivoblu = adaptadorblu.getRemoteDevice(mac);
                    try {
                        socketblu = dispositivoblu.createRfcommSocketToServiceRecord(uuid);
                        socketblu.connect();
                        Toast.makeText(Exoesqueleto.this, "Conectado a: " + nombreblu, Toast.LENGTH_SHORT).show();
                        conexion=true;

                        connectedThread= new ConnectedThread(socketblu);
                        connectedThread.start();

                        getSupportActionBar().setTitle("Conectado con: "+nombreblu);
                    } catch (IOException erro) {

                        Toast.makeText(Exoesqueleto.this, "Algo salio Mal :(", Toast.LENGTH_SHORT).show();
                    }
                }
               /* Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();*/
            }
        );
    }

    @Override
    public boolean onSupportNavigateUp() {
        if (conexion) {
            try {
                socketblu.close();
                Toast.makeText(this, "Desconectado de " + nombreblu, Toast.LENGTH_SHORT).show();
                onBackPressed();
            } catch (IOException erro) {
                Toast.makeText(this, "Algo salio mal", Toast.LENGTH_SHORT).show();
            }
        } else {
            Toast.makeText(this, "No estabas conectado", Toast.LENGTH_SHORT).show();
            onBackPressed();
        }
        return true;
    }

    private class ConnectedThread extends Thread {

        private final InputStream mmInStream;
        private final OutputStream mmOutStream;

        public ConnectedThread(BluetoothSocket socket) {

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
            byte[] buffer = new byte[1024];  // buffer store for the stream
            int bytes; // bytes returned from read()

        }

        /* Call this from the main activity to send data to the remote device */
        public void enviar(String datosenviados) {
            byte[] bytes= datosenviados.getBytes();
            try {
                mmOutStream.write(bytes);
            } catch (IOException e) { }
        }

    }

}
