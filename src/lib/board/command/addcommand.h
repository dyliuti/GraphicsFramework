#ifndef BOARD_ADD_COMMAND_H
#define BOARD_ADD_COMMAND_H

#include "boarddefine.h"
#include "iundoredocommand.h"

BOARD_NAMESPACE_BEGIN
class AddCommand : public IUndoRedoCommand {
public:
    using IUndoRedoCommand::IUndoRedoCommand;

    void exec() override;
    void undo() override;
    void redo() override;
};
BOARD_NAMESPACE_END
#endif // BOARD_ADD_COMMAND_H
