#pragma once
#include <string>
#include "cryptopp\sha.h"
#include "cryptopp\hex.h"
using std::string;
//!
//! \class SHA25
//!
//! \brief Implement SHA256 functions
//!
//! \author Louis Henri Franc
//!
class SHA25
{
public:
	using SHA256Hash = CryptoPP::SHA256;
	
	static string sha256(string message) {
		CryptoPP::SHA256 hash;
		byte digest[CryptoPP::SHA256::DIGESTSIZE];
		hash.CalculateDigest(digest, (byte *)message.c_str(), message.length());

		CryptoPP::HexEncoder encoder;
		std::string sha;
		encoder.Attach(new CryptoPP::StringSink(sha));
		encoder.Put(digest, sizeof(digest));
		encoder.MessageEnd();
		return sha;
	}


	

};

