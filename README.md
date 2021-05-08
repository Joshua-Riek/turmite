## Turmite
A simple N-state N-color Turing machine that operates on a 
grid of cells, and follows a custom set of rules every tick 
of a clock.

## Make your own Turmite
To create a turmite, a rule must be made and specified by a curly-bracketed 
table of `n_states` rows by `n_colors` columns, consisting of triples
`{A,B,C}` where `A` is the new color to write `[0,1,2,...,(n_colors-1)]`,
`B` is the direction(s) for the turmite to turn `[1=forward, 2=right, 4=u-turn,
8=left]`, and `C` is the new state to adopt `[0,1,2,...,(n_states-1)]`.

For example, the fibonacci turmite, has a rule definition
`{{{1,8,1},{1,8,1}},{{1,2,1},{0,1,0}}}`, consisting of two states, 
two colors, and four triplets. The particular triple is selected based on 
the current state and current color. The `{1,8,1}` triple therefore states that
the color should change to `1`, turn left (8), and adopt state `1` before moving.

## Arguments
If no rule or color is given, then both will be selected at random.
You can find a list of pre-defined rules [here](turmite.cpp#L4).
```
$ turmite -h
Usage: turmite [options] ...
Options:
  -h, --help             Display help information
  -w, --wrap             Wrap turmite around window edges
  -r, --rule=<rule>      Specify the turn rule
  -d, --delay=<delay>    Seconds between turmite steps
  -c, --color=<color>    Primary color of the turmite
  -s, --scale=<scale>    Size of each cell
  -o, --offset=<offset>  Spacing between cells
  -x, --width=<width>    Window width in pixels
  -y, --height=<height>  Window height in pixels
```

## Requirements
Visualization is preformed by the [SFML](https://www.sfml-dev.org/index.php) library.