Post Untimed portion: CurrentRSS (MB)=12.1328
Post Untimed portion: PeakRSS (MB)=12.1328
************************************************
Program Name/Arguments: 
circuit_sims.mwx 
32 
1 
0 
0 
************************************************
Simulator Version: EMUSIM-18.04
************************************************
Configuration Details:
Gossamer Cores per Nodelet=4
Log2 Num Nodelets=3
Log2 Memory Size/Nodelet=33
Capture queue depths=false
Send ACKs from remotes=true
Bandwidth multiplier through MigrEng=1
Core Clock=300 MHz, Pd=3.333
Memory DDR4-2133: Bandwidth = 1.886 GiB/s = 2.025 GB/s
SRIO SystemIC bandwidth=2.32 GiB/s (2.5GB/s)
************************************************
Post SystemC Startup: CurrentRSS (MB)=12.1328
Post SystemC Startup: PeakRSS (MB)=12.1328
PROGRAM ENDED.
Emu system run time 0.107 sec==106739325000 ps
System thread counts:
	active=0, created=513, died=513,
	max live=58 first occurred @5455147764 ps with prog 5.11% complete
	and last occurred @5455147764 ps with prog 5.15% complete
Num_Core_Cycles=32025000
Num_SRIO_Cycles=66712078
Num_Mem_Cycles=27022613
************************************************
MEMORY MAP
208891,6657,6661,6931,6632,9643,8111,19018
6686,14600,38,0,0,0,0,0
6728,0,14784,38,0,0,0,0
6998,0,0,15323,38,0,0,0
6700,0,0,0,14866,38,0,0
9713,0,0,0,0,19283,38,0
8180,0,0,0,0,0,16747,38
19096,3,3,3,4,6,5,32581

************************************************
REMOTES MAP
0,1970,1946,2036,1936,2939,2429,6064
96,0,38,0,0,0,0,0
96,0,0,38,0,0,0,0
96,0,0,0,38,0,0,0
96,0,0,0,0,38,0,0
96,0,0,0,0,0,38,0
96,0,0,0,0,0,0,38
134,0,0,0,0,0,0,0

************************************************
Module: #_created, #_spawns, #_quits, #_migrates, #_rmos_in, #_rmos_out, mem_bw, IPC
NLET[0]: 1, 64, 513, 63653, 710, 19320, 0.0116178, 0.0561203
NLET[1]: 0, 64, 0, 6724, 1970, 134, 0.000979809, 0.00418751
NLET[2]: 0, 64, 0, 6766, 1984, 134, 0.000994611, 0.00424653
NLET[3]: 0, 64, 0, 7036, 2074, 134, 0.00103288, 0.0044099
NLET[4]: 0, 64, 0, 6738, 1974, 134, 0.000998571, 0.00427525
NLET[5]: 0, 64, 0, 9751, 2977, 134, 0.00135105, 0.00558745
NLET[6]: 0, 64, 0, 8218, 2467, 134, 0.00115026, 0.00481855
NLET[7]: 0, 64, 0, 19120, 6102, 134, 0.00244943, 0.00955104

Module: #_in_xacts, in_bw, #_to_nqms, #_to_sysic, p_zero, p_one, opt1, opt2, restored
ME[0].FromNQM[0]: 83683, 0.0475469, 83683, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[1]: 8828, 0.00490117, 8828, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[2]: 8884, 0.00493177, 8884, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[3]: 9244, 0.00512849, 9244, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[4]: 8846, 0.00491135, 8846, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[5]: 12862, 0.00710657, 12862, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[6]: 10819, 0.00598966, 10819, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[7]: 25356, 0.0139329, 25356, 0, 0, 0, 0, 0, 0

Module: #_in_xacts, in_bw, out_bw, passers_by, passers_stored
ME[0].FromSysIC[0]: 0, 0, 0, 0, 0
ME[0].FromSysIC[1]: 0, 0, 0, 0, 0
ME[0].FromSysIC[2]: 0, 0, 0, 0, 0
ME[0].FromSysIC[3]: 0, 0, 0, 0, 0
ME[0].FromSysIC[4]: 0, 0, 0, 0, 0
ME[0].FromSysIC[5]: 0, 0, 0, 0, 0

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToNQM[0]: 84131, 0.0466924, 0.00324831, 1.17876, 0, -nan, 0.00324831, 1.17876
ME[0].ToNQM[1]: 8764, 0.00497187, 0.000275029, 1, 0, -nan, 0.000275029, 1
ME[0].ToNQM[2]: 8820, 0.00500334, 0.000276826, 1.00011, 0, -nan, 0.000276826, 1.00011
ME[0].ToNQM[3]: 9180, 0.00520568, 0.000288151, 1, 0, -nan, 0.000288151, 1
ME[0].ToNQM[4]: 8782, 0.0049823, 0.000275628, 1.00011, 0, -nan, 0.000275628, 1.00011
ME[0].ToNQM[5]: 12798, 0.00724016, 0.00040254, 1, 0, -nan, 0.00040254, 1
ME[0].ToNQM[6]: 10755, 0.0060914, 0.00033789, 1, 0, -nan, 0.00033789, 1
ME[0].ToNQM[7]: 25292, 0.0142616, 0.000801184, 1, 0, -nan, 0.000801184, 1

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToSysIC[0]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[1]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[2]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[3]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[4]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[5]: 0, 0, 0, -nan, 0, -nan, 0, -nan


************************************************
End of simulation: CurrentRSS (MB)=27.9258
End of simulation: PeakRSS (MB)=27.9258
************************************************
Simulator wall clock time (seconds): 1045
