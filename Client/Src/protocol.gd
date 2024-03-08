class_name Protocol
enum Top
{
	Unspecified,
	Core,
	Lobby,
	Game,
	Physics
}


#FORMAT: {TopProtocol}{SubProtocol}{Actual Data}

enum CoreProt
{
	UserName
};

enum LobbyProt
{
	LobbyEntered,
	LobbyLeft,
	LobbyCreated,
	LobbyOwnerChanged,
	LobbyMessageReceived,
	LobbyMessageSent
};

enum GameProt
{

};

enum PhysicsProt
{

};



# type id data
