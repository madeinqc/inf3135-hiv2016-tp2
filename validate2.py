from pytmx import *
tmxdata = pytmx.TiledMap("assets/map1.tmx")

#print(tmxdata.get_tile_image_by_gid(10))

for x in tmxdata.get_tileset_from_gid(10):
	print(x)
