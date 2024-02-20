#ifndef BOARD_MOVE_COMMAND_H
#define BOARD_MOVE_COMMAND_H

#include "boarddefine.h"
#include "iundoredocommand.h"

BOARD_NAMESPACE_BEGIN
struct MoveParam : IUndoRedoParam {
    QPointF oldPos;
    QPointF newPos;
};

class MoveCommand : public IUndoRedoCommand {
public:
    using IUndoRedoCommand::IUndoRedoCommand;

    void exec() override;
    void undo() override;
    void redo() override;
};
BOARD_NAMESPACE_END
#endif // BOARD_MOVE_COMMAND_H
