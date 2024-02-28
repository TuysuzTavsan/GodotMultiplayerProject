extends CharacterBody3D

@onready var camera  : Camera3D= $cameraPivot/Camera3D
@onready var cameraPivot : Node3D = $cameraPivot
const WALK_SPEED = 4.0
const SPRINT_SPEED = 8.0
const JUMP_VELOCITY = 4.5
const GRAVITY = 9.8
const BOBFREQ = 2.0
const BOBAMP = 0.08
const BASE_FOV = 75.0
const FOV_CHANGE = 1.5
const PUSH_FORCE = 80.0

var bob = 0
var rotX : float = 0.0
var rotY : float = 0.0



func _ready():
	Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)

func _unhandled_input(event):
	if event is InputEventMouseMotion:
		rotX -= event.relative.x * 0.001
		rotY -= event.relative.y * 0.001
		rotY = clamp(rotY, deg_to_rad(-75), deg_to_rad(80))
		basis = Basis() #Reset rotation of characterbody.
		cameraPivot.basis = Basis() #Reset rotation of camera
		rotate_object_local(Vector3(0, 1, 0), rotX) # first rotate in Y
		cameraPivot.rotate_object_local(Vector3(1, 0, 0), rotY) # first rotate in X
	
	
	if event is InputEventKey:
		if event.pressed and event.keycode == KEY_ESCAPE:
			get_tree().quit(0);
		


func _physics_process(delta):
	# Add the gravity.
	if not is_on_floor():
		velocity.y -= GRAVITY * delta

	# Handle jump.
	if Input.is_action_just_pressed("move_jump") and is_on_floor():
		velocity.y = JUMP_VELOCITY
	
	
	var input_dir = Input.get_vector("move_left", "move_right", "move_forward", "move_backward")
	var direction = (transform.basis * Vector3(input_dir.x, 0, input_dir.y)).normalized()
	var speed : float = WALK_SPEED
	
	if Input.is_action_pressed("sprint"):
		speed = SPRINT_SPEED
	
	if is_on_floor():
		if direction:
			velocity.x = direction.x * speed
			velocity.z = direction.z * speed
		else:
			velocity.x = lerp(velocity.x, direction.x * speed, delta * 7.0)
			velocity.z = lerp(velocity.z, direction.z * speed, delta * 7.0)
	else:
		velocity.x = lerp(velocity.x, direction.x * speed, delta * 3.0)
		velocity.z = lerp(velocity.z, direction.z * speed, delta * 3.0)
	
	bob += delta * velocity.length() * float(is_on_floor())
	cameraPivot.transform.origin = headbob(bob)
	
	var velocityClamped = clamp(velocity.length(), 0.5, speed * 2)
	var targetFov = BASE_FOV + FOV_CHANGE * velocityClamped
	camera.fov = lerp(camera.fov, targetFov, delta * 8)
	
	move_and_slide()
	
	for i in get_slide_collision_count():
		var c : KinematicCollision3D = get_slide_collision(i)
		if c.get_collider() is RigidBody3D:
			c.get_collider().apply_central_impulse(-c.get_normal() * PUSH_FORCE)


func headbob(time) -> Vector3:
	var pos = Vector3.ZERO
	pos.y = sin(time * BOBFREQ) * BOBAMP
	pos.x = cos(time * BOBFREQ / 2) * BOBAMP
	return pos
