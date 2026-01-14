#include "core/opium_core.h"

int main() {
   opium_log_t *log = opium_log_init(NULL, NULL, NULL);

   opium_log_err(log, "Hello!\n");

   return 1;
}
