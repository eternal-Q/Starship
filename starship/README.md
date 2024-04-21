





### 2.3 日志模块开发
日志模块：
```
1、日志级别
2、打印到文件，支持日期命名，以及日志的滚动
3、格式化风格
4、线程安全
```

LogLevel:
```
Debug
Info
Error
```

LogEvent:
```
文件名
行号
msgNo
进程号
线程号（Thread id）
时间（精确到ms）
自定义消息
```

日志格式
```
[level][%y-%m-%d %H:%M:%S.%ms]\t[pid:thread_id]\t[file_name:line][%msg]
```

logger 日志器
```
1、提供打印日志的方法
2、设置日志输出的路径（文件or控制台）
```