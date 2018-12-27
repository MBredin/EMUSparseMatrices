Post Untimed portion: CurrentRSS (MB)=11.2188
Post Untimed portion: PeakRSS (MB)=11.2188
************************************************
Program Name/Arguments: 
space_sims.mwx 
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
Post SystemC Startup: CurrentRSS (MB)=11.2188
Post SystemC Startup: PeakRSS (MB)=11.2188
PROGRAM ENDED.
Emu system run time 0.0731 sec==73133352600 ps
System thread counts:
	active=0, created=513, died=513,
	max live=60 first occurred @1889711010 ps with prog 2.58% complete
	and last occurred @1889711010 ps with prog 2.67% complete
Num_Core_Cycles=21942200
Num_SRIO_Cycles=45708345
Num_Mem_Cycles=18514772
************************************************
MEMORY MAP
192552,3866,3794,3723,3859,3737,3595,3492
3918,9021,15,0,0,0,0,0
3864,0,9064,15,0,0,0,0
3788,0,0,8674,15,0,0,0
3925,0,0,0,8925,15,0,0
3801,0,0,0,0,8631,15,0
3659,0,0,0,0,0,8457,15
3559,3,6,1,2,0,0,8305

************************************************
REMOTES MAP
0,1186,1151,1129,1174,1134,1088,1054
96,0,15,0,0,0,0,0
96,0,0,15,0,0,0,0
96,0,0,0,15,0,0,0
96,0,0,0,0,15,0,0
96,0,0,0,0,0,15,0
96,0,0,0,0,0,0,15
111,0,0,0,0,0,0,0

************************************************
Module: #_created, #_spawns, #_quits, #_migrates, #_rmos_in, #_rmos_out, mem_bw, IPC
NLET[0]: 1, 64, 513, 26066, 687, 7916, 0.0138299, 0.0631303
NLET[1]: 0, 64, 0, 3933, 1186, 111, 0.000863689, 0.00347107
NLET[2]: 0, 64, 0, 3879, 1166, 111, 0.000865255, 0.00349081
NLET[3]: 0, 64, 0, 3803, 1144, 111, 0.000832038, 0.00333089
NLET[4]: 0, 64, 0, 3940, 1189, 111, 0.000859206, 0.00343457
NLET[5]: 0, 64, 0, 3816, 1149, 111, 0.000832416, 0.00331238
NLET[6]: 0, 64, 0, 3674, 1103, 111, 0.000810164, 0.0032412
NLET[7]: 0, 64, 0, 3571, 1069, 111, 0.000792556, 0.00316937

Module: #_in_xacts, in_bw, #_to_nqms, #_to_sysic, p_zero, p_one, opt1, opt2, restored
ME[0].FromNQM[0]: 34669, 0.0284362, 34669, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[1]: 5230, 0.00418823, 5230, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[2]: 5156, 0.00413072, 5156, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[3]: 5058, 0.00405005, 5058, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[4]: 5240, 0.00419571, 5240, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[5]: 5076, 0.0040639, 5076, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[6]: 4888, 0.00391292, 4888, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[7]: 4751, 0.0038034, 4751, 0, 0, 0, 0, 0, 0

Module: #_in_xacts, in_bw, out_bw, passers_by, passers_stored
ME[0].FromSysIC[0]: 0, 0, 0, 0, 0
ME[0].FromSysIC[1]: 0, 0, 0, 0, 0
ME[0].FromSysIC[2]: 0, 0, 0, 0, 0
ME[0].FromSysIC[3]: 0, 0, 0, 0, 0
ME[0].FromSysIC[4]: 0, 0, 0, 0, 0
ME[0].FromSysIC[5]: 0, 0, 0, 0, 0

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToNQM[0]: 35117, 0.0282216, 0.00221222, 1.34325, 0, -nan, 0.00221222, 1.34325
ME[0].ToNQM[1]: 5166, 0.00422273, 0.000236435, 1, 0, -nan, 0.000236435, 1
ME[0].ToNQM[2]: 5092, 0.00416339, 0.000233126, 1.00039, 0, -nan, 0.000233126, 1.00039
ME[0].ToNQM[3]: 4994, 0.00408072, 0.000228531, 1, 0, -nan, 0.000228531, 1
ME[0].ToNQM[4]: 5176, 0.00423048, 0.00023694, 1.00019, 0, -nan, 0.00023694, 1.00019
ME[0].ToNQM[5]: 5012, 0.00409503, 0.000229358, 1, 0, -nan, 0.000229358, 1
ME[0].ToNQM[6]: 4824, 0.0039399, 0.00022072, 1, 0, -nan, 0.00022072, 1
ME[0].ToNQM[7]: 4687, 0.00382728, 0.000214427, 1, 0, -nan, 0.000214427, 1

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToSysIC[0]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[1]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[2]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[3]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[4]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[5]: 0, 0, 0, -nan, 0, -nan, 0, -nan


************************************************
End of simulation: CurrentRSS (MB)=20.707
End of simulation: PeakRSS (MB)=20.707
************************************************
Simulator wall clock time (seconds): 401
