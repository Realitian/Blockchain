#include "Message.h"



//!
//! \brief Construct a Message that will be loaded into a Transaction
//!
//! \param : _domainName The DomainName require
//! \param : _info The info towards the Domain Name
//! \param : keypair The pair of Key loaded into the Message to check the authenticity of the sender
//! \return :
//!
Message::Message(string _domainName, string _info, const KeyPair& keypair) :
	nom_de_domaine(_domainName), information(_info), hashDomainName(SHA25::sha256(nom_de_domaine)), publicKey(keypair.getClePublique()),
	longueurMessage(nom_de_domaine.size() + information.size() + hashDomainName.size())
{
	sign(keypair.getPrivateKey());
}


Message::~Message()
{
}


string Message::getNomDomaine() const {
	return nom_de_domaine;
}
string Message::getinformation() const {
	return information;
}
string Message::getHashDomainName() const {
	return hashDomainName;
}
RSA::PublicKey Message::getPublicKey() const
{
	return publicKey;
}

//!
//! \brief Check the authenticity of the Message
//!
//! \return :bool True if the message is Correct
//!
bool Message::verifier() const
{
	CryptoPP::RSASSA_PKCS1v15_SHA_Verifier verifier(publicKey);
	string message = nom_de_domaine + information;
	// Verify
	bool result = verifier.VerifyMessage((const byte*)message.c_str(),
		message.length(), signature, signature.size());
	return result;
}

//!
//! \brief Sign the message with the Private Key of the sender
//! 
//! \param : privateKey The private Key of the Sender
//! \return :SecByteBlock The signature of the Message
//!
SecByteBlock Message::sign(RSA::PrivateKey& privateKey) {

	AutoSeededRandomPool rng;
	CryptoPP::RSASSA_PKCS1v15_SHA_Signer signer(privateKey);
	size_t length = signer.MaxSignatureLength();
	signature = SecByteBlock(length);

	// Sign message
	string message = nom_de_domaine + information;
	length = signer.SignMessage(rng, (const byte*)message.c_str(),
		message.length(), signature);
	signature.resize(length);
	signature = SecByteBlock(signature.data(), signature.size());
	return signature;
}