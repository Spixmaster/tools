#ifndef TOOLS_SHA256ENGINE_H
#define TOOLS_SHA256ENGINE_H

#include <Poco/Crypto/DigestEngine.h>

class SHA256Engine : public Poco::Crypto::DigestEngine
{
public:
	//pointer of itself
	typedef std::shared_ptr<SHA256Engine> ptr;

	//member variables
	enum
	{
		BLOCK_SIZE = 64,
		DIGEST_SIZE = 32
	};

	//constructors
	SHA256Engine() : DigestEngine("SHA256")
	{}
};

#endif
