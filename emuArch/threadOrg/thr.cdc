Post Untimed portion: CurrentRSS (MB)=10.3242
Post Untimed portion: PeakRSS (MB)=10.3242
************************************************
Program Name/Arguments: 
thr.mwx 
************************************************
Simulator Version: EMUSIM-18.04.1
************************************************
Configuration Details:
Gossamer Cores per Nodelet=4
Log2 Num Nodelets=3
Log2 Memory Size/Nodelet=33
Capture queue depths=true
Timing sample interval (ns)=10000
Send ACKs from remotes=true
Bandwidth multiplier through MigrEng=1
Core Clock=300 MHz, Pd=3.333
Memory DDR4-2133: Bandwidth = 1.886 GiB/s = 2.025 GB/s
SRIO SystemIC bandwidth=2.32 GiB/s (2.5GB/s)
************************************************
Post SystemC Startup: CurrentRSS (MB)=10.3242
Post SystemC Startup: PeakRSS (MB)=10.3242
PROGRAM ENDED.
Emu system run time 0.000194 sec==194313900 ps
System thread counts:
	active=0, created=9, died=9,
	max live=9 first occurred @76369029 ps with prog 39.3% complete
	and last occurred @76369029 ps with prog 39.3% complete
Num_Core_Cycles=58300
Num_SRIO_Cycles=121446
Num_Mem_Cycles=49193
************************************************
MEMORY MAP
485,1,1,1,1,1,1,1
1,127,0,0,0,0,0,0
1,0,127,0,0,0,0,0
1,0,0,127,0,0,0,0
1,0,0,0,127,0,0,0
1,0,0,0,0,127,0,0
1,0,0,0,0,0,127,0
1,0,0,0,0,0,0,127

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
NLET[0]: 1, 8, 9, 7, 0, 0, 0.0140264, 0.0569811
NLET[1]: 0, 0, 0, 1, 0, 0, 0.00390299, 0.01753
NLET[2]: 0, 0, 0, 1, 0, 0, 0.00390299, 0.01753
NLET[3]: 0, 0, 0, 1, 0, 0, 0.00390299, 0.01753
NLET[4]: 0, 0, 0, 1, 0, 0, 0.00390299, 0.01753
NLET[5]: 0, 0, 0, 1, 0, 0, 0.00390299, 0.01753
NLET[6]: 0, 0, 0, 1, 0, 0, 0.00390299, 0.01753
NLET[7]: 0, 0, 0, 1, 0, 0, 0.00390299, 0.01753

Module: #_in_xacts, in_bw, #_to_nqms, #_to_sysic, p_zero, p_one, opt1, opt2, restored
ME[0].FromNQM[0]: 7, 0.00168096, 7, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[1]: 1, 0.00025729, 1, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[2]: 1, 0.00025729, 1, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[3]: 1, 0.00025729, 1, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[4]: 1, 0.00025729, 1, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[5]: 1, 0.00025729, 1, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[6]: 1, 0.00025729, 1, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[7]: 1, 0.00025729, 1, 0, 0, 0, 0, 0, 0

Module: #_in_xacts, in_bw, out_bw, passers_by, passers_stored
ME[0].FromSysIC[0]: 0, 0, 0, 0, 0
ME[0].FromSysIC[1]: 0, 0, 0, 0, 0
ME[0].FromSysIC[2]: 0, 0, 0, 0, 0
ME[0].FromSysIC[3]: 0, 0, 0, 0, 0
ME[0].FromSysIC[4]: 0, 0, 0, 0, 0
ME[0].FromSysIC[5]: 0, 0, 0, 0, 0

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToNQM[0]: 7, 0.00180103, 0.000120281, 1, 0, -nan, 0.000120281, 1
ME[0].ToNQM[1]: 1, 0.000240137, 1.71562e-05, 1, 0, -nan, 1.71562e-05, 1
ME[0].ToNQM[2]: 1, 0.000240137, 1.71562e-05, 1, 0, -nan, 1.71562e-05, 1
ME[0].ToNQM[3]: 1, 0.000240137, 1.71562e-05, 1, 0, -nan, 1.71562e-05, 1
ME[0].ToNQM[4]: 1, 0.000240137, 1.71562e-05, 1, 0, -nan, 1.71562e-05, 1
ME[0].ToNQM[5]: 1, 0.000240137, 1.71562e-05, 1, 0, -nan, 1.71562e-05, 1
ME[0].ToNQM[6]: 1, 0.000240137, 1.71562e-05, 1, 0, -nan, 1.71562e-05, 1
ME[0].ToNQM[7]: 1, 0.000240137, 1.71562e-05, 1, 0, -nan, 1.71562e-05, 1

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToSysIC[0]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[1]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[2]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[3]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[4]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[5]: 0, 0, 0, -nan, 0, -nan, 0, -nan


************************************************
End of simulation: CurrentRSS (MB)=10.3242
End of simulation: PeakRSS (MB)=10.3242
************************************************
Simulator wall clock time (seconds): 0
