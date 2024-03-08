#include <parser.h>

#include <protocol.h>
#include <locator.h>

/* Section NULLParser starts */

void NULLParser::Handle(ClientID peer, std::unique_ptr<char>&& data, size_t size)
{
	/*Do nothing*/
	std::cout << "[NULLParser is Provided]\n";
}

/* Section NULLParser ends */

Parser::Parser()
{

}

Parser::~Parser()
{

}

void Parser::Handle(ClientID peer, std::unique_ptr<char>&& data, size_t size)
{
	std::string _data;

	_data.assign(data.get());

	Protocol _protocol(_data);


	switch (_protocol.m_topProt)
	{
	case TopProtocol::Core:
		break;

	case TopProtocol::Lobby:
		
		Locator::GetLobbyHandler().InputMsg(_protocol, std::move(data));

		break;

	case TopProtocol::Game:
		break;

	case TopProtocol::Physics:
		break;
		
	}


}