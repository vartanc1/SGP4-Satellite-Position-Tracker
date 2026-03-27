#include "propagator.h"
#include <ctime>
#include <cstring>
#include <iostream>
#include <thread>
/*
    Constructor

    Initializes SGP4 using TLE lines.
*/

void propagate(Satellite& sat,std::mutex& cout_mtx) {
    char line0[130];
    char line1[130];
    char line2[130];
    elsetrec satrec;
    strcpy(line0, sat.name.c_str());
    strcpy(line1, sat.line1.c_str());
    strcpy(line2, sat.line2.c_str());

    double startmfe, stopmfe, deltamin;

    twoline2rv(
        line1,
        line2,
        'c',
        'e',
        'i',
        wgs84,
        startmfe,       
        stopmfe,
        deltamin,
        satrec
    );


    
    time_t rawtime = time(nullptr);
    struct tm *utc = gmtime(&rawtime);

    double jd;

    // Use correct jday signature (ONLY jd)
    jday(
        utc->tm_year + 1900,
        utc->tm_mon + 1,
        utc->tm_mday,
        utc->tm_hour,
        utc->tm_min,
        (double)utc->tm_sec,
        jd
    );

    double tsince =(jd - satrec.jdsatepoch) * 1440.0;//time since epoch

    //std::cout << "tsince: " << tsince << std::endl;

    double r[3];
    double v[3];

    {
        std::lock_guard<std::mutex> lock(cout_mtx);
        std::cout<<"NAME:" << sat.name<<std::endl;
        if (sgp4(wgs84, satrec, tsince, r, v)) {
            std::cout<< sat.sat_id <<" "<<r[0] << " "<< r[1]<< " "<< r[2] << "\n";
        }
    }


}

