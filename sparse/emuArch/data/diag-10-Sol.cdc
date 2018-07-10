Post Untimed portion: CurrentRSS (MB)=10.1992
Post Untimed portion: PeakRSS (MB)=10.1992
************************************************
Program Name/Arguments: 
diag-10-Sol.mwx 
************************************************
Simulator Version: EMUSIM-18.04.1
************************************************
Configuration Details:
Gossamer Cores per Nodelet=4
Log2 Num Nodelets=3
Log2 Memory Size/Nodelet=33
Capture queue depths=false
Send ACKs from remotes=true
Bandwidth multiplier through MigrEng=1
Core Clock=3600 MHz, Pd=0.278
Memory DDR4-2133: Bandwidth = 1.886 GiB/s = 2.025 GB/s
SRIO SystemIC bandwidth=2.32 GiB/s (2.5GB/s)
************************************************
Post SystemC Startup: CurrentRSS (MB)=10.1992
Post SystemC Startup: PeakRSS (MB)=10.1992
PROGRAM ENDED.
Emu system run time 4.39e-05 sec==43896200 ps
System thread counts:
	active=0, created=9, died=9,
	max live=4 first occurred @17492038 ps with prog 39.8% complete
	and last occurred @17492038 ps with prog 64.2% complete
Num_Core_Cycles=157900
Num_SRIO_Cycles=27435
Num_Mem_Cycles=11112
************************************************
MEMORY MAP
564,1,1,1,1,1,1,1
2,67,0,0,0,0,0,0
2,0,67,0,0,0,0,0
2,0,0,67,0,0,0,0
2,0,0,0,67,0,0,0
2,0,0,0,0,67,0,0
2,0,0,0,0,0,67,0
2,0,0,0,0,0,0,98

************************************************
REMOTES MAP
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0

************************************************
Module: #_created, #_spawns, #_quits, #_migrates, #_rmos_in, #_rmos_out, mem_bw, IPC
NLET[0]: 1, 1, 9, 7, 0, 0, 0.0677646, 0.0199683
NLET[1]: 0, 1, 0, 2, 0, 0, 0.00782937, 0.00270424
NLET[2]: 0, 1, 0, 2, 0, 0, 0.00782937, 0.00270424
NLET[3]: 0, 1, 0, 2, 0, 0, 0.00782937, 0.00270424
NLET[4]: 0, 1, 0, 2, 0, 0, 0.00782937, 0.00270424
NLET[5]: 0, 1, 0, 2, 0, 0, 0.00782937, 0.00270424
NLET[6]: 0, 1, 0, 2, 0, 0, 0.00782937, 0.00270424
NLET[7]: 0, 1, 0, 2, 0, 0, 0.0106192, 0.00400887

Module: #_in_xacts, in_bw, #_to_nqms, #_to_sysic, p_zero, p_one, opt1, opt2, restored
ME[0].FromNQM[0]: 7, 0.000930969, 7, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[1]: 2, 0.000265991, 2, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[2]: 2, 0.000265991, 2, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[3]: 2, 0.000265991, 2, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[4]: 2, 0.000265991, 2, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[5]: 2, 0.000265991, 2, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[6]: 2, 0.000265991, 2, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[7]: 2, 0.000265991, 2, 0, 0, 0, 0, 0, 0

Module: #_in_xacts, in_bw, out_bw, passers_by, passers_stored
ME[0].FromSysIC[0]: 0, 0, 0, 0, 0
ME[0].FromSysIC[1]: 0, 0, 0, 0, 0
ME[0].FromSysIC[2]: 0, 0, 0, 0, 0
ME[0].FromSysIC[3]: 0, 0, 0, 0, 0
ME[0].FromSysIC[4]: 0, 0, 0, 0, 0
ME[0].FromSysIC[5]: 0, 0, 0, 0, 0

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToNQM[0]: 14, 0.00186194, 8.8828e-05, 1, 0, -nan, 8.8828e-05, 1
ME[0].ToNQM[1]: 1, 0.000132996, 6.33388e-06, 1, 0, -nan, 6.33388e-06, 1
ME[0].ToNQM[2]: 1, 0.000132996, 6.33388e-06, 1, 0, -nan, 6.33388e-06, 1
ME[0].ToNQM[3]: 1, 0.000132996, 6.33388e-06, 1, 0, -nan, 6.33388e-06, 1
ME[0].ToNQM[4]: 1, 0.000132996, 6.33388e-06, 1, 0, -nan, 6.33388e-06, 1
ME[0].ToNQM[5]: 1, 0.000132996, 6.33388e-06, 1, 0, -nan, 6.33388e-06, 1
ME[0].ToNQM[6]: 1, 0.000132996, 6.33388e-06, 1, 0, -nan, 6.33388e-06, 1
ME[0].ToNQM[7]: 1, 0.000132996, 6.33388e-06, 1, 0, -nan, 6.33388e-06, 1

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToSysIC[0]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[1]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[2]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[3]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[4]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[5]: 0, 0, 0, -nan, 0, -nan, 0, -nan


************************************************
End of simulation: CurrentRSS (MB)=10.1992
End of simulation: PeakRSS (MB)=10.1992
************************************************
Simulator wall clock time (seconds): 1
