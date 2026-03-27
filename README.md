# SGP4 Satellite Position Tracker

A multithreaded C++ application that fetches live Two-Line Element (TLE) satellite data from CelesTrak and computes real-time orbital positions for 100+ active satellites using the Vallado SGP4 propagation library.

## What it does

Connects to CelesTrak every 10 minutes, downloads the latest satellite catalog, and calculates the current position of every satellite in Earth-centered inertial (ECI) coordinates using the SGP4 algorithm. All satellites are processed in parallel using a custom thread pool.

## How it works

1. HTTP client fetches live TLE data from CelesTrak using libcurl
2. TLE parser reads each satellite's orbital parameters into structured objects
3. A thread pool with 8 configurable workers pulls satellites from a shared queue
4. Each worker runs the SGP4 propagator to compute current position and velocity
5. Results are printed to stdout with satellite ID and ECI position vector in km
6. Program sleeps 10 minutes and repeats

## Tech Stack

- C++
- libcurl — HTTP client for live data fetching
- Vallado SGP4 library — orbital mechanics propagation
- POSIX threads — multithreading and mutex synchronization

## Build

g++ -O3 main.cpp propagator.cpp tle_parser.cpp http_client.cpp thread_pool.cpp -o tracker -lcurl

## Run

./tracker

## Output

NAME: ISS (ZARYA)
25544 -3456.12 5678.34 1234.56
NAME: STARLINK-1234
...

Position values are ECI coordinates in kilometers.

## Project Structure

main.cpp           — Entry point, runs thread pool every 10 minutes
http_client.cpp    — Fetches raw TLE data from CelesTrak via libcurl
tle_parser.cpp     — Parses TLE text into Satellite structs
propagator.cpp     — Wraps Vallado SGP4 to compute position from TLE
thread_pool.cpp    — Worker thread pool with mutex-protected queue
satellite.h        — Satellite struct definition

## Dependencies

- libcurl
- Vallado SGP4 library (sgp4unit, sgp4ext, sgp4io)
