# Loop Pedal with procedurally generated rythms and drum synthesis

# Pedal overview
![pedalOverview](https://github.com/MariusIrgens/LoopPedal/assets/78429226/f668eea8-f432-497c-9add-428f51fd7747)

The purpose of the pedal is to create procedurally generated beats with the right footswitch, and record an instrumental backing track with the left footswitch, then practice playing along with the results. This makes instrument practice fun and engaging.

The drum sounds are made using synthesis, randomized within certain parameters. The beats are made using predefined randomization templates based on “sampling without replacement”. I have included a template generator in HTML code. I will go into a bit more detail around these concepts below.

# Code overview
![Pedal uml](https://github.com/MariusIrgens/LoopPedal/assets/78429226/3f76dd34-bf25-4984-b71d-f3d6ae25585b)

This is an overview of the current code. I would like to refactor “sequencer” out of “audioManager” and into “systemController” instead, alongside “audioManager” and “interactionManager”, then put “drumSound” and everything below it directly under “audioManager”.
Other than that I think the system design is decent.

# Audiosystem
![Pedal audio](https://github.com/MariusIrgens/LoopPedal/assets/78429226/dbada959-29fe-4041-ad6a-e32fc84db6c6)
I separate the drums and input/loop at output to facilitate for individual audio post-processing. 

# Template generator and procedural beats
![templateEmpty](https://github.com/MariusIrgens/LoopPedal/assets/78429226/0e5a9343-82b7-4eb0-b1d7-1a4eec5493f9)

The template generator is provided in HTML form in the HTML folder, along with many presets. Open it in your browser of choice. Clicking the mouse button on a step in the pattern will cycle between colored dots. The dot colors represent the following logic:

- Black dot hits will always play.
- Green dot hits will commonly play.
- Red dot hits will occasionally play.
- Blue dot hits will rarely play.

Pressing the “generate” button will generate an array for the respective drum sound. There are two arrays: one “always” and one “variable” array. The hits inserted into the “always” array (black dots) will always play. The hits inserted into the “variable” array will be picked from at random by a picking function in the sequencer code. A green dot will place 3 instances of a step in the array, a red dot will place 2 instances, and the blue dot will place 1 instance. This makes a green dot step 3 times more likely to be selected than a blue dot. These numbers can be modified in the template generator at the top (next to the “load” button). For different time signatures (like odd signatures), use the + and - button above the pattern to increment/decrement signature.
![templateSamba](https://github.com/MariusIrgens/LoopPedal/assets/78429226/5b2eb7ac-cda3-4b7f-8b83-80a50dd8b949)

When a pattern has been made, press “generate” for each sound, and its respective array will be generated. The output can be directly copied and pasted into the drumTemplates.cpp class of the code. The templates in the class can easily be deleted or commented out if only certain patterns are required.

https://github.com/MariusIrgens/LoopPedal/blob/a50a74c27e1bdc3f48690f88fd667be2349ab218/LoopPedal/DrumTemplates.h#L17-L35

A template is a struct. Busyness variables can be selected for each sound, along with a BPM range. These values are not output by the template generator, and must be manually entered. They are initialized with default values. 

https://github.com/MariusIrgens/LoopPedal/blob/a50a74c27e1bdc3f48690f88fd667be2349ab218/LoopPedal/DrumTemplates.cpp#L165-L187

To make a new template entry, copy the output from the template generator and make a new entry in the drumTemplates.cpp constructor. If needed, override the busyness values and BPM values. Then, push the new template to the allTemplates vector. A template is chosen at random from the list when “new sequence” is run (right footswitch).

In the sequence generator, “always” hits are added instantly. Afterwards, extra hits are picked from the variable arrays in the following way:

https://github.com/MariusIrgens/LoopPedal/blob/a50a74c27e1bdc3f48690f88fd667be2349ab218/LoopPedal/Sequencer.cpp#L160-L173

- Should one more hit be added? A “oneMoreHit” function runs to check if one more hit should be added. This uses the “busyness” variable to generate a curve falloff along a hit number axis. If, for instance, the busyness value is 0.5, the curve will halve for each extra hit added, making it half as likely to add a new hit recursively. 0.9 will result in many hits added, while 0.2 will result in few (if any) hits added. A low busyness on snare and a high busyness on closed hihats would be more common. It also adds a "contribution" factor, based on how many variable hits are actually in the template pattern (more hits to chose from usually means more hits should occur as well).

https://github.com/MariusIrgens/LoopPedal/blob/a50a74c27e1bdc3f48690f88fd667be2349ab218/LoopPedal/Sequencer.cpp#L145-L158

- A random hit location is drawn from the template distribution array. The distribution array is the current drum sound variable array from the template in use. Common hits are more represented in the array, and therefore more likely to get selected than occasional and rare hits. When a hit is picked, all instances of it are removed from the array, resulting in a “picking without replacement” algorithm.

![Sequence](https://github.com/MariusIrgens/LoopPedal/assets/78429226/24b36089-9458-4728-a2d3-6db608e31068)
A full sequence is made from concatenating 8 patterns. In the first pattern of a new sequence, a cymbal crash is added to the first step. In the last pattern, a tom fill is added, spanning the last two beats. After a tom fill, a new sequence is generated using the same template, making changes to the beat while staying within the rules of the template. This results in an ever changing beat. Pattern 2 and 6 are a bit busyer, while pattern 4 and 8 are the busyest - drummers will often add hits to the sequence in this way to make it easier to orient oneself in it, and add exitement in the form of rythmic "dissonance" and "resolution".

# Randomized drum sound synthesis
(Example - drumSoundKick.cpp)
https://github.com/MariusIrgens/LoopPedal/blob/a50a74c27e1bdc3f48690f88fd667be2349ab218/LoopPedal/DrumSoundKick.cpp#L78-L130

Each drum sound consist of a number of oscillators that are automated with a custom envelope class (the one provided with the audio API could not be used for whichever value so I made a custom version). The envelopes are updated regularly by a fast timer (running at 25 ms intervals from the audioManager). New synthesis settings are set with the newDrum function. A sound is triggered by the trigger function. The envelopes are updated with the update function. The logic is not very complicated, and it should be easy to customize the drum synthesis to ones liking.

# Looper
https://github.com/MariusIrgens/LoopPedal/blob/a50a74c27e1bdc3f48690f88fd667be2349ab218/LoopPedal/Looper.cpp

The looper is pretty basic: if record is triggered (left footswitch), it will start recording on the start of the next bar. If record is triggered again, it will stop recording on the start of the next bar. The loop length can not exceed 4 bars at the moment, but this might change in future updates. A recorded loop will start playing after recording has been stopped, and will continue to play until deleted (right footswitch). I wanted to be able to record multiple loops on top of eachother, but since the SD card can not be read from and written to simultaneously, this unfortunately could not be implemented. If anyone knows how to fix this, please let me know.

# Interaction
https://github.com/MariusIrgens/LoopPedal/blob/a50a74c27e1bdc3f48690f88fd667be2349ab218/LoopPedal/InteractionManager.cpp

The interactionManager contains all the input and output pins. Interrupts wil trigger functionality in the systemController. If you need to change any pin numbers, you can do it in the header file.
