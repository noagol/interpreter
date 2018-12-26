//
// Created by EB on 26/12/2018.
//

#include "EntercCommand.h"

EntercCommand::EntercCommand(Parser *p) : BaseCommand(p) {}

void EntercCommand::doCommand() {
    // Wait for user input
    cout << "After engine is on please press ENTER" << endl;
    char dummy;
    scanf("%c", &dummy);
}
