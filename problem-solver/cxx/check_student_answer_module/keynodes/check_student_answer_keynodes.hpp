#pragma once
#include <sc-memory/sc_keynodes.hpp>

namespace dm
{
class CheckStudentAnswerKeynodes : public ScKeynodes
{
public:
  static inline ScKeynode const action_check_student_answer{"action_check_student_answer", ScType::ConstNodeClass};

  static inline ScKeynode const nrel_expected_answer{"nrel_cexpected_answer", ScType::ConstNodeNonRole};
};
}  // namespace dm
