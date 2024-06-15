#include <stdio.h>

// "flag{who_DOeSNT_LiKE_a_FREE_NegRonI}\n"
unsigned char FLAG[] = {0xe,  0x1,  0x13, 0x10, 0x7,  0xf6, 0xee, 0xe4, 0xcf, 0xd1,
                        0xd5, 0xfa, 0xf7, 0xe7, 0xfa, 0xec, 0xf4, 0xd4, 0x89, 0x82,
                        0x93, 0xb0, 0x89, 0x9d, 0xb2, 0xa0, 0xaf, 0xb0, 0xba, 0x9c,
                        0x99, 0x56, 0x66, 0x60, 0x5a, 0x65, 0x17};

// "Enter username: "
unsigned char ENTER_USERNAME[] =
    {0x2d, 0x3, 0x6, 0x12, 0xe, 0xa1, 0xf3, 0xf8, 0xf5, 0xe7, 0xf4, 0xfe, 0xc9, 0xcc, 0x94, 0x93};

// "Enter password: "
unsigned char ENTER_PASSWORD[] =
    {0x2d, 0x3, 0x6, 0x12, 0xe, 0xa1, 0xf6, 0xea, 0xe3, 0xe6, 0xed, 0xf0, 0xd6, 0xcd, 0x94, 0x93};

// "Access Granted! Enjoy your free drink!\n"
unsigned char ACCESS_GRANTED[] = {0x29, 0xe,  0x11, 0x12, 0xf,  0xf2, 0xa6, 0xcc, 0xe2, 0xf4,
                                  0xf4, 0xeb, 0xc1, 0xcd, 0x8f, 0x93, 0xfd, 0xd3, 0xa8, 0xa8,
                                  0xb5, 0xf1, 0xaf, 0xb4, 0x95, 0x97, 0xca, 0x89, 0x86, 0x9c,
                                  0x9b, 0x24, 0x6d, 0x7c, 0x7a, 0x76, 0x76, 0x3,  0x2d};

// "Access Denied! Incorrect username or password.\n"
unsigned char ACCESS_DENIED[] = {0x29, 0xe,  0x11, 0x12, 0xf,  0xf2, 0xa6, 0xcf, 0xf5, 0xfb,
                                 0xf3, 0xfa, 0xc0, 0x88, 0x8e, 0xfa, 0xd6, 0xde, 0xad, 0xb5,
                                 0xbe, 0xb4, 0xb5, 0xaf, 0xc0, 0x90, 0x99, 0x8a, 0x86, 0x97,
                                 0x9f, 0x69, 0x6c, 0x2e, 0x7c, 0x6a, 0x3d, 0x52, 0x46, 0x5f,
                                 0x42, 0x41, 0x54, 0x32, 0x21, 0x64, 0x45};

/**
 * @brief a simple djb2 hash function with a non-standard seed of 7741
 *
 * @param[in] str the string to hash
 */
unsigned long djb2(const char *str) {
    unsigned long hash = 7741;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

/**
 * @brief decrypt the encoded bytes with rolling xor and print each character
 *
 * @param[in] encrypted the reference to the encrypted bytes
 * @param[in] len length of the encrypted bytes
 * @param[in] key the initial key to decrypt the first byte
 */
void rolling_xor_decrypt_and_println(const unsigned char *encrypted, int len, unsigned char key) {
    int i;
    for (i = 0; i < len; i++) {
        putchar(encrypted[i] ^ key);
        key = (key + 5) % 0xFF;
    }
}

int main() {
    char username[256];
    char password[256];
    unsigned long username_hash, password_hash;

    // djb2 hash of "Lom Tevasseur\n"
    unsigned long expected_username_hash = 967993393;

    // djb2 hash of "Ihopewegetmoresponsorsnextyear\n"
    unsigned long expected_password_hash = 2248063266;

    // Enter username:
    rolling_xor_decrypt_and_println(ENTER_USERNAME, sizeof(ENTER_USERNAME), 0x68);
    fgets(username, sizeof(username), stdin);

    // Enter password:
    rolling_xor_decrypt_and_println(ENTER_PASSWORD, sizeof(ENTER_PASSWORD), 0x68);
    fgets(password, sizeof(password), stdin);

    // calculate the hash of the username and password
    username_hash = djb2(username);
    password_hash = djb2(password);

    if (username_hash == expected_username_hash && password_hash == expected_password_hash) {
        rolling_xor_decrypt_and_println(ACCESS_GRANTED, sizeof(ACCESS_GRANTED), 0x68);
        rolling_xor_decrypt_and_println(FLAG, sizeof(FLAG), 0x68);
    } else {
        rolling_xor_decrypt_and_println(ACCESS_DENIED, sizeof(ACCESS_DENIED), 0x68);
        return 1;
    }

    return 0;
}
