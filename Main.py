import sys
import open_rump


if __name__ == '__main__':
	game = open_rump.Game()
	player = game.load_player('applejack', 'Body.mesh')
	game.attach_camera_to_entity('applejack', 'MainCamera')
	game.run()
	sys.exit(0)
