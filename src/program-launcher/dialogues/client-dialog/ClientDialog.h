#ifndef MARKETPLACE_ERP_TUI_CLIENTDIALOG_H
#define MARKETPLACE_ERP_TUI_CLIENTDIALOG_H


class ClientDialog {
public:
    static void openManagementDialog();
    static void addNewClient();
    static void listAllClients();
private:
    static void printSectionVariants();
    static bool getChoiceAndExecuteActionAndReturnQuitResult();
};


#endif
