# game-engine-from-scratch

## Chapter 7

> 内容：使用Windows系统API创建一个窗口。

####问题1：编译器选择

使用Microsoft Visual Studio 2015中的cl.exe工具进行编译，需要将cl.exe添加到系统环境变量中。cl.exe位置：\$VS2015\$/VC/bin。

#### 问题2：如何编译

**step1**：首先运行```> vcvars32```命令，准备编译和链接的环境（set up the required environment for compiling and linking）。

**step2**：运行```> cl -l user32.lib helloengine_win.c```。

