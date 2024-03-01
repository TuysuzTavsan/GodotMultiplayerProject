extends Control

func _ready():
	Client.Reset()

func _on_quit_button_pressed():
	get_tree().quit(0)

func _on_playground_button_pressed():
	SceneLoader.Load("Scenes/playZone.tscn", true)

func _on_connect_to_server_pressed():
	SceneLoader.Load("Scenes/authentication.tscn", true)
