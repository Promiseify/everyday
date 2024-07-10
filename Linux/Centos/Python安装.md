### 安装指定版本的python环境

version: Centos7

#### 更新 Python 需要的安装依赖

由于python编译和安装过程中需要使用到其他工具, 如果这些工具依赖版本过低可能会导致编译安装不成功；或者安装成功后实际运行中缺少包会包冲突的问题，所以需要先更新相关依赖。

```shell
sudo yum -y install epel-release
sudo yum -y update

sudo yum -y groupinstall "Development Tools"
sudo yum -y install openssl-devel bzip2-devel libffi-devel xz-devel
```

验证是否安装成功

```shell
# [root@iZ2ze3fk84qbagxsn29a31Z ~]# gcc --version
# gcc (GCC) 4.8.5 20150623 (Red Hat 4.8.5-44)
# Copyright (C) 2015 Free Software Foundation, Inc.
# This is free software; see the source for copying  conditions.  There is NO
# warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

#### 下载目标版本的Python压缩包

在Linux系统上, python的安装过程为: 下载压缩包, 解压, 编译, 安装。所以我们需要先从官网下载目标版本的压缩包。如果存在网络过慢, 则可以从国内[镜像网站](https://so.csdn.net/so/search?q=镜像网站&spm=1001.2101.3001.7020)下载。

```shell
sudo yum -y install wget
wget https://www.python.org/ftp/python/3.10.5/Python-3.10.5.tgz
# 官网下载速度过慢的情况，可以使用国内阿里镜像下载
# 淘宝镜像 http://npm.taobao.org/mirrors/python/
wget https://registry.npmmirror.com/-/binary/python/3.10.5/Python-3.10.5.tgz

# 下载到指定位置

# 解压
tar xvf Python-3.10.5.tgz

# 切换到安装包解压目录
cd Python-3.10*/
```

