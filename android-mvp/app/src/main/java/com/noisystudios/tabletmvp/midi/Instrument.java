package com.noisystudios.tabletmvp.midi;

import static com.noisystudios.tabletmvp.midi.MidiConstants.PERCUSSION_OFFSET;

public enum Instrument {

    PIANO(0),
    SIDE_STICK(PERCUSSION_OFFSET + 37);

    private int midiCode;
    Instrument(int midiCode) {
        this.midiCode = midiCode;
    }
    public int getMidiCode() {
        return midiCode;
    }

}
