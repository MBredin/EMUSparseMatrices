Post Untimed portion: CurrentRSS (MB)=10.6719
Post Untimed portion: PeakRSS (MB)=10.6719
************************************************
Program Name/Arguments: 
test.mwx 
2 
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
Post SystemC Startup: CurrentRSS (MB)=10.6719
Post SystemC Startup: PeakRSS (MB)=10.6719
PROGRAM ENDED.
Emu system run time 0.012 sec==12047128500 ps
System thread counts:
	active=0, created=1, died=1,
	max live=1 first occurred @0 s with prog 0% complete
	and last occurred @0 s with prog 0% complete
Num_Core_Cycles=3614500
Num_SRIO_Cycles=7529455
Num_Mem_Cycles=3049905
************************************************
MEMORY MAP
12865,329,312,296,258,234,254,272
328,443,2,0,0,0,0,0
312,0,387,2,0,0,0,0
296,0,0,367,2,0,0,0
258,0,0,0,329,2,0,0
234,0,0,0,0,305,2,0
254,0,0,0,0,0,325,2
273,1,0,0,0,0,0,343

************************************************
REMOTES MAP
0,158,149,141,122,110,120,129
218,0,2,0,0,0,0,0
211,0,0,2,0,0,0,0
203,0,0,0,2,0,0,0
184,0,0,0,0,2,0,0
172,0,0,0,0,0,2,0
181,0,0,0,0,0,0,2
192,0,0,0,0,0,0,0

************************************************
Module: #_created, #_spawns, #_quits, #_migrates, #_rmos_in, #_rmos_out, mem_bw, IPC
NLET[0]: 1, 0, 1, 1955, 1361, 929, 0.00572149, 0.0241168
NLET[1]: 0, 0, 0, 330, 158, 220, 0.00036329, 0.00202877
NLET[2]: 0, 0, 0, 314, 151, 213, 0.000332797, 0.00188546
NLET[3]: 0, 0, 0, 298, 143, 205, 0.000315748, 0.00179748
NLET[4]: 0, 0, 0, 260, 124, 186, 0.000278369, 0.0016135
NLET[5]: 0, 0, 0, 236, 112, 174, 0.000254762, 0.0014973
NLET[6]: 0, 0, 0, 256, 122, 183, 0.000274435, 0.00159026
NLET[7]: 0, 0, 0, 274, 131, 192, 0.00029214, 0.00167271

Module: #_in_xacts, in_bw, #_to_nqms, #_to_sysic, p_zero, p_one, opt1, opt2, restored
ME[0].FromNQM[0]: 4245, 0.0135878, 4245, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[1]: 708, 0.00232619, 708, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[2]: 678, 0.00221663, 678, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[3]: 646, 0.00210596, 646, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[4]: 570, 0.00184313, 570, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[5]: 522, 0.00167713, 522, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[6]: 561, 0.00181464, 561, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[7]: 597, 0.00193913, 597, 0, 0, 0, 0, 0, 0

Module: #_in_xacts, in_bw, out_bw, passers_by, passers_stored
ME[0].FromSysIC[0]: 0, 0, 0, 0, 0
ME[0].FromSysIC[1]: 0, 0, 0, 0, 0
ME[0].FromSysIC[2]: 0, 0, 0, 0, 0
ME[0].FromSysIC[3]: 0, 0, 0, 0, 0
ME[0].FromSysIC[4]: 0, 0, 0, 0, 0
ME[0].FromSysIC[5]: 0, 0, 0, 0, 0

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToNQM[0]: 4245, 0.0138268, 0.0011909, 1, 0, -nan, 0.0011909, 1
ME[0].ToNQM[1]: 708, 0.00229188, 0.000196328, 1, 0, -nan, 0.000196328, 1
ME[0].ToNQM[2]: 678, 0.00218232, 0.000187988, 1, 0, -nan, 0.000187988, 1
ME[0].ToNQM[3]: 646, 0.00207166, 0.000179096, 1, 0, -nan, 0.000179096, 1
ME[0].ToNQM[4]: 570, 0.00180883, 0.000157984, 1, 0, -nan, 0.000157984, 1
ME[0].ToNQM[5]: 522, 0.00164283, 0.000144656, 1, 0, -nan, 0.000144656, 1
ME[0].ToNQM[6]: 561, 0.00178088, 0.000155485, 1, 0, -nan, 0.000155485, 1
ME[0].ToNQM[7]: 597, 0.00190538, 0.000165483, 1, 0, -nan, 0.000165483, 1

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToSysIC[0]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[1]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[2]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[3]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[4]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[5]: 0, 0, 0, -nan, 0, -nan, 0, -nan


************************************************
End of simulation: CurrentRSS (MB)=11.3047
End of simulation: PeakRSS (MB)=11.3047
************************************************
Simulator wall clock time (seconds): 44
