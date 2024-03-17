extends Control

const mainMenu : String = "res://Scenes/mainMenu.tscn"
const m_handleID : Prot.Top = Prot.Top.Lobby

var defaultLobbyListItem = preload("res://Scenes/defaultLobbyListItem.tscn")
@onready var userName = $MarginContainer/HBoxContainer/VBoxContainer2/VBoxContainer2/UserName
@onready var refreshbutton = $MarginContainer/HBoxContainer/LobbyListVBox/HBoxContainer/Refresh
@onready var createLobby = $MarginContainer/HBoxContainer/VBoxContainer2/VBoxContainer/CreateLobby
@onready var lobbyListVBox = $MarginContainer/HBoxContainer/LobbyListVBox/ScrollContainer/VBoxContainer
@onready var createLobbyName = $MarginContainer/HBoxContainer/VBoxContainer2/VBoxContainer/NewLobbyName
@onready var newLobbyCapacity = $MarginContainer/HBoxContainer/VBoxContainer2/VBoxContainer/NewLobbyCapacity


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
	SendCreateLobby(createLobbyName.text, int(newLobbyCapacity.text))
	
	createLobby.disabled = false


func SendCreateLobby(name : String, capacity : int) ->void:
	var packet : PacketOut = PacketOut.new(0, ENetPacketPeer.FLAG_RELIABLE)
	
	var str : String = ""
	str += "{"
	str += name
	str += "}"
	
	str += "{"
	str += str(capacity)
	str += "}"
	
	packet.SetData(str, Prot.Top.Lobby, Prot.Lobby.LobbyCreated)
	PacketDispatcher.PutPacket(packet)

func ClearLobbyList() -> void:
	for child in lobbyListVBox.get_children(false):
		lobbyListVBox.remove_child(child)
		child.queue_free()

func SetLobbyList(packedLobbyList : String) ->void:
	var arr : PackedStringArray = parseLobbyList(packedLobbyList)
	
	for count in range (arr.size()/4):
		var lobbyName : String = arr[count * 4]
		var playerCount : int = int(arr[count * 4 +1])
		var capacity : int = int(arr[count * 4 + 2])
		var m_isSealed : bool = int(arr[count * 4 + 3])
		
		var lobbyListItem = defaultLobbyListItem.instantiate()
		lobbyListVBox.add_child(lobbyListItem)
		lobbyListItem.init(lobbyName, playerCount, capacity, m_isSealed)

func parseLobbyList(packedLobbylist : String) ->PackedStringArray:
	var arr : Array[String] = []
	
	var count : int = packedLobbylist.countn("{", 0,0)
	
	var beginPos : int = 0
	var endPos : int = 0
	for index in count:
		beginPos = packedLobbylist.find("{", endPos)
		endPos = packedLobbylist.find("}", beginPos)
		var str : String = packedLobbylist.substr(beginPos + 1, endPos - (beginPos + 1))
		arr.push_back(str)
	
	return arr


func Handle(packet : PacketIn) ->void:
	
	match packet.m_subProt:
		Prot.Lobby.LobbyCreated:
			#Change Scene
			pass
		Prot.Lobby.LobbyList:
			ClearLobbyList()
			SetLobbyList(packet.m_data)
		Prot.Lobby.LobbyJoin:
			pass
		Prot.Lobby.LobbyLeft:
			pass


func _on_new_lobby_name_text_submitted(new_text):
	createLobbyName.shortcut_keys_enabled = false
	SendCreateLobby(new_text, int(newLobbyCapacity.text))
	createLobbyName.shortcut_keys_enabled = true
