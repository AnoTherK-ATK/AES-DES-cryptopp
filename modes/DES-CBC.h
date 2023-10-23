#ifndef __DES_CBC_H__
#define __DES_CBC_H__
#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

#include "cryptopp/cryptlib.h"
using CryptoPP::Exception;

#include "cryptopp/hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "cryptopp/filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include "cryptopp/aes.h"
using CryptoPP::AES;

#include "cryptopp/ccm.h"
using CryptoPP::CBC_Mode;
using CryptoPP::byte;
using CryptoPP::SecByteBlock;
#include <assert.h>

class CBC{
public:
	CBC(){}
	string encrypt(const string &plain, string skey, string siv){
		string cipher;
		SecByteBlock key(reinterpret_cast<const CryptoPP::byte*>(&skey[0]), skey.size());
		SecByteBlock iv(reinterpret_cast<const CryptoPP::byte*>(&siv[0]), siv.size());
		CBC_Mode< DES >::Encryption e;
		e.SetKeyWithIV(key, key.size(), iv, iv.size());
		StringSource s(plain, true, 
			new StreamTransformationFilter(e,
				new StringSink(cipher)
			)    
		); 
		return cipher;
	}
	string decrypt(const string &cipher, string skey, string siv){
		string recovered;
		SecByteBlock key(reinterpret_cast<const CryptoPP::byte*>(&skey[0]), skey.size());
		SecByteBlock iv(reinterpret_cast<const CryptoPP::byte*>(&siv[0]), siv.size());
		CBC_Mode< DES >::Decryption d;
		d.SetKeyWithIV(key, key.size(), iv, iv.size());
		StringSource s(cipher, true, 
			new StreamTransformationFilter(d,
				new StringSink(recovered)
			)    
		); 
		return recovered;
	}
};
#endif