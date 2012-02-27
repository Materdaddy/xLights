rem ******************************************************
rem *
rem * xLights makefile generator
rem *
rem * This file uses cbp2make to create makefiles
rem * for each xLights module.
rem *
rem * cbp2make is available on SourceForge
rem *
rem ******************************************************

cd xMenu
cbp2make -in MainMenu.cbp -targets ReleaseLinux -unix
cd ..
cd xScheduler
cbp2make -in xSchedule.cbp -targets ReleaseLinux -unix
cd ..
cd xConverter
cbp2make -in xConverter.cbp -targets ReleaseLinux -unix
cd ..
