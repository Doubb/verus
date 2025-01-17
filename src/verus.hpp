/*
  MIT License

  Copyright (c) 2015 Yasir Zaki, Thomas Pötsch, Jay Chen, Lakshmi Subramanian

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef VERUS_H_
#define VERUS_H_

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/time.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <atomic>
#include <fstream>
#include <queue>
#include <map>
#include <atomic>

// ALGLIB library
#include "../lib/alglib/src/ap.h"
#include "../lib/alglib/src/interpolation.h"

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/assign/std/vector.hpp>

// VERUS PARAMETERS
#define  MTU 1450
#define  VERUS_M_DECREASE 0.7
#define  CURVE_TIMER 1e6  // timer in microseconds, how often do we update the curve
#define  EPOCH 1e1 // JJW: Verus epoce for 100ms
//#define  EPOCH 5e3 // Verus epoch in microseconds
#define  DELTA1 1.0 // delta decrease
#define  DELTA2 2.0 // delta increase
#define  VERUS_R 6.0 // verus ratio of Dmax/Dmin
#define	 SS_EXIT_THRESHOLD 500.0
#define  SS_INIT_TIMEOUT 1000.0
#define  MAX_TIMEOUT 1000.0
#define  MIN_TIMEOUT 150.0
#define  MISSING_PKT_EXPIRY 150.0
#define  MAX_W_DELAY_CURVE 40000

using namespace alglib;

typedef struct __attribute__((packed, aligned(2))) m {
  int ss_id;
  unsigned long long seq;
  long long w;
  long long seconds;
  long long millis;
} udp_packet_t;

typedef struct __attribute__((packed, aligned(2))) n {
  int ss_id;
  unsigned long long seq;
  long long w;
  long long seconds;
  long long millis;
} missing_packet_t;

typedef struct {
  long long w;
  struct timeval time;
} mapEntry;

void* delayProfile_thread (void *arg);
void restartSlowStart(void);
double ewma (double vals, double delay, double alpha);
udp_packet_t *udp_pdu_init(int seq, unsigned int PACKETSIZE, int w, int ssId);

#endif /* VERUS_H_ */
