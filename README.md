# 项目预览

## linux下运行

```bash
bash start.sh
```

## windows下运行

直接启动运行程序即可

## 默认ip和端口

- Ip :0.0.0.0
- Port: 8081

## 获得路由支持

**打开http://127.0.0.1:8081/** ,你会注意到浏览器中的欢迎信息

此时,访问info路由，即

**打开http://127.0.0.1:8081/info** ,你可以看到当前的用户IP信息和时间

*如果要获取帮助文档* ,请你

**打开http://127.0.0.1:8081/help** ,里面有详细的帮助介绍

帮助文档是在路由建立的时候就注册信息的，结构体定义如下

```cpp
struct HelpDoc {
    std::string url;
    std::vector<std::string> paramList;
    std::string description;
    std::vector<std::string> httpMethods; // 支持的 HTTP 方法
    std::string requestExample;           // 请求示例
    std::string responseExample;          // 响应示例
    std::map<int, std::string> errorCodes;// 错误码和描述
    std::string permissions;              // 权限要求
    std::string version;                  // 版本信息
    std::string notes;                    // 备注
};
```

![alt text](snapshot/{7AAE425C-F03C-4A4B-9AF0-694E0C760633}.png)

## 测试
*我项目的测试用的是pytest，里面是测试路由的*

* py请求发送测试
    * 你可以用Python测试，我写了一个websocketreq.py
    
* js请求发送测试
    * 启动服务器之后，你可以打开client目录下的example.html,并且进行测试

## 要求

```
图像的获取（端到端）：
（1）连接红外设备后拍摄照片；   √

（2）拍摄视频：按钮同时连接拍摄视频开关以及袖带充气加压电源 ；  √(这个电源不知道什么情况)

（3）拍摄内容包括红外热图像、对应可见光图像、对应csv文件。（三者可一次性获取）   (还不清楚什么可见光之类的)

（4）相机校准、温标、最高温和最低温显示、配色切换。     (还没看)
```

## 构建和打包

### 本地构建

```bash
mkdir build
cd build
cmake ..
make
```

### 使用CPack打包

```bash
mkdir build
cd build
cmake ..
make
cpack
```

这将在build目录下生成安装包。在Windows上会生成.zip文件。

### GitHub Actions自动构建和发布

当推送带有`v`前缀的标签时（如`v1.0.0`），GitHub Actions将自动在Windows平台上构建项目并创建Release。