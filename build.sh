#! /bin/bash

CC=""
CXX=""
MAKE=""
QMAKE=""
PROJECT=""

config_gcc() {
    echo "Checking gcc." 
    dpkg -s gcc &> /dev/null
    if [[ $? -ne 0 ]]; then
        echo "A 'gcc' package not found. Set 'gcc' path as the second parameter or install 'gcc'."
        exit 1
    else
        gcc_version="$(gcc -dumpversion)"
        regex='^[5-9]{1}\.[0-9]+\.[0-9]+$'
        if [[ $gcc_version =~ $regex ]]; then
            CC="gcc"
        else
            echo "You need 'gcc' 5 version and more."
            exit 1
        fi
        unset regex
        unset gcc_version
    fi
}

config_gpp() {
    echo "Checking gcc." 
    dpkg -s g++ &> /dev/null
    if [[ $? -ne 0 ]]; then
        echo "A 'g++' package not found. Set 'g++' path as the second parameter or install 'gcc'."
        exit 1
    else
        gxx_version="$(g++ -dumpversion)"
        regex='^[5-9]{1}\.[0-9]+\.[0-9]+$'
        if [[ $gxx_version =~ $regex ]]; then
            CXX="g++"
        else
            echo "You need 'g++' 5 version and more."
            exit 1
        fi
        unset regex
        unset gxx_version
    fi
}

config_make() {
    echo "Checking make."
    dpkg -s make &> /dev/null
    if [[ $? -ne 0 ]]; then
        echo "A 'make' package not found. Set make path as the third parameter or install 'make'."
        exit 1
    else
        make_version="$(make -v | grep "^GNU Make [4-9]\.[0-9]*")"
        if [[ $make_version ]]; then
            MAKE="make"
        else
            echo "You need 'make' 4 version and more."
            exit 1
        fi
        unset make_version
    fi
}

config_qmake() {
    echo "Checking qmake."
    qmake_version="$(qmake -v | grep "^QMake version [3-9]\.[0-9]*")"
    if [[ $qmake_version ]]; then
        QMAKE="qmake"
    else
        echo "QMake not found. Check your Qt version."
        exit 1
    fi
    unset qmake_version
}

build_project() {
    if ! [[ $QMAKE ]]; then
        config_qmake
    fi
    
    if ! [[ $MAKE ]]; then
        config_make
    fi
    
    if ! [[ $CC ]]; then
        config_gcc
    fi
    
    if ! [[ $CXX ]]; then
        config_gpp
    fi
    
    if [[ $QMAKE ]] && [[ $MAKE ]] && [[ $CC ]] && [[ $CXX ]]; then
        qmake_command="$QMAKE $PROJECT -spec linux-g++"
        eval $qmake_command
        if [[ $? -ne 0 ]]; then
            echo "QMake error."
            exit 2
        fi
        make_command="$MAKE CC=$CC CXX=$CXX"
        eval $make_command
        if [[ $? -ne 0 ]]; then
            echo "Make error."
            exit 2
        fi
        clean="$MAKE clean"
        eval $clean
        if [[ $? -ne 0 ]]; then
            echo "Not clean."
        fi
        unset clean
        unset make
        unset qmake_command
    else
        echo "Unknown error." 
        exit 128
    fi
}

usage() {
    echo "Usage: ./build.sh [options] file.pro
Options:
  --help            Display this information.
Build options:
  -qmake            QMake special path.
  -make             Make special path.
  -gcc              A special path to the C compiler.
  -g++              A special path to the C++ compiler."
}


if [[ $# -eq 1 ]]; then
    if [[ $1 == "--help" ]]; then
        usage
        exit 1
    fi
    
    if [[ $1 ]]; then
        if [[ -f $1 ]]; then
            PROJECT=$1
        else
            echo "The project not found."
            exit 1
        fi
    else 
        echo "No project for build."
        exit 1
    fi
    
    # The C compiler configuration.
    config_gcc
    # The C++ compiler configuration.
    config_gpp
    # Make configuration.
    config_make
    # QMake confugiration.
    config_qmake
    # Build a project.
    build_project
    
    
elif [[ $# -ge 1 ]]; then
    for arg in "$@"; do
        case $arg in
            -qmake=*)
                QMAKE="${arg#*=}"
                shift
                ;;
            -make=*)
                MAKE="${arg#*=}"
                shift
                ;;
            -gcc=*)
                CC="${arg#*=}"
                shift
                ;;
            -g++=*)
                CXX="${arg#*=}"
                shift
                ;;
            --help)
                usage
                exit 1
                ;;
            -*)
                echo "Unknown option."
                exit 128
                ;;
            *)
                ;;
        esac
    done
    
    if [[ -f $arg ]]; then
            PROJECT=$arg
    else
        echo "The project not found."
        exit 1
    fi
    # Build a project.
    build_project
else
    echo ""
fi





