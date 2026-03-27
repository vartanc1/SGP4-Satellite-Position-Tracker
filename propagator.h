#ifndef PROPAGATOR_H
#define PROPAGATOR_H

#include "satellite.h"
#include "sgp4/sgp4unit.h"
#include "sgp4/sgp4ext.h"
#include "sgp4/sgp4io.h"
#include <vector>
/*
    Wraps Vallado SGP4 propagation.
*/

void propagate(Satellite& sat,std::mutex& cout_mtx);

#endif