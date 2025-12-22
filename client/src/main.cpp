#include "debug.hpp"
#include <net.h>

int main() {
    debug::debug("hello from the client");
    net::hello_client();
}
