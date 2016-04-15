#ifndef KEY_H_
#define KEY_H_

#include "cryptopp\rsa.h"
using CryptoPP::RSA;
using CryptoPP::InvertibleRSAFunction;
using CryptoPP::RSAES_OAEP_SHA_Encryptor;
using CryptoPP::RSAES_OAEP_SHA_Decryptor;

#include "cryptopp\sha.h"
using CryptoPP::SHA1;

#include "cryptopp\filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::PK_EncryptorFilter;
using CryptoPP::PK_DecryptorFilter;

#include "cryptopp\files.h"
using CryptoPP::FileSink;
using CryptoPP::FileSource;

#include "cryptopp\osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include "cryptopp\SecBlock.h"
using CryptoPP::SecByteBlock;

#include "cryptopp\cryptlib.h"
using CryptoPP::Exception;
using CryptoPP::DecodingResult;

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
