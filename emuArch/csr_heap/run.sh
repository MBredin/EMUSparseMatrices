#!/bin/bash
cd ~/dramV2/10perc

echo "10% Sparsity Set"
echo "   2 Thread Simulations"
echo "      Trial 1"
emu_handler_and_loader 0 16  test.mwx 2 1 0 0 &> preset.txt
for X in {2..10..1}
do
	echo "      Trial $X"
	emu_handler_and_loader 0 16  test.mwx 2 1 0 0 &>> preset.txt
done

echo "Test Complete"
