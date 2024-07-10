### **使用 apt-get 进行安装Docker**

version: Ubuntu 14.04/16.04

#### 安装必要的一些系统工具

```shell
sudo apt-get update
sudo apt-get -y install apt-transport-https ca-certificates curl software-properties-common
```

#### 安装GPG证书

```shell
curl -fsSL https://mirrors.aliyun.com/docker-ce/linux/ubuntu/gpg | sudo apt-key add -
```

#### 写入软件源信息

```shell
sudo add-apt-repository "deb [arch=amd64] https://mirrors.aliyun.com/docker-ce/linux/ubuntu $(lsb_release -cs) stable"
```

#### 更新并安装Docker-CE

```shell
sudo apt-get -y update
sudo apt-get -y install docker-ce
```

```shell
# 安装指定版本的Docker-CE:
# Step 1: 查找Docker-CE的版本:
# apt-cache madison docker-ce
#   docker-ce | 17.03.1~ce-0~ubuntu-xenial | https://mirrors.aliyun.com/docker-ce/linux/ubuntu xenial/stable amd64 Packages
#   docker-ce | 17.03.0~ce-0~ubuntu-xenial | https://mirrors.aliyun.com/docker-ce/linux/ubuntu xenial/stable amd64 Packages
# Step 2: 安装指定版本的Docker-CE: (VERSION例如上面的17.03.1~ce-0~ubuntu-xenial)
# sudo apt-get -y install docker-ce=[VERSION]
```

