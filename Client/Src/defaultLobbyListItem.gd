extends Control

@onready var lobbyID = $DefaultLobbyHBox/LobbyID
@onready var players = $DefaultLobbyHBox/Players
@onready var status = $DefaultLobbyHBox/Status

func init(lobbyName : String, playerCapacity : int, playerCount : int, state : bool):
	lobbyID.text = lobbyName
	
	if(state == true):
		status.text = "Open"
	else:
		status.text = "Closed"
	
	players.text = str(playerCapacity) + "/" + str(playerCount)

func _on_join_pressed():
	var packet : PacketOut = PacketOut.new(0, ENetPacketPeer.FLAG_RELIABLE)
	packet.SetData(lobbyID.text, Prot.Top.Lobby, Prot.Lobby.LobbyJoin)
	PacketDispatcher.PutPacket(packet)
	
	pass # Replace with function body.
