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

def get_dict_GID():
	tileSet = get_set_GID()
	tileDict = dict((data.get_tile_properties_by_gid(i)['source'][:-4], i) for i in tileSet)
	return tileDict

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

def validate_level1():
	tileSet = set()
	tileList = []
	for tile in data.get_tile_properties_by_layer(1):
		print(tile)
		tileList.append(tile[0])
	#print(tileList)

def validate_tile(tile):
	''' Retourne False si la tuile n'est pas valide '''
	# on verifie si la tuile est sur l'eau ou sur une case vide 
	unterTile = list(tile)
	print underTile[2]
	return False
	underTile[2] = underTile[2] -1
	underTile = tuple(underTile)
	# si la tuile est un arbre, roche, maison, bonhomme, escaliers,  on verifie qu'il n'y ait rien en haut 
	return True

def big_fat_function():
	positionList = []
	tileSet = get_set_GID()
	for gid in tileSet:
		positionList.extend(list(data.get_tile_locations_by_gid(gid)))
	positionList = filter(lambda x: x[2] != 0, positionList) #enleve les tuples du level 0
	while positionList != []:
		tile = positionList.pop()
		if not validate_tile(tile):
			print "Invalid Map! Position error: %s " %(str(tile))
			return False
	print('Valid Map')
	return True

			 


#--------------------------------#
print_GID()
setGID = get_set_GID()
print('----')
#print(get_dict_GID())
print('00000000')
big_fat_function()