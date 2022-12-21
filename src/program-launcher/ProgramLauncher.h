#ifndef MARKETPLACE_ERP_TUI_TESTS_PROGRAMLAUNCHER_H
#define MARKETPLACE_ERP_TUI_TESTS_PROGRAMLAUNCHER_H


class ProgramLauncher {
public:
    static void start();
private:
    static bool getChoiceAndExecuteActionAndReturnQuitResult();
};


#endif
