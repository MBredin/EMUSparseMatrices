************************************************
Program Name/Arguments: 
test.mwx 
32 
64 
32 
************************************************
Simulator Version: EMUSIM-18.11-CPLUS
************************************************
Configuration Details:
Gossamer Cores per Nodelet=4
Log2 Nodelets per Node=3
Number of Nodes=1
Total nodelet count=8
Log2 Memory Size per Nodelet=33
Total Memory (in GiB)=64
Capture queue depths=false
Initial thread: Send ACKs from remotes=true
Bandwidth multiplier through MigrEng=1
Core Clock=300 MHz, Pd=3.333
Memory DDR4-2133: Bandwidth = 1.886 GiB/s = 2.025 GB/s
SRIO SystemIC bandwidth=2.32 GiB/s (2.5GB/s)
************************************************
PROGRAM ENDED.
Emu system run time 0.894 sec==893778613200 ps
System thread counts:
	active=0, created=147, died=147,
	max live=53 first occurred @24909642120 ps with prog 2.79% complete
	and last occurred @24909642120 ps with prog 2.79% complete
Num_Core_Cycles=268160400
Num_SRIO_Cycles=558611633
Num_Mem_Cycles=226273066
************************************************
MEMORY MAP
477131,6973,6802122,1255,1233,1223,1205,1226
4887,5545,2086,0,0,0,0,0
6805369,0,3735,0,0,0,0,0
1008,0,247,3477,0,0,0,0
1004,0,229,0,3470,0,0,0
992,0,231,0,0,3418,0,0
990,0,215,0,0,0,3464,0
987,0,239,0,0,0,0,3479

************************************************
REMOTES MAP
0,0,2024,2025,0,0,0,0
0,0,2025,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0

************************************************
Module: #_created, #_spawns, #_quits, #_migrates, #_rmos_in, #_rmos_out, mem_bw, IPC
NLET[0]: 1, 146, 147, 6815237, 0, 4049, 0.0330687, 0.136322
NLET[1]: 0, 0, 0, 6973, 0, 2025, 7.67833e-05, 0.000327498
NLET[2]: 0, 0, 0, 6805369, 4049, 0, 0.0301138, 0.0635668
NLET[3]: 0, 0, 0, 1255, 2025, 0, 3.33226e-05, 0.000131444
NLET[4]: 0, 0, 0, 1233, 0, 0, 2.42274e-05, 0.000130403
NLET[5]: 0, 0, 0, 1223, 0, 0, 2.38782e-05, 0.000128699
NLET[6]: 0, 0, 0, 1205, 0, 0, 2.40152e-05, 0.000129363
NLET[7]: 0, 0, 0, 1226, 0, 0, 2.41743e-05, 0.000130474

Module: #_in_xacts, in_bw, #_to_nqms, #_to_sysic, p_zero, p_one, opt1, opt2, restored
ME[0].FromNQM[0]: 6819286, 0.584324, 6819286, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[1]: 8998, 0.000589386, 8998, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[2]: 6809418, 0.583522, 6809418, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[3]: 3280, 0.000106526, 3280, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[4]: 1233, 9.70762e-05, 1233, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[5]: 1223, 9.62409e-05, 1223, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[6]: 1205, 9.46635e-05, 1205, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[7]: 1226, 9.64796e-05, 1226, 0, 0, 0, 0, 0, 0

Module: #_in_xacts, in_bw, out_bw, passers_by, passers_stored
ME[0].FromSysIC[0]: 0, 0, 0, 0, 0
ME[0].FromSysIC[1]: 0, 0, 0, 0, 0
ME[0].FromSysIC[2]: 0, 0, 0, 0, 0
ME[0].FromSysIC[3]: 0, 0, 0, 0, 0
ME[0].FromSysIC[4]: 0, 0, 0, 0, 0
ME[0].FromSysIC[5]: 0, 0, 0, 0, 0

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToNQM[0]: 6819286, 0.584294, 0.0631649, 1.00012, 0, -nan, 0.0631649, 1.00012
ME[0].ToNQM[1]: 8998, 0.000574279, 3.35738e-05, 1, 0, -nan, 3.35738e-05, 1
ME[0].ToNQM[2]: 6809418, 0.583552, 0.0609763, 1.00001, 0, -nan, 0.0609763, 1.00001
ME[0].ToNQM[3]: 3280, 0.000121629, 1.2233e-05, 1, 0, -nan, 1.2233e-05, 1
ME[0].ToNQM[4]: 1233, 9.70762e-05, 4.59844e-06, 1, 0, -nan, 4.59844e-06, 1
ME[0].ToNQM[5]: 1223, 9.62409e-05, 4.56114e-06, 1, 0, -nan, 4.56114e-06, 1
ME[0].ToNQM[6]: 1205, 9.46635e-05, 4.494e-06, 1, 0, -nan, 4.494e-06, 1
ME[0].ToNQM[7]: 1226, 9.64796e-05, 4.57233e-06, 1, 0, -nan, 4.57233e-06, 1

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToSysIC[0]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[1]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[2]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[3]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[4]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[5]: 0, 0, 0, -nan, 0, -nan, 0, -nan


************************************************
Simulator wall clock time (seconds): 3434
