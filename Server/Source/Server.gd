extends Node

const MAXPLAYERS : int = 16
const SERVERPORT : int = 9999

var multiplayerPeer : ENetMultiplayerPeer = ENetMultiplayerPeer.new()

# Called when the node enters the scene tree for the first time.
func _ready():
	var error : Error = multiplayerPeer.create_server(SERVERPORT, MAXPLAYERS)
	if(error != Error.OK):
		print("Failed to Create server on port %d with maxPlayerCount %d. [ErrorCode]%d" \
		% [SERVERPORT, MAXPLAYERS, error])
		get_tree().quit(-1)
	
	print("Succesfully created Server on port %d with maxPlayerCount %d." \
	% [SERVERPORT, MAXPLAYERS])
	
	


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
