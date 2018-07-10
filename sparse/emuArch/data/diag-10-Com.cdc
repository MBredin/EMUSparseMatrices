Post Untimed portion: CurrentRSS (MB)=10.2656
Post Untimed portion: PeakRSS (MB)=10.2656
************************************************
Program Name/Arguments: 
diag-10-Com.mwx 
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
Post SystemC Startup: CurrentRSS (MB)=10.2656
Post SystemC Startup: PeakRSS (MB)=10.2656
PROGRAM ENDED.
Emu system run time 8.64e-05 sec==86374600 ps
System thread counts:
	active=0, created=17, died=17,
	max live=7 first occurred @12893918 ps with prog 14.9% complete
	and last occurred @12893918 ps with prog 19.7% complete
Num_Core_Cycles=310700
Num_SRIO_Cycles=53984
Num_Mem_Cycles=21866
************************************************
MEMORY MAP
1049,2,2,2,2,2,2,2
4,167,0,0,0,0,0,0
4,0,167,0,0,0,0,0
4,0,0,167,0,0,0,0
4,0,0,0,167,0,0,0
4,0,0,0,0,167,0,0
4,0,0,0,0,0,167,0
4,0,0,0,0,0,0,260

************************************************
REMOTES MAP
0,0,0,0,0,0,0,0
3,0,0,0,0,0,0,0
3,0,0,0,0,0,0,0
3,0,0,0,0,0,0,0
3,0,0,0,0,0,0,0
3,0,0,0,0,0,0,0
3,0,0,0,0,0,0,0
3,0,0,0,0,0,0,0

************************************************
Module: #_created, #_spawns, #_quits, #_migrates, #_rmos_in, #_rmos_out, mem_bw, IPC
NLET[0]: 1, 2, 17, 14, 21, 0, 0.0651239, 0.0212584
NLET[1]: 0, 2, 0, 4, 0, 3, 0.00887222, 0.00410042
NLET[2]: 0, 2, 0, 4, 0, 3, 0.00887222, 0.00410042
NLET[3]: 0, 2, 0, 4, 0, 3, 0.00887222, 0.00410042
NLET[4]: 0, 2, 0, 4, 0, 3, 0.00887222, 0.00410042
NLET[5]: 0, 2, 0, 4, 0, 3, 0.00887222, 0.00410042
NLET[6]: 0, 2, 0, 4, 0, 3, 0.00887222, 0.00410042
NLET[7]: 0, 2, 0, 4, 0, 3, 0.0131254, 0.0072224

Module: #_in_xacts, in_bw, #_to_nqms, #_to_sysic, p_zero, p_one, opt1, opt2, restored
ME[0].FromNQM[0]: 35, 0.00101384, 35, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[1]: 7, 0.000299324, 7, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[2]: 7, 0.000299324, 7, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[3]: 7, 0.000299324, 7, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[4]: 7, 0.000299324, 7, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[5]: 7, 0.000299324, 7, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[6]: 7, 0.000299324, 7, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[7]: 7, 0.000299324, 7, 0, 0, 0, 0, 0, 0

Module: #_in_xacts, in_bw, out_bw, passers_by, passers_stored
ME[0].FromSysIC[0]: 0, 0, 0, 0, 0
ME[0].FromSysIC[1]: 0, 0, 0, 0, 0
ME[0].FromSysIC[2]: 0, 0, 0, 0, 0
ME[0].FromSysIC[3]: 0, 0, 0, 0, 0
ME[0].FromSysIC[4]: 0, 0, 0, 0, 0
ME[0].FromSysIC[5]: 0, 0, 0, 0, 0

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToNQM[0]: 49, 0.00209527, 0.000158039, 1, 0, -nan, 0.000158039, 1
ME[0].ToNQM[1]: 5, 0.000144834, 1.60949e-05, 1, 0, -nan, 1.60949e-05, 1
ME[0].ToNQM[2]: 5, 0.000144834, 1.60949e-05, 1, 0, -nan, 1.60949e-05, 1
ME[0].ToNQM[3]: 5, 0.000144834, 1.60949e-05, 1, 0, -nan, 1.60949e-05, 1
ME[0].ToNQM[4]: 5, 0.000144834, 1.60949e-05, 1, 0, -nan, 1.60949e-05, 1
ME[0].ToNQM[5]: 5, 0.000144834, 1.60949e-05, 1, 0, -nan, 1.60949e-05, 1
ME[0].ToNQM[6]: 5, 0.000144834, 1.60949e-05, 1, 0, -nan, 1.60949e-05, 1
ME[0].ToNQM[7]: 5, 0.000144834, 1.60949e-05, 1, 0, -nan, 1.60949e-05, 1

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToSysIC[0]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[1]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[2]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[3]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[4]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[5]: 0, 0, 0, -nan, 0, -nan, 0, -nan


************************************************
End of simulation: CurrentRSS (MB)=10.2656
End of simulation: PeakRSS (MB)=10.2656
************************************************
Simulator wall clock time (seconds): 2
