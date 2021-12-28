package com.noisystudios.tabletmvp;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;

import com.noisystudios.tabletmvp.midi.Instrument;
import com.noisystudios.tabletmvp.midi.InstrumentEvent;
import com.noisystudios.tabletmvp.midi.InstrumentPlayer;
import com.noisystudios.tabletmvp.midi.MidiMessage;
import com.noisystudios.tabletmvp.midi.Notes;

import org.billthefarmer.mididriver.MidiDriver;

public class FreeStyleActivity extends AppCompatActivity implements MidiDriver.OnMidiStartListener, View.OnTouchListener, AdapterView.OnItemSelectedListener {

    Button bt;
    MidiDriver midiDriver = new MidiDriver();
    Notes currentKey;
    InstrumentPlayer instrumentPlayer = new InstrumentPlayer();

    @SuppressLint("ClickableViewAccessibility")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_freestyle);
        setSpinners();
    }

    @SuppressLint("ClickableViewAccessibility")
    public void setSpinners() {
        Spinner keySpinner = (Spinner) findViewById(R.id.key);
        // Create an ArrayAdapter using the string array and a default spinner layout
        ArrayAdapter<CharSequence> keyAdapter = ArrayAdapter.createFromResource(this,
                R.array.keys_array, android.R.layout.simple_spinner_item);
        // Specify the layout to use when the list of choices appears
        keyAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        // Apply the adapter to the spinner
        keySpinner.setAdapter(keyAdapter);
        keySpinner.setOnItemSelectedListener(this);
        switch ((String)keySpinner.getSelectedItem()) {
            case "A":
                currentKey = Notes.A;
                break;
            case "B":
                currentKey = Notes.B;
                break;
            case "C":
                currentKey = Notes.C;
                break;
            case "D":
                currentKey = Notes.D;
                break;
            case "E":
                currentKey = Notes.E;
                break;
            case "F":
                currentKey = Notes.F;
                break;
            case "G":
                currentKey = Notes.G;
        }

        Spinner tempoSpinner = (Spinner) findViewById(R.id.tempo);
        ArrayAdapter<CharSequence> tempoAdapter = ArrayAdapter.createFromResource(this,
                R.array.tempos_array, android.R.layout.simple_spinner_item);
        tempoAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        tempoSpinner.setAdapter(tempoAdapter);

        midiDriver.setOnMidiStartListener(this);
        midiDriver.start();

        bt = findViewById(R.id.button);
        bt.setOnTouchListener(this);
        bt = findViewById(R.id.button2);
        bt.setOnTouchListener(this);
        bt = findViewById(R.id.button3);
        bt.setOnTouchListener(this);
    }

    @SuppressLint("ClickableViewAccessibility")
    @Override
    public boolean onTouch(View v, MotionEvent event) {
        Log.d(this.getClass().getName(), "Motion event: " + event);

        if (v.getId() == R.id.button2) {
            switch (event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    playNote(Instrument.PIANO);
                    break;
                case MotionEvent.ACTION_UP:
                    stopNote(Instrument.PIANO);
            }
        }
        else if (v.getId() == R.id.button) {
            switch (event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    playNote(Instrument.SIDE_STICK);
                    break;
                case MotionEvent.ACTION_UP:
                    stopNote(Instrument.SIDE_STICK);
            }
        }
        else if (v.getId() == R.id.button3) {
            switch (event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    playMajorChord(Instrument.PIANO);
                    break;
                case MotionEvent.ACTION_UP:
                    stopMajorChord(Instrument.PIANO);
            }
        }

        return false;
    }

    @Override
    public void onMidiStart() {
//        MidiMessage event = new MidiMessage();
//        event.setEventMessage((byte)0xc0);
//        event.setEventPitch((byte)0x00);
//
//        midiDriver.write(event.getEvent());
    }

    private void playNote(Instrument instrument) {
        InstrumentEvent event = new InstrumentEvent();
        event.setInstrument(instrument);
        event.setTurnOn(true);
        event.setPitch(currentKey.getPitch(0, 0));
        event.setVelocity(127);

        for (MidiMessage message : instrumentPlayer.getMidiEvents(event)) {
            midiDriver.write(message.getMessageBytes());
        }
    }

    private void stopNote(Instrument instrument) {
        InstrumentEvent event = new InstrumentEvent();
        event.setInstrument(instrument);
        event.setTurnOn(false);
        event.setPitch(currentKey.getPitch(0, 0));
        event.setVelocity(127);

        for (MidiMessage message : instrumentPlayer.getMidiEvents(event)) {
            midiDriver.write(message.getMessageBytes());
        }
    }

    private void playMajorChord(Instrument instrument) {
        int[] offsets = {0, 4, 7};
        for (int offset : offsets) {
            InstrumentEvent event = new InstrumentEvent();
            event.setInstrument(instrument);
            event.setTurnOn(true);
            event.setPitch(currentKey.getPitch(0, offset));
            event.setVelocity(127);

            for (MidiMessage message : instrumentPlayer.getMidiEvents(event)) {
                midiDriver.write(message.getMessageBytes());
            }
        }
    }

    private void stopMajorChord(Instrument instrument) {
        int[] offsets = {0, 4, 7};
        for (int offset : offsets) {
            InstrumentEvent event = new InstrumentEvent();
            event.setInstrument(instrument);
            event.setTurnOn(false);
            event.setPitch(currentKey.getPitch(0, offset));
            event.setVelocity(127);

            for (MidiMessage message : instrumentPlayer.getMidiEvents(event)) {
                midiDriver.write(message.getMessageBytes());
            }
        }
    }

    @Override
    public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
        Log.d(this.getClass().getName(), "item selected: " + (String)parent.getItemAtPosition(position));
        switch ((String)parent.getItemAtPosition(position)) {
            case "A":
                currentKey = Notes.A;
                break;
            case "B":
                currentKey = Notes.B;
                break;
            case "C":
                currentKey = Notes.C;
                break;
            case "D":
                currentKey = Notes.D;
                break;
            case "E":
                currentKey = Notes.E;
                break;
            case "F":
                currentKey = Notes.F;
                break;
            case "G":
                currentKey = Notes.G;
        }
    }

    @Override
    public void onNothingSelected(AdapterView<?> parent) {

    }
}



// TODO remove linting suppression and create a custom view https://stackoverflow.com/questions/47107105/android-button-has-setontouchlistener-called-on-it-but-does-not-override-perform