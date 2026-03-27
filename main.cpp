#include <iostream>
#include <unistd.h>
#include "tle_parser.h"
#include "propagator.h"
#include "http_client.h"
#include "thread_pool.h"
int main() {

    // std::string tle_data =
    //     "ISS (ZARYA)\n"
    //     "1 25544U 98067A   24066.51041667  .00016717  00000+0  10270-3 0  9993\n"
    //     "2 25544  51.6425  74.1287 0004325  47.1671  81.4872 15.50012345678901\n";

    std::string url = "https://celestrak.org/NORAD/elements/gp.php?GROUP=visual&FORMAT=tle";
    while(true){
        run_thread_pool(url,8);
        sleep(600);//update every 10 minutes
    }
    return 0;
}