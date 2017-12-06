#ifndef COMMAND_H
#define COMMAND_H

#include "Light.h"
#include "Stereo.h"

// 命令接口
class Command
{
public:
    Command(){}
    virtual~Command(){}
    virtual void execute() = 0;
    virtual void undo() = 0;
};


// 空命令
class NoCommand : public Command 
{
public:
    NoCommand(){}
    ~NoCommand(){}
    void execute(){}
    void undo(){}
};

// 开灯命令
class LightOnCommand: public Command
{
public:
    LightOnCommand(Light *l): light(l)
    {
    }
    ~LightOnCommand(){}

    void execute()
    {
        light->on();
    }
    void undo()
    {
        light->off();
    }
private:
    Light *light;
};

// 关灯命令
class LightOffCommand: public Command
{
public:
    LightOffCommand(Light *l): light(l)
    {
    }
    ~LightOffCommand(){}

    void execute()
    {
        light->off();
    }
    void undo()
    {
        light->on();
    }
private:
    Light *light;
};

// 开音响命令
class StereoOnCommand: public Command
{
public:
    StereoOnCommand(Stereo *s): stereo(s)
    {
    }
    ~StereoOnCommand(){}

    void execute()
    {
        stereo->on();
    }
    void undo()
    {
        stereo->off();
    }
private:
    Stereo *stereo;
};

// 关音响命令
class StereoOffCommand: public Command
{
public:
    StereoOffCommand(Stereo *s): stereo(s)
    {
    }
    ~StereoOffCommand(){}

    void execute()
    {
        stereo->off();
    }
    void undo()
    {
        stereo->on();
    }
private:
    Stereo *stereo;
};


class RemoteControl 
{
private:
    Command* onCommands[7];
    Command* offCommands[7];
    Command* undoCommand;
    Command* noCommand;
public:
    RemoteControl()
    {
        noCommand = new NoCommand();
        for (int i=0; i<7; i++) {
            onCommands[i] = noCommand;
            offCommands[i] = noCommand;
        }
        undoCommand = noCommand;
    }
    ~RemoteControl()
        {
            delete noCommand;
        }
    void setCommand(int slot, Command* onCommand, Command* offCommand)
    {
        onCommands[slot] = onCommand;
        offCommands[slot] = offCommand;
    }
    void onButtonWasPushed(int slot)
    {
        onCommands[slot]->execute();
        undoCommand = onCommands[slot];
    }
    void offButtonWasPushed(int slot)
    {
        offCommands[slot]->execute();
        undoCommand = offCommands[slot];
    }
    void undoButtonWasPushed()
    {
        undoCommand->undo();
    }
};

class MacroCommand: public Command
{
private:
    Command** command;
    int cnt;
public:
    MacroCommand(Command** cmd, int c): command(cmd), cnt(c)
    {
    }
    ~MacroCommand(){}

    void execute()
    {
        for (int i=0; i<cnt; i++) {
            command[i]->execute();
        }
    }
    void undo()
    {
       for (int i=0; i<cnt; i++) {
            command[i]->undo();
        }
    }


};


#endif

