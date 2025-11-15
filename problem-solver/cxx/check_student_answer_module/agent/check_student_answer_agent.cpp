#include "check_student_answer_agent.hpp"

#include "keynodes/check_student_answer_keynodes.hpp"

namespace dm
{

ScAddr CheckStudentAnswerAgent::GetActionClass() const
{
  return CheckStudentAnswerKeynodes::action_check_student_answer;
}

ScResult CheckStudentAnswerAgent::DoProgram(ScAction & action)
{
  ScAddr const & studentAnswerAddr = action.GetArgument(ScKeynodes::rrel_1);
  if (!m_context.IsElement(studentAnswerAddr)) {
    m_logger.Warning("Action does not have one of arguments(or all).");
    return action.FinishWithError();
  }
  ScTemplate templ1;
  templ1.Quintuple(
    action,
    ScType::VarCommonArc,
    ScType::VarNodeStructure >> "_structure",
    ScType::VarPermPosArc,
    CheckStudentAnswerKeynodes::nrel_expected_answer
  );
  ScTemplateSearchResult templ1Result;
  m_context.SearchByTemplate(templ1, templ1Result);
  if (templ1Result.Size() != 1) {
    m_logger.Warning("Action does not have(or more than one) connection with expected answer.");
    return action.FinishWithError();
  }
  ScAddr const & expectedAnswerAddr = templ1Result[0]["_structure"];
  
  ScAction someAction = m_context.GenerateAction(CheckStudentAnswerKeynodes::action_compare_structures);
  ScAddr const & rrel1Addr = m_context.SearchElementBySystemIdentifier(ScKeynodes::rrel_1);
  ScAddr const & rrel2Addr = m_context.SearchElementBySystemIdentifier(ScKeynodes::rrel_2);
  ScAddr const & arc1 = m_context.GenerateConnector(ScType::ConstPermPosArc, someAction, studentAnswerAddr);
  m_context.GenerateConnector(ScType::ConstPermPosArc, rrel1Addr, arc1);
  ScAddr const & arc2 = m_context.GenerateConnector(ScType::ConstPermPosArc, someAction, expectedAnswerAddr);
  m_context.GenerateConnector(ScType::ConstPermPosArc, rrel2Addr, arc2);
  someAction.InitiateAndWait(100);
  if (someAction.IsFinishedUnsuccessfully()) {
    m_logger.Warning("Compare structures action finished unseccessfully.");
    return action.FinishWithError();
  }
  ScStructure const & someActionResult = someAction.GetResult();
  ScTemplate templ2;
  templ2.Triple(
    someActionResult,
    ScType::VarPermPosArc,
    CheckStudentAnswerKeynodes::concept_forward_difference >> "_class"
  );
  ScTemplateSearchResult templ2Result;
  m_context.SearchByTemplate(templ2, templ2Result);
  ScAddr const & conceptForwardDifferenceAddr = templ2Result[0]["_class"];
  
  ScTemplate templ3;
  templ3.Triple(
    conceptForwardDifferenceAddr,
    ScType::VarPermPosArc,
    ScType::VarNodeStructure >> "_structure"
  );
  ScTemplateSearchResult templ3Result;
  m_context.SearchByTemplate(templ3, templ3Result);
  ScAddr const & structWithMissingElementsAddr = templ3Result[0]["_structure"];
  ScTemplate templ4;
  templ4.Triple(
    structWithMissingElementsAddr,
    ScType::VarPermPosArc,
    ScType::Unknown
  );
  ScTemplateSearchResult templ4Result;
  m_context.SearchByTemplate(templ4, templ4Result);
  if (templ4Result.Size() == 0) {
    ScAddr const & linkAddr = m_context.GenerateNode(ScType::ConstNodeLink);
    std::string linkContent = "Student gave right answer";
    m_context.SetLinkContent(linkAddr, linkContent);
    action.FormResult(linkAddr);
    return action.FinishSuccessfully();
  }
  else {
    ScAddr const & conceptStructureWithElementsNotInAnswer = m_context.SearchElementBySystemIdentifier(CheckStudentAnswerKeynodes::concept_structure_with_elements_not_in_answer);
    ScAddr const & arc = m_context.GenerateConnector(ScType::ConstPermPosArc, conceptStructureWithElementsNotInAnswer, structWithMissingElementsAddr);
    action.FormResult(conceptStructureWithElementsNotInAnswer, arc, structWithMissingElementsAddr);
    return action.FinishSuccessfully();
  }
}
}  // namespace dm  
