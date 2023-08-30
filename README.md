# Gobang.Chessplayer.C

## 运行

推荐使用系统自带的 cmd.exe（位于 C:\WINDOWS\system32 目录下）启动，使用其它终端程序（例如可从微软商店获取的 Terminal 应用等）可能会存在不兼容的问题，从而导致文本图形渲染错误。

## 构建

需要 CMake 3.10 及以上版本、支持 C11 标准的编译器：

```
$ cd Gobang.Chessplayer.C
$ mkdir build && cd build
$ cmake ..
$ make
```

主程序 Main.exe 将生成在 Gobang.Chessplayer.C/build/Chessapp 下。
