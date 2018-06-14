# Mediaplayer 
`Mediaplayer` is a Linux-based player written on C++ using [Qt5](http://doc.qt.io/qt-5/index.html).

![mediaplayer](https://github.com/Chukak/mediaplayer/blob/master/mediaplayer.png)


## How to compile the application

In Linux, you need Qt 5.7+ version, Make 4+ version, GCC 5+ version. Clone this repository. Run `build.sh` script:
```bash
chmod +x build.sh && ./build.sh
```
Or you can run `build.sh` with specials paths. For example:
```bash
chmod +x build.sh
./build.sh -qmake=/path/to/qmake -g++=/path/to/g++/version
```
To get more information:
```bash
./build.sh --help
```

After the assembly, just run the executable `mediaplayer` file.
```bash
./mediaplayer
```

## Tests
For testing check this [page](https://github.com/Chukak/mediaplayer/blob/master/tests/unit-tests/readme.md).

## Resources
* C++ 
* [Qt5](http://doc.qt.io/qt-5.9/index.html) - version 5.9.4

