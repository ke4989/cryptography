**分组密码算法实现 （二选一）**

**实践题目** **1 DES** **算法实现**

**实践要求：**

\1. 分别实现 ECB、CBC、CFB、OFB 这四种操作模式的 DES。每种操作模式都有一组对

应的测试数据，以便检查程序的正确性。其中，CFB 操作模式为 32 位 CFB 操作模式，

OFB 操作模式为 32 位 OFB 操作模式。

\2. 要求以命令行的形式，指定明文文件、密钥文件、初始化向量文件的位置和名称、加密的

操作模式以及加密完成后密文文件的位置和名称。加密时先分别从指定的明文文件、密钥

文件和初始化向量文件中读取有关信息，然后按指定的操作模式进行加密，最后将密文

（用 16 进制表示）写入指定的密文文件。 

命令行的具体格式如下： 

e1des -p plainfile -k keyfile [-v vifile] -m mode -c cipherfile 

参数： 

-p plainfile 指定明文文件的位置和名称

-k keyfile 指定密钥文件的位置和名称

-v vifile 指定初始化向量文件的位置和名称

-m mode 指定加密的操作模式

-c cipherfile 指定密文文件的位置和名称。

\3. 分别实现对每种操作模式下加密及解密速度的测试，要求选取 5MB 的随机测试数据（不

要求使用随机数发生器），连续加密、解密 10 次，记录并报告每种模式的加密和解密的

总时间（毫秒）和速度（MByte/秒）。

\4. 用 C 和/或 C++语言完成程序。

\5. 额外输出每个加密分组中第𝑛轮加密的输出，其中𝑛 = *学号* 𝑚𝑜𝑑 16,例如如果同学的学号

是 12345678，那么需要输出第𝑛 = 14轮 Feistel 加密的输出。

\6. 最终上交的作业包括：电子版的实践报告和程序源代码，要求由源代码能重新正确生成可

执行代码。

\7. 实践报告应包括以下内容：作业标题、学号、姓名、E-mail、作业内容描述、实践环境描

述、实践过程简述、实践结果（实践的正确性以及每种操作模式下加密和解密速度的测试

结果）、作业的收获和体会。

附录：测试数据 

明文 1：(16 个字节，128bit，用 16 进制表示) 

B20536564E776F726375726974657479 (明文文件如：des_plain1.txt) 

明文 2：(自选 5M 大小消息，消息不能全 0 或全 1，用 16 进制表示) (明文文件如：

des_plain2.txt)密钥：(8 个字节，64bit，用 16 进制表示) 

6C69657696C16D53 (密钥文件如：des_key.txt) 

初始化向量 **IV**（在 CBC、CFB、OFB 模式中使用）：(8 个字节，64bit，用 16 进制表示) 

5072656E74696365 (初始化向量文件如：des_iv.txt) 

密文：(16 个字节，128bit，用 16 进制表示) 

a) 将给定 16 字节明文 1 对应模式下对应轮数的密文输出（密文文件如 DES_ Cipher.txt) 

b) 将自选 5M 明文在四种对应模式下完成加密计算的运行时间输出并记录下来（表格

需包含 10 次运行结果的所有运行时间，并据此计算加密效率，以 MB/s 为单位）

**实践题目** **2 AES** **算法实现**

实践要求：

1.只要求实现块长为 128 位、密钥长为 128 位的 AES，分别实现 ECB、CBC、CFB、

OFB 这四种操作模式。每种操作模式都有一组对应的测试数据，以便检查程序的正确

性。其中，CFB 操作模式为 32 位 CFB 操作模式，OFB 操作模式为 32 位 OFB 操作

模式。

2.要求以命令行的形式，指定明文文件、密钥文件、初始化向量文件的位置和名称、加密

的操作模式以及加密完成后密文文件的位置和名称。加密时先分别从指定的明文文件、

密钥文件和初始化向量文件中读取有关信息，然后按指定的操作模式进行加密，最后将

密文（用 16 进制表示）写入指定的密文文件。 

命令行的具体格式如下： 

e2aes -p plainfile -k keyfile [-v vifile] -m mode -c cipherfile 

参数： 

-p plainfile 指定明文文件的位置和名称

-k keyfile 指定密钥文件的位置和名称

-v vifile 指定初始化向量文件的位置和名称

-m mode 指定加密的操作模式

-c cipherfile 指定密文文件的位置和名称。

3.分别实现对每种操作模式下加密及解密速度的测试，要求在程序中生成 5MB 的随机测

试数据（不要求使用随机数发生器），连续加密、解密 10 次，记录并报告每种模式的加

密和解密的总时间（毫秒）和速度（MByte/秒）。

4.用 C 和/或 C++语言完成程序。

5.额外输出每个加密分组第𝑛轮加密的输出，其中𝑛 = *学号* 𝑚𝑜𝑑 10,例如如果同学的学号是

12345678，那么需要输出第𝑛 = 8轮经轮密钥加密后的输出。

6.最终上交的作业包括：电子版的实践报告和程序源代码，要求由源代码能重新正确生成

可执行代码。

7.实践报告应包括以下内容：作业标题、学号、姓名、E-mail、作业内容描述、实践环境描

述、实践过程简述、实践结果(实践的正确性以及每种操作模式下加密和解密速度的测试

结果)、作业的收获和体会。

附录：测试数据 

明文 1：(32 个字节，256bit，用 16 进制表示) 

7970746F6437277B536563757269747926170687920616E64204E6574776F726

（明文文件如：aes_plain1.txt）

明文 2：(自选 5M 大小消息，用 16 进制表示，消息不能全 0 或全 1，用 16 进制表示) 

(明文文件如：aes_plain2.txt)密钥：(16 个字节，128bit，用 16 进制表示)

69616D537461657696C6CC6C696E6773（密钥文件如：aes_key.txt）

初始化向量 **IV**（在 CBC、CFB、OFB 模式中使用）：(16 个字节，128bit，用

16 进制表示) 5072656E7469636548616C6C496E632E （初始化向量文件如：

aes_iv.txt）

密文：(32 个字节，256bit，用 16 进制表示) 

a) 将对应模式下对应轮数的密文输出（密文文件如 AES_ Cipher.txt）

b) 将自选 5M 明文在四种对应模式下完成加密计算的运行时间输出并记录下来（表格

需包含 10 次运行结果的所有运行时间，并据此计算加密效率，以 MB/s 为单位）