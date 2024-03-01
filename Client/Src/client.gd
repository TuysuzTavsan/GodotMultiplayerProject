extends Node

var client : ENetMultiplayerPeer = ENetMultiplayerPeer.new()
const PORT : int = 9999
const ADRESS : String = "127.0.0.1"
const CHANNELS : int = 2
var peerID : int = -1


# Called when the node enters the scene tree for the first time.
func _ready():
	multiplayer.connected_to_server.connect(_connected_to_server)
	multiplayer.connection_failed.connect(_connection_failed)
	multiplayer.server_disconnected.connect(_server_disconnected)


func ConnectServer() -> void:
	var error : Error = client.create_client(ADRESS, PORT, CHANNELS)
	
	if(error != OK):
		match error:
			ERR_ALREADY_IN_USE:
				print("[ERROR] Trying to create client but it is already created. Close connection to recreate it.")
				return
			_:
				print("[ERROR] Creating client failed!")
				get_tree().quit(-1)
	
	multiplayer.multiplayer_peer = client
	print("[Success] Created client.")

func Reset() -> void:
	client.close()

func SendMsg(msg : String, type : Protocol.type) -> void:
	var str : String
	str += "{"
	str += str(client.get_unique_id())
	str += "}"
	str += "{"
	str += str(type)
	str += "}"
	str += "{"
	str += msg
	str += "}"
	
	client.put_packet(str.to_ascii_buffer())

func _connected_to_server() -> void:
	print("[Success] Connected to server.")

func _server_disconnected() -> void:
	print("[Error] Server disconnected.")

func _connection_failed() -> void:
	print("[ERROR] Connection failed.")
