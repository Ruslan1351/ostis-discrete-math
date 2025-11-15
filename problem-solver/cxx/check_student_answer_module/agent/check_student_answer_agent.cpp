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
  ScAddr const & expectedAnswerAddr = action.GetArgument(CheckStudentAnswerKeynodes::nrel_expected_answer);
  if (!m_context.IsElement(studentAnswerAddr) or !m_context.IsElement(expectedAnswerAddr)) {
    m_logger.Warning("Action does not have one of arguments(or all).");
    return action.FinishWithError();
  }
  
  //вызов агента сравнения структур, получение узла structWithMissingElementsAddr
  
  ScAddr const & structWithMissingElementsAddr = m_context.GenerateNode(ScType::ConstNodeStructure);
  ScTemplate templ;
  templ.Triple(
    structWithMissingElementsAddr,
    ScType::VarPermPosArc,
    ScType::Unknown
  );
  ScTemplateSearchResult templResult;
  m_context.SearchByTemplate(templ, templResult);
  if (templResult.Size() == 0) {
    ScAddr const & linkAddr = m_context.GenerateNode(ScType::ConstNodeLink);
    std::string linkContent = "Student gave right answer";
    m_context.SetLinkContent(linkAddr, linkContent);
    action.FormResult(linkAddr);
    return action.FinishSuccessfully();
  }
  else {
    ScAddr const & conceptStructureWithElementsNotInAnswer = m_context.ResolveElementSystemIdentifier("concept_structure_with_elements_not_in_answer", ScType::ConstNodeClass);
    ScAddr const & arc = m_context.GenerateConnector(ScType::ConstPermPosArc, conceptStructureWithElementsNotInAnswer, structWithMissingElementsAddr);
    action.FormResult(conceptStructureWithElementsNotInAnswer, arc, structWithMissingElementsAddr);
    return action.FinishSuccessfully();
  }
  
}
}  // namespace dm  
