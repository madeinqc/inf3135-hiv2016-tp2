import pytmx
tmxdata = pytmx.TiledMap("assets/map1.tmx")

print('tmxdata.properties')
print(tmxdata.properties)

print('tmxdata.visible_layers')
for layer in tmxdata.visible_layers:
	print(layer)

print('tmxdata.visible_layers properties')
for layer in tmxdata.visible_layers:
	print(layer.properties)

print('la')
print('tmxdata.visible_tile_layers')
for tile in tmxdata.visible_tile_layers:
	print(tile)

nbLayers = sum(1 for _ in tmxdata.visible_tile_layers)
print(nbLayers)

aTile = tmxdata.get_tile_properties(0,0,0)
print(aTile["source"])

otherTile = tmxdata.get_tile_properties_by_gid(8)
print(otherTile["source"])

print('ici')
for tile in tmxdata.get_tile_properties_by_layer(1):
	print(tile)

layerTest = tmxdata.get_layer_by_name('Level0')
print(layerTest)

# -------------------------------------- #
def printGID():
	tileSet = set()

	for noLayer in tmxdata.visible_tile_layers:
		for tile in tmxdata.get_tile_properties_by_layer(noLayer):
			tileSet.add(tile[0])
	tileSet = sorted(tileSet)

	o = [(i,tmxdata.get_tile_properties_by_gid(i)) for i in tileSet]

	for item in o:
		print(item)

printGID()
