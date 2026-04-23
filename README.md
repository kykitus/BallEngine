# BallEngine

## My second major project. An unfinished one.

So it is technically a game making framework created on SDL2 and SDL GPU.


### Second version is a rewrite take, that lacks some of the functionality of the original

both have:
- an entire update/render scalable system represented in a set of multipurpose layers.
- a collision system built upon code system of [this guy](https://noonat.github.io/intersect/) with unfinished idea to extend it over every case possible.
- an actually really funcitonal Spatial Hash Map for collision optimisation.
- an asset repository for enabling easy reuse of any already loaded asset on working application.

and original had:
- Working tile map with collision and actually working optimisation algorithm for it
- Mostly working text rendering
- Try on making events
- Object - Component system (the greatest cause of convincing me to make a rewrite)
- not really complicated input, with some foundations made for making them editable in the terms of things like input cooldown, lag, or continuity.
- Cursor system - everything with onclick handling is definetely a cursor object, but not every cursor needs to have it.

not everything mentioned is completely functional, nor I really want to test all of it after 2 years.