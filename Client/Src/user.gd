extends Node

var m_userName : String = ""
const m_handleID : Prot.Top = Prot.Top.User

func _ready():
	PacketHandler.Subscribe(m_handleID, self)


func Handle(packet : PacketIn) -> void:
	
	match packet.m_subProt:
		Prot.User.UserNameSubmit:
			m_userName = packet.m_data
			print("USERNAME RECEİVED!")


func _exit_tree():
	pass
