make all

./polyomino_generator 3 -o results/polyominoes_3.bits
./polyomino_generator 4 -o results/polyominoes_4.bits -i results/polyominoes_3.bits
./polyominoo_generator 5 -o results/polyominoes_5.bits -i results/polyominoes_4.bits
./polyomino_generator 6 -o results/polyominoes_6.bits -i results/polyominoes_5.bits
./polyomino_generator 7 -o results/polyominoes_7.bits -i results/polyominoes_6.bits
./polyomino_generator 8 -o results/polyominoes_8.bits -i results/polyominoes_7.bits
./polyomino_generator 9 -o results/polyominoes_9.bits -i results/polyominoes_8.bits
./polyomino_generator 10 -o results/polyominoes_10.bits -i results/polyominoes_9.bits
./polyomino_generator 11 -o results/polyominoes_11.bits -i results/polyominoes_10.bits
./polyomino_generator 12 -o results/polyominoes_12.bits -i results/polyominoes_11.bits
./polyomino_generator 13 -o results/polyominoes_13.bits -i results/polyominoes_12.bits
./polyomino_generator 14 -o results/polyominoes_14.bits -i results/polyominoes_13.bits
./polyomino_generator 15 -o results/polyominoes_15.bits -i results/polyominoes_14.bits
# ./polyomino_generator 16 -o results/polyominoes_16.bits -i results/polyominoes_15.bits
# ./polyomino_generator 17 -o results/polyominoes_17.bits -i results/polyominoes_16.bits
# ./polyomino_generator 18 -o results/polyominoes_18.bits -i results/polyominoes_17.bits
# ./polyomino_generator 19 -o results/polyominoes_19.bits -i results/polyominoes_18.bits