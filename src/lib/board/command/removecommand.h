#ifndef BOARD_REMOVE_COMMAND_H
#define BOARD_REMOVE_COMMAND_H

#include "iundoredocommand.h"

BOARD_NAMESPACE_BEGIN
class RemoveCommand : public IUndoRedoCommand {
public:
    using IUndoRedoCommand::IUndoRedoCommand;

    void exec() override;
    void undo() override;
    void redo() override;
};
BOARD_NAMESPACE_END
#endif // BOARD_REMOVE_COMMAND_H
