# 密码学课程实践

## 分组密码算法实现

### DES算法实现

分别实现 ECB、CBC、CFB、OFB 这四种操作模式的 DES。其余信息详见[分组密码算法实现要求文档](./des/requirement_des.md)。

### AES算法实现

分别实现 ECB、CBC、CFB、OFB 这四种操作模式。

### 命令行具体格式

```program [-r] -p plainfile -k keyfile [-v vifile] -m mode -c cipherfile```

```-h``` 获取帮助，查看具体命令

```-r``` 随机生成明文文件

```-p plainfile``` 指定明文文件的位置和名称

```-k keyfile``` 指定密钥文件的位置和名称

```-v vifile``` 指定初始化向量文件的位置和名称

```-m mode``` 指定加密的操作模式

```-c cipherfile``` 指定密文文件的位置和名称

## RSA 的实现

要求实现简单的RSA过程，为节省时间，使用python。其余信息详见[RSA实现要求文档](./rsa/requirement_rsa.md)。

### 命令行具体格式

```program -p plainfile -n nfile [-e efile] [-d dfile] -c cipherfile```

```-h``` 获取帮助，查看具体命令

```-p plainfile``` 指定明文文件的位置和名称

```-n nfile``` 指定存放整数 n 的文件的位置和名称

```-e efile``` 在数据加密时，指定存放整数 e 的文件的位置和名称

```-d dfile``` 在数字签名时，指定存放整数 d 的文件的位置和名称

```-c cipherfile``` 指定密文文件的位置和名称

```-r``` 随机生成密钥，使用此参数时要求输入```-n```, ```-d```, ```-e```三个参数

### 错误解决

rsa库无法使用时，尝试使用```requirements.txt```文件；若无法运行，尝试删除密钥生成部分代码。

其他情况请自行解决。

## 说明

本项目仅供学习使用。

des代码主要参考来源 [jackfromeast/DES_algorithm](https://github.com/jackfromeast/DES_algorithm)（十分感谢），并修改成为一个```.h```文件，加快运行速度（与原项目相比）。

代码修改十分凌乱，后续有时间再来进行整理。

