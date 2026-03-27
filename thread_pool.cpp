#include <iostream>
#include <unistd.h>
#include "tle_parser.h"
#include "propagator.h"
#include "http_client.h"
#include <string>
#include <thread>
#include <queue>
void worker_function(std::queue<Satellite>& q, std::mutex& mtx,std::mutex& cout_mtx);
void run_thread_pool(std::string url,int thread_count){
    std::vector<std::thread> threads;

    std::mutex cout_mtx;
    std::mutex mtx;

    //fetch TLE data
    std::cout << "Fetching data";
    std::string tle_data = fetch_url(url);
    //parse into satellites
    std::vector<Satellite> satellites = parse_tle_string(tle_data);

    std::queue<Satellite> q;
    //push satelittes into shared queue
    for(const Satellite& sat: satellites){
        q.push(sat);
    }
    //spawn N threads
    for(int i =0; i < thread_count; i++){
        threads.emplace_back(worker_function,std::ref(q),std::ref(mtx),std::ref(cout_mtx));
    }
    //join all threads when done
    for(auto& thread : threads){
        thread.join();
    }
    std::cout << "All threads joined";
    
}

void worker_function(std::queue<Satellite>& q, std::mutex& mtx,std::mutex& cout_mtx){

    while(!q.empty()){
        Satellite sat;
        {
         std::lock_guard<std::mutex> lock(mtx);//will automatically unlock once out of scope
        if(q.empty()){
            break;
        }
        sat = q.front(); //grab front element
        q.pop(); //remove from que           
        }//inner scope added so mutex unlocks before propogate is called
        propagate(sat,cout_mtx);
    }
};