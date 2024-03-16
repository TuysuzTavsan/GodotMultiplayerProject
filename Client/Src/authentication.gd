extends Control

@onready var connectButton = $MarginContainer/VBoxContainer/Connectbutton
@onready var textEdit = $MarginContainer/VBoxContainer/TextEdit
const popUp = preload("res://Scenes/popUp.tscn")
const lobbyMenu : String = "res://Scenes/lobbyMenu.tscn"
var feedbackFlag : bool = false


func _ready():
	var popup = popUp.instantiate()
	add_child(popup)
	popup.init("Connected", true, 0.0)
	
	Client.unhandledPacketReceived.connect(_packetReceived)


func _on_quit_button_pressed():
	get_tree().quit(0)

func _on_return_button_pressed():
	SceneLoader.Load("Scenes/mainMenu.tscn", true)

func _on_connectbutton_pressed():
	textEdit.shortcut_keys_enabled = false
	connectButton.disabled = true
	authenticate()
	textEdit.shortcut_keys_enabled = true
	connectButton.disabled = false

func _on_text_edit_text_submitted(text):
	textEdit.shortcut_keys_enabled = false
	connectButton.disabled = true
	authenticate()
	textEdit.shortcut_keys_enabled = true
	connectButton.disabled = false

func authenticate():
	var pckt : PacketOut = PacketOut.new(0, ENetPacketPeer.FLAG_RELIABLE)
	pckt.SetData("", Prot.Top.Distribute, Prot.Distribute.lobby)
	
	var str : String = textEdit.text
	var pckt2 : PacketOut = PacketOut.new(0, ENetPacketPeer.FLAG_RELIABLE)
	pckt2.SetData(str, Prot.Top.User, Prot.User.UserNameSubmit)
	
	PacketDispatcher.PutPacket(pckt2)
	PacketDispatcher.PutPacket(pckt)
	
	var popup = popUp.instantiate()
	add_child(popup)
	popup.init("Waiting server feedback", false, 0.0)
	
	var tempstr : String= "Waiting server feedback"
	var animatorCount : int = 0
	
	
	# Wait for server feedback to jump on lobby menu.
	
	for i in range (13):
		await get_tree().create_timer(1).timeout
		
		tempstr += "."
		animatorCount +=1
		if(animatorCount == 5):
			tempstr = "Waiting server feedback"
		popup.setmsg(tempstr)
		
		if(feedbackFlag):
			SceneLoader.Load(lobbyMenu, true)
	
	remove_child(popup)
	
	var popup2 = popUp.instantiate()
	add_child(popup2)
	popup2.init("Server did not respond", true, 0.0)

func _packetReceived(packet : PacketIn):
	if(packet.m_topProt == Prot.Top.Distribute && packet.m_subProt == Prot.Distribute.lobby):
		feedbackFlag = true
