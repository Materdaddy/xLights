#
# shell script to build xLights
#

rm -rf bin
cd xMenu
make -f MainMenu.cbp.mak all
cd ..
cd xScheduler
make -f xSchedule.cbp.mak all
cd ..
cd xConverter
make -f xConverter.cbp.mak all
cd ..

