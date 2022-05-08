# Filler

Hive Helsinki school project. The goal is to write a player in C language for the provided game Filler.

Filler is an algorithmic game which consists in filling a grid of a known size in advance
with pieces of random size and shapes, without the pieces being stacked more than one
square above each other and without them exceeding the grid. If one of these conditions
is not met, the game stops.

As a bonus I also created a graphic visualizer in Rust language using Bevy engine.

![demo](filler.webp)

# Usage
- "make" to compile "nsamoilo.filler" executable.
- there are two test scripts in "/resources/resources/" directory - "test_maps00_01.sh" for two smallest maps and "test_map02.sh" for the largest one. Each script will run the executable 5 times on each map against six provided players. You can use these scripts for your project by changing the executable name in them.
- to use the visualizer, you have to save the whole match in a file (for example "trace") and then use it as an argument ("./visualizer_rust trace").
- if you're using macOS, you can use the executable "visualizer_rust". For other systems you should install Rust and do "cargo run trace_name" inside the "visualizer" directory.
