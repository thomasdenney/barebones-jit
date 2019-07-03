# Barebones JIT example

This repository contains the code associated with a [blog post][] I wrote on
JIT compilation on a BBC micro:bit. You can find more complete code, with a
full JIT compiler, in my [bachelor's project][project].

To run the code on a micro:bit, run the following commands:

    yt build
    cp build/bbc-microbit-classic-gcc/source/barebones-jit-combined.hex /Volumes/MICROBIT

(You may need to adapt the second command based on your OS, see these
[instructions][]).

[blog post]: https://thomasdenney.co.uk/blog/2019/7/3/jit-compilation-on-an-arm-cortex-m0/#2019-07-03-jit-compilation-on-an-arm-cortex-m0fnref1
[project]: https://github.com/thomasdenney/microjit
[instructions]: https://lancaster-university.github.io/microbit-docs/offline-toolchains/
