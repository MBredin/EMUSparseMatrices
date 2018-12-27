#!/bin/bash
echo "space Preset Simulation Tests"
echo "   4 Thread Simulations"
echo "      Trial 1"
./space_x86.x 4 1 0 0 &> space_4.txt
for X in {2..10..1}
do
	echo "      Trial $X"
	./space_x86.x 4 1 0 0 &>> space_4.txt
done


echo "   8 Thread Simulations"
echo "      Trial 1"
./space_x86.x 8 1 0 0 &> space_8.txt
for X in {2..10..1}
do
	echo "      Trial $X"
	./space_x86.x 8 1 0 0 &>> space_8.txt
done


echo "   16 Thread Simulations"
echo "      Trial 1"
./space_x86.x 16 1 0 0 &> space_16.txt
for X in {2..10..1}
do
	echo "      Trial $X"
	./space_x86.x 16 1 0 0 &>> space_16.txt
done


echo "   32 Thread Simulations"
echo "      Trial 1"
./space_x86.x 32 1 0 0 &> space_32.txt
for X in {2..10..1}
do
	echo "      Trial $X"
	./space_x86.x 32 1 0 0 &>> space_32.txt
done

