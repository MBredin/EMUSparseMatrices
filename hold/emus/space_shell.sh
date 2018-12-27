#!/bin/bash
echo "space Preset Simulation Tests"
echo "   4 Thread Simulations"
echo "      Trial 1"
emu_handler_and_loader 0 16 space_sims.mwx 4 1 0 0 &> space_4.txt
for X in {2..10..1}
do
	echo "      Trial $X"
	emu_handler_and_loader 0 16 space_sims.mwx 4 1 0 0 &>> space_4.txt
done


echo "   8 Thread Simulations"
echo "      Trial 1"
emu_handler_and_loader 0 16 space_sims.mwx 8 1 0 0 &> space_8.txt
for X in {2..10..1}
do
	echo "      Trial $X"
	emu_handler_and_loader 0 16 space_sims.mwx 8 1 0 0 &>> space_8.txt
done


echo "   16 Thread Simulations"
echo "      Trial 1"
emu_handler_and_loader 0 16 space_sims.mwx 16 1 0 0 &> space_16.txt
for X in {2..10..1}
do
	echo "      Trial $X"
	emu_handler_and_loader 0 16 space_sims.mwx 16 1 0 0 &>> space_16.txt
done


echo "   32 Thread Simulations"
echo "      Trial 1"
emu_handler_and_loader 0 16 space_sims.mwx 32 1 0 0 &> space_32.txt
for X in {2..10..1}
do
	echo "      Trial $X"
	emu_handler_and_loader 0 16 space_sims.mwx 32 1 0 0 &>> space_32.txt
done

echo "Tests Complete"
