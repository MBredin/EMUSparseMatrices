#!/bin/bash
echo "494 Preset Simulation Tests"
echo "   4 Thread Simulations"
echo "      Trial 1"
./494_x86.x 4 1 0 0 &> preset_4.txt
for X in {2..10..1}
do
	echo "      Trial $X"
	./494_x86.x 4 1 0 0 &>> preset_4.txt
done


echo "   8 Thread Simulations"
echo "      Trial 1"
./494_x86.x 8 1 0 0 &> preset_8.txt
for X in {2..10..1}
do
	echo "      Trial $X"
	./494_x86.x 8 1 0 0 &>> preset_8.txt
done


echo "   16 Thread Simulations"
echo "      Trial 1"
./494_x86.x 16 1 0 0 &> preset_16.txt
for X in {2..10..1}
do
	echo "      Trial $X"
	./494_x86.x 16 1 0 0 &>> preset_16.txt
done


echo "   32 Thread Simulations"
echo "      Trial 1"
./494_x86.x 32 1 0 0 &> preset_32.txt
for X in {2..10..1}
do
	echo "      Trial $X"
	./494_x86.x 32 1 0 0 &>> preset_32.txt
done

#############################################################

echo "10% Spasrity Tests Simulation Tests"
echo "   4 Thread Simulations (1024, 2048, 4096)"
echo "      Trial 1"
./494_x86.x 4 0 1024 10 &> gen_1028_4.txt
./494_x86.x 4 0 2048 10 &> gen_2048_4.txt
./494_x86.x 4 0 4096 10 &> gen_4096_4.txt
for X in {2..10..1}
do
	echo "      Trial $X"
	./494_x86.x 4 0 1024 10 &>> gen_1028_4.txt
	./494_x86.x 4 0 2048 10 &>> gen_2048_4.txt
	./494_x86.x 4 0 4096 10 &>> gen_4096_4.txt
done


echo "   8 Thread Simulations"
echo "      Trial 1"
./494_x86.x 8 0 1024 10 &> gen_1028_8.txt
./494_x86.x 8 0 2048 10 &> gen_2048_8.txt
./494_x86.x 8 0 4096 10 &> gen_4096_8.txt
for X in {2..10..1}
do
	echo "      Trial $X"
	./494_x86.x 8 0 1024 10 &>> gen_1028_8.txt
	./494_x86.x 8 0 2048 10 &>> gen_2048_8.txt
	./494_x86.x 8 0 4096 10 &>> gen_4096_8.txt
done


echo "   16 Thread Simulations"
echo "      Trial 1"
./494_x86.x 16 0 1024 10 &> gen_1028_16.txt
./494_x86.x 16 0 2048 10 &> gen_2048_16.txt
./494_x86.x 16 0 4096 10 &> gen_4096_16.txt
for X in {2..10..1}
do
	echo "      Trial $X"
	./494_x86.x 16 0 1024 10 &>> gen_1028_16.txt
	./494_x86.x 16 0 2048 10 &>> gen_2048_16.txt
	./494_x86.x 16 0 4096 10 &>> gen_4096_16.txt
done


echo "   32 Thread Simulations"
echo "      Trial 1"
./494_x86.x 32 0 1024 10 &> gen_1028_32.txt
./494_x86.x 32 0 2048 10 &> gen_2048_32.txt
./494_x86.x 32 0 4096 10 &> gen_4096_32.txt
for X in {2..10..1}
do
	echo "      Trial $X"
	./494_x86.x 32 0 1024 10 &>> gen_1028_32.txt
	./494_x86.x 32 0 2048 10 &>> gen_2048_32.txt
	./494_x86.x 32 0 4096 10 &>> gen_4096_32.txt
done
echo "Tests Complete"
