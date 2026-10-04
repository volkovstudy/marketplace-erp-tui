#pragma once

class ProgramLauncher {
 public:
  static void start();

 private:
  static bool getChoiceAndExecuteActionAndReturnQuitResult();
};
