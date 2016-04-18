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


void KeyPair::setPrivateKey(const RSA::PrivateKey& cle)
{
	privateKey = cle;
}
void KeyPair::setPublicKey(const RSA::PublicKey& cle) {
	publicKey = cle;
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
		std::cerr << "Erreur while encrypting a string";
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
		throw "erreur while decrypting ";
	}

	return		pl_text;
}




void KeyPair::Save(const string& filename, const CryptoPP::BufferedTransformation& bt)
{
	FileSink file(filename.c_str());

	bt.CopyTo(file);
	file.MessageEnd();
}

void KeyPair::savePrivateKey(const string& filename, const RSA::PrivateKey& key)
{
	CryptoPP::ByteQueue queue;
	key.Save(queue);
	Save(filename, queue);
}

void KeyPair::savePublicKey(const string& filename, const RSA::PublicKey& key) {
	CryptoPP::ByteQueue queue;
	key.Save(queue);
	Save(filename, queue);
}





void KeyPair::Load(const string& filename, CryptoPP::BufferedTransformation& bt)
{
	FileSource file(filename.c_str(), true /*pumpAll*/);

	file.TransferTo(bt);
	bt.MessageEnd();
}

bool KeyPair::loadPrivateKey(const string& filename, RSA::PrivateKey& key)
{
	CryptoPP::ByteQueue queue;
	Load(filename, queue);
	key.Load(queue);
}

bool KeyPair::loadPublicKey(const string& filename, RSA::PublicKey& key)
{
	CryptoPP::ByteQueue queue;
	Load(filename, queue);
	key.Load(queue);
}