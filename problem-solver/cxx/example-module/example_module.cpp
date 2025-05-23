#include "example_module.hpp"

#include "agent/example_agent.hpp"

namespace dm
{
SC_MODULE_REGISTER(ExampleModule)->Agent<ExampleAgent>();
}  // namespace dm
