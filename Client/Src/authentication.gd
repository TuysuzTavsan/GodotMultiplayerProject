extends Control

@onready var textEdit = $MarginContainer/VBoxContainer/TextEdit
const popUp = preload("res://Scenes/popUp.tscn")

func _ready():
	var popup = popUp.instantiate()
	add_child(popup)
	popup.init("Connected", true, 0.0)

func _on_quit_button_pressed():
	get_tree().quit(0)


func _on_return_button_pressed():
	SceneLoader.Load("Scenes/mainMenu.tscn", true)


func _on_connectbutton_pressed():
	Client.SendMsg(textEdit.text, Protocol.type.Username)


func _on_text_edit_text_submitted(text):
	Client.SendMsg(text, Protocol.type.Username)
