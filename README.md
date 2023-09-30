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
![20230930_204527](https://github.com/MariusIrgens/LoopPedal/assets/78429226/38571b0b-20b8-4f43-8512-7db4c6c6a570)
  
Back view  
![20230930_204417](https://github.com/MariusIrgens/LoopPedal/assets/78429226/d67516ff-d455-4721-95ea-1c53fb0cdaf4)
  
Front view  
![20230930_204424](https://github.com/MariusIrgens/LoopPedal/assets/78429226/051472aa-3288-4d75-8c0c-875cddc171e2)
  
SD card used (formatted with FAT32)  
![20230930_204738](https://github.com/MariusIrgens/LoopPedal/assets/78429226/fc7c7b0d-c032-4543-bbef-92062b38cab4)
