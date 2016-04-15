#include "KeyPair.h"

KeyPair::KeyPair(const RSA::PublicKey& pbkey, const RSA::PrivateKey& prkey) :
	publicKey(pbkey),
	privateKey(prkey)
{
}

KeyPair::KeyPair() :
	publicKey(), privateKey()
{
	AutoSeededRandomPool rng;

	InvertibleRSAFunction parameters;
	parameters.GenerateRandomWithKeySize(rng, 1024);
	publicKey = RSA::PublicKey(parameters);
	privateKey = RSA::PrivateKey(parameters);
}

KeyPair::KeyPair(const KeyPair& rhs) :
	publicKey(rhs.publicKey), privateKey(rhs.privateKey)
{

}


string KeyPair::encrypt(string message) {
	AutoSeededRandomPool rng;
	string cipher;
	RSAES_OAEP_SHA_Encryptor e(publicKey);
	try {
		StringSource ss(message, true,
			new PK_EncryptorFilter(rng, e,
				new StringSink(cipher)
			)
		);
	}
	catch (std::exception e) {
		std::cerr << "Erreur encryption";
	}

	return cipher;
}
string KeyPair::decrypt(string cipher) {
	AutoSeededRandomPool rng;
	string pl_text;
	try {
		RSAES_OAEP_SHA_Decryptor d(privateKey);
		StringSource(cipher, true,
			new PK_DecryptorFilter(rng, d,
				new StringSink(pl_text)
			)
		);
	}
	catch (...) {

	}

	return		pl_text;
}


