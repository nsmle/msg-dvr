#!/bin/bash    

args1="$1"
args2="$2"
buildType="client"
platform='unknown'
executableExtension=''

if [[ "$args2" == "run" ]]; then
    clear;
fi

if [[ "$args1" == "server" ]]; then
    buildType="server"
fi

# Check Platform
case "$OSTYPE" in 
  linux*)   
        platform="LINUX"
        executableExtension=".so"
    ;;
  msys*)    
        platform="WINDOWS"
        executableExtension=".exe"
    ;;
  cygwin*)  
        platform="WINDOWS"
        executableExtension=".exe"
    ;;
  *)        
        platform="$OSTYPE"
        executableExtension=""
    ;;
esac

buildExecutable="${buildType}${executableExtension}"


if [[ "$args2" == "init" || ! -d "./build/$buildType/CMakeFiles" ]]; then
    cd "build/$buildType" && cmake ../../ && cd ../../
else
    if [[ "$args1" ==  "server" ]]; then
        echo -e "\n\033[0;36m=========================================================="
        echo -e "= \033[0;36m-------------------- \033[5;34mBUILD SERVER\033[0;36m -------------------- =\033[0m"
        echo -e "\033[0;36m==========================================================\033[0m"
    elif [[ "$args1" ==  "client" ]]; then
        echo -e "\n\033[0;34m=========================================================="
        echo -e "= \033[0;34m-------------------- \033[5;36mBUILD CLIENT\033[0;34m -------------------- =\033[0m"
        echo -e "\033[0;34m==========================================================\033[0m"
    fi
fi

make -C "build/$buildType" -s

if [[ "$args2" == "run" ]]; then
    echo -e "\n\033[6;33m========================= \033[5;31mOUTPUT\033[5;33m =========================\033[0m"    
    exec "./build/bin/$buildExecutable"
fi
