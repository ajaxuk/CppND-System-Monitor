#include "format.h"

#include <string>

using std::string;

#define SECS_IN_HOUR 3600
#define SECS_IN_MINUTE 60

// DONE (Not Tested): Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function

string Format::ElapsedTime(long seconds) {
  string HH = std::to_string(seconds / SECS_IN_HOUR);
  string MM = std::to_string((seconds % SECS_IN_HOUR) / SECS_IN_MINUTE);
  string SS = std::to_string(seconds % SECS_IN_MINUTE);

  // if HH / MM / SS are smaller than 2 digits then add a zero before
  if (HH.size() < 2) HH.insert(0, 1, '0');
  if (MM.size() < 2) MM.insert(0, 1, '0');
  if (SS.size() < 2) SS.insert(0, 1, '0');

  return HH + ":" + MM + ":" + SS;
}