extends Node

var m_thread : Thread = Thread.new()
var m_mutex : Mutex = Mutex.new()
var m_packetIn : Array = []
var m_packetOut : Array = []
var m_semaphore : Semaphore = Semaphore.new()
var m_shouldRun : bool = false


###
# PacketDispatcher is the responsible singleton from sending packets in its own thread.
###

func Activate() -> void:
	m_mutex.lock()
	m_shouldRun = true
	m_mutex.unlock()
	
	if(!m_thread.is_alive()):
		m_thread.start(Dispatch,Thread.PRIORITY_HIGH)

func Inactivate() -> void:
	m_mutex.lock()
	m_shouldRun = false
	m_mutex.unlock()
	m_semaphore.post()

func _exit_tree():
	if(m_thread.is_alive()):
		Inactivate()
		m_semaphore.post()
		m_thread.wait_to_finish()

func PutPacket(pct : Packet) -> void:
	m_mutex.lock()
	
	m_packetIn.push_back(pct)
	m_semaphore.post()
	
	
	m_mutex.unlock()
	pass


func Dispatch() -> void:
	while(m_shouldRun):
		m_semaphore.wait()
		
		m_mutex.lock()
		
		# Swap
		for pct in m_packetIn:
			m_packetOut.push_back(pct)
		
		# Reset
		m_packetIn.clear()
		
		m_mutex.unlock()
		
		# Send packets
		for pct : Packet in m_packetOut:
			Client.m_server.send(pct.m_channel, pct.m_data, pct.m_flags)
		
		m_packetOut.clear()

