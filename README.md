# ISU-CE
### Cold Electronics Testing for the DUNE experiment at Iowa State University. Focused on functional testing, analysis, and the mechanical integrity of the LArASICs in LN2 and in room temperature.

_____

The Functional Performance Analysis Folder contains both the standard femb software parameters (RMS, Mean, Gain, and ENC) as well as expanded parameters like Linearity and Pulse Characteristics. The code found in these folders were developed to analyze edited .list and .dat files created directly by the femb testing software. An example of the edited files for individual ASICs are found in the folders. Also, a description of the code regarding each functional parameter (noise, baseline, linearity, pulse characteristics) and how those functional parameters were extracted are provided as a word document.
_____

The SAM Analysis folder contains all code infrastructure for the correlation analysis. The correlation analysis quantifies and identifies anti-correlation regions observed using SAM. A full manual/documentation is provided detailing how the code works and the experimental procedures used for collecting acoustic data.
_____

The conclusion of functional testing and SAM analysis results are summarized in the documents found here: https://iastate.box.com/s/54cgno7zj62wg4i6efrmid69h1zy1gzt. Results on the anti-correlation regions observed during stress testing of the P3 DUNE LArASICs can be found attached as a PDF document in the link, as well as summarized in a powerpoint format.
_____

The codes and scripts used for extracting the .ROOT files created using the femb software for QC testing are provided under the Functional Performance Analysis folder, as well as a description on how to run the scripts.
_____
