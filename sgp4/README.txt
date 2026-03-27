README for DIRSIG5 Thirdparty SGP4 Propagator Code

This is the C++ code for Simplified General Perturbations-4 (SGP4) 
distributed by Vallado, et al. It is considered to be the standard
for predicting the location of satellites from two-line element (TLE)
datasets provided by NORAD on a regular basis.

Full documentation and source code are available here:
https://celestrak.com/publications/AIAA/2006-6753/

There is no license associated with the code and is available for any
purpose - personal or commercial.

CHANGES:
- We wrapped the definition of asinh() in sgp4ext with an ifdef since
  a modern C++ compiler already has an implementation and this one
  causes conflicts.
