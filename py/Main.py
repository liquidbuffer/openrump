import sys
import open_rump


if __name__ == '__main__':
    game = open_rump.Game()
    game.load_player('applejack_mane_neck', 'Cube.003.mesh')  # Mane neck
    game.load_player('applejack_tail', 'Cube.004.mesh')  # Tail
    game.load_player('applejack_mane_head_1', 'Cube.005.mesh')  # Mane head (1)
    game.load_player('applejack_mane_head_2', 'Cube.024.mesh')  # Mane head (2)
    game.load_player('applejack_mane_head_3', 'Cube.025.mesh')  # Mane head (3)
    game.load_player('applejack_body', 'Cube.mesh')  # body
    game.load_player('applejack_hat', 'Cylinder.001.mesh')  # hat
    game.load_player('applejack_eyelid_right', 'Eyelid.R.003.mesh')  # eyelid right
    # Eyelid.R.008.mesh is a duplicate of Eyelid.R.003.mesh?
    # Plane.mesh is ground
    game.load_player('applejack', 'Sphere.001.mesh')
    game.load_player('1', 'Sphere.005.mesh')
    game.load_player('2', 'Sphere.006.mesh')
    game.load_player('3', 'Sphere.007.mesh')
    game.attach_camera_to_entity('applejack_body', 'MainCamera')
    game.run()
    sys.exit(0)
