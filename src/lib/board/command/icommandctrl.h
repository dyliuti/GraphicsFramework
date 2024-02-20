#ifndef BOARD_ICOMMANDCTRL_H
#define BOARD_ICOMMANDCTRL_H

#include "boarddefine.h"
#include <QObject>
#include <memory>

BOARD_NAMESPACE_BEGIN
class IUndoRedoCommand;
struct CommandInfo;
class ICommandCtrl : public QObject {
    Q_OBJECT
public:
    using QObject::QObject;

    virtual void execUndoRedoCommand(std::shared_ptr<IUndoRedoCommand> pCommand) = 0;
    virtual void undo(int step, bool needCheckUndoDeleteCommand = 0) = 0;
    virtual void redo(int step) = 0;
    virtual void deleteCommand(int index) = 0;

public:
signals:
    void sigAddCommand();
};
BOARD_NAMESPACE_END
#endif // BOARD_ICOMMANDCTRL_H
