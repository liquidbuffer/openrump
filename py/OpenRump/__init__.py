__all__ = ['World']

from _open_rump import Game, Ontology

###############################################################################
# Some monkey patching - you saw nothing
###############################################################################

# easier method for getting systems
ontology_system_map = {
    "CameraOrbit": Ontology.SystemManager.get_camera_orbit,
    "DefaultPhysicsWorld": Ontology.SystemManager.get_default_physics_world,
    "InputInterface": Ontology.SystemManager.get_input_interface,
    "LoopTimer": Ontology.SystemManager.get_loop_timer,
    "OgreDotSceneLoader": Ontology.SystemManager.get_ogre_dot_scene_loader,
    "OgreRenderer": Ontology.SystemManager.get_ogre_renderer,
    "ThirdPersonController": Ontology.SystemManager.get_third_person_controller
}
def get_system_helper(self, systemName):
    return ontology_system_map[systemName](self.get_system_manager())

# patch class
Ontology.World.get_system = get_system_helper