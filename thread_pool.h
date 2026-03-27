#include <iostream>
#include <unistd.h>
#include "tle_parser.h"
#include "propagator.h"
#include "http_client.h"
#include <string>
#include <thread>
#include <queue>
void worker_function(std::queue<Satellite>& q, std::mutex& mtx,std::mutex& cout_mtx);

void run_thread_pool(std::string url,int thread_count);

