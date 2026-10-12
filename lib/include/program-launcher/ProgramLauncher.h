#pragma once

#include <istream>
#include <ostream>

class ProgramLauncher {
 public:
  explicit ProgramLauncher(std::ostream& out, std::istream& in);

  void start();

 private:
  void printProgramSections();
  bool getChoiceAndExecuteActionAndReturnQuitResult();

  std::ostream& out_;
  std::istream& in_;
};
