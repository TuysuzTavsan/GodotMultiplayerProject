class_name Packet extends RefCounted

var m_channel : int = -1
var m_data : PackedByteArray = []
var m_flags : int = -1

# var pct : Packet = Packet.new(channel, data, flag)

func SetData(data : String, topProtocol : Prot.Top, subProtocol : int) -> void:
	var m_str : String = ""
	m_str += "{"
	m_str += str(topProtocol)
	m_str += "}"
	
	m_str += "{"
	m_str += str(subProtocol)
	m_str += "}"
	
	m_str += "{"
	m_str += data
	m_str += "}"
	
	m_data = m_str.to_ascii_buffer()

func _init(channel : int, flags : int):
	m_channel = channel
	m_flags = flags



