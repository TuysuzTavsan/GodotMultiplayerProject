extends Node

var isLoading : bool = false
var loadingArr : Array
var isSingle : bool = false

var singleSceneFlag : bool = false

signal SingleSceneLoaded

func _ready():
	set_process(false)


func _process(_delta):
	if(!isLoading):
		return
	
	if(singleSceneFlag):
		singleSceneFlag = false
		SingleSceneLoaded.emit()
	
	var deleteArr : Array = []
	
	for res : String in loadingArr:
		var progress : Array = []
		var status = ResourceLoader.load_threaded_get_status(res, progress)
		
		match status:
			ResourceLoader.THREAD_LOAD_FAILED:
				printerr("[Error] sceneLoader load failed. Cant load scene at path %s" %res)
				deleteArr.push_back(res)
			ResourceLoader.THREAD_LOAD_INVALID_RESOURCE:
				printerr("[Error] sceneLoader error invalid resource. Cant load scene at path %s" %res)
				deleteArr.push_back(res)
			ResourceLoader.THREAD_LOAD_IN_PROGRESS:
				if(isSingle):
					pass #TODO: We need to show status.
				print("[SceneLoader] Loading scene at path %s. [Progress %f]" %[res, progress[0]])
			ResourceLoader.THREAD_LOAD_LOADED:
				print("[SceneLoader] Loading scene at path %s done. [Progress %d]" %[res, progress[0]])
				var scene = ResourceLoader.load_threaded_get(res)
				if(isSingle):
					singleSceneFlag = true
					get_tree().change_scene_to_packed(scene)
				else:
					get_parent().add_child(scene)
				
				deleteArr.push_back(res)
	
	#Clean up
	for element in deleteArr:
		loadingArr.erase(element)
	
	if(loadingArr.size() == 0 and singleSceneFlag != true):
		set_process(false)


# Load scene from string.
func Load(scenePath : String, singleScene : bool = false) ->void:
	var err : Error = ResourceLoader.load_threaded_request(scenePath)
	if(err != OK):
		printerr("[Error] sceneLoader cant start loading. error code# %s" %err)
	
	isLoading = true #Loading request successfull.
	isSingle = singleScene #Loading request specifies progress should be shown.
	set_process(true)
	loadingArr.push_back(scenePath)


func IsLoading() -> bool:
	return isLoading
