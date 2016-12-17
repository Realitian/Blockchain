#include "../../include/blockchain/KeyPair.h"

//!
//! \brief Constructor of a Keypair with Key already existing pair of Key
//!
//! \param : pbkey A RSA::PublicKey
//! \param : prkey A RSA::PrivateKey
//! \return :
//!
KeyPair::KeyPair(const RSA::PublicKey& pbrkey, const RSA::PrivateKey& prkey) :
	publicKey(pbrkey),
	privateKey(prkey)
{
}




//!
//! \brief Build a new Pair of Key
//!
//! \return :
//!
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

RSA::PublicKey KeyPair::getClePublique() const
{
	return publicKey;
}
RSA::PrivateKey KeyPair::getPrivateKey() const
{
	return privateKey;
}

//!
//! \brief Encrypt a message with the Keypair
//!
//! \param : message The message to encrypt
//! \return :string The encrypted message
//!
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
//!
//! \brief Decrypt a message with the KeyPair
//!
//! \param : cipher The cypher text
//! \return :string The original Message
//!
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





//!
//! \brief Private function for saving a Key
//!
//! \param : filename 
//! \param : bt 
//! \return :void
//!
void KeyPair::Save(const string& filename, const CryptoPP::BufferedTransformation& bt)
{

	FileSink file(filename.c_str());

	bt.CopyTo(file);
	file.MessageEnd();

}

//!
//! \brief Save a private Key in a file
//!
//! \param : filename The name of the file
//! \param : key The Private Key to save
//! \return :void
//!
void KeyPair::savePrivateKey(const string& filename, const RSA::PrivateKey& key)
{
	CryptoPP::ByteQueue queue;
	key.Save(queue);
	Save(filename, queue);
}

//!
//! \brief Save a public key in a file
//!
//! \param : filename The name of the file
//! \param : key The Public Key to Save
//! \return :void
//!
void KeyPair::savePublicKey(const string& filename, const RSA::PublicKey& key) {
	CryptoPP::ByteQueue queue;
	key.Save(queue);
	Save(filename, queue);
}





void KeyPair::Load(const string& filename, CryptoPP::BufferedTransformation& bt)
{

	try {
		FileSource file(filename.c_str(), true /*pumpAll*/);
		file.TransferTo(bt);
		bt.MessageEnd();
	}
	catch (FileSource::Err e)
	{
		return;
	}
	catch (...)
	{
		throw FileSource::Err::INVALID_ARGUMENT;
	}

}

//!
//! \brief Load a Private Key into a file
//!
//! \param : filename The name of the file
//! \param : key The Private Key that will be loaded
//! \return :bool
//!
bool KeyPair::loadPrivateKey(const string& filename, RSA::PrivateKey& key)
{
	try {
		CryptoPP::ByteQueue queue;
		Load(filename, queue);
		key.Load(queue);
		return true; // TODO
	}
	catch (std::exception e)
	{
		return false;
	}
	catch (...)
	{
		return false;
	}
}

//!
//! \brief Load a Private Key into a file
//!
//! \param : filename The name of the file
//! \param : key The Public Key that will be loaded
//! \return :bool
//!
bool KeyPair::loadPublicKey(const string& filename, RSA::PublicKey& key)
{
	try {
		CryptoPP::ByteQueue queue;
		Load(filename, queue);
		key.Load(queue);
		return true; // TODO
	}
	catch (std::exception e)
	{
		return false;
	}
	catch (...)
	{
		return false;
	}
}