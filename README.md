# game-engine-from-scratch

## Chapter 7

> 内容：使用Windows系统API创建一个窗口。

####问题1：编译器选择

使用Microsoft Visual Studio 2015中的cl.exe工具进行编译，需要将cl.exe添加到系统环境变量中。cl.exe位置：\$VS2015\$/VC/bin。

#### 问题2：如何编译

**step1**：首先运行```> vcvars32```命令，准备编译和链接的环境（set up the required environment for compiling and linking）。

**step2**：运行```> cl  user32.lib helloengine_win.c```。

## Chapter 10

> 内容：编译使用GPU绘图的程序

#### 编译命令

```>cl user32.lib ole32.lib d2d1.lib helloengine_d2d.cpp```





1.  在环境变量中Path 那一项中添加两个路径（记得加分号）：
    `E:\VS2017\VC\Tools\MSVC\14.10.25017\bin\HostX64\x64;`
    `E:\VS2017\Common7\IDE`
    第一行是编译器的目录，根据电脑选吧，但是至少HostX86\x86是所有平台都能用，64位系统就像例子中那么填
2.  在环境变量中新建一个LIB 变量，并添加三个路径（记得加分号）：
    `C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.10.25017\lib\x64;`
    `C:\Program Files (x86)\Windows Kits\10\Lib\10.0.14393.0\ucrt\x86;`
    `C:\Program Files (x86)\Windows Kits\8.1\Lib\winv6.3\um\x86;`
    第一个路径填的是lib路径，如果在path变量中填了HostX64\x64的话就用x64的lib
    第二个路径填的我也不知道，但是填就填最新版的话，目前没发现什么问题
3.  在环境变量中新建一个INCLUDE 变量，并添加两个路径（记得加分号）：
    `E:\VS2017\VC\Tools\MSVC\14.10.25017\include;`
    `C:\Program Files (x86)\Windows Kits\10\Include\10.0.14393.0\ucrt;`
    第二个路径和上面第二个路径对应
4.  在E:\VS2017\VC\Auxiliary\Build 这个路径中点击vcvarall.bat 这个批处理程序。之后打开命令行，输入cl，如果没有报错，则配置成功……

*安装的时候要选定SDK 10*
*实际路径根据自己的安装路径有所不同。*

>   参考：http://zuciwang.com/show/229362.html