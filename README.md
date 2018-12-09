# Toy Blocks

An implementation of a toy blockchain in C++. This toy example uses lines from Shakespere as input data and is designed to provide a concrete understanding of the basic ideas that make a blockchain  what it is: an unchangeable array of data (immutable database). Once data has been written to it the blockchain, it becomes very difficult to change it (Note this implementation only shows the protection that is achieved by hashing and proof-of-work, and omits hash consensus via a peer-to-peer network. This implementation was inspired by this [video](https://www.youtube.com/watch?v=SSo_EIwHSd4), and sifting through [Wikipedia](https://en.wikipedia.org/wiki/Blockchain).

## Getting Started

Download the repo, build and run the code.

```git clone git@github.com:mikesapi/toyblocks.git
cd toyblocks
mkdir build && cd build
cmake ..
make
./bin/toyblocks
```

You should see the following output:

```A simple blockchain toy example.

mining blk: 0
mining blk: 1...............
mining blk: 2..
mining blk: 3......................
mining blk: 4........................
mining blk: 5..
mining blk: 6......................................................................................................
mining blk: 7......................................................
mining blk: 8..........
mining blk: 9..........
mining blk: 10.


Verifying Blockchain:

-----------------------------------------
prevHash: 0
block id: 0
    data: Tomorrow, and tomorrow, and tomorrow,
    hash: 599699999
-----------------------------------------  <GOOD>
-----------------------------------------
prevHash: 599699999
block id: 1
    data: Creeps in this petty pace from day to day,
    hash: 6808299999
-----------------------------------------  <GOOD>
-----------------------------------------
prevHash: 6808299999
block id: 2
    data: To the last syllable of recorded time;
    hash: 4574399999
-----------------------------------------  <GOOD>
-----------------------------------------
prevHash: 4574399999
block id: 3
    data: And all our yesterdays have lighted fools
    hash: 8759099999
-----------------------------------------  <GOOD>
-----------------------------------------
prevHash: 8759099999
block id: 4
    data: The way to dusty death. Out, out, brief candle!
    hash: 4786299999
-----------------------------------------  <GOOD>
-----------------------------------------
prevHash: 4786299999
block id: 5
    data: Life's but a walking shadow, a poor player,
    hash: 4069699999
-----------------------------------------  <GOOD>
-----------------------------------------
prevHash: 4069699999
block id: 6
    data: That struts and frets his our upon the stage,
    hash: 2434799999
-----------------------------------------  <GOOD>
-----------------------------------------
prevHash: 2434799999
block id: 7
    data: And then is heard no more. It is a tale
    hash: 2766699999
-----------------------------------------  <GOOD>
-----------------------------------------
prevHash: 2766699999
block id: 8
    data: Told by an idiot, full of sound and fury,
    hash: 4038699999
-----------------------------------------  <GOOD>
-----------------------------------------
prevHash: 4038699999
block id: 9
    data: Signifying nothing.
    hash: 6333499999
-----------------------------------------  <GOOD>
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
