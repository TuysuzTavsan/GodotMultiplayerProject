extends Node

const popUp = preload("res://Scenes/popUp.tscn")

const PORT : int = 9999
const ADRESS : String = "127.0.0.1"
const CHANNELS : int = 2
const MAX_PLAYERS : int = 32

var m_client : ENetConnection = ENetConnection.new()
var m_server : ENetPacketPeer = null
var m_peerID : int = -1
var m_isValid : bool = false

signal connected(peer : ENetPacketPeer)
signal connection_error(peer : ENetPacketPeer)
signal disconnected(peer : ENetPacketPeer)
signal connectionResulted(type : ENetPacketPeer.PeerState)

signal unhandledPacketReceived(packet : PacketIn)


func _ready():
	connected.connect(connected_to_server)
	disconnected.connect(server_disconnected)

func _process(_delta):
	if(m_isValid):
		Poll()

func Activate() -> void:
	m_isValid = true

func Inactivate() -> void:
	m_isValid = false

func Poll() -> void:
	var arr : Array = m_client.service()
	# Format: EventType - ENetPacketPeer - data - channel
	
	var eventType : ENetConnection.EventType = arr[0] 
	var peer : ENetPacketPeer = arr[1]
	#var data  : String = arr[2].get_string_from_ascii()
	var _channel : int = arr[3]
	
	
	match eventType:
		m_client.EVENT_CONNECT:
			connected.emit(peer)
			m_server = peer
		m_client.EVENT_DISCONNECT:
			disconnected.emit(peer)
		m_client.EVENT_ERROR:
			pass #TODO
		m_client.EVENT_NONE:
			pass #TODO
		m_client.EVENT_RECEIVE:
			var packet : PacketIn = PacketIn.new(peer.get_packet(), _channel)
			print("Received Packet is:")
			print(packet.m_data)
			if(!PacketHandler.ForwardPacket(packet)):
				unhandledPacketReceived.emit(packet)


func ConnectServer() -> void:
	var error : Error = m_client.create_host(MAX_PLAYERS, CHANNELS)
	
	if(error != OK):
		print("[ERROR] Creating client failed!")
		get_tree().quit(-1)
	
	m_server = m_client.connect_to_host(ADRESS, PORT, CHANNELS)
	Activate()


#TODO Check for NULL values.
func Reset() -> void:
	if(!m_isValid):
		return
	
	
	if(m_server):
		m_server.peer_disconnect_now()
		m_server = null
	
	PacketDispatcher.Inactivate()
	
	m_peerID = -1
	m_client.destroy()
	Inactivate()

func connected_to_server(_peer : ENetPacketPeer) -> void:
	print("[Success] Connected to server.")

func server_disconnected(_peer : ENetPacketPeer) -> void:
	print("[Error] Server disconnected.")
	
	Reset()
	
	SceneLoader.Load("Scenes/mainMenu.tscn", true)
	
	await SceneLoader.SingleSceneLoaded
	
	var popup = popUp.instantiate()
	get_tree().root.add_child(popup)
	popup.init("Connection Lost", true, 0)

func connection_failed(_peer : ENetPacketPeer) -> void:
	print("[ERROR] Connection failed.")
