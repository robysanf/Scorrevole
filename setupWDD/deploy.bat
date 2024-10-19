echo @on
cd ./
set arg1=%1
if "%arg1%" == "p" call cordova platform add android  
set arg2=%2
if "%arg2%" == "b" call cordova build android
echo "check device"
call adb kill-server
call adb devices -l
echo "install"
call adb install -r  E:\WDD\Repository\Scorrevole\setupWDD\platforms\android\app\build\outputs\apk\debug\app-debug.apk

