# fuck_cpp
这是该死的cpp面向对象程序设计的作业

## 依赖
- g++
- ubuntu 24.04

## 编译
比较懒 直接用g++编译
```
g++ src/test.cpp -o ./build/test
```

## run
```
./build/test
```

### window下cmd编码方式的更改
查看当前编码方式
```
chcp
```
使用UTF-8的编码方式
```
chcp 65001 
```
65001为UTF-8
936为中国-简体中文（GB2312）


## plane_geometry
这是关于平面几何的cpp程序，包括了点、线、园、矩形、三角形的类和每种图形的移动、缩放、旋转、镜像。
在namespace plane_geometry中，主程序包含了测试代码。

## plane_geometry_plus
这是平面几何的升级版，是多态版的实现

## src
### secant
这是最优化一维搜素的割线法
### newton_raphson
这是最优化一维搜素的牛顿法
