#!/bin/bash    

parent_dir=$(basename $PWD)
args1="$1"

if [[ "$args1" != "" ]]; then
    if [[ "$args1" == "server" ]]; then
        
        if [[ -d "./build/server/CMakeFiles" ]]; then
            echo -e "\n\033[0;36m=========================================================="
            echo -e "= \033[0;36m--------------- \033[5;34mCLEANUP SERVER SUCCESS\033[0;36m --------------- =\033[0m"
            echo -e "\033[0;36m==========================================================\033[0m"
        
            echo -e "\n\033[1;38mFile removed :\n\033[0m$(echo "$(find build/server -mindepth 1 -not -name '.gitkeep')" | sed -e 's/^/\\033[5;38m- \\033[0m\\033[1;31m/' -e 's/[^-]*$/\\033[3;91;3m\\033[3;3m\0\\033[0m/')"
            find ./build/server/ -mindepth 1 -not -name '.gitkeep' -delete;
        else 
            echo -e "\n\033[0;36m============== \033[5;34mDIRECTORY build/server CLEAN\033[0;36m ==============\033[0;37m\n\nNo Removable files available\033[0m\n"
        fi
    elif [[ "$args1" == "client" ]]; then
        
        if [[ -d "./build/client/CMakeFiles" ]]; then
            echo -e "\n\033[0;34m=========================================================="
            echo -e "= \033[0;34m--------------- \033[5;36mCLEANUP CLIENT SUCCESS\033[0;34m --------------- =\033[0m"
            echo -e "\033[0;34m==========================================================\033[0m"
        
            echo -e "\n\033[1;38mFile removed :\n\033[0m$(echo "$(find build/client -mindepth 1 -not -name '.gitkeep')" | sed -e 's/^/\\033[5;38m- \\033[0m\\033[1;31m/' -e 's/[^-]*$/\\033[3;91;3m\\033[3;3m\0\\033[0m/')"
            find ./build/client/ -mindepth 1 -not -name '.gitkeep' -delete;
        else 
            echo -e "\n\033[0;34m============== \033[5;36mDIRECTORY build/client CLEAN\033[0;34m ==============\033[0;37m\n\nNo Removable files available\033[0m\n"
        fi

    fi

    exit;
fi




if [[ $(find build -mindepth 1 -not -name '.gitkeep' | grep -E 'bin|lib|dist|client/|server//') ]]; then
    echo -e "\n\033[0;32m=========================================================="
    echo -e "= \033[0;32m----------------- \033[5;36mALL CLEANUP SUCCESS\033[0;32m ---------------- =\033[0m"
    echo -e "\033[0;32m==========================================================\033[0m"
    echo -e "\n\033[1;38mFile removed :\n\033[0m$(echo "$(find build -mindepth 1 -not -name '.gitkeep' | grep 'bin\|lib\|dist\|client\/\|server\/\/')" | sed -e 's/^/\\033[5;38m- \\033[0m\\033[1;31m/' -e 's/\(bin\|lib\|dist\|client\|server\)/\\033[0;31m\\033[1;31m\0\\033[1;31m/g' -e 's/[^-]*$/\\033[3;91;3m\\033[3;3m\0\\033[0m/')"
    
    # clear executable file
    rm -rf ./build/bin && rm -rf ./build/lib && rm -rf ./build/dist 

    # clear server build
    find ./build/server/ -mindepth 1 -not -name '.gitkeep' -delete;

    # clear client build
    find ./build/client/ -mindepth 1 -not -name '.gitkeep' -delete;
else
    echo -e "\n\033[0;32m================== \033[5;36mALL DIRECTORY CLEAN\033[0;32m ===================\033[0;37m\n\nNo Removable files available\033[0m\n"
fi
