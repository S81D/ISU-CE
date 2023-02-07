# ISU-CE
### Cold Electronics Testing for the DUNE experiment at Iowa State University. Focused on functional testing, analysis, and the mechanical integrity of the LArASICs in LN2 and in room temperature.

_____

The Functional Analysis Folder contains both the standard femb software parameters (RMS, Mean, Gain, and ENC) as well as expanded parameters like Linearity and Pulse Characteristics. The code found in these folders were developed to analyze root files created directly by the femb testing software developed for the P3 LArASICs for ProtoDUNE (found here, femb_python: https://github.com/DUNE/femb_python). An example of the edited files for individual ASICs are found in the folders. These scripts are not largely applicable to other testing software, and is only designed for the femb_python QC testing software provided by BNL.
_____

The SAM Analysis folder contains all code infrastructure for the correlation analysis. The correlation analysis quantifies and identifies anti-correlation regions observed using SAM. The acoustic data files are of .sdt filetype, and are recorded at the CNDE at ISU. This directory only requires minor changes and .sdt file inputs for different acoustic samples.
_____

The codes and scripts used for extracting the .ROOT files created using the femb software for QC testing are provided under the Functional Performance Analysis folder, as well as a description on how to run the scripts.
_____
