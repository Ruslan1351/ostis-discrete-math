#pragma once

#include <sc-memory/sc_agent.hpp>

namespace dm
{
class ExampleAgent : public ScActionInitiatedAgent
{
public:
  ScAddr GetActionClass() const override;

  ScResult DoProgram(ScAction & action) override;
};
}  // namespace dm
