#include "Message.h"


//************************************
// Method:    Message
// FullName:  Message::Message
// Access:    public 
// Returns:   
// Qualifier: : nom_de_domaine(_domainName), information(_info), hashDomainName(SHA25::sha256(nom_de_domaine)), publicKey(keypair.getClePublique()), longueurMessage(nom_de_domaine.size() + information.size() + hashDomainName.size()), signature(sign(keypair.getPrivateKey()))
// Parameter: string _domainName
// Parameter: string _info
// Parameter: const KeyPair & keypair
//************************************
Message::Message(string _domainName, string _info, const KeyPair& keypair) :
	nom_de_domaine(_domainName), information(_info), hashDomainName(SHA25::sha256(nom_de_domaine)), publicKey(keypair.getClePublique()),
	longueurMessage(nom_de_domaine.size() + information.size() + hashDomainName.size()),
	signature(sign(keypair.getPrivateKey()))
{
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

bool Message::verifier() const
{
	CryptoPP::RSASSA_PKCS1v15_SHA_Verifier verifier(publicKey);
	string message = nom_de_domaine + information;
	// Verify
	bool result = verifier.VerifyMessage((const byte*)message.c_str(),
		message.length(), signature, signature.size());
	return result;
}

SecByteBlock Message::sign(RSA::PrivateKey& privateKey) {

	AutoSeededRandomPool rng;
	CryptoPP::RSASSA_PKCS1v15_SHA_Signer signer(privateKey);
	size_t length = signer.MaxSignatureLength();
	SecByteBlock sig(length);

	// Sign message
	string message = nom_de_domaine + information;
	length = signer.SignMessage(rng, (const byte*)message.c_str(),
		message.length(), sig);
	sig.resize(length);
	sig = SecByteBlock(sig.data(), sig.size());
	return sig;
}