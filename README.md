# Build Instructions

## 平台要求

各个平台所对应的构建要求如下：

macOS
Linux
Windows

## 前置知识

此外，你还需要安装depot_tools，这是一个用于获取Chromium，及其相关依赖工具。

另外，如果使用Windows系统, 你需要设置环境变量DEPOT_TOOLS_WIN_TOOLCHAIN=0。 依次打开 Control Panel → System and Security → System → Advanced system settings ，然后添加系统变量 DEPOT_TOOLS_WIN_TOOLCHAIN ，并设置默认值为 0. 这将促使depot_tools 使用本地已安装的Visual Studio(默认状态下，depot_tools将会下载一个只有谷歌内部员工有权限使用的内部版本)。

## 获取代码

```sh
$ mkdir rtvc && cd rtvc
$ gclient config --name "src/yealink" --unmanaged http://gitcode.yealink.com/server/client/web_app/rtvc.git
$ gclient sync --with_branch_heads --with_tags
# This will take a while, go get a coffee.
```

## 更新代码

```sh
$ cd src/yealink
$ git pull
$ gclient sync -f
```

## 构建

```sh
$ cd src
$ export CHROMIUM_BUILDTOOLS_PATH=`pwd`/buildtools
```

或者

```sh
$ cd src
$ set CHROMIUM_BUILDTOOLS_PATH=%cd%\buildtools
```
