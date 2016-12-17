#include "Transaction.h"

void testTransaction()
{
	Identite id("Franc", "Jerome");
	cout << "--------------------------Test identite --------------------------";
	cout << id.getNom() << " " << id.getPrenom() << endl;
	cout << "Affichage de la clé :" << endl;
	KeyPair p = id.getKeyPair();
	cout << "Cle publique : " << p.getClePublique().GetPublicExponent() << " " << p.getClePublique().GetModulus() << endl;
	cout << "ClePrivee :" << p.getPrivateKey().GetPrivateExponent() << endl;

	string nomDeDomaine = "facebook.com";
	string information = "retrouvez moi sur ounoenvoirnior.fr";
	Transaction t(id, nomDeDomaine, information);
	cout << "-------------------------- Test Transaction -------------------------- " << endl;
	cout << t.toString() << endl;
	std::shared_ptr<Message> message(t.getMessage());
	cout << t.getHashTransaction() << endl;

	cout << "--------------------------Test message --------------------------";
	cout << message->getHashDomainName() << " " << message->getinformation() << message->getNomDomaine() << endl;

	bool v = message->verifier();
	if (v) cout << "Message verifier";
	else cout << "Erreur dans la verification";
}
