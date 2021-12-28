package com.noisystudios.tabletmvp.midi;

import java.util.HashMap;
import java.util.Map;

public class MidiConstants {
    // codes
    public static final byte MIDI_TIME_CODE = -15;
    public static final byte SONG_POSITION_POBYTEER = -14;
    public static final byte SONG_SELECT = -13;
    public static final byte TUNE_REQUEST = -10;
    public static final byte END_OF_EXCLUSIVE = -9;
    public static final byte TIMING_CLOCK = -8;
    public static final byte START = -6;
    public static final byte CONTINUE = -5;
    public static final byte STOP = -4;
    public static final byte ACTIVE_SENSING = -2;
    public static final byte SYSTEM_RESET = -1;
    public static final byte NOTE_OFF = -128;
    public static final byte NOTE_ON = -112;
    public static final byte POLY_PRESSURE = -96;
    public static final byte CONTROL_CHANGE = -80;
    public static final byte PROGRAM_CHANGE = -64;
    public static final byte CHANNEL_PRESSURE = -48;
    public static final byte PITCH_BEND = -32;

    // other info
    public static final int TOTAL_CHANNELS = 16;
    public static final int PERCUSSION_CHANNEL = 10 - 1;
    public static final Map<Instrument, Integer> PERCUSSION_PITCHES = new HashMap<Instrument, Integer>() {{
        for (Instrument instrument : Instrument.values()) {
            if (instrument.getMidiCode() >= PERCUSSION_OFFSET) {
                put(instrument, instrument.getMidiCode() - PERCUSSION_OFFSET);
            }
        }
    }};

    //implementation specific
    public static final int PERCUSSION_OFFSET = 256; // this is just an offset in the instrument midicode to indicate a percussion instrument

    public MidiConstants() {
    }
}