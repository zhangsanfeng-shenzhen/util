/*******************************************************************************************
 *  961338985@qq.com
 *  Compilation Command: gcc -o rsa rsa.c -fPIC -shared -lssl -lcrypto 
 *******************************************************************************************/

#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>

const int padding = RSA_PKCS1_OAEP_PADDING;

int public_encrypt(unsigned char* data, int data_len, unsigned char* key, unsigned char* encrypted)
{
    int ret = -1;
    BIO* keybio = BIO_new_mem_buf(key, -1);
    if (keybio != NULL) {
        RSA* rsa = NULL;
        rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
        if (rsa != NULL) {
            ret = RSA_public_encrypt(data_len, data, encrypted, rsa, padding);
            RSA_free(rsa);
        }
        BIO_free_all(keybio);
    }
    return ret;
}

int private_decrypt(unsigned char* enc_data, int data_len, unsigned char* key, unsigned char* decrypted)
{
    int ret = -1;
    BIO* keybio = BIO_new_mem_buf(key, -1);
    if (keybio != NULL) {
        RSA* rsa = NULL;
        rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
        if (rsa != NULL) {
            ret = RSA_private_decrypt(data_len, enc_data, decrypted, rsa, padding);
            RSA_free(rsa);
        }
        BIO_free_all(keybio);
    }
    return ret;
}

int main()
{
	int len,i;
	unsigned char *data="fghfghdfhfdhfg";
	unsigned char key[1024*10];
	unsigned char encrypted[1024*10];
	unsigned char en[1024*10];

    FILE *fp;
    char ch;
	fp = fopen("/tmp/test_pub.key","r");
    if(fp == NULL) {
        printf("file cannot open \n");
		exit(0);
    }
	i=0;
    while((ch=fgetc(fp))!=EOF)
        key[i++]=ch;
    fclose(fp);

	//printf("key:%s",key);
	len = public_encrypt(data, strlen(data), key, encrypted);
	if (len != -1) {
		for(i=0;i<len;i++) {
			printf("%02x",encrypted[i]);
		}
	}

	fp = fopen("/tmp/test.key","r");
    if(fp == NULL) {
        printf("file cannot open \n");
		exit(0);
    }
	i=0;
    while((ch=fgetc(fp))!=EOF)
        key[i++]=ch;
    fclose(fp);

	len = private_decrypt(encrypted, len, key, en);
	printf("\nstr:%s    %d\n",en,len);
    return 0;
}
