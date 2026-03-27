#ifndef SATELLITE_H
#define SATELLITE_H
#include <string>

struct Satellite {
    int sat_id; //id of satellite 


    std::string name; //EX: ISS(ZARYA);

    std::string line1;


    /*
        TLE Line 1

        Contains:
        - Satellite catalog number
        - Classification
        - Launch information
        - Epoch time (reference time of orbital elements)
        - Mean motion derivative
        - BSTAR drag term
        - Checksum

        The SGP4 algorithm reads this line to determine
        drag effects and epoch reference.
    */
    std::string line2;
    /*
        TLE Line 2

        Contains:
        - Inclination (degrees)
        - Right Ascension of Ascending Node (RAAN)
        - Eccentricity (implied decimal)
        - Argument of Perigee (degrees)
        - Mean Anomaly (degrees)
        - Mean Motion (revolutions per day)
        - Checksum

        These parameters define the satellite's orbital
        geometry around Earth.

        The SGP4 propagator uses this to compute the
        satellite's position at any given time.
    */

};
#endif