extends Control

@onready var label = $MarginContainer/VBoxContainer/Label
@onready var button = $MarginContainer/VBoxContainer/Button
var timerSecond : float = 0

func init(msg : String, isClickable : bool, seconds : float) -> void:
	if(isClickable):
		button.show()
	else:
		button.hide()
	
	label.text = msg
	
	timerSecond = seconds
	
	set_process(seconds)


func setmsg(msg : String):
	label.text = msg

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	
	await get_tree().create_timer(timerSecond).timeout
	queue_free()


func _on_button_pressed():
	queue_free()
