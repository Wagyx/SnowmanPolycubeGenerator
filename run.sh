make all

./polycube_generator 3 -o results/polyominoes_3.bits
./polycube_generator 4 -o results/polyominoes_4.bits -i results/polyominoes_3.bits
./polycube_generator 5 -o results/polyominoes_5.bits -i results/polyominoes_4.bits
./polycube_generator 6 -o results/polyominoes_6.bits -i results/polyominoes_5.bits
./polycube_generator 7 -o results/polyominoes_7.bits -i results/polyominoes_6.bits
./polycube_generator 8 -o results/polyominoes_8.bits -i results/polyominoes_7.bits
./polycube_generator 9 -o results/polyominoes_9.bits -i results/polyominoes_8.bits
./polycube_generator 10 -o results/polyominoes_10.bits -i results/polyominoes_9.bits
./polycube_generator 11 -o results/polyominoes_11.bits -i results/polyominoes_10.bits
./polycube_generator 12 -o results/polyominoes_12.bits -i results/polyominoes_11.bits
./polycube_generator 13 -o results/polyominoes_13.bits -i results/polyominoes_12.bits
./polycube_generator 14 -o results/polyominoes_14.bits -i results/polyominoes_13.bits
./polycube_generator 15 -o results/polyominoes_15.bits -i results/polyominoes_14.bits
./polycube_generator 16 -o results/polyominoes_16.bits -i results/polyominoes_15.bits
./polycube_generator 17 -o results/polyominoes_17.bits -i results/polyominoes_16.bits