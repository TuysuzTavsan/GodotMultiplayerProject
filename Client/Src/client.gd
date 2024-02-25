extends Node

var client : ENetMultiplayerPeer = ENetMultiplayerPeer.new()
const PORT : int = 9999
const ADRESS : String = "127.0.0.1"
const CHANNELS : int = 2


# Called when the node enters the scene tree for the first time.
func _ready():
	var error : Error = client.create_client(ADRESS, PORT, CHANNELS)
	if(error != Error.OK):
		printerr("[ERROR] Creating client failed!")
		get_tree().quit(-1)
		
	multiplayer.multiplayer_peer = client
	print("Succesfully created client.")


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
