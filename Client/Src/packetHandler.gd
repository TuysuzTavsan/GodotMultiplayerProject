extends Node

var subscribers : Dictionary = {}

func Subscribe(protocol : Prot.Top, subscriber : Node) ->void:
	subscribers[int(protocol)] = subscriber

func UnSubscribe(protocol : Prot.Top, subscriber : Node) -> void:
	subscribers.erase(int(protocol))

func ForwardPacket(packet : PacketIn) -> bool:
	
	var subscriber = subscribers.get(packet.m_topProt)
	
	if(subscriber != null):
		subscribers[packet.m_topProt].Handle(packet)
		return true
	else:
		print("[INFO] Unhandled packet received")
		return false
