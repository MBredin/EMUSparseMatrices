#!/bin/bash
echo "494 Preset Simulation Tests"
echo "   4 Thread Simulations"
echo "      Trial 1"
emusim.x 494_sims.mwx 4 1 0 0 &> 494_4.txt


echo "   8 Thread Simulations"
echo "      Trial 1"
emusim.x 494_sims.mwx 8 1 0 0 &> 494_8.txt


echo "   16 Thread Simulations"
echo "      Trial 1"
emusim.x 494_sims.mwx 16 1 0 0 &> 494_16.txt


echo "   32 Thread Simulations"
echo "      Trial 1"
emusim.x 494_sims.mwx 32 1 0 0 &> 494_32.txt

echo "Tests Complete"
