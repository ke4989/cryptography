//
// Created by ke4989 on 2024/4/23.
//

#ifndef DES_CLION_OPERATIONS_H
#define DES_CLION_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

#define TEXT_LENGTH 64
#define DATA_SIZE (5 * 1024 * 1024)
#define VI_SIZE 16
#define student_num 20221415

// 初始置换表
int IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
            60, 52, 44, 36, 28, 20, 12, 4,
            62, 54, 46, 38, 30, 22, 14, 6,
            64, 56, 48, 40, 32, 24, 16, 8,
            57, 49, 41, 33, 25, 17, 9, 1,
            59, 51, 43, 35, 27, 19, 11, 3,
            61, 53, 45, 37, 29, 21, 13, 5,
            63, 55, 47, 39, 31, 23, 15, 7};

// ip逆置换表
int INVERSE_IP[] = {40, 8, 48, 16, 56, 24, 64, 32,
                    39, 7, 47, 15, 55, 23, 63, 31,
                    38, 6, 46, 14, 54, 22, 62, 30,
                    37, 5, 45, 13, 53, 21, 61, 29,
                    36, 4, 44, 12, 52, 20, 60, 28,
                    35, 3, 43, 11, 51, 19, 59, 27,
                    34, 2, 42, 10, 50, 18, 58, 26,
                    33, 1, 41, 9, 49, 17, 57, 25};

// E扩展运算表
int E[] = {32, 1, 2, 3, 4, 5,
           4, 5, 6, 7, 8, 9,
           8, 9, 10, 11, 12, 13,
           12, 13, 14, 15, 16, 17,
           16, 17, 18, 19, 20, 21,
           20, 21, 22, 23, 24, 25,
           24, 25, 26, 27, 28, 29,
           28, 29, 30, 31, 32, 1};

// pc1置换
int PC_1[] = {57, 49, 41, 33, 25, 17, 9,
              1, 58, 50, 42, 34, 26, 18,
              10, 2, 59, 51, 43, 35, 27,
              19, 11, 3, 60, 52, 44, 36,
              63, 55, 47, 39, 31, 23, 15,
              7, 62, 54, 46, 38, 30, 22,
              14, 6, 61, 53, 45, 37, 29,
              21, 13, 5, 28, 20, 12, 4};

// pc2置换
int PC_2[] = {14, 17, 11, 24, 1, 5,
              3, 28, 15, 6, 21, 10,
              23, 19, 12, 4, 26, 8,
              16, 7, 27, 20, 13, 2,
              41, 52, 31, 37, 47, 55,
              30, 40, 51, 45, 33, 48,
              44, 49, 39, 56, 34, 53,
              46, 42, 50, 36, 29, 32};

// s盒
int S_BOX[8][4][16] = {
    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},

    {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
     {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
     {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
     {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},

    {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
     {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
     {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
     {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},

    {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
     {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
     {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
     {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},

    {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
     {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
     {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
     {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},

    {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
     {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
     {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
     {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},

    {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
     {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
     {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
     {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},

    {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
     {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
     {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
     {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};

// p置换表
int P[] = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22,
           11, 4, 25};

// ls行移位表
int LS[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// 字符串转十六进制
void str2hex(char *str, char *hex)
{
    char hexbuf[65];
    char hexstr[65] = {0};
    // 将读取的字符串转化成十六进制
    for (size_t i = 0; i < strlen(str); i++)
    {
        sprintf(hexbuf, "%02X", str[i]);
        strncat(hexstr, hexbuf, 2);
    }
    hexstr[64] = '\0';
    strcpy(hex, hexstr);
}

// 2进制转10进制
int bin2dec(char *bin)
{
    int res = 0;
    int len = strlen(bin);
    char temp[2];
    temp[0] = '0';
    temp[1] = '1';
    for (size_t i = 0; i < len; i++)
    {
        if (bin[len - i - 1] == temp[1])
        {
            res += pow(2, i);
        }
        else
        {
            continue;
        }
    }
    return res;
}

// 十进制转二进制
int dec2bin(int n)
{
    int sum = 0;
    int y, x = 1; // y表示余数，x为叠加的系数
    while (n != 0)
    {
        y = n % 2;
        sum += x * y;
        x *= 10;
        n /= 2;
    }
    return sum;
}

// 十六进制转二进制
void hex2bin(char *hex, char *bin)
{
    int len = strlen(hex);
    char buff[65];
    char binbuff[65] = {0};
    for (int i = 0; i < len; i++)
    {
        switch (hex[i])
        {
        case '0':
            strcpy(buff, "0000");
            strncat(binbuff, buff, 4);
            break;
        case '1':
            strcpy(buff, "0001");
            strncat(binbuff, buff, 4);
            break;
        case '2':
            strcpy(buff, "0010");
            strncat(binbuff, buff, 4);
            break;
        case '3':
            strcpy(buff, "0011");
            strncat(binbuff, buff, 4);
            break;
        case '4':
            strcpy(buff, "0100");
            strncat(binbuff, buff, 4);
            break;
        case '5':
            strcpy(buff, "0101");
            strncat(binbuff, buff, 4);
            break;
        case '6':
            strcpy(buff, "0110");
            strncat(binbuff, buff, 4);
            break;
        case '7':
            strcpy(buff, "0111");
            strncat(binbuff, buff, 4);
            break;
        case '8':
            strcpy(buff, "1000");
            strncat(binbuff, buff, 4);
            break;
        case '9':
            strcpy(buff, "1001");
            strncat(binbuff, buff, 4);
            break;
        case 'a':
        case 'A':
            strcpy(buff, "1010");
            strncat(binbuff, buff, 4);
            break;
        case 'b':
        case 'B':
            strcpy(buff, "1011");
            strncat(binbuff, buff, 4);
            break;
        case 'c':
        case 'C':
            strcpy(buff, "1100");
            strncat(binbuff, buff, 4);
            break;
        case 'd':
        case 'D':
            strcpy(buff, "1101");
            strncat(binbuff, buff, 4);
            break;
        case 'e':
        case 'E':
            strcpy(buff, "1110");
            strncat(binbuff, buff, 4);
            break;
        case 'f':
        case 'F':
            strcpy(buff, "1111");
            strncat(binbuff, buff, 4);
            break;
        default:
            printf("hex error\n");
            break;
        }
    }
    binbuff[65] = '\0';
    strcpy(bin, binbuff);
}

// 二进制转十六进制
void bin2hex(char *bin, char *hex)
{
    int len = strlen(bin) / 4;
    char buf[5];
    buf[4] = '\0';
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            buf[j] = bin[i * 4 + j];
        }
        int dec = bin2dec(buf);
        switch (dec)
        {
        case 0:
            hex[i] = '0';
            break;
        case 1:
            hex[i] = '1';
            break;
        case 2:
            hex[i] = '2';
            break;
        case 3:
            hex[i] = '3';
            break;
        case 4:
            hex[i] = '4';
            break;
        case 5:
            hex[i] = '5';
            break;
        case 6:
            hex[i] = '6';
            break;
        case 7:
            hex[i] = '7';
            break;
        case 8:
            hex[i] = '8';
            break;
        case 9:
            hex[i] = '9';
            break;
        case 10:
            hex[i] = 'A';
            break;
        case 11:
            hex[i] = 'B';
            break;
        case 12:
            hex[i] = 'C';
            break;
        case 13:
            hex[i] = 'D';
            break;
        case 14:
            hex[i] = 'E';
            break;
        case 15:
            hex[i] = 'F';
            break;
        default:
            break;
        }
    }
}

// 写入文件
void writeFile(char *filename, char *txt)
{
    FILE *fp = NULL;
    fp = fopen(filename, "a+");
    fputs(txt, fp);
    fclose(fp);
    //    printf("%s\n",fp);
}

char keyfile[50];
char cipherfile[50];
char plaintextfile[50];
char initvecfile[50];

// 密钥
char keybuf[9];
// 十六进制
char keyhex[17];
// 当前密钥的二进制
char keybin[65];

// 用于密钥的生成
// key的前28位
char c[29];
// key的后28位
char d[29];
char cd[57];

// 初始化向量
char vechex[17];
char vecbin[65];

// 输出计数
int outputconut = 0;

// 读取密钥
void readKey(char *filename)
{
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open file \"%s\" for reading\n", filename);
        return; // 退出函数
    }
    fgets(keyhex, 17, (FILE *)fp);
    keyhex[16] = '\0';
    fclose(fp);
}

// 生成随机向量
void generateRandomVec(char *filename)
{
    //    char *vi;
    FILE *fp;
    int i;
    //    char *iv;

    srand(time(NULL)); // 初始化随机数种子

    // 分配内存，用于存储随机生成的测试数据
    //    iv = (char *) malloc(VI_SIZE/2);
    //    if (iv == NULL) {
    //        printf("memory allocate fail!\n");
    //        return;
    //    }

    // 生成随机数据
    for (i = 0; i < VI_SIZE / 2; i++)
    {
        int randomNum = rand() % 256;               // 生成 0 到 255 之间的随机数
        printf("%02X", randomNum);                  // 打印十六进制格式的随机数
        sprintf(&vechex[i * 2], "%02X", randomNum); // 将随机数转换为两个十六进制字符并存储到 vechex 中
                                                    //        sprintf(&vechex[i], "%c", vi[i]);
                                                    //        sprintf(&vechex[i], "%X", iv[i]);
                                                    //        printf("%X", toupper((unsigned char) vechex[i]));
    }
    printf("\n");
    vechex[16] = '\0';

    // 将生成的随机数复制到vechex中
    //    strcpy(vechex, vi);
    //    vechex[16] = '\0';

    // 写入文件
    fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        printf("Error: Unable to create file \"%s\" for writing\n", filename);
        return;
    }
    fprintf(fp, "%s", vechex); // 将 veche 写入文件
                               //    for (i = 0; i < VI_SIZE / 2; i++) {
                               //        fprintf(fp, "%02X", toupper((unsigned char) vechex[i])); // 将每个字节转换为2位16进制数，并写入文件
                               //    }
    fclose(fp);
    printf("Random file generated and saved in \"%s\" !\n", filename);
}

// 读取初始化向量
void readInitVec(char *filename)
{
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open file \"%s\" for reading\nthere are random numbers: ", filename);
        generateRandomVec(filename); // 生成随机向量并保存到文件中
                                     //        fp = fopen(filename, "r");
        return;
    }
    fgets(vechex, 17, (FILE *)fp);
    vechex[16] = '\0';
    fclose(fp);
}

// 字符串合并
void strMerge(char *str1, char *str2, char *res)
{
    int len = strlen(str1);
    for (size_t i = 0; i < len; i++)
    {
        res[i] = str1[i];
        res[len + i] = str2[i];
    }
}

// 初始ip置换
void initSwitch(char *m)
{
    char temp[64];
    strcpy(temp, m);
    for (int i = 0; i < 64; i++)
    {
        m[i] = temp[IP[i] - 1];
    }
}

// ip逆置换
void reIPSwitch(char *m)
{
    char temp[65];
    strcpy(temp, m);
    for (int i = 0; i < 64; i++)
    {
        m[i] = temp[INVERSE_IP[i] - 1];
    }
}

// s盒置换
void sSwitch(char *str, char *end)
{
    char s[7];
    s[6] = '\0';
    char hang[3];
    hang[2] = '\0';
    int h;
    char lie[5];
    lie[4] = '\0';
    int l;
    int afters[8];
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 6; j++)
        {
            s[j] = str[6 * i + j];
        }
        hang[0] = s[0];
        hang[1] = s[5];
        for (size_t k = 0; k < 4; k++)
        {
            lie[k] = s[1 + k];
        }

        // 二进制转十进制
        h = bin2dec(hang);
        l = bin2dec(lie);

        // 完成s盒转换
        afters[i] = S_BOX[i][h][l];
    }
    char buf[5];
    buf[4] = '\0';
    for (size_t i = 0; i < 8; i++)
    {
        // 将s盒变换后的数字转成二进制，并补位成四位
        itoa(dec2bin(afters[i]), buf, 10);
        // linux
        //        sprintf(buf, "%04d", afters[i]);
        int lenofbuf = strlen(buf);
        switch (lenofbuf)
        {
        case 4:
            break;
            // 进行补位
        case 3:
            buf[3] = buf[2];
            buf[2] = buf[1];
            buf[1] = buf[0];
            buf[0] = '0';
            break;
        case 2:
            buf[2] = buf[0];
            buf[3] = buf[1];
            buf[0] = '0';
            buf[1] = '0';
            break;
        case 1:
            buf[3] = buf[0];
            buf[0] = '0';
            buf[1] = '0';
            buf[2] = '0';
            break;
        default:
            break;
        }
        for (size_t j = 0; j < 4; j++)
        {
            end[4 * i + j] = buf[j];
        }
    }
}

// E扩展运算
void extend(char *r, char *e)
{
    for (int i = 0; i < 48; i++)
    {
        e[i] = r[E[i] - 1];
    }
}

// p置换
void pSwitch(char *start, char *end)
{
    for (size_t i = 0; i < 32; i++)
    {
        end[i] = start[P[i] - 1];
    }
}

// ls移位
void lsSwitch(char *str, int round)
{
    int times = LS[round - 1];
    char temp[28];
    strcpy(temp, str);
    for (size_t i = 0; i < 28; i++)
    {
        str[i] = temp[(i + times) % 28];
    }
}

// 异或运算
// 参数分别为异或的两个数，返回的结果和异或的位数
void Xor(char *a, char *b, char *res, int len)
{
    char ret[len + 1];
    ret[len] = '\0';
    for (size_t i = 0; i < len; i++)
    {
        if (a[i] == b[i])
        {
            ret[i] = '0';
        }
        else
        {
            ret[i] = '1';
        }
    }
    strcpy(res, ret);
}

// 子密钥生成函数
void keyGen(char *key, int round, char *afterkey)
{
    // 如果是第一轮加密，进行pc1置换
    if (round == 1)
    {
        char temp[65];
        strcpy(temp, key);
        // pc1置换
        for (size_t i = 0; i < 56; i++)
        {
            cd[i] = temp[PC_1[i] - 1];
        }
        cd[56] = '\0';
        c[28] = '\0';
        d[28] = '\0';
    }

    // 将cd分解为c和d
    for (size_t i = 0; i < 28; i++)
    {
        c[i] = cd[i];
        d[i] = cd[28 + i];
    }

    // 进行ls移位
    lsSwitch(c, round);
    lsSwitch(d, round);
    c[28] = '\0';
    d[28] = '\0';
    // 将移位后的c、d合并到cd
    strMerge(c, d, cd);
    cd[56] = '\0';
    // pc2置换
    for (size_t i = 0; i < 48; i++)
    {
        afterkey[i] = cd[PC_2[i] - 1];
    }
}

// des加密
void des(char *in, char *out)
{
    int n = student_num % 16;
    // 读取密钥
    readKey(keyfile);
    // 密钥转换成二进制
    hex2bin(keyhex, keybin);
    keybin[64] = '\0';

    char temp[65];
    strcpy(temp, in);
    temp[64] = '\0';

    // 进行ip置换
    initSwitch(temp);
    char l[33];
    char r[33];
    // 将输入分为左右两部分
    for (int i = 0; i < 32; i++)
    {
        l[i] = temp[i];
        r[i] = temp[32 + i];
    }

    l[32] = '\0';
    r[32] = '\0';
    // 进行十六轮加密
    for (int round = 1; round < 17; round++)
    {
        // e扩展运算
        char er[49];
        er[48] = '\0';
        extend(r, er);
        // printf("exr:\t%s\n", er);

        // 生成轮密钥
        char key1[49];
        key1[48] = '\0';
        keyGen(keybin, round, key1);
        strcpy(keybin, key1);

        // 密钥与E（R）异或得到结果res
        char res[49];
        res[48] = '\0';
        Xor(keybin, er, res, 48);
        // printf("kxer:\t%s\n", res);

        // 进行s盒置换
        char afters[64];
        sSwitch(res, afters);
        // printf("sw:\t%s\n", afters);

        // 再进行p置换
        char afterp[33];
        afterp[32] = '\0';
        pSwitch(afters, afterp);
        // printf("ps:\t%s\n", afterp);

        // 两边再异或
        char r0[33];
        r0[32] = '\0';
        Xor(l, afterp, r0, 32);

        strMerge(r, r0, temp);
        if (round - 1 == n)
        {
            printf("%s", temp);
        }

        strcpy(l, r);
        strcpy(r, r0);
    }
    // 执行最后一步换位
    strMerge(r, l, temp);
    // 进行逆ip置换
    reIPSwitch(temp);
    strcpy(out, temp);
}

// des解密 过程与加密一样，只是子密钥反过来使用
void dedes(char *in, char *out)
{
    int n = student_num % 16;
    char temp[65];
    strcpy(temp, in);
    temp[64] = '\0';

    char keys[16][68];
    // 读取密钥
    readKey(keyfile);
    // 密钥转换成二进制
    hex2bin(keyhex, keybin);
    // 进行ip置换
    initSwitch(temp);
    char l[33];
    char r[33];
    // 将输入分为左右两部分
    for (int i = 0; i < 32; i++)
    {
        l[i] = temp[i];
        r[i] = temp[32 + i];
    }

    l[32] = '\0';
    r[32] = '\0';
    // 生成十六轮密钥
    for (int i = 0; i < 16; i++)
    {
        keyGen(keybin, i + 1, keys[i]);
        keys[i][48] = '\0';
    }
    // 解密
    for (int round = 1; round < 17; round++)
    {

        // e扩展运算
        char er[49];
        er[48] = '\0';
        extend(r, er);
        // printf("exr:\t%s\n", er);

        // 密钥与E（R）异或得到结果res
        char res[49];
        res[48] = '\0';
        Xor(keys[16 - round], er, res, 48);
        // printf("kxer:\t%s\n", res);

        // s盒置换
        char afters[64];
        sSwitch(res, afters);
        // printf("sw:\t%s\n", afters);

        // p置换
        char afterp[33];
        afterp[32] = '\0';
        pSwitch(afters, afterp);

        char r0[33];
        r0[32] = '\0';
        Xor(l, afterp, r0, 32);
        strMerge(r, r0, temp);
        // printf("out:\t%s\n", in);
        if (round - 1 == n)
        {
            printf("%s\n", temp);
        }
        strcpy(l, r);
        strcpy(r, r0);
    }
    // 执行最后一步换位
    strMerge(r, l, temp);
    // 进行逆ip置换
    reIPSwitch(temp);
    strcpy(out, temp);
}

// 分组字符串
char strbuff[9];
// 分组——16进制
char pkthex[17];
// 当前分组数据的二进制
char pktbin[65];

// 8位的分组
char ebhex[3];
char ebbin[9];
// 8位的密文分组
char ebcipherbin[9];
char ebcipherhex[3];

// 密文二进制
char cipherbin[65];
// 密文十六进制
char cipherhex[17];

// 随机生成测试数据
void initTxtData()
{
    FILE *fp;
    char *data;
    int i;

    srand(time(NULL)); // 初始化随机数种子

    // 分配内存，用于存储随机生成的测试数据
    data = (char *)malloc(DATA_SIZE / 2);
    if (data == NULL)
    {
        printf("memory allocate fail!\n");
        return;
    }

    // 生成随机测试数据
    for (i = 0; i < DATA_SIZE / 2; i++)
    {
        data[i] = rand() % 256; // 生成0到255之间的随机数
    }

    // 将测试数据以16进制格式写入文件
    fp = fopen(plaintextfile, "wb");
    if (fp == NULL)
    {
        printf("can not open file\n");
        return;
    }
    for (i = 0; i < DATA_SIZE / 2; i++)
    {
        fprintf(fp, "%02X", toupper((unsigned char)data[i])); // 将每个字节转换为2位16进制数，并写入文件
    }
    fclose(fp);
    printf("generate 5mb data successfully\n");
}

// 分组密码操作模式
// 电子密码本模式
void des_ecb()
{
    cipherbin[64] = '\0';
    cipherhex[16] = '\0';
    int n = student_num % 16;
    // 打开明文文件
    FILE *fp = NULL;
    //    printf("%s\n", plaintextfile);
    fp = fopen(plaintextfile, "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open file \"%s\" for reading\n", plaintextfile);
        return; // 退出函数
    }
    //    outputconut = 0;
    printf("%d round output:\n", n);
    while (fgets(pkthex, 17, (FILE *)fp))
    {
        hex2bin(pkthex, pktbin);
        des(pktbin, cipherbin);
        bin2hex(cipherbin, cipherhex);
        writeFile(cipherfile, cipherhex);
    }
    fclose(fp);
    printf("\n\n");
    printf("+---------------------------------------+\n");
    printf("|                                       |\n");
    printf("| des of ECB mode encrypt successfully! |\n");
    printf("|                                       |\n");
    printf("+---------------------------------------+\n");
}

// ECB模式解密
void dedes_ecb()
{
    cipherbin[64] = '\0';
    cipherhex[16] = '\0';
    int n = student_num % 16;
    // 打开明文文件
    FILE *fp = NULL;
    fp = fopen(cipherfile, "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open file \"%s\" for reading\n", cipherfile);
        return; // 退出函数
    }
    printf("%d round output:\n", n);
    while (fgets(pkthex, 17, (FILE *)fp))
    {
        hex2bin(pkthex, pktbin);
        dedes(pktbin, cipherbin);
        bin2hex(cipherbin, cipherhex);
        writeFile(plaintextfile, cipherhex);
    }
    fclose(fp);
    printf("\n\n");
    printf("+-----------------------------------------+\n");
    printf("|                                         |\n");
    printf("| des of ECB mode  decrypt  successfully! |\n");
    printf("|                                         |\n");
    printf("+-----------------------------------------+\n");
}

// 密码分组链接模式
void des_cbc()
{
    cipherbin[64] = '\0';
    cipherhex[16] = '\0';
    int n = student_num % 16;
    // 读取初始化向量
    readInitVec(initvecfile);

    // 将初始化向量转成二进制
    hex2bin(vechex, vecbin);

    // 与输入按位异或
    FILE *fp = NULL;
    fp = fopen(plaintextfile, "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open file \"%s\" for reading\n", plaintextfile);
        return; // 退出函数
    }

    char in[65];

    printf("%d round output:\n", n);
    while (fgets(pkthex, 17, (FILE *)fp))
    {
        // 明文分组转二进制
        hex2bin(pkthex, pktbin);
        // 明文分组与前一密文或初始化向量的异或得到输入
        Xor(vecbin, pktbin, in, 64);
        in[64] = '\0';
        // 将输入经过des加密
        des(in, cipherbin);
        // 将密文作为与下一明文分组异或的链接
        strcpy(vecbin, cipherbin);
        // 将密文转为十六进制写入密文文件
        bin2hex(cipherbin, cipherhex);
        writeFile(cipherfile, cipherhex);
    }
    fclose(fp);
    printf("\n\n");
    printf("+---------------------------------------+\n");
    printf("|                                       |\n");
    printf("| des of CBC mode encrypt successfully! |\n");
    printf("|                                       |\n");
    printf("+---------------------------------------+\n");
}

// CBC模式解密
void dedes_cbc()
{
    cipherbin[64] = '\0';
    cipherhex[16] = '\0';
    int n = student_num % 16;
    // 读取初始化向量
    readInitVec(initvecfile);

    // 将初始化向量转成二进制
    hex2bin(vechex, vecbin);

    FILE *fp = NULL;
    fp = fopen(cipherfile, "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open file \"%s\" for reading\n", cipherfile);
        return; // 退出函数
    }
    char in[65];

    printf("%d round output:\n", n);
    while (fgets(cipherhex, 17, (FILE *)fp))
    {
        // 密文分组转二进制
        hex2bin(cipherhex, cipherbin);
        // des解密
        dedes(cipherbin, in);
        in[64] = '\0';
        // 与前一密文或初始化向量的异或得到明文分组
        Xor(vecbin, in, pktbin, 64);
        // 将密文作为与下一明文分组异或的链接
        strcpy(vecbin, cipherbin);
        // 将明文转为十六进制写入明文文件
        bin2hex(pktbin, pkthex);
        writeFile(plaintextfile, pkthex);
    }

    fclose(fp);
    printf("\n\n");
    printf("+-----------------------------------------+\n");
    printf("|                                         |\n");
    printf("| des of CBC mode  decrypt  successfully! |\n");
    printf("|                                         |\n");
    printf("+-----------------------------------------+\n");
}

// 8位密码反馈模式
void des_cfb()
{
    int n = student_num % 16;
    // 8位操作模式
    ebcipherbin[9] = '\0';
    ebcipherhex[3] = '\0';

    // 读取初始化向量
    readInitVec(initvecfile);
    // 将初始化向量转成二进制
    hex2bin(vechex, vecbin);
    // 与输入按位异或
    FILE *fp = NULL;
    fp = fopen(plaintextfile, "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open file \"%s\" for reading\n", plaintextfile);
        return; // 退出函数
    }
    char in[65];

    printf("%d round output:\n", n);
    while (fgets(ebhex, 3, (FILE *)fp))
    {
        // 将明文转为二进制
        hex2bin(ebhex, ebbin);
        in[64] = '\0';
        // 将移位寄存器内容加密得到输入
        des(vecbin, in);
        // 将输入的前八位与8位明文异或得到密文
        Xor(in, ebbin, ebcipherbin, 8);
        // 将密文转为二进制并写入文件
        bin2hex(ebcipherbin, ebcipherhex);
        writeFile(cipherfile, ebcipherhex);

        // 移动移位寄存器
        char temp[65];
        temp[64] = '\0';
        strcpy(temp, vecbin);
        for (size_t i = 0; i < 56; i++)
        {
            vecbin[i] = temp[8 + i];
        }
        for (size_t i = 56; i < 64; i++)
        {
            vecbin[i] = ebcipherbin[i - 56];
        }
    }
    fclose(fp);
    printf("\n\n");
    printf("+---------------------------------------+\n");
    printf("|                                       |\n");
    printf("| des of CFB mode encrypt successfully! |\n");
    printf("|                                       |\n");
    printf("+---------------------------------------+\n");
}

// cfb模式解密
void dedes_cfb()
{
    int n = student_num % 16;
    // 8位操作模式
    ebbin[9] = '\0';
    ebhex[3] = '\0';
    // 读取初始化向量
    readInitVec(initvecfile);
    // 将初始化向量转成二进制
    hex2bin(vechex, vecbin);
    // 与输入按位异或
    FILE *fp = NULL;
    fp = fopen(cipherfile, "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open file \"%s\" for reading\n", cipherfile);
        return; // 退出函数
    }
    char in[65];

    printf("%d round output:\n", n);
    while (fgets(ebcipherhex, 3, (FILE *)fp))
    {
        // 将密文转为二进制
        hex2bin(ebcipherhex, ebcipherbin);
        in[64] = '\0';
        // 将移位寄存器内容加密得到输入
        des(vecbin, in);
        // 将输入的前八位与8位密文异或得到明文
        Xor(in, ebcipherbin, ebbin, 8);
        // 将明文转为二进制并写入文件
        bin2hex(ebbin, ebhex);
        writeFile(plaintextfile, ebhex);

        // 移动移位寄存器
        char temp[65];
        temp[64] = '\0';
        strcpy(temp, vecbin);
        for (size_t i = 0; i < 56; i++)
        {
            vecbin[i] = temp[8 + i];
        }
        for (size_t i = 56; i < 64; i++)
        {
            vecbin[i] = ebcipherbin[i - 56];
        }
    }
    fclose(fp);
    printf("\n\n");
    printf("+-----------------------------------------+\n");
    printf("|                                         |\n");
    printf("| des of CFB mode  decrypt  successfully! |\n");
    printf("|                                         |\n");
    printf("+-----------------------------------------+\n");
}

// 8位输出反馈模式
void des_ofb()
{
    int n = student_num % 16;

    cipherbin[64] = '\0';
    cipherhex[16] = '\0';
    // 读取初始化向量
    readInitVec(initvecfile);
    // 将初始化向量转成二进制
    hex2bin(vechex, vecbin);
    FILE *fp = NULL;
    fp = fopen(plaintextfile, "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open file \"%s\" for reading\n", plaintextfile);
        return; // 退出函数
    }
    char in[65];
    printf("%d round output:\n", n);
    while (fgets(pkthex, 17, (FILE *)fp))
    {
        hex2bin(pkthex, pktbin);
        des(vecbin, in);
        in[64] = '\0';
        strcpy(vecbin, in);
        Xor(in, pktbin, cipherbin, 64);
        bin2hex(cipherbin, cipherhex);
        writeFile(cipherfile, cipherhex);
    }
    fclose(fp);
    printf("\n\n");
    printf("+---------------------------------------+\n");
    printf("|                                       |\n");
    printf("| des of OFB mode encrypt successfully! |\n");
    printf("|                                       |\n");
    printf("+---------------------------------------+\n");
}

// ofb解密模式
void dedes_ofb()
{
    int n = student_num % 16;

    pktbin[64] = '\0';
    pkthex[16] = '\0';
    // 读取初始化向量
    readInitVec(initvecfile);
    // 将初始化向量转成二进制
    hex2bin(vechex, vecbin);
    FILE *fp = NULL;
    fp = fopen(cipherfile, "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open file \"%s\" for reading\n", cipherfile);
        return; // 退出函数
    }
    char in[65];
    printf("%d round output:\n", n);
    while (fgets(cipherhex, 17, (FILE *)fp))
    {
        hex2bin(cipherhex, cipherbin);
        des(vecbin, in);
        in[64] = '\0';
        strcpy(vecbin, in);
        Xor(in, cipherbin, pktbin, 64);
        bin2hex(pktbin, pkthex);
        writeFile(plaintextfile, pkthex);
    }
    fclose(fp);
    printf("\n\n");
    printf("+-----------------------------------------+\n");
    printf("|                                         |\n");
    printf("| des of OFB mode  decrypt  successfully! |\n");
    printf("|                                         |\n");
    printf("+-----------------------------------------+\n");
}

#endif // DES_CLION_OPERATIONS_H
