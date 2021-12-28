package com.noisystudios.tabletmvp.midi;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;

import static com.noisystudios.tabletmvp.midi.MidiConstants.CONTROL_CHANGE;
import static com.noisystudios.tabletmvp.midi.MidiConstants.PERCUSSION_CHANNEL;
import static com.noisystudios.tabletmvp.midi.MidiConstants.PERCUSSION_OFFSET;
import static com.noisystudios.tabletmvp.midi.MidiConstants.PERCUSSION_PITCHES;
import static com.noisystudios.tabletmvp.midi.MidiConstants.PROGRAM_CHANGE;
import static com.noisystudios.tabletmvp.midi.MidiConstants.TOTAL_CHANNELS;

// this event generates midi events from instrument events
public class InstrumentPlayer {

    private static Map<Instrument, Integer> instrumentChannels = new HashMap<Instrument, Integer>() {{
        for (Instrument instrument : Instrument.values()) {
            if (instrument.getMidiCode() >= PERCUSSION_OFFSET) {
                put(instrument, PERCUSSION_CHANNEL);
            }
        }
    }};

    private static Queue<Instrument> lastInstrumentUsed = new LinkedList<>();
    private static Queue<Integer> availableChannels = new LinkedList<Integer>() {{
        add(0);
        add(1);
        add(2);
        add(3);
        add(4);
        add(5);
        add(6);
        add(7);
        add(8);
        add(10);
        add(11);
        add(12);
        add(13);
        add(14);
        add(15);
    }};

    public List<MidiMessage> getMidiEvents(InstrumentEvent event) {
        // basic logic for getting an optional channel switch event and then on/off event
        List<MidiMessage> messages = new ArrayList<>();

        if (PERCUSSION_PITCHES.containsKey(event.getInstrument())) {
            // if this is the case then we're done since this channel is preassigned
            messages.add(event.getMidiMessageOnChannel(PERCUSSION_CHANNEL));
        }
        else {
            if (!instrumentChannels.containsKey(event.getInstrument())) {
                int freeChannel;
                if (availableChannels.size() > 0) {
                    freeChannel = availableChannels.remove();
                }
                else {
                    // get new channel for the instrument
                    Instrument instrumentToFree;
                    do {
                        instrumentToFree = lastInstrumentUsed.remove();
                    } while (instrumentChannels.get(instrumentToFree) == null);
                    freeChannel = instrumentChannels.get(instrumentToFree);
                    instrumentChannels.remove(instrumentToFree);

                    // send a channel switch message
                    MidiMessage message = new MidiMessage();
                    message.setStatusByte(PROGRAM_CHANGE);
                    message.addToStatusByte((byte)freeChannel);
                    message.setByte1((byte)event.getInstrument().getMidiCode());
                    messages.add(message);
                }
                instrumentChannels.put(event.getInstrument(), freeChannel);
            }

            messages.add(event.getMidiMessageOnChannel(instrumentChannels.get(event.getInstrument())));
        }

        return messages;
    }

}
