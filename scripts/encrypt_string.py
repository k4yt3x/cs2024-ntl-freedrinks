#!/usr/bin/python


def rolling_xor_encrypt(text: str, key):
    data = text.encode("utf-8")

    encrypted = bytearray()
    for b in data:
        encrypted.append(b ^ key)
        key = (key + 5) % 0xFF
        print(f"key: {key:02x}")

    return bytes(encrypted)


def main():
    string = input("String to encrypt: ")
    string = string.replace("\\n", "\n")
    xor_encrypted = rolling_xor_encrypt(string, 0x68)

    # print each byte of the encrypted string
    for byte in xor_encrypted:
        print(hex(byte), end=", ")


if __name__ == "__main__":
    main()
