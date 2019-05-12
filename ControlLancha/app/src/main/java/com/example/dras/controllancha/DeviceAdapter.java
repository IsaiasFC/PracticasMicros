package com.example.dras.controllancha;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.Intent;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import java.util.List;
import java.util.UUID;

/**
 * Created by Dras on 02/11/2017.
 */

public class DeviceAdapter extends RecyclerView.Adapter<DeviceAdapter.DeviceHolder>  {
    static Context ctx;
    List<DevicePOJO> items;

    public DeviceAdapter(List<DevicePOJO> items,Context ctx) {
        this.items = items;
        this.ctx=ctx;


    }

    @Override
    public DeviceHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View v= LayoutInflater.from(parent.getContext()).inflate(R.layout.device_cardview,parent,false);
        return new DeviceHolder(v);
    }

    @Override
    public void onBindViewHolder(DeviceHolder holder, int position) {
        holder.name.setText(items.get(position).getName());
        holder.address.setText(items.get(position).getAddress());
    }

    @Override
    public int getItemCount() {
        return items.size();
    }

    public static class DeviceHolder extends RecyclerView.ViewHolder{
        TextView name, address;
        Button button;
        BluetoothDevice dispositivoblu=null;
        BluetoothAdapter adaptadorblu=BluetoothAdapter.getDefaultAdapter();
        BluetoothSocket socketblu=null;
        UUID uuid=UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");

        public DeviceHolder(View itemView) {
            super(itemView);
            name=(TextView)itemView.findViewById(R.id.TV_devicename_CV);
            address=(TextView)itemView.findViewById(R.id.TV_deviceaddress_CV);
            button=(Button)itemView.findViewById(R.id.BTN_button_CV);
            button.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    Intent intent = new Intent(ctx.getApplicationContext(),AcelerometroActivity.class);
                    intent.putExtra("NAME",name.getText().toString());
                    intent.putExtra("MAC",address.getText().toString());
                    intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                    ctx.getApplicationContext().startActivity(intent);
                    /*
                    dispositivoblu=adaptadorblu.getRemoteDevice(address.getText().toString());
                    try{
                        socketblu=dispositivoblu.createRfcommSocketToServiceRecord(uuid);
                        socketblu.connect();
                        Toast.makeText(ctx, "Conectado a: "+name.getText().toString(), Toast.LENGTH_SHORT).show();
                    }catch (IOException erro){
                        Toast.makeText(ctx, "Algo salio Mal :(", Toast.LENGTH_SHORT).show();

                    }
                    if(socketblu.isConnected()){
                        Intent intent = new Intent(ctx.getApplicationContext(),AcelerometroActivity.class);
                        intent.putExtra("NAME",name.getText().toString());
                        intent.putExtra("MAC",address.getText().toString());
                        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                        ctx.getApplicationContext().startActivity(intent);
                    }
                    */

                }
            });
        }
    }
}
