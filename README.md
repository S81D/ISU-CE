# ISU-CE
Cold Electronics Testing for the DUNE experiment at Iowa State University. Specifically focused on functional testing and analysis of the P3 LArASICs in LN2 and in room temperature.

_____
### Gain, Pedestal RMS and Mean
From functional tests ran using the femb python setup, we can evaluate output parameters from the tests. Three primary parameters of the ASICs that have been shown to be a good indicator of ASIC performance include the pedestal Mean and RMS, and the Gain. For the functional test, pulses are sent, shaped, and digitized by the on-board electronics. The voltage rises in a stair-step fashion - as a result, the amplitude of the sampling pulses increases. The accumulation of the pulses into a .root file 'creates' a waveform of pulses. There are a total of 35 voltage increases, each corresponding to a 'Subrun'. Subrun[0] denotes no injected pulses, and thus indicates the baseline value for a given channel on a given ASIC. This baseline value is the Pedestal Mean. The spread in the pedestal for a given channel is the Pedestal RMS, and represents the noise of the electronics (board and ASIC). The Gain is calculated by analyzing the waveform (cummulation of pulses), extracting the inverse slope, and converting to proper units of (e-/adc). The Gain is used to determine if the ASIC 'passes' or 'fails'. The Gain is a rough representation of the linearity of the ASICs, as well. ENC is also outputted, but is just a product of RMS and the Gain. A helpful visualization of the passage/failures of the ASICs as a function of cryocycle is given in the code (P-F Channel Response - RT Cryocycle.ipynb). This code plots the channel responses of the ASICs in a bar-plot-style format, with a y-value of 2 denoting at least 1 failed channel, and a 1 denoting all channels 'passed'. This is a quick way to visualize the overall health of the ASICs. A LN2 functional test version is given as well, under the guise of CT.

.list files are created from functional tests, that have the form:

> |RMS    |Mean   |Ch #|P/F|Gain |ENC  |
>
> |92.1571|2269.12|0   |0  |52.13|4804.|
> 
> 64.1465	|2334.48|1	 |0	 |53.28|3417.|

For a given functional test, there are 4 ASICs on the board, so this .list data comes in a 64 row, 64 channel format. Each ASIC has 16 channels (the first is denoted channel 0). The data can be sliced into individual ASIC .dat files, then read, loaded, and analyzed into the (Mean, RMS, Gain RT Cryocycle - Single ASIC plots.ipynb) jupyter notebook. This code analyzes each ASIC's Pedestal RMS and Mean, and Gain data by plotting each parameter as a 3-subplot figure. Very useful in analyzing the difference in the ASICs as a function of cryocycle. See code for details. The other jupyter notebook for LN2 functional tests (CT functional tests) is included with the same tag, but with CT. It is structured and formatted almost identically, with a few minor differences (like there is not CT[0] baseline tests). 
>
In addition to individual ASIC information, we can analyze the set of N chips as a whole, to see if their Pedestal Mean, RMS, and Gain distributions change as a functional of cryocycles. The code (RT RMS, Mean, Gain Histograms.ipynb) plots the histograms, as well as performs a Gaussian-style statistical analysis (CT included).
>
*** Upload scripts and .C files for reading and analyzing the .root files ***
___

