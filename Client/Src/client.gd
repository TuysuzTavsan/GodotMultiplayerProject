extends Node

const PORT : int = 9999
const ADRESS : String = "127.0.0.1"
const CHANNELS : int = 2
const MAX_PLAYERS : int = 32

var client : ENetConnection = ENetConnection.new()
var serverPeer : ENetPacketPeer = null
var peerID : int = -1

signal connected(peer : ENetPacketPeer)
signal connection_error(peer : ENetPacketPeer)
signal disconnected(peer : ENetPacketPeer)
signal connectionResulted(type : ENetPacketPeer.PeerState)

var isResolutionNeeded : bool = true


func _ready():
	connected.connect(connected_to_server)
	disconnected.connect(server_disconnected)
	
	set_process(false)

func _process(_delta):
	Poll()

func Poll() -> void:
	var arr : Array = client.service()
	# Format: EventType - ENetPacketPeer - data - channel
	
	var eventType : ENetConnection.EventType = arr[0] 
	var peer : ENetPacketPeer = arr[1]
	var data = arr[2]
	var _channel : int = arr[3]
	
	
	match eventType:
		client.EVENT_CONNECT:
			connected.emit(peer)
			serverPeer = peer
		client.EVENT_DISCONNECT:
			disconnected.emit(peer)
		client.EVENT_ERROR:
			pass #TODO
		client.EVENT_NONE:
			pass #TODO
		client.EVENT_RECEIVE:
			print("Received data is:")
			print(data)


func ConnectServer() -> void:
	var error : Error = client.create_host(MAX_PLAYERS, CHANNELS)
	
	if(error != OK):
		print("[ERROR] Creating client failed!")
		get_tree().quit(-1)
	
	serverPeer = client.connect_to_host(ADRESS, PORT, CHANNELS)
	set_process(true)


func Reset() -> void:
	isResolutionNeeded = true
	set_process(false)
	if(serverPeer):
		serverPeer.peer_disconnect_now()
		serverPeer = null
	
	client.destroy()


func SendMsg(msg : String, type : Protocol.type) -> void:
	var m_str : String = ""
	m_str += "{"
	m_str += str(peerID)
	m_str += "}"
	m_str += "{"
	m_str += str(type)
	m_str += "}"
	m_str += "{"
	m_str += msg
	m_str += "}"
	
	serverPeer.send(0, m_str.to_ascii_buffer(), ENetPacketPeer.FLAG_RELIABLE)

func connected_to_server(_peer : ENetPacketPeer) -> void:
	print("[Success] Connected to server.")
	set_process(true)

func server_disconnected(_peer : ENetPacketPeer) -> void:
	print("[Error] Server disconnected.")
	set_process(false)

func connection_failed(_peer : ENetPacketPeer) -> void:
	print("[ERROR] Connection failed.")
