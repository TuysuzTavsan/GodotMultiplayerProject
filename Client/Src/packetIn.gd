class_name PacketIn extends RefCounted

var m_channel : int = -1
var m_data : String = ""
var m_topProt : Prot.Top = Prot.Top.Unspecified
var m_subProt : int = 0

# var pct : Packet = Packet.new(channel, data, flag)

func _init(info : PackedByteArray, channel : int):
	var data  : String = info.get_string_from_ascii()
	
	m_topProt = data.substr(1,1).to_int()
	m_subProt = data.substr(4,1).to_int()
	m_data = data.substr(7, data.length() - 8)
	
	m_channel = channel
