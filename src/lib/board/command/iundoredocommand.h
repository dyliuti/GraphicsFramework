#ifndef BOARD_IUNDOREDOCOMMAND_H
#define BOARD_IUNDOREDOCOMMAND_H
#include "boarddefine.h"
#include <QString>
#include <QVector>
#include <memory>

BOARD_NAMESPACE_BEGIN
struct CommandInfo {
    QString commandName;
};

struct IUndoRedoParam {
    typedef std::shared_ptr<IUndoRedoParam> ptr;
    bool valid = true;
    CommandInfo commandInfo;
    QGraphicsItem* item {};
    QGraphicsScene* scene {};
};

// 不涉及文件的撤销恢复命令的基类
class IUndoRedoCommand {
public:
    IUndoRedoCommand(IUndoRedoParam::ptr param);
    virtual void exec() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual void clear() {};
    virtual bool isValid() const;
    IUndoRedoParam::ptr getParam();

    template <class T>
    std::shared_ptr<T> getTypicalParam()
    {
        return std::static_pointer_cast<T>(m_param);
    }

    void setCommandInfo(const CommandInfo& info);
    const CommandInfo& getCommandInfo() const;

protected:
    IUndoRedoParam::ptr m_param;
};

class GroupCommand : public IUndoRedoCommand {
public:
    using IUndoRedoCommand::IUndoRedoCommand;
    void exec() override;
    void undo() override;
    void redo() override;
    void appendCommand(std::shared_ptr<IUndoRedoCommand> command);
    void insertCommand(int index, std::shared_ptr<IUndoRedoCommand> command);
    void eraseCommand(int index);
    void clearCommands();
    int size();

protected:
    QVector<std::shared_ptr<IUndoRedoCommand>> m_commandVec;
};
BOARD_NAMESPACE_END
#endif // BOARD_IUNDOREDOCOMMAND_H
