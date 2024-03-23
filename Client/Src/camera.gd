extends Node3D

@onready var camera = $Camera3D
@onready var fov : float  = camera.fov
var rot : float = 0
var mov : Vector3 = Vector3(0,0,0)


const movMultiplier = 20
const rotMultiplier = 1
const fovMultiplier = 2
const minFOV = 60
const maxFOV = 90

func _process(delta):
	
	#Rotate
	rot += Input.get_axis("rotate_left", "rotate_right") * delta
	var current_rot = Quaternion(transform.basis)
	var target_rot = Quaternion(Vector3.UP, rot * rotMultiplier)
	var smoothrot = current_rot.slerp(target_rot, 0.05)
	transform.basis = Basis(smoothrot)
	
	#Move
	var mov2d = (Input.get_vector("move_right", "move_left", "move_backward", "move_forward") * delta)
	var mov3d = Vector3(mov2d.x, 0 , mov2d.y)
	mov += mov3d.rotated(Vector3.UP, rot * rotMultiplier)
	transform.origin = transform.origin.lerp(mov * movMultiplier, 0.05)
	
	camera.fov = lerpf(camera.fov, fov, 0.05)


func _input(event):
	if event.is_action_pressed("roll_in"):
		fov -= 1 * fovMultiplier
	
	if event.is_action_pressed("roll_out"):
		fov += 1 * fovMultiplier
	
	fov = clampf(fov, minFOV, maxFOV)

