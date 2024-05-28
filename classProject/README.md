# 使用说明

## 操作步骤

### 随机生成密钥

- 随机生成SM2密钥对```python main.py -sk -pk -r```

- 随机生成SM4(CBC)密钥```python main.py -k -iv -r```

### 发送方加密

发送方使用加密算法SM4的密钥对明文进行加密、使用自己的SM2密钥对明文进行签名，签名文件会存储在密文路径下
```python main.py -p plain -k key_for_SM4 -iv iv_for_SM4 -sk private_key_of_sender -c cipher```

发送方使用接收方的SM2公钥对SM4密钥进行加密
- ```python main.py -p key_for_SM4 -pk public_key_of_receiver -c encrypted_key```
- ```python main.py -p iv_for_SM4 -pk public_key_of_receiver -c encrypted_iv```

### 接收方解密

接收方使用自己的SM2私钥对加密后的SM4密钥进行解密
- ```python main.py -p key_for_SM4 -sk private_key_of_receiver -c encrypted_key```
- ```python main.py -p iv_for_SM4 -sk private_key_of_receiver -c encrypted_iv```

接收方使用上一步解密的SM4密钥对消息进行解密
```python main.py -p decrypted_data -k key_for_SM4 -iv iv_for_SM4 -c cipher```

接收方使用发送方的SM2公钥进行签名验证
```python main.py -p decrypted_data  -pk public_key_of_sender -s sign```

## 问题解决

### 环境不适配

gmssl包报错或不匹配请尝试使用requirements.txt文件

### 参数不正确

```Error: need right parameters, see it in README.```

## 参考

感谢这篇文章作者提供的思路：[Python生成SM2公私密钥对进行签名验签](https://samo.fun/2021/03/24/Python_Generate_SM2_key/)