''' 
NOTES:
	On assume qu'on peut avoir des elements sur le sable, terre et gason seulement a l'exeption de la terre qui peut etre sur une case d'eau (pont).
	On peut avoir qu'une maison et personnage par carte. 
	Il faut avoir au moins une roche par carte. 

	TOCHECK:
		source water, stairs etc
		sous-carte map 1 15x14
'''

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

def get_dict_by_GID(gid):
	''' Retourne le le nom correspondant au GID demande
	ATTENTION!: cette methode est specifique au nom du path utilise dans la carte'''
	tileSet = get_set_GID()
	tileDict = dict((i, data.get_tile_properties_by_gid(i)['source'][:-4]) for i in tileSet)
	tileDict[0] = 'vide'
	return tileDict[gid]

def get_dict_by_type(name):
	''' Retourne le le GID correspondant au nom demande
	ATTENTION!: cette methode est specifique au nom du path utilise dans la carte'''
	tileSet = get_set_GID()
	tileDict = dict((data.get_tile_properties_by_gid(i)['source'][:-4], i) for i in tileSet)
	tileDict['vide'] = 0
	return tileDict[name]

def validate_level0():
	''' Verifie que le level 0 ait seulement des tuiles valides (eau, terre, sable et gazon). Retourne False si invalide. '''
	tileSet = set()
	tileAllowed = [1, 2, 3, 4, 5, 6, 7]
	for tile in data.get_tile_properties_by_layer(0):
		tileSet.add(tile[0])
	if tileSet.difference(tileAllowed) != set():
		return False 
	else:
		return True

def is_tile_type(tile, tileType):
	''' Retourne True si le type de la tuile est celui demande. ''' 
	tileGID = data.get_tile_gid(tile[0], tile[1], tile[2])
	tileName = get_dict_by_GID(tileGID)
	if tileName == tileType:
		return True
	else:
		return False

def is_valide_tile(tile):
	''' Retourne False si la tuile n'est pas valide 
	La tuile est valide seulement si elle est sur la terre, sur du sable ou sur du gazon a l'exeption de la terre qui peu etre sur l'eau. '''
	temp = list(tile)
	temp[2] -= 1
	underTile = tuple(temp)
	temp[2] += 1

	if not is_tile_type(underTile, 'grass') and not is_tile_type(underTile, 'sand') and not is_tile_type(underTile, 'earth'):
		if is_tile_type(tile, 'earth') and is_tile_type(underTile, 'water'):
			return True
		else:
			return False
	return True

def validate_levels():
	''' Recupere chaque tuple de tuile qui n'est pas au level 0. Pour chaque tuile recuperees, appelle la function is_valide_tile(). 
	Retourne False si un truile est trouvee invalide.'''
	locationList = []
	tileSet = get_set_GID()
	for gid in tileSet:
		locationList.extend(list(data.get_tile_locations_by_gid(gid)))
	locationList = filter(lambda x: x[2] != 0, locationList) #enleve les tuples du level 0
	while locationList != []:
		tile = locationList.pop()
		if not is_valide_tile(tile):
			print " Position error: %s " %(str(tile))
			return False
	return True


def is_map_complete():
	''' Verifie qu'il y a seulement une maison et un seul personnage sur la carte et au moins une roche.'''
	elemList = []
	elemList.extend(list(data.get_tile_locations_by_gid(get_dict_by_type('house'))))
	if len(elemList) != 1:
		return False
	elemList.pop()
	elemList.extend(list(data.get_tile_locations_by_gid(get_dict_by_type('character'))))
	if len(elemList) != 1:
		return False
	elemList.pop()
	elemList.extend(list(data.get_tile_locations_by_gid(get_dict_by_type('rock'))))
	if len(elemList) < 1:
		return False
	return True

def continuous_levels():
	''' Verifie qu'il y ait 4 niveaux consecutifs. '''
	layerList = list(data.visible_tile_layers)
	if len(layerList) != 4:
		return False
	for i in range(len(layerList) -2):
		if i+1-i != 1:
			return False
	return True

def transitive_tiles():
	locationList = []
	tileSet = get_set_GID()
	for gid in tileSet:
		locationList.extend(list(data.get_tile_locations_by_gid(gid)))
	width = max(locationList, key=lambda item: item[0])[0] +1
	height = max(locationList, key=lambda item: item[1])[1] +1
	'''print width, height
	print width // 14 != width % 14 +1
	print width // 14
	print width % 14
	if (width // 14 != width % 14 +1):
		return False
	elif (height // 14 != height % 14 +1):
		return False
	else:
		print width, height 
		return True '''
	#locationList = filter(lambda x: x[0] == 15 or x[1] == 14, locationList)
	#print (locationList)
	return True


#--------------------------------#
transitive_tiles()

if not continuous_levels():
	print 'Invalid Map! It is required to have 4 continuous levels.'
elif not validate_level0():
	print 'Invalid Map! Level 0 contains invalid tiles.'
elif not validate_levels():
	print 'Invalid Map! Position Error.'
elif not is_map_complete():
	print 'Invalid Map! Missing a required element.'
else:
	print 'Valid Map'
