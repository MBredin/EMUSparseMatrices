************************************************
Program Name/Arguments: 
test.mwx 
256 
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
Emu system run time 0.0349 sec==34923840600 ps
System thread counts:
	active=0, created=515, died=515,
	max live=167 first occurred @13545841947 ps with prog 38.8% complete
	and last occurred @13545841947 ps with prog 38.8% complete
Num_Core_Cycles=10478200
Num_SRIO_Cycles=21827400
Num_Mem_Cycles=8841478
************************************************
MEMORY MAP
3710286,897,119253,160,160,160,159,161
621,690,276,0,0,0,0,0
119688,0,462,0,0,0,0,0
128,0,32,441,0,0,0,0
128,0,32,0,434,0,0,0
129,0,31,0,0,453,0,0
127,0,32,0,0,0,411,0
129,0,32,0,0,0,0,453

************************************************
REMOTES MAP
0,0,248,249,0,0,0,0
0,0,249,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0

************************************************
Module: #_created, #_spawns, #_quits, #_migrates, #_rmos_in, #_rmos_out, mem_bw, IPC
NLET[0]: 1, 514, 515, 120950, 0, 497, 0.43853, 0.940443
NLET[1]: 0, 0, 0, 897, 0, 249, 0.000247131, 0.00106116
NLET[2]: 0, 0, 0, 119688, 497, 0, 0.0136569, 0.0289442
NLET[3]: 0, 0, 0, 160, 249, 0, 0.000107561, 0.000425646
NLET[4]: 0, 0, 0, 160, 0, 0, 7.83806e-05, 0.000420301
NLET[5]: 0, 0, 0, 160, 0, 0, 8.09819e-05, 0.000433853
NLET[6]: 0, 0, 0, 159, 0, 0, 7.53268e-05, 0.000404172
NLET[7]: 0, 0, 0, 161, 0, 0, 8.1095e-05, 0.000434426

Module: #_in_xacts, in_bw, #_to_nqms, #_to_sysic, p_zero, p_one, opt1, opt2, restored
ME[0].FromNQM[0]: 121447, 0.262472, 121447, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[1]: 1146, 0.00193487, 1146, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[2]: 120185, 0.259904, 120185, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[3]: 409, 0.000340898, 409, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[4]: 160, 0.000316848, 160, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[5]: 160, 0.000316848, 160, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[6]: 159, 0.000315226, 159, 0, 0, 0, 0, 0, 0
ME[0].FromNQM[7]: 161, 0.000319616, 161, 0, 0, 0, 0, 0, 0

Module: #_in_xacts, in_bw, out_bw, passers_by, passers_stored
ME[0].FromSysIC[0]: 0, 0, 0, 0, 0
ME[0].FromSysIC[1]: 0, 0, 0, 0, 0
ME[0].FromSysIC[2]: 0, 0, 0, 0, 0
ME[0].FromSysIC[3]: 0, 0, 0, 0, 0
ME[0].FromSysIC[4]: 0, 0, 0, 0, 0
ME[0].FromSysIC[5]: 0, 0, 0, 0, 0

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToNQM[0]: 121447, 0.262398, 0.0157151, 1.00009, 0, -nan, 0.0157151, 1.00009
ME[0].ToNQM[1]: 1146, 0.00188429, 0.000109576, 1, 0, -nan, 0.000109576, 1
ME[0].ToNQM[2]: 120185, 0.259996, 0.0155011, 1.00007, 0, -nan, 0.0155011, 1.00007
ME[0].ToNQM[3]: 409, 0.000385467, 3.90485e-05, 1, 0, -nan, 3.90485e-05, 1
ME[0].ToNQM[4]: 160, 0.000313794, 1.52746e-05, 1, 0, -nan, 1.52746e-05, 1
ME[0].ToNQM[5]: 160, 0.000313794, 1.52746e-05, 1, 0, -nan, 1.52746e-05, 1
ME[0].ToNQM[6]: 159, 0.000312363, 1.51791e-05, 1, 0, -nan, 1.51791e-05, 1
ME[0].ToNQM[7]: 161, 0.000316657, 1.53701e-05, 1, 0, -nan, 1.53701e-05, 1

Module: #_out_xacts, out_bw, avg_total_reqs, avg_total_reqs_exZero, avg_rio_reqs, avg_rio_reqs_exZero, avg_nqm_reqs, avg_nqm_reqs_exZero
ME[0].ToSysIC[0]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[1]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[2]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[3]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[4]: 0, 0, 0, -nan, 0, -nan, 0, -nan
ME[0].ToSysIC[5]: 0, 0, 0, -nan, 0, -nan, 0, -nan


************************************************
Simulator wall clock time (seconds): 104
