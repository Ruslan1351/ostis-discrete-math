#pragma once
#include <sc-memory/sc_keynodes.hpp>

namespace dm
{
class ExampleKeynodes : public ScKeynodes
{
public:
  static inline ScKeynode const action_example{"action_example", ScType::ConstNodeClass};
};
}  // namespace dm
