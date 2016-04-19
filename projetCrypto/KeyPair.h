#ifndef KEYPAIR_H_
#define KEYPAIR_H_

#define SIZE_KEY 160

#include <vector>
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

#ifndef SIZE_KEY
#define SIZE_KEY 1024
#endif // !SIZE_KEY


class KeyPair
{
public:
	KeyPair();
	KeyPair(const RSA::PublicKey&, const RSA::PrivateKey&);
	KeyPair(const KeyPair&);

	RSA::PublicKey getClePublique() const
	{
		return publicKey;
	}
	RSA::PrivateKey getPrivateKey() const
	{
		return privateKey;
	}

	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		string aa, bb, cc, dd;
		aa = boost::lexical_cast<std::string>(privateKey.GetPrivateExponent());
		bb = boost::lexical_cast<std::string>(privateKey.GetModulus());
		cc = boost::lexical_cast<std::string>(publicKey.GetPublicExponent());
		aa = boost::lexical_cast<std::string>(publicKey.GetModulus());
		ar & aa & bb & cc & dd;
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		string aa, bb, cc, dd;
		ar & aa & bb & cc & dd;
		privateKey.SetPrivateExponent(CryptoPP::Integer( aa.c_str()));
		privateKey.SetModulus(CryptoPP::Integer(bb.c_str()));
		publicKey.SetPublicExponent(CryptoPP::Integer(cc.c_str()));
		publicKey.SetModulus(CryptoPP::Integer(dd.c_str()));
	}

	template<class Archive>
	void serialize(
		Archive & ar,
		const unsigned int file_version
	) {
		boost::serialization::split_member(ar, *this, file_version);
	}

	void setPrivateKey(const RSA::PrivateKey&);
	void setPublicKey(const RSA::PublicKey&);
	string encrypt(string);
	string decrypt(string);
	void reGenerate() {};

	static void savePrivateKey(const string& filename, const RSA::PrivateKey& key);
	static void savePublicKey(const string& filename, const RSA::PublicKey& key);
	static bool loadPrivateKey(const string& filename, RSA::PrivateKey& key);		// TODO pensez a verifier si le chargement s'est bien passe , si le fichier existati
	static bool loadPublicKey(const string& filename, RSA::PublicKey& key);

private:
	static void Save(const string& filename, const CryptoPP::BufferedTransformation& bt);
	static void Load(const string& filename, CryptoPP::BufferedTransformation& bt);

	RSA::PrivateKey privateKey;
	RSA::PublicKey publicKey;

};
#endif