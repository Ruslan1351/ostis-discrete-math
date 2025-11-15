#pragma once
#include <sc-memory/sc_keynodes.hpp>

namespace dm
{
class CompareStructuresKeynodes : public ScKeynodes
{
public:
  static inline ScKeynode const action_compare_structures{"action_compare_structures", ScType::ConstNodeClass};
};
}  // namespace dm
