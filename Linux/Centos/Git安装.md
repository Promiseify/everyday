### 安装最新版git

#### 下载编译工具

```shell
yum -y groupinstall "Development Tools"
```

#### 下载依赖包

```shell
yum -y install zlib-devel perl-ExtUtils-MakeMaker asciidoc xmlto openssl-devel
```

#### 下载 Git 最新版本的源代码

```shell
wget https://www.kernel.org/pub/software/scm/git/git-2.13.3.tar.gz
```

#### 解压

```shell
tar -zxvf git-2.11.0.tar.gz
```

#### 进入目录配置，编译

```shell
cd git-2.13.3
./configure --prefix=/usr/local/git
```

#### 安装

```shell
make && make install
```

#### 配置全局路径

```shell
export PATH="/usr/local/git/bin:$PATH"
source /etc/profile
```

#### 验证是否安装成功

```shell
[root@iZ2ze3fk84qbagxsn29a31Z ~]# git --version
git version 2.13.3
```

