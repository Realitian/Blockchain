#ifndef KEY_H_
#define KEY_H_

#include "../../libs/cryptocpp/cryptopp/rsa.h"
using CryptoPP::RSA;
using CryptoPP::InvertibleRSAFunction;
using CryptoPP::RSAES_OAEP_SHA_Encryptor;
using CryptoPP::RSAES_OAEP_SHA_Decryptor;

#include "../../libs/cryptocpp/cryptopp/sha.h"
using CryptoPP::SHA1;

#include "cryptopp\filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::PK_EncryptorFilter;
using CryptoPP::PK_DecryptorFilter;

#include "../../libs/cryptocpp/cryptopp/files.h"
using CryptoPP::FileSink;
using CryptoPP::FileSource;

#include "../../libs/cryptocpp/cryptopp/\osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include "../../libs/cryptocpp/cryptopp/SecBlock.h"
using CryptoPP::SecByteBlock;

#include "../../libs/cryptocpp/cryptopp/cryptlib.h"
using CryptoPP::Exception;
using CryptoPP::DecodingResult;
using CryptoPP::
#include <string>
using std::string;

#include <exception>
using std::exception;

class Key
{
private:
public:
	Key() :
		modulus(0),
		exponent(0)
	{

	}
	Key(const BigInteger &modulus, const BigInteger &exponent) :
		modulus(modulus), exponent(exponent)
	{

	}

	Key(const Key& rhs) :
		modulus(rhs.modulus),
		exponent(rhs.exponent)
	{

	}

	const BigInteger &GetModulus() const
	{
		return modulus;
	}
	const BigInteger &GetExponent() const
	{
		return exponent;
	}
};

#endif /*KEY_H_*/
