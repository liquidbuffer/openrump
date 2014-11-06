__all__ = ['World']

from _open_rump import Game, Ontology

###############################################################################
# Some monkey patching - you saw nothing
###############################################################################

###############################################################################
# easier method for getting systems from the game object
###############################################################################

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


class System(object):

    def __init__(self):
        self.camera_orbit = Ontology.SystemManager.get_camera_orbit
        self.default_physics_world = Ontology.SystemManager.get_default_physics_world
        self.input_interface = Ontology.SystemManager.get_input_interface
        self.loop_timer = Ontology.SystemManager.get_loop_timer
        self.ogre_dot_scene_loader = Ontology.SystemManager.get_ogre_dot_scene_loader
        self.ogre_renderer = Ontology.SystemManager.get_ogre_renderer
        self.third_person_controller = Ontology.SystemManager.get_third_person_controller

###############################################################################
# pull all systems into namespace of 'Game'
###############################################################################

