#include "example_agent.hpp"

#include "keynodes/example_keynodes.hpp"

namespace dm
{

ScAddr ExampleAgent::GetActionClass() const
{
  return ExampleKeynodes::action_example;
}

ScResult ExampleAgent::DoProgram(ScAction & action)
{
  return action.FinishSuccessfully();
}

}  // namespace dm
