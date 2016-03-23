import pytmx
data = pytmx.TiledMap("assets/map1.tmx")

def print_GID():
	''' Imprime les tuiles diponibles dans la carte avec le GID et proprietes '''
	tileSet = set()

	for noLayer in data.visible_tile_layers:
		for tile in data.get_tile_properties_by_layer(noLayer):
			tileSet.add(tile[0])
	tileSet = sorted(tileSet)

	o = [(i,data.get_tile_properties_by_gid(i)) for i in tileSet]

	for item in o:
		print(item)

def get_set_GID():
	''' Retourne un set de tous les GIDs diponibles dans la carte '''
	tileSet = set()

	for noLayer in data.visible_tile_layers:
		for tile in data.get_tile_properties_by_layer(noLayer):
			tileSet.add(tile[0])
	tileSet = sorted(tileSet)
	return tileSet

def validate_level0():
	''' Verifie que le level 0 ait seulement des tuiles valides. Retourne False si invalide. '''
	tileSet = set()
	tileAllowed = [1, 2, 3, 4, 5, 6, 7]
	for tile in data.get_tile_properties_by_layer(0):
		tileSet.add(tile[0])
	if tileSet.difference(tileAllowed) != set():
		# print('Invalid Map')
		return False 
	else:
		# print('Valid Map')
		return True 

#--------------------------------#
print_GID()
setGID = get_set_GID()
validate_level0()