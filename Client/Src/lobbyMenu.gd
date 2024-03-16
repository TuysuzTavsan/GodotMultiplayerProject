extends Control

const mainMenu : String = "res://Scenes/mainMenu.tscn"
@onready var lobbyHBox = $MarginContainer/HBoxContainer/VBoxContainer/DefaultLobbyHBox
@onready var userName = $MarginContainer/HBoxContainer/VBoxContainer2/VBoxContainer2/UserName

func _ready():
	userName.text = User.m_userName

func _on_return_pressed():
	SceneLoader.Load(mainMenu, true)

func _on_refresh_pressed():
	# Send message to server.
	pass # Replace with function body.


func _on_create_lobby_pressed():
	# Send message to server.
	pass # Replace with function body.
