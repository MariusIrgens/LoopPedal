# Loop Pedal with generative rythms

This is my code for a loop pedal with generative, synthesized backing rythm.  
It is not finished yet, so this documentation is currently minimal. It is part of a university project set to finish in November.  

It uses a Teensy 4.0 and a audio adapter board.  
  
There are 2 buttons.  
Button 1: Generates a random beat based on sampling without replacement, using user-defined distribution templates. Currently there is only one template, but I will add more soon.  
Button 2: Starts/stops recording of input. It will sychronize start and stop on 4/4s.  
  
There is one RGB LED.  
It blinks on every beat, and has red light between beats when recording.  
  
There are 2 pots.  
One controls audio in volume, the other controls drum volume.  
  
Top view  
![20230930_204527](https://github.com/MariusIrgens/LoopPedal/assets/78429226/c2855f8c-e439-41cc-b979-e07003665d69)
  
Back view  
![20230930_204417](https://github.com/MariusIrgens/LoopPedal/assets/78429226/5f62422c-1067-44e5-98b3-58dfe9e66d2c)
  
Front view  
![20230930_204424](https://github.com/MariusIrgens/LoopPedal/assets/78429226/a6245a6f-e33d-45b7-869e-674ee4606ee2)
  
SD card used (formatted with FAT32)  
![20230930_204738](https://github.com/MariusIrgens/LoopPedal/assets/78429226/814e6101-8a80-4674-9a4b-3e68100ca5be)
