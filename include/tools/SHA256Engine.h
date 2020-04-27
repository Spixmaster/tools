#ifndef TOOLS_SHA256ENGINE_H
#define TOOLS_SHA256ENGINE_H

#include <Poco/Crypto/DigestEngine.h>
#include <memory>


namespace tools
{
	/**
	 * @class SHA256Engine
	 * @brief A simple help class that is only needed due to Poco
	 */
	class SHA256Engine : public Poco::Crypto::DigestEngine
	{
	public:
		//Pointer of itself
		/**
		 * @var ptr
		 * @brief A pointer of itself
		 */
		typedef std::shared_ptr<SHA256Engine> ptr;

		//Member variables
		enum
		{
			BLOCK_SIZE = 64,
			DIGEST_SIZE = 32
		};

		//Constructors
		SHA256Engine() : DigestEngine("SHA256")
		{}
	};
}

#endif
