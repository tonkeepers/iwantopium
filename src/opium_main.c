#include "core/opium_core.h"
#include "bridge/opium_selector.h"
#include "kernels/module/opium_module.h"

int main() {
   opium_log_t *log = opium_log_init(NULL, NULL, NULL);

   opium_selector_start();
   opium_log_err(log, "Hello!\n");

   opium_allocator_t allocator;
   opium_allocator_init(&allocator, log);

   return 1;
}
