package com.example.dras.controllancha;

/**
 * Created by Dras on 02/11/2017.
 */

public class DevicePOJO {
    String name;
    String address;

    public  DevicePOJO(){

    }

    public DevicePOJO(String name, String address) {
        this.name = name;
        this.address = address;
    }

    public String getName() {
        return name;
    }

    public String getAddress() {
        return address;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setAddress(String address) {
        this.address = address;
    }
}
