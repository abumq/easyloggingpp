
#include "easylogging++.h" // Include header


void writeLegacyLogs (void) {
  INFO("Legacy info");
  ERROR("Legacy error");
  WARNING("Legacy warning" << " with concat");
  DEBUG("Legacy debug");
}
