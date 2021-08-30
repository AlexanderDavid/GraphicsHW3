#include <fmt/core.h>

#include "dummy.hh"

auto main() -> int
{
    fmt::print("{}\n", fib(10));
    return 0;
}
