extends Control

const mainMenu : String = "res://Scenes/mainMenu.tscn"
const m_handleID : Prot.Top = Prot.Top.Lobby

var defaultLobbyListItem = preload("res://Scenes/defaultLobbyListItem.tscn")
@onready var userName = $MarginContainer/HBoxContainer/VBoxContainer2/VBoxContainer2/UserName
@onready var refreshbutton = $MarginContainer/HBoxContainer/LobbyListVBox/HBoxContainer/Refresh
@onready var createLobby = $MarginContainer/HBoxContainer/VBoxContainer2/VBoxContainer/CreateLobby
@onready var createLobbyName = $MarginContainer/HBoxContainer/VBoxContainer2/VBoxContainer/LobbyName
@onready var lobbyListVBox = $MarginContainer/HBoxContainer/LobbyListVBox


func _ready():
	PacketHandler.Subscribe(m_handleID, self)
	userName.text = User.m_userName

func _on_return_pressed():
	SceneLoader.Load(mainMenu, true)

func _on_refresh_pressed():
	refreshbutton.disabled = true
	# Send message to server.
	var packet : PacketOut = PacketOut.new(0, ENetPacketPeer.FLAG_RELIABLE)
	packet.SetData("", Prot.Top.Lobby, Prot.Lobby.LobbyList)
	PacketDispatcher.PutPacket(packet)
	
	
	refreshbutton.disabled = false



func _on_create_lobby_pressed():
	createLobby.disabled = true
	# Send message to server.
	var packet : PacketOut = PacketOut.new(0, ENetPacketPeer.FLAG_RELIABLE)
	packet.SetData(createLobbyName.text, Prot.Top.Lobby, Prot.Lobby.LobbyCreated)
	PacketDispatcher.PutPacket(packet)
	
	#createLobby.disabled = false


func SetLobbyList(packedLobbyList : String) ->void:
	#Parse data
	
	#Clear Already existing List.
	
	
	var packedStrArray : PackedStringArray = packedLobbyList.split("}", true)
	
	for lobby in packedStrArray:
		var lobbyName : String = lobby.substr(1, -1)
		
		var lobbyListItem = defaultLobbyListItem.instantiate()
		lobbyListVBox.add_child(lobbyListItem)
		lobbyListItem.init(lobbyName, 8, 12, true)


func Handle(packet : PacketIn) ->void:
	
	match packet.m_subProt:
		Prot.Lobby.LobbyCreated:
			#Change Scene
			pass
		Prot.Lobby.LobbyList:
			SetLobbyList(packet.m_data)
		Prot.Lobby.LobbyJoin:
			pass
		Prot.Lobby.LobbyLeft:
			pass
