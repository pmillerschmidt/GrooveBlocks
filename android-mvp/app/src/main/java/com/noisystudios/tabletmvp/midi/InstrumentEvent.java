package com.noisystudios.tabletmvp.midi;

import static com.noisystudios.tabletmvp.midi.MidiConstants.NOTE_ON;
import static com.noisystudios.tabletmvp.midi.MidiConstants.NOTE_OFF;
import static com.noisystudios.tabletmvp.midi.MidiConstants.PERCUSSION_OFFSET;
import static com.noisystudios.tabletmvp.midi.MidiConstants.PERCUSSION_PITCHES;

// This is a POJO which might get some complex population code
public class InstrumentEvent {

    private Instrument instrument;
    private int pitch;
    private int velocity;
    private boolean turnOn;

    public Instrument getInstrument() {
        return instrument;
    }
    public void setInstrument(Instrument instrument) {
        this.instrument = instrument;
    }

    public int getPitch() {
        return pitch;
    }
    public void setPitch(int pitch) {
        this.pitch = pitch;
    }

    public int getVelocity() {
        return velocity;
    }
    public void setVelocity(int velocity) {
        this.velocity = velocity;
    }

    public boolean isTurnOn() {
        return turnOn;
    }
    public void setTurnOn(boolean turnOn) {
        this.turnOn = turnOn;
    }

    public MidiMessage getMidiMessageOnChannel(final int channel) {
        MidiMessage message = new MidiMessage();

        message.setStatusByte(turnOn ? NOTE_ON : NOTE_OFF);
        message.addToStatusByte((byte)channel);

        // if percussion, midicode is the pitch for that percussion instrument
        if (PERCUSSION_PITCHES.containsKey(instrument)) {
            message.setByte1(PERCUSSION_PITCHES.get(instrument).byteValue());
        }
        else {
            message.setByte1((byte)pitch);
        }

        message.setByte2((byte)velocity);

        return message;
    }

}
