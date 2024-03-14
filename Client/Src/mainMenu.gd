extends Control

const popUp = preload("res://Scenes/popUp.tscn")
@onready var connectButton = $"MarginContainer/VBoxContainer/Connect To Server"

func _ready():
	Client.Reset()

func _on_quit_button_pressed():
	get_tree().quit(0)

func _on_playground_button_pressed():
	SceneLoader.Load("Scenes/playZone.tscn", true)

func _on_connect_to_server_pressed():
	connectButton.disabled = true
	
	Client.ConnectServer()
	
	var popup = popUp.instantiate()
	add_child(popup)
	popup.init("Connecting", false, 0.0)
	
	#Wait for .... time for connectionstatus.
	
	var tempstr : String= "Connecting"
	var animatorCount : int = 0
	
	
	for time in range(10):
		await get_tree().create_timer(1).timeout
		
		tempstr += "."
		animatorCount +=1
		
		if(animatorCount == 5):
			tempstr = "Connecting"
		
		popup.setmsg(tempstr)
		
		if(Client.m_server.get_state() == ENetPacketPeer.STATE_CONNECTED):
			break
	
	if(Client.m_server.get_state() == ENetPacketPeer.STATE_CONNECTED):
		Client.Activate()
		PacketDispatcher.Activate()
		remove_child(popup)
		SceneLoader.Load("Scenes/authentication.tscn", true)
	else:
		remove_child(popup)
		var popup2 = popUp.instantiate()
		add_child(popup2)
		popup2.init("Connection Failed!", true, 0.0)
		print("[ERROR] Can not establish connection!")
		Client.Reset()
		PacketDispatcher.Inactivate()
		
		connectButton.disabled = false
