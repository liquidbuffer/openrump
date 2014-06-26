import sys
import open_rump


def load_player_parts():
    # game.load_player('applejack_mane_neck', 'Cube.003.mesh')  # Mane neck
    # game.load_player('applejack_tail', 'Cube.004.mesh')  # Tail
    # game.load_player('applejack_mane_head_1', 'Cube.005.mesh')  # Mane head (1)
    # game.load_player('applejack_mane_head_2', 'Cube.024.mesh')  # Mane head (2)
    # game.load_player('applejack_mane_head_3', 'Cube.025.mesh')  # Mane head (3)
    game.load_player('applejack_body', 'Cube.mesh')  # body
    # game.load_player('applejack_hat', 'Cylinder.001.mesh')  # hat
    # game.load_player('applejack_eyelid_right', 'Eyelid.R.003.mesh')  # eyelid right
    # game.load_player('applejack_eyelid_left', 'Eyelid.R.008.mesh')
    # Plane.mesh is ground
    # game.load_player('applejack', 'Sphere.001.mesh')
    # game.load_player('1', 'Sphere.005.mesh')
    # game.load_player('2', 'Sphere.006.mesh')
    # game.load_player('3', 'Sphere.007.mesh')


class Test(object):

    def __init__(self, game_obj):
        self.game_obj = game_obj
        self.game_obj.add_game_update_callback(self.__game_update)
        self.__count = 0

    def __game_update(self, time_step):
        self.__count += 1
        if self.__count == 60:
            self.__count = 0
            print time_step
            self.game_obj.remove_game_update_callback(self.__game_update)
        return True


if __name__ == '__main__':
    game = open_rump.Game()
    load_player_parts()
    game.attach_camera_to_entity('applejack_body', 'MainCamera')
    test = Test(game)
    game.run()
    sys.exit(0)
