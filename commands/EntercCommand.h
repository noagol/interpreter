//
// Created by EB on 26/12/2018.
//

#ifndef PROJECT_ADVANCED_ENTERCCOMMAND_H
#define PROJECT_ADVANCED_ENTERCCOMMAND_H


#include "BaseCommand.h"

class EntercCommand : public BaseCommand {
public:
    EntercCommand(Parser *p);

    void doCommand() override;

};


#endif //PROJECT_ADVANCED_ENTERCCOMMAND_H
