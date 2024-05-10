import rsa
import argparse
import sys


# 以下四个函数可以合并为一个，为便于理解分开来写
def load_key(file_path):
    with open(file_path, "r") as file:
        # 从文件读取十六进制字符串并转换为整数
        return int(file.read().strip(), 16)  # 添加16表示基数为十六进制


def save_key(file_path, key):
    with open(file_path, "w") as file:
        # 将整数key转换为十六进制字符串(去除前缀'0x')后写入文件
        file.write(f"{key:X}")  # 使用:x来格式化key为十六进制


def load_data(file_path):
    with open(file_path, "r") as file:
        return int(file.read().strip(), 16)


def save_data(file_path, data):
    with open(file_path, "w") as file:
        file.write(f"{data:X}")


# 以下两个函数可以合并为一个
def encrypt(plaintext, n, e):
    ciphertext = pow(plaintext, e, n)
    return ciphertext


def decrypt(ciphertext, n, d):
    plaintext = pow(ciphertext, d, n)
    return plaintext


def generate_keys():
    (pubkey, privkey) = rsa.newkeys(
        512
    )  # 生成512位密钥，可根据需求更改位数，如1024,4096
    # (public, private) = rsa.newkeys(512, poolsize=8)  # 使用多进程加速生成
    # print(f'n: {pubkey.n}')
    # print(f'e: {pubkey.e}')
    # print(f'd: {str(privkey.d)}')
    print(f"n: {pubkey.n:X}")  # 输出十六进制格式
    print(f"e: {pubkey.e:X}")  # 输出十六进制格式
    print(f"d: {privkey.d:X}")  # 输出十六进制格式
    return pubkey, privkey


def main():
    parser = argparse.ArgumentParser(description="Encrypt or decrypt files using RSA.")
    parser.add_argument(
        "-p", "--plainfile", type=str, help="Path to the plaintext file"
    )
    parser.add_argument(
        "-n", "--nfile", type=str, help="Path to the file with integer n"
    )
    parser.add_argument(
        "-e", "--efile", type=str, help="Path to the file with integer e for encryption"
    )
    parser.add_argument(
        "-d", "--dfile", type=str, help="Path to the file with integer d for decryption"
    )
    # parser.add_argument('-c', '--cipherfile', type=str, required=True, help='Path to the cipher file')
    parser.add_argument("-c", "--cipherfile", type=str, help="Path to the cipher file")
    # # 创建互斥组
    # group = parser.add_mutually_exclusive_group(required=True)
    parser.add_argument(
        "-r", "--random", action="store_true", help="Generate random keys"
    )

    args = parser.parse_args()

    if args.random:
        # 检查参数是否满足要求
        if not (args.nfile and args.efile and args.dfile):
            parser.error("-r/--random need -e, -d, -n")
        # 生成随机密钥并保存
        pubkey, privkey = generate_keys()
        if args.nfile:
            save_key(args.nfile, pubkey.n)
        if args.efile:
            save_key(args.efile, pubkey.e)
        if args.dfile:
            save_key(args.dfile, privkey.d)
        print("Random keys generated and saved！")
        return

    n = load_key(args.nfile)

    if args.efile:
        e = load_key(args.efile)
        if args.plainfile:
            plaintext = load_data(args.plainfile)
            ciphertext = encrypt(plaintext, n, e)
            print("Ciphertext: ")
            print(f"{ciphertext:X}")
            print("Encryption completed and ciphertext saved!")
            save_data(args.cipherfile, ciphertext)
        else:
            print("Error: Plainfile is required for encryption", file=sys.stderr)
            sys.exit(1)

    elif args.dfile:
        d = load_key(args.dfile)
        if args.cipherfile:
            ciphertext = load_data(args.cipherfile)
            plaintext = decrypt(ciphertext, n, d)
            print("Plaintext: ")
            print(f"{plaintext:X}")
            print("Decryption completed and plaintext saved!")
            save_data(args.plainfile, plaintext)
        else:
            print("Error: Cipherfile is required for decryption", file=sys.stderr)
            sys.exit(1)
    else:
        print(
            "Error: Either efile or dfile must be specified for operation",
            file=sys.stderr,
        )
        sys.exit(1)


if __name__ == "__main__":
    main()
