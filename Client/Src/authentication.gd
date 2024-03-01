extends Control

@onready var textEdit = $MarginContainer/VBoxContainer/TextEdit


func _on_quit_button_pressed():
	get_tree().quit(0)


func _on_return_button_pressed():
	SceneLoader.Load("Scenes/mainMenu.tscn", true)


func _on_connectbutton_pressed():
	Client.ConnectServer()
	Client.SendMsg(textEdit.text, Protocol.type.Username)


func _on_text_edit_text_submitted(new_text):
	Client.ConnectServer()
	Client.SendMsg(textEdit.text, Protocol.type.Username)
