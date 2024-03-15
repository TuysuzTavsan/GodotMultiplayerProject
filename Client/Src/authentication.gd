extends Control

@onready var textEdit = $MarginContainer/VBoxContainer/TextEdit
const popUp = preload("res://Scenes/popUp.tscn")
const lobbyMenu : String = "res://Scenes/lobbyMenu.tscn"

func _ready():
	var popup = popUp.instantiate()
	add_child(popup)
	popup.init("Connected", true, 0.0)

func _on_quit_button_pressed():
	get_tree().quit(0)

func _on_return_button_pressed():
	SceneLoader.Load("Scenes/mainMenu.tscn", true)

func _on_connectbutton_pressed():
	var str : String = textEdit.text
	var pckt : Packet = Packet.new(0, ENetPacketPeer.FLAG_RELIABLE)
	pckt.SetData(str, Prot.Top.Distribute, Prot.Distribute.lobby)
	PacketDispatcher.PutPacket(pckt)
	SceneLoader.Load(lobbyMenu, true)

func _on_text_edit_text_submitted(text):
	var pckt : Packet = Packet.new(0, ENetPacketPeer.FLAG_RELIABLE)
	pckt.SetData(text, Prot.Top.Distribute, Prot.Distribute.lobby)
	PacketDispatcher.PutPacket(pckt)
	SceneLoader.Load(lobbyMenu, true)
