/*
 * \file    main.cpp
 * \brief  
 * \details
 * \author  conquistador
 */

#include "tools.h"
#include <arpa/inet.h>

using namespace std;
using namespace conq_tools;

TICKET_FN(223)
{
	cout << "#" << ticket << ": endian independed htons, htonl, ntohs, ntohl\n";
	cout << "current platform is " <<
	        (Endian :: checkEndian() == Endian :: Type :: LittleEndian ? "little" : "big") << " endian\n";

	uint16_t v16 = 0xFFAA;
	uint32_t v32 = 0xFFAA1122;

	cout << "test of two values 2 bytes = 0x" << hex << v16 << ", 4 bytes = 0x" << hex << v32 << endl;

	uint32_t orig_be_v32 = htonl(v32);
	uint16_t orig_be_v16 = htons(v16);

	cout << "orig htons / htonl 2 bytes = 0x" << hex << orig_be_v16 << ", 4 bytes = 0x" << hex << orig_be_v32 << endl;

	uint32_t be_v32 = Endian :: htonl(v32);
	uint16_t be_v16 = Endian :: htons(v16);

	cout << "test htons / htonl 2 bytes = 0x" << hex << be_v16 << ", 4 bytes = 0x" << hex << be_v32 << endl;

	orig_be_v32 = ntohl(orig_be_v32);
	orig_be_v16 = ntohs(orig_be_v16);

	cout << "orig ntohs / ntohl 2 bytes = 0x" << hex << orig_be_v16 << ", 4 bytes = 0x" << hex << orig_be_v32 << endl;

	be_v32 = Endian :: ntohl(be_v32);
	be_v16 = Endian :: ntohs(be_v16);

	cout << "test ntohs / ntohl 2 bytes = 0x" << hex << be_v16 << ", 4 bytes = 0x" << hex << be_v32 << endl;
}

int main(int argc, char * argv[])
{
	ticket_223(argc, argv);

	return 0;
}
