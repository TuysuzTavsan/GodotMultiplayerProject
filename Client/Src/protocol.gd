class_name Prot


####
#FORMAT: {TopProtocol}{SubProtocol}{Data}
#TopProtocol will be used by the Parser to forward incoming packets.
#SubProtocol is meant to be used by the packet consumer class, example LobbyHandler.
####

enum Top
{
	Unspecified,
	Distribute,
	Lobby,
}

enum Lobby
{
	LobbyCreated
}

enum Distribute
{
	unspecified,
	lobby,
}
