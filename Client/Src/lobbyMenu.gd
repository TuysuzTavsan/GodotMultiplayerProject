extends Control

const mainMenu : String = "res://Scenes/mainMenu.tscn"

func _on_return_pressed():
	SceneLoader.Load(mainMenu, true)
