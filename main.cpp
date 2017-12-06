#include "Command.h"

int main()
{
    Light *light = new Light("Simple light");
    Stereo *stereo = new Stereo("Cool stereo");

    LightOnCommand *loc = new LightOnCommand(light);
    LightOffCommand *lofc = new LightOffCommand(light);
    StereoOnCommand *soc = new StereoOnCommand(stereo);
    StereoOffCommand *sofc = new StereoOffCommand(stereo);

    RemoteControl* remoteControl = new RemoteControl();

    remoteControl->setCommand(0, loc, lofc);
    remoteControl->setCommand(1, soc, sofc);

    remoteControl->onButtonWasPushed(0);
    remoteControl->offButtonWasPushed(0);

    remoteControl->onButtonWasPushed(1);
    remoteControl->offButtonWasPushed(1);
    remoteControl->undoButtonWasPushed();

    cout << "==============================" << endl;

    Command* cmd[2] = {loc, soc};
    MacroCommand* macroCommand = new MacroCommand(cmd, 2);
    macroCommand->execute();
    macroCommand->undo();

    delete macroCommand;
    delete remoteControl;
    delete sofc;
    delete soc;
    delete lofc;
    delete loc;
    delete stereo;
    delete light;

    return 0;
}

