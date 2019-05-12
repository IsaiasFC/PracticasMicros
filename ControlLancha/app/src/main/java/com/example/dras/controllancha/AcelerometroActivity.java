package com.example.dras.controllancha;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.pm.ActivityInfo;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ImageButton;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

public class AcelerometroActivity extends AppCompatActivity {
    ConnectedThread connectedThread;
    Sensor sensor;
    SensorManager sensorManager;
    SensorEventListener sensorEventListener;
    int whip=0;
    Boolean conexion;
    BluetoothDevice dispositivoblu=null;
    BluetoothAdapter adaptadorblu=BluetoothAdapter.getDefaultAdapter();
    BluetoothSocket socketblu=null;
    UUID uuid=UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");
    String nombreblu,mac,direccion;
    boolean del=false, atr=false;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_acelerometro);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        Bundle bolsa=getIntent().getExtras();
        nombreblu=bolsa.getString("NAME");
        getSupportActionBar().setTitle("Esperando conexion con: "+nombreblu);
        mac=bolsa.getString("MAC");
        conexion=false;
        final TextView valores=(TextView)findViewById(R.id.TV_grados);
        valores.setText("Detenido");
        final ImageButton up=(ImageButton) findViewById(R.id.BTN_UP);
        final ImageButton down=(ImageButton) findViewById(R.id.BTN_DOWN);
        final RelativeLayout izquierda=(RelativeLayout)findViewById(R.id.RL_LEFT);
        final RelativeLayout derecha=(RelativeLayout)findViewById(R.id.RL_RIGHT);

        direccion="";
        FloatingActionButton play =(FloatingActionButton)findViewById(R.id.fab_play);
        play.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                start();
            }
        });
        FloatingActionButton fabc = (FloatingActionButton) findViewById(R.id.fab_conectar);
        fabc.setOnClickListener(new View.OnClickListener() {
                                   @Override
                                   public void onClick(View view) {
                                       //////////////////////////////////////////
                                       if(nombreblu.equals("EXAMPLE")){
                                           stop();
                                           valores.setText("Detenido");
                                       }else {

                                           dispositivoblu = adaptadorblu.getRemoteDevice(mac);
                                           try {
                                               socketblu = dispositivoblu.createRfcommSocketToServiceRecord(uuid);
                                               socketblu.connect();
                                               Toast.makeText(AcelerometroActivity.this, "Conectado a: " + nombreblu, Toast.LENGTH_SHORT).show();
                                               conexion=true;

                                               connectedThread= new ConnectedThread(socketblu);
                                               connectedThread.start();
                                               start();
                                               //stop();
                                               getSupportActionBar().setTitle("Conectado con: "+nombreblu);
                                           } catch (IOException erro) {

                                               Toast.makeText(AcelerometroActivity.this, "Algo salio Mal :(", Toast.LENGTH_SHORT).show();
                                           }
                                       }
                                       ////////////////////////////////////////
                                   }
                               });

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab_acelerometro);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(conexion){

                    //connectedThread.enviar("PARAR");
                    connectedThread.enviar("6");

                }
                up.setVisibility(View.VISIBLE);
                down.setVisibility(View.VISIBLE);
                izquierda.setVisibility(View.INVISIBLE);
                derecha.setVisibility(View.INVISIBLE);
                stop();
                valores.setText("Detenido");
            }
        });

        up.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction()==MotionEvent.ACTION_DOWN){
                    //Boton presionado
                    up.setVisibility(View.INVISIBLE);
                    down.setVisibility(View.VISIBLE);
                    if (conexion){
                        //connectedThread.enviar("DELANTE");
                        //direccion="DELANTE";
                        del=true;
                        atr=false;
                    }
                    valores.setText("Vas hacia delante");
                    //stop();
                    //start();
                }else if(event.getAction()==MotionEvent.ACTION_UP){
                    //Boton desprecionado
                    del=false;
                    atr=false;
                    up.setVisibility(View.VISIBLE);
                    down.setVisibility(View.VISIBLE);
                    valores.setText("Esperando...");
                }
                return false;
            }
        });

        down.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction()==MotionEvent.ACTION_DOWN){
                    //Boton presionado
                    up.setVisibility(View.VISIBLE);
                    down.setVisibility(View.INVISIBLE);
                    if(conexion){
                        // connectedThread.enviar("ATRAS");
                        //direccion="ATRAS";
                        atr=true;
                        del=false;
                    }
                    valores.setText("Vas hacia atras");
                    //stop();
                    //start();

                }else if(event.getAction()==MotionEvent.ACTION_UP){
                    //Boton desprecionado
                    up.setVisibility(View.VISIBLE);
                    down.setVisibility(View.VISIBLE);
                    atr=false;
                    del=false;
                    valores.setText("Esperando...");
                }
                return false;
            }
        });




        sensorManager=(SensorManager)getSystemService(SENSOR_SERVICE);
        sensor=sensorManager.getDefaultSensor(sensor.TYPE_ACCELEROMETER);
        if(sensor==null){
            finish();
        }
        sensorEventListener=new SensorEventListener() {
            @Override
            public void onSensorChanged(SensorEvent sensorEvent) {
                float x=sensorEvent.values[1];
             // valores.setText(Float.toString(x));
                if(x<-3){ //IZQUIERDA
                    izquierda.setVisibility(View.VISIBLE);
                    derecha.setVisibility(View.INVISIBLE);
                    if(conexion){
                        if(del){
                            //IZQUIERDA DELANTE
                            connectedThread.enviar("2");//enviar dato para girar hacia la izquierda
                            valores.setText("Izquierda");
                        }else{
                            connectedThread.enviar("5");//enviar dato para girar hacia la izquierda
                            valores.setText("Izquierda");
                        }

                    }
                }
                if(x>3){ //DERECHA
                    izquierda.setVisibility(View.INVISIBLE);
                    derecha.setVisibility(View.VISIBLE);
                    if(conexion){
                        if(del){
                            //derecha delante
                            connectedThread.enviar("1");//enviar dato para girar hacia la derecha
                            valores.setText("derecha");
                        }else{
                            //derecha
                            connectedThread.enviar("4");//enviar dato para girar hacia la derecha
                            valores.setText("derecha");
                        }

                    }
                }
                if(-3<x && x<3){ //CENTRO
                    izquierda.setVisibility(View.VISIBLE);
                    derecha.setVisibility(View.VISIBLE);
                    if(conexion){

                        if(del){
                            connectedThread.enviar("0"); //Enviar dato para ir hacia delante
                            valores.setText("Delante");
                        }else if(atr){
                            connectedThread.enviar("3"); //Enviar dato para ir hacia atraz
                            valores.setText("Atraz");

                        }else{
                                //connectedThread.enviar("PARAR");
                                connectedThread.enviar("6");
                            //up.setVisibility(View.VISIBLE);
                            //down.setVisibility(View.VISIBLE);
                            //izquierda.setVisibility(View.INVISIBLE);
                            //derecha.setVisibility(View.INVISIBLE);
                            //stop();
                            valores.setText("Detenido");
                        }
                        /*if(direccion.equals("DELANTE")){
                            connectedThread.enviar("0");
                        }
                        if(direccion.equals("ATRAS")){
                            connectedThread.enviar("3");
                        }*/

                    }
                }
               /* if(x<-5 && whip==0){
                    whip++;
                    getWindow().getDecorView().setBackgroundColor(Color.GREEN);
                }else if(x>5 && whip==1){
                    whip++;
                    getWindow().getDecorView().setBackgroundColor(Color.YELLOW);
                }
                if(whip==2){
                    whip=0;
                }*/
            }

            @Override
            public void onAccuracyChanged(Sensor sensor, int i) {

            }
        };

        if(nombreblu.equals("EXAMPLE")){
            start();
        }


    }

    private   void start(){
        sensorManager.registerListener(sensorEventListener,sensor,SensorManager.SENSOR_DELAY_NORMAL);
    }

    private void stop(){
        sensorManager.unregisterListener(sensorEventListener);
    }

    @Override
    protected void onPause() {
      //  stop();
        super.onPause();
    }

    @Override
    protected void onResume() {
      // stop();

        super.onResume();
    }


    @Override
    public boolean onSupportNavigateUp() {
        if(nombreblu.equals("EXAMPLE")){
            onBackPressed();
        }else {
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
        }
        return true;
    }

    private class ConnectedThread extends Thread {

        private final InputStream mmInStream;
        private final OutputStream mmOutStream;

        public ConnectedThread(BluetoothSocket socket) {

            InputStream tmpIn = null;
            OutputStream tmpOut = null;

            // Get the input and output streams, using temp objects because
            // member streams are final
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
             
            // Keep listening to the InputStream until an exception occurs
            while (true) {
                try {
                    // Read from the InputStream
                    bytes = mmInStream.read(buffer);
                    // Send the obtained bytes to the UI activity
                   // mHandler.obtainMessage(MESSAGE_READ, bytes, -1, buffer)
                     //       .sendToTarget();
                } catch (IOException e) {
                    break;
                }
            }

        }

        /* Call this from the main activity to send data to the remote device */
        public void enviar(String datosenviados) {
            byte[] bytes= datosenviados.getBytes();
            try {
                mmOutStream.write(bytes);
            } catch (IOException e) { }
        }

        /* Call this from the main activity to shutdown the connection
        public void cancel() {
            try {
                socketblu.close();
            } catch (IOException e) { }
        } */
    }

}
