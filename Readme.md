# Polyomino Generator in C

A 2D polyomino generator based on [this repository](https://github.com/snowmanam2/SnowmanPolycubeGenerator). This version is using the exact same logic but was made to work a dimension lower where cubes are replaced by squares.
Please check the [A000988](https://oeis.org/A000988) sequence on the OEIS website to take a look at a more proper definition, the enumeration results and main references on the topic.

## Compiling

```bash
make all
```

Note the current Makefile was written for Linux with GCC. The only external dependencies are pthreads and zlib. It seems to work in Cygwin or MinGW, though the executable is a bit slower.

## Usage
The following returns the number of 2D polyominos of length 5:
```bash
./polyomino_generator 5
```

The following returns the number of 2D polyominos of each length up to 8:
```bash
./polyomino_generator 8 -a
```

For lengths larger than 9, the "-t" option allows specification of a number of compute threads. The default is 16 threads, shown here with 10 threads.
```bash
./polyomino_generator 13 -n 10
```

A cache file can be generated by adding "-o" with the filename:
```bash
./polyomino_generator 5 -o cubes5.bits
```

A PCube cache file can be compressed by adding "-oz" with the filename:
```bash
./polyomino_generator 5 -oz cubes5.bits
```

A cache file can be input for use in computation by adding "-i" with the filename:
```bash
./polyomino_generator 7 -i cubes5.bits
```

## Algorithms

Basics:
- The core of this version uses sorted point lists as the basis of the generated cube "keys". The lowest coordinate is 1 in each direction.
- Before any computation is performed, we compute all relevant rotations of the initial point list, including versions expand the dimensions of the list beyond the original size.
- Rotations are reduced to 4 for any dimension set with a dimension not equal to the other 2 dimensions. All 24 rotations are used otherwise.
- Candidate points are determined on all faces of the initial list of length n-1. We sort the list and compare with the original point list to eliminate overlapping points.

This is "hashtable-less" implementation similar to that described by [presseyt](https://github.com/mikepound/opencubes/issues/11). The difference is checking if the removed point from the new polyomino is the highest possible index in the polyomino point list. When doing this in combination with removing all duplicate polyominos from the current "seed" shape, we are left with a unique set of generated cubes. Specific steps taken:
1. Start with polyomino p. Extend by cube a to yield cube q (q = p + a).
2. Repeat step 1 for all possible additions of a.
3. Filter result of step 2 to only have unique values, saving the highest possible of the index of a in each q.
4. For each q, check if there is any possible r at a higher index of q that can be removed while remaining a polyomino. Otherwise output q.

The advantage of this method is we don't need to recanonize the combinations. I used a rather lazy implementation of steps 3 and 4:
1. Sort all generated q polyominos. Check the current q with the last q to eliminate duplicates.
2. Use a fast "number of neighbors" check to eliminate the majority of higher duplicate r indexes. Specifically, if a cube in q only has 1 neighbor, it can safely be removed.
3. If the neighbor check doesn't cancel the output, iteratively check all r values of index higher than a. We count the number of cubes that can be reached to make sure it is connected. 

## Performance

Uing a rather dated Intel Xeon(R) CPU E5420 with 16 computing threads on Ubuntu with no cache generation or input, measured cumulatively:
- n=16 in 18 seconds
- n=17 in 71 seconds
- n=18 in 298 seconds

## Cache Files

This program can read or write in a basic binary .bits format where each polyomino is encoded as:
1. (1 byte) dimension along x of the polyomino
2. (1 byte) dimension along y of the polyomino
2. (n bytes) Polyomino data where n = ceil(x\*y/8). The data is a flattened representation of the x*y grid that contains the poyomino where each bit indicates whether a square exists in the cell.
Compressing the output file with gzip can reach around 55% compression rate.

## Known Areas for Improvement
- rotations could be excluded when the x and y dimensions are different.

Mostly the same things as in the original repo
- qsort [can be slow](https://travisdowns.github.io/blog/2019/05/22/sorting.html), and it appears in critical areas (filtering for duplicate removal). Maybe mergesort or other methods could be faster.
- Graph algorithms could probably improve the performance of the full connection check.
- Cross-platform compatibility (maybe use CMake).
- CLI is rather basic.
- Increasing I/O depth and/or moving compression & packing methods to threads might help with cache file write speed.
- The 6 expansion rotation sets might be faster to compute if calculated as offsets relative to the main set or each other.

## For the future
Make it work for any dimension

## License

[MIT](https://choosealicense.com/licenses/mit/)
