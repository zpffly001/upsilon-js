# UPSILON-JS[Υ υ：Upsilon]
Small and efficient embedded Internet of Things Javascript engine

底层JavaScript Engine：QuickJS

扩展的模块：MQTT、SQLite



未来要扩展的模块：更好用的多线程API、MySQL、Redis、加解密、KCP


目录结构：
        /deps：     该目录下是υ-js所依赖的三方库源码。如果自己在其他地方把依赖的三方库编译为.so的话，该文件夹可有可无
        /example:   该目录下是js调用各种组件(.so)扩展功能的示例。如mqtt通信
        /include:   该目录下是υ-js所依赖的三方库API头文件
        /lib:       该目录下是υ-js所依赖的三方库编译成的.so动态库，默认是Ubuntu版本的库
        /local:     该目录下是.js文件require导入.so模块的时候动态库所链接的库(需要把改目录设置为默认搜索路径)
        /src:       源代码目录
        /test:      测试目录
