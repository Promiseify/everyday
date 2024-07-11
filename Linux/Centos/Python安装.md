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

#### 编译python并安装

```shell
# 运行编译脚本
./configure --enable-optimizations

sudo make altinstall
```

#### 查看python版本, 检查是否安装成功

```shell
python3.10 --version
Python 3.10.5

pip3.10 --version
pip 22.0.4 from /usr/local/lib/python3.10/site-packages/pip (python 3.10)
```

#### 修改pip安装源为国内镜像源

 ```shell
vim /etc/pip.conf
vim ~/.pip/pip.conf # mkdir ~/.pip
vim ~/.config/pip/pip.conf # mkdir ~/.config
 ```

```shell
# pip.conf文件内容
[global] 
index-url = https://pypi.tuna.tsinghua.edu.cn/simple
[install]
trusted-host = https://pypi.tuna.tsinghua.edu.cn  # trusted-host 此参数是为了解决地址不受信任问题
```

#### 附: pycurl导包问题

运行[tornado](https://so.csdn.net/so/search?q=tornado&spm=1001.2101.3001.7020)项目时需要使用pycurl. 如果安装pycurl时没有指定与编译时相同的ssl选项, 则会导致冲突.

```shell
pycurl: libcurl link-time ssl backend (nss) is different from compile-time ssl backend (none/other)
```

##### 解决方案: 切换 pycurl 的ssl库为nss后重新安装

```shell
sudo -s # 如果是使用sudo安装包或启动命令的话, 需要先执行该命令后修改PY_SSL_LIBRARY
pip uninstall pycurl
export PYCURL_SSL_LIBRARY=nss
pip install pycurl
```















