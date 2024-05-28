# Created by ke4989 in 2024/05/26

from gmssl import sm2, sm3, sm4, func
import argparse
import sys
import os


# 参考于 https://samo.fun/2021/03/24/Python_Generate_SM2_key/ ，有修改
# 继承SM2类
# class Generator_SM2_Key(sm2.CryptSM2):
#     def __init__(self, private_key=None, public_key=None, ecc_table=sm2.default_ecc_table, mode=0):
#         super().__init__(private_key, public_key, ecc_table, mode)
#
#     def get_private_key(self):
#         if self.private_key is None:
#             self.private_key = func.random_hex(self.para_len)  # d∈[1, n-2]
#         return self.private_key
#
#     def get_public_key(self):
#         if self.public_key is None:
#             self.public_key = self._kg(int(self.get_private_key(), 16), self.ecc_table['g'])  # P=[d]G
#         return self.public_key
class Generator_SM2_Key(sm2.CryptSM2):

    def __init__(self, private_key=None, public_key=None, ecc_table=sm2.default_ecc_table, mode=0, asn1=False):
        self.para_len = len(ecc_table['n'])
        self.ecc_a3 = (int(ecc_table['a'], base=16) + 3) % int(ecc_table['p'], base=16)
        self.ecc_table = ecc_table
        assert mode in (0, 1), 'mode must be one of (0, 1)'
        self.mode = mode
        self.asn1 = asn1
        # Generate keys if they are not provided
        if private_key is None:
            private_key = self.generate_private_key(ecc_table)
        if public_key is None:
            public_key = self.generate_public_key(private_key, ecc_table)

        # Initialize the parent class with the generated or provided keys
        super().__init__(private_key, public_key, ecc_table, mode)

    def generate_private_key(self, ecc_table):
        # Generates a random private key if not provided
        pri_key = func.random_hex(len(ecc_table['n']))
        return pri_key

    def generate_public_key(self, private_key, ecc_table):
        # Generates the public key based on the private key
        pub_key = self._kg(int(private_key, 16), ecc_table['g'])
        return pub_key

    def get_private_key(self):
        if self.private_key is None:
            self.private_key = self.generate_private_key(self.ecc_table)
        return self.private_key

    def get_public_key(self):
        if self.public_key is None:
            self.public_key = self.generate_public_key(self.get_private_key(), self.ecc_table)
        return self.public_key

    def get_para_len(self):
        return self.para_len


def load_data(file_path):
    with open(file_path, 'r') as file:
        return int(file.read().strip(), 16)


def save_data(file_path, data):
    with open(file_path, 'w') as file:
        if isinstance(data, str):
            file.write(data)
        else:
            file.write(f"{data:X}")


# def save_data_a(file_path, data):
#     with open(file_path, 'a') as file:
#         file.write(f"{data:X}")


def load_data_bytes(file_path):
    with open(file_path, 'rb') as file:  # 以二进制模式打开文件
        data = file.read()  # 读取文件内容，返回bytes
        return data


def save_data_bytes(file_path, data):
    with open(file_path, 'wb') as file:  # 以二进制模式打开文件
        file.write(data)  # 将bytes写入文件


def generate_sm4_key():
    # random numbers
    # key = os.urandom(16)
    # iv = os.urandom(16)
    key = func.random_hex(128)
    print("SM4 Key:", key)
    iv = func.random_hex(128)
    print("SM4 iv:", iv)
    return key.encode('utf-8'), iv.encode('utf-8')


def generate_sm2_keypair():
    sm2key = Generator_SM2_Key()
    private_key = sm2key.get_private_key()
    public_key = sm2key.get_public_key()
    print("Private Key:", private_key)
    print("Public Key:", public_key)
    return private_key, public_key


def get_para_len():
    sm2key = Generator_SM2_Key()
    return sm2key.get_para_len()


def new_sign_path(data_path):
    dir_name, file_name = os.path.split(data_path)
    # new_file_name = 'sign_' + file_name
    new_file_name = 'sign.txt'
    new_data_path = os.path.join(dir_name, new_file_name)
    return new_data_path


def sm4_encrypt(plaintext, key, iv):
    cipher = sm4.CryptSM4()
    cipher.set_key(key, sm4.SM4_ENCRYPT)
    ciphertext = cipher.crypt_cbc(iv, plaintext)
    return ciphertext


def sm4_decrypt(ciphertext, key, iv):
    cipher = sm4.CryptSM4()
    cipher.set_key(key, sm4.SM4_DECRYPT)
    plaintext = cipher.crypt_cbc(iv, ciphertext)
    # print('Plaintext: ')
    # print(plaintext)
    return plaintext


def sm2_sign_with_sm3(data, private_key):
    sm2_crypt = sm2.CryptSM2(private_key=private_key, public_key=private_key.decode('utf-8'))
    sign = sm3.sm3_hash(func.bytes_to_list(data))
    sign = sm2_crypt.sign(sign.encode('utf-8'), func.random_hex(get_para_len()))
    print('Sign: ')
    print(sign)
    return sign


def sm2_verify_sign(public_key, sign, data):
    sm2_crypt = sm2.CryptSM2(public_key=public_key.decode('utf-8'), private_key=public_key)
    hash_value = sm3.sm3_hash(func.bytes_to_list(data))
    result = sm2_crypt.verify(sign, hash_value.encode('utf-8'))
    if result:
        print("success")
    else:
        print("failure")


def sm2_encrypt(data, public_key):
    sm2_crypt = sm2.CryptSM2(public_key=public_key.decode('utf-8'), private_key=None)
    enc_data = sm2_crypt.encrypt(data)
    print(type(enc_data))
    print('Ciphertext: ')
    integer = int.from_bytes(enc_data, byteorder='big')  # 按大端序解释字节串
    print(integer)
    # print(f'{enc_data:X}')
    return enc_data


def sm2_decrypt(data, key):
    sm2_crypt = sm2.CryptSM2(private_key=key, public_key=key.decode('utf-8'))
    decrypted_data = sm2_crypt.decrypt(data)
    # print('Decrypted_data: ')
    # print(decrypted_data)
    return decrypted_data


def main():
    parser = argparse.ArgumentParser(description='Encrypt or decrypt files.')
    parser.add_argument('-p', '--plainfile', type=str, help='Path to the plaintext file')
    parser.add_argument('-k', '--kfile', type=str, help='Path to the file for key of sm4')
    parser.add_argument('-iv', '--ivfile', type=str, help='Path to the file for iv of sm4 (CBC)')
    parser.add_argument('-pk', '--pkfile', type=str, help='Path to the file for public key sm2')
    parser.add_argument('-sk', '--skfile', type=str, help='Path to the file for private key sm2')
    parser.add_argument('-c', '--cipherfile', type=str, help='Path to the cipher file')
    parser.add_argument('-r', '--random', action='store_true', help='Generate random keys')
    parser.add_argument('-s', '--signfile', type=str, help='Path to the sign of original data')

    args = parser.parse_args()

    if args.random:
        # 检查参数是否满足要求
        if not ((args.kfile and args.ivfile) or (args.pkfile and args.skfile)):
            parser.error('-r/--random only need (-k, -iv) or (-pk, -sk)')
        if args.kfile:
            key, iv = generate_sm4_key()
            save_data_bytes(args.kfile, key)
            save_data_bytes(args.ivfile, iv)
        if args.pkfile:
            private_key, public_key = generate_sm2_keypair()
            save_data_bytes(args.pkfile, public_key.encode('utf-8'))
            save_data_bytes(args.skfile, private_key.encode('utf-8'))
        print('Random keys generated and saved！')
        return

    # 发送方加密第一步
    if args.plainfile and args.kfile and args.ivfile and not args.pkfile \
            and args.skfile and args.cipherfile and not args.signfile:
        private_key = load_data_bytes(args.skfile)
        key = load_data_bytes(args.kfile)
        iv = load_data_bytes(args.ivfile)
        plaintext = load_data_bytes(args.plainfile)

        sign = sm2_sign_with_sm3(plaintext, private_key)
        sign_path = new_sign_path(args.cipherfile)
        save_data_bytes(sign_path, sign.encode('utf-8'))  # str to bytes
        ciphertext = sm4_encrypt(plaintext, key, iv)
        save_data_bytes(args.cipherfile, ciphertext)

        print('Encryption completed! Ciphertext and sign saved!')

    # 发送方使用接收方的SM2公钥对SM4密钥进行加密
    elif args.plainfile and not args.kfile and not args.ivfile and args.pkfile \
            and not args.skfile and args.cipherfile and not args.signfile:
        public_key = load_data_bytes(args.pkfile)
        data = load_data_bytes(args.plainfile)
        cipher = sm2_encrypt(data, public_key)
        save_data_bytes(args.cipherfile, cipher)

    # 接收方使用自己的SM2私钥对加密后的SM4密钥进行解密
    elif args.plainfile and not args.kfile and not args.ivfile and not args.pkfile \
            and args.skfile and args.cipherfile and not args.signfile:
        private_key = load_data_bytes(args.skfile)
        data = load_data_bytes(args.cipherfile)
        cipher = sm2_decrypt(data, private_key)
        save_data_bytes(args.plainfile, cipher)

        print('Decrypted data saved!')

    # 接收方使用SM4进行文件解密
    elif args.plainfile and args.kfile and args.ivfile and not args.pkfile \
            and not args.skfile and args.cipherfile and not args.signfile:
        key = load_data_bytes(args.kfile)
        iv = load_data_bytes(args.ivfile)
        ciphertext = load_data_bytes(args.cipherfile)

        plaintext = sm4_decrypt(ciphertext, key, iv)
        save_data_bytes(args.plainfile, plaintext)

        print('Decryption completed and plaintext saved!')

    # 签名验证
    elif args.plainfile and not args.kfile and not args.ivfile and args.pkfile \
            and not args.skfile and not args.cipherfile and args.signfile:
        public_key = load_data_bytes(args.pkfile)
        decrypted_data = load_data_bytes(args.plainfile)
        sign = load_data_bytes(args.signfile)

        sm2_verify_sign(public_key, sign, decrypted_data)

    else:
        print('Error: need right parameters, see it in README.', file=sys.stderr)
        sys.exit(1)


if __name__ == '__main__':
    main()
