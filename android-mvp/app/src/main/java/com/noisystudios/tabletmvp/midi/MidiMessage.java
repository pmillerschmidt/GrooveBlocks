package com.noisystudios.tabletmvp.midi;

public class MidiMessage {

    private byte[] message = new byte[3];

    public void setStatusByte(final byte status) {
        message[0] = status;
    }
    public MidiMessage withStatusByte(final byte message) {
        setStatusByte(message);
        return this;
    }

    public void setByte1(final byte byte1) {
        message[1] = byte1;
    }
    public MidiMessage withByte1(final byte byte1) {
        setByte1(byte1);
        return this;
    }

    public void setByte2(final byte byte2) {
        message[2] = byte2;
    }
    public MidiMessage withByte2(final byte byte2) {
        setByte2(byte2);
        return this;
    }

    public byte[] getMessageBytes() {
        return message;
    }


    public void addToStatusByte(final byte addition) {
        message[0] += addition;
    }

}
