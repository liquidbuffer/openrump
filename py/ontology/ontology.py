# easier method for getting systems
ontology_system_map = {
    "CameraOrbit": get_camera_orbit,
    "DefaultPhysicsWorld": get_default_physics_world,
    "InputInterface": get_default_input_interface,
    "LoopTimer": get_loop_timer,
    "OgreDotSceneLoader": get_ogre_dot_scene_loader,
    "OgreRenderer": get_ogre_renderer,
    "ThirdPersonController": get_third_person_controller
}
def get_system_helper(self, systemName):
    return self.get_system_manager().ontology_system_map[systemName]()
# patch class
World.get_system = get_system_helper

class Test(object):
    def __init__(self):
        pass
    def test(self):
        print 'hello world'