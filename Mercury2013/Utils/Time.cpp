#include "Time.h"
#include "Utility.h"

double getCurrentMillis() {
	/*struct timespec tt;
	 clock_gettime(CLOCK_REALTIME, &tt);
	 double diff = (tt.tv_sec*1000.0) + (double)(tt.tv_nsec /1000000.0);
	 return diff;*/
	return GetFPGATime() * 1.0e-3;
}
