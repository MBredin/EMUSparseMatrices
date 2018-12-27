#!/bin/bash
echo "space Preset Simulation Tests"
echo "   4 Thread Simulations"
echo "      Trial 1"
emusim.x space_sims.mwx 4 1 0 0 &> space_4.txt


echo "   8 Thread Simulations"
echo "      Trial 1"
emusim.x space_sims.mwx 8 1 0 0 &> space_8.txt


echo "   16 Thread Simulations"
echo "      Trial 1"
emusim.x space_sims.mwx 16 1 0 0 &> space_16.txt


echo "   32 Thread Simulations"
echo "      Trial 1"
emusim.x space_sims.mwx 32 1 0 0 &> space_32.txt

echo "Tests Complete"
