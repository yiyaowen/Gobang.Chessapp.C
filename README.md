# Gobang.Chessplayer.C

#### Build on macOS with gcc and CMake

```	
% cd Gobang.Chessplayer.C/Core
% mkdir build && cd build
% cmake -DCMAKE_INSTALL_PREFIX=YOUR_INSTALL_PREFIX ..
% make && make install
% cd ../..
% gcc -l core -L ./Core/build/lib -rpath ./Core/build/lib -o main ChessApp/*.c -D UNIX
```

