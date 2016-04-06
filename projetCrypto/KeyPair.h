#define SIZE_KEY 160
#include <vector>
class KeyPair
{
public:
	KeyPair();
	~KeyPair();
	std::vector<unsigned char> getClePublique();
	std::vector<unsigned char> getPrivateKey();
	void reGenerate();
private:
	std::vector<unsigned char> cle_publique;
	std::vector<unsigned char> cle_privee;
};
